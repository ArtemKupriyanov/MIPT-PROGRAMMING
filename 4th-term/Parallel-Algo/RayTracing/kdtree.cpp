#include "kdtree.hpp"
#include <algorithm>
#include <cassert>

using std::max;
using std::pair;
using std::vector;
using std::shared_ptr;

struct cmpWithDim {
    int dim;
    cmpWithDim(int _dim) { dim = _dim; }
    bool operator() (shared_ptr<Figure> f1,shared_ptr<Figure> f2) {
        return f1->getRightBound(dim) < f2->getRightBound(dim);
    }
};

Kdtree::~Kdtree() {
    if(leftTree) {
        delete leftTree;
    }
    
    if(rightTree) {
        delete rightTree;
    }
}

int vert = 0;

Kdtree::Kdtree(vector<shared_ptr<Figure> >& _data, Point& _leftBound, Point& _rightBound , int dim_out, int depth, int notDiv): data(_data), leftBound(_leftBound), rightBound(_rightBound) {
    ++vert;

    dim = (dim_out + 1)%3;
    
    size_t size = data.size();
    
    cutIndex = -1;
    
    if(depth++ > MAX_DEPTH || size <= 1) {
        leftTree = nullptr;
        rightTree = nullptr;
        return;
    }
    
    cmpWithDim cmp(dim);
    sort(data.begin(),data.end(),cmp);
   
    
/*  maybe somewhen SAH heuristic will added for more balanced contol kdtree's depth
 **/
//    ld defaultSAH = EMPTY_COST + getSurface(leftBound,rightBound) * size;
//    
//    int indexMinSAH = -1;
//    ld minSAH = 0;
//    ld coordsMidForLeft[3] = {rightBound[0], rightBound[1], rightBound[2]};
//    ld coordsMidForRight[3] = {leftBound[0], leftBound[1], leftBound[2]};
////    ld halfDimLen = (rightBound[dim] - leftBound[dim])/2;
//
//    for(int i = 0;i < size; ++i) {
//        coordsMidForRight[dim]  = coordsMidForLeft[dim] = data[i]->getRightBound(dim);
//        Point boundForLeft(coordsMidForLeft), boundForRight(coordsMidForRight);
//        ld SAH = EMPTY_COST + getSurface(leftBound, boundForLeft) * i + getSurface(boundForRight, rightBound) * (size - i) * 1.5;
//        if(SAH < minSAH || indexMinSAH == -1) {
//            indexMinSAH = i;
//            minSAH = SAH;
//        }
//    }
//    
//    if(minSAH > defaultSAH - EPS) {
//        leftTree = nullptr;
//        rightTree = nullptr;
//    }
    
    
    vector <shared_ptr<Figure> > dataLeft;
    vector <shared_ptr<Figure> > dataRight;
    
    median = (data[size/2]->getRightBound(dim) + data[size/2]->getRightBound(dim))/2;
    
    for(int i = 0; i < size;++i) {
        if(data[i]->getLeftBound(dim) <= median) {
            dataLeft.push_back(data[i]);
        }
        
        if(data[i]->getRightBound(dim) > median) {
            dataRight.push_back(data[i]);
        }
    }
    
    Point offset;
    offset.d[dim] = median - leftBound[dim];
    Point boundForRight = leftBound + offset;
    offset.d[dim] = rightBound[dim] - median;
    Point boundForLeft = rightBound - offset;
    
    if(dataLeft.size() == data.size() || dataRight.size() == data.size()) {
        ++notDiv;
    } else {
        notDiv = 0;
    }
    
    if(notDiv == 3) {
        leftTree = rightTree = nullptr;
        return;
    }
    
    cutIndex = size/2;
    
    leftTree = new Kdtree(dataLeft,leftBound,boundForLeft,dim,depth,notDiv);
    rightTree = new Kdtree(dataRight,boundForRight,rightBound,dim,depth,notDiv);
    
    if(depth == 2) {
        cout << "kd: " << vert << endl;
    }
}

pair<ld,ld> Kdtree::getIntersectionRatioWithBoundingBox(Point& ray, Point& start) {
    Point diag = rightBound - leftBound;
    Point base[3];
    Point orig[3];
    for(int i = 0;i < 3;++i) {
        orig[i].d[i] = diag[i];
        base[i].d[i] = 1;
    }

    ld intersections[3][2];
    pair <ld,ld> intersectRatio = std::make_pair(-1,-1);
    
    for(int i = 0;i < 3; ++i) {
        for(int j = 0;j < 2; ++j) {
            Point intersectPoint;
            Point v0 = leftBound + orig[i] * j;
            
            intersections[i][j] = getIntersectionFlatRatio(ray,start,base[i],v0, base[(dim+1)%3], base[(dim+2)%3]);
            
            if(intersections[i][j] < 0) {
                continue;
            }
            
            intersectPoint = start + ray * intersections[i][j];
            
            if(!pointInside(intersectPoint)) {
                continue;
            }
            
            if(intersectRatio.first < 0) {
                intersectRatio.first = intersections[i][j];
            } else {
                intersectRatio.second = intersections[i][j];
            }
        }
    }
    
    packingRatio(intersectRatio);
    
    return intersectRatio;
}

ld Kdtree::getIntersectionRatioWithMedianFlat(Point& ray, Point& start) {
    Point diag = rightBound - leftBound;
    Point base[3];
    Point orig[3];
    for(int i = 0;i < 3;++i) {
        orig[i].d[i] = diag[i];
        base[i].d[i] = 1;
    }
    
    Point v0 = leftBound + orig[dim] * ((median - leftBound[dim])/(diag[dim]));
    Point intersectPoint;
    
    ld ratio = getIntersectionFlatRatio(ray, start, base[dim], v0, base[(dim+1)%3], base[(dim+2)%3]);
    
    if(ratio < 0) {
        return -1;
    }
    
    intersectPoint = start + ray * ratio;
    
    if(!pointInside(intersectPoint)) {
        return -1;
    }
    
    return ratio;
}

bool Kdtree::pointInside(Point& point) {
    return (   point.x > leftBound.x - EPS
            && point.x < rightBound.x + EPS
            && point.y > leftBound.y - EPS
            && point.y < rightBound.y + EPS
            && point.z > leftBound.z - EPS
            && point.z < rightBound.z + EPS);
}

IntersectionData Kdtree::find(Point& ray, Point& start) {
    IntersectionData bestIntersection;
    ld bestDist2 = INFINITY;
    status(bestIntersection) = NOT_INTERSECT;
    
    pair<ld,ld> intersectRatioWithBoundingBox = getIntersectionRatioWithBoundingBox(ray, start);

    find(ray,start,bestDist2,bestIntersection, intersectRatioWithBoundingBox);
    return bestIntersection;
}

void Kdtree::find(Point& ray, Point& start, ld& bestDist2, IntersectionData& bestIntersection, pair <ld,ld> intersectionRatio) {

    if(intersectionRatio.first < 0) {
//        assert(intersectionRatio.second < 0);
        return;
    }
    
//    intersectionRatio = getIntersectionRatioWithBoundingBox(ray, start);
    ld dist2ToInter = intersectionRatio.first*intersectionRatio.first*ray.dist2();
    
    if((intersectionRatio.second >= 0 && dist2ToInter > bestDist2) || data.empty()) {
        return;
    }
//
    if(cutIndex != -1) {
//        assert(leftTree != nullptr);
        updateWithFigure(data[cutIndex], ray, start, bestDist2, bestIntersection);
    
        ld medianIntersectRatio = getIntersectionRatioWithMedianFlat(ray, start);
        
        pair<ld,ld> ratioLeftBox = std::make_pair(-1,-1);
        pair<ld,ld> ratioRightBox = std::make_pair(-1,-1);
        
        Point pNear = start + ray * intersectionRatio.first;
        Point pFar = start + ray * intersectionRatio.second;
        Point pSplit = start + ray * medianIntersectRatio;
        
        if(intersectionRatio.first >= 0) {
            if(leftTree->pointInside(pNear)) {
                ratioLeftBox.first = intersectionRatio.first;
            }
            
            if(rightTree->pointInside(pNear)) {
                ratioRightBox.first = intersectionRatio.first;
            }
        }

        if(intersectionRatio.second >= 0) {
            if(leftTree->pointInside(pFar)) {
                ratioLeftBox.second = intersectionRatio.second;
            }
            
            if(rightTree->pointInside(pFar)) {
                ratioRightBox.second = intersectionRatio.second;
            }
        }
        
        packingRatio(ratioLeftBox);
        packingRatio(ratioRightBox);
        
        if(medianIntersectRatio >= 0 && !(pSplit == pNear) && !(pSplit == pFar)) {
            if(leftTree->pointInside(pSplit)) {
                ratioLeftBox.second = medianIntersectRatio;
            }
            
            if(rightTree->pointInside(pSplit)) {
                ratioRightBox.second = medianIntersectRatio;
            }
        }
        
        packingRatio(ratioLeftBox);
        packingRatio(ratioRightBox);
        
        if(ratioLeftBox.first < ratioRightBox.first) {
            leftTree->find(ray, start, bestDist2, bestIntersection,ratioLeftBox);
            rightTree->find(ray, start, bestDist2, bestIntersection,ratioRightBox);
        } else {
            rightTree->find(ray, start, bestDist2, bestIntersection,ratioRightBox);
            leftTree->find(ray, start, bestDist2, bestIntersection,ratioLeftBox);
        }
    } else {
        for(shared_ptr<Figure> figure : data) {
            updateWithFigure(figure, ray, start, bestDist2, bestIntersection);
        }
    }
}

void Kdtree::updateWithFigure(shared_ptr<Figure> figure, Point& ray, Point& start, ld& bestDist2, IntersectionData& bestIntersection) {
    pair <Status, Point> intersectData = figure->checkIntersect(ray, start);
    if(intersectData.first != NOT_INTERSECT) {
        Point vecToCurrentIntersection = intersectData.second - start;
        
        ld dist2ToCurrentIntersection = vecToCurrentIntersection.dist2();
        
        if(dist2ToCurrentIntersection < bestDist2) {
            bestDist2 = dist2ToCurrentIntersection;
            status(bestIntersection) = intersectData.first;
            point(bestIntersection) = intersectData.second;
            figure(bestIntersection) = figure;
        }
    }
}

