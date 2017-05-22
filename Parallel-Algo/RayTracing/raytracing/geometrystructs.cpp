#include "geometrystructs.hpp"
#include <cassert>

Triangle::Triangle(Color _color, Point _v[3], Point normal, int _reflectAlpha, int _transparentAlpha): normalToFrontSide(normal) {
    textureId = -1;
    textureAlpha = 0;
    reflectAlpha = _reflectAlpha;
    transparentAlpha = _transparentAlpha;
    color = _color;
    
    for(int i = 0;i < 3;++i) {
        v[i] = _v[i];
    }
    
    if(normalToFrontSide == Point(0,0,0)) {
        Point vec1 = v[1] - v[0];
        Point vec2 = v[2] - v[0];
        
        normalToFrontSide = vect(vec1, vec2);
    }
    
    ld maxx[3], minn[3];
    
    for(int i = 0; i < 3; ++i) {
        maxx[i] = fmax(v[0][i],fmax(v[1][i],v[2][i]));
        minn[i] = fmin(v[0][i],fmin(v[1][i],v[2][i]));
    }
    
    rightBound = Point(maxx[0],maxx[1],maxx[2]);
    leftBound = Point(minn[0],minn[1],minn[2]);
}

Sphere::Sphere(Color _color,Point _centr, ld _radius, int _reflectAlpha, int _transparentAlpha): centr(_centr), radius(_radius) {
    textureId = -1;
    textureAlpha = 0;
    reflectAlpha = _reflectAlpha;
    transparentAlpha = _transparentAlpha;
    color = _color;
    
    Point rad(radius,radius,radius);
    
    rightBound = centr + rad;
    leftBound = centr - rad;
}

pair <Status,Point> Triangle::checkIntersect(Point ray, Point start) {
    Point intersect;

    Point v_01 = v[1] - v[0];
    Point v_02 = v[2] - v[0];


    ld ratio = getIntersectionFlatRatio(ray, start, normalToFrontSide, v[0], v_01, v_02);
    
    if(ratio < 0) {
        return make_pair(NOT_INTERSECT,intersect);
    }
    
    intersect = start + ray * ratio;
    
    //check that intersection inside triangle:
    
    Point v_0inter = intersect - v[0];
    
    ld m[3][3];
    ld vc[3];
    
    m[0][0] = v_01.x;
    m[0][1] = v_01.y;
    m[0][2] = v_01.z;
    m[1][0] = v_02.x;
    m[1][1] = v_02.y;
    m[1][2] = v_02.z;
    m[2][0] = normalToFrontSide.x;
    m[2][1] = normalToFrontSide.y;
    m[2][2] = normalToFrontSide.z;
    vc[0] = v_0inter.x;
    vc[1] = v_0inter.y;
    vc[2] = v_0inter.z;
    
    std::tuple <ld,ld,ld> solution = solveMatrix(m, vc);
    pair<ld,ld> coord = make_pair(std::get<0>(solution), std::get<1>(solution));
    
    ld line1[3] = {1,0,0};
    ld line2[3] = {0,1,0};
    ld line3[3] = {-1,-1,1};
    
    if(sgnP(coord,line1) && sgnP(coord, line2) && sgnP(coord,line3)) {
        Status intersectionStatus = (scal(normalToFrontSide, ray) > 0 ? FRONT_SIDE_INTERSECT : BACK_SIDE_INTERSECT);
        return make_pair(intersectionStatus, intersect);
    } else {
        //case if intersection outside of triangle
        return make_pair(NOT_INTERSECT, intersect);
    }
}

std::pair <Status,Point> Sphere::checkIntersect(Point ray, Point start) {
    Point intersect;
    ld offset = -scal(ray, centr);
    ld t = -(scal(ray, start) + offset)/(ray.dist2());
    

    Point projection = start + ray * t;
    
    Point v_inter = projection - centr;
    
    ld offsetInsideSphere = sqrt((radius*radius - v_inter.dist2())/ray.dist2());
    
    t -= offsetInsideSphere;
    
    //check case if start point inside sphere
    if(t < 0) {
        t += (offsetInsideSphere * 2);
    }
    
    //case if Sphere in other side of ray
    if(t < 0) {
        return make_pair(NOT_INTERSECT,intersect);
    }
    
    intersect = start + ray * t;

    if(v_inter.dist2() < radius * radius) {
        Point dir = intersect - centr;
        Status intersectionStatus = (scal(dir, ray) > 0 ? FRONT_SIDE_INTERSECT : BACK_SIDE_INTERSECT);
        return make_pair(intersectionStatus, intersect);
    } else {
        return make_pair(NOT_INTERSECT, intersect);
    }
}

Point Triangle::getFrontSideNormalInPoint(Point p) {
    return normalToFrontSide;
}

Point Sphere::getFrontSideNormalInPoint(Point p) {
    return p - centr;
}

Color Triangle::calcTextureColor(Point intersection, Picture& texture) {
    Color textureColor;
    Point v01 = v[1] - v[0];
    Point v02 = v[2] - v[0];
    Point dir = intersection - v[0];
    uint64_t xmax = texture.size();
    uint64_t ymax = texture[0].size();
    uint64_t coord1 = (uint64_t)(scal(dir, v01)/sqrtl(v01.dist2())) % ymax;
    Point normalv02 = v02 - v01 * (scal(v01,v02)/v01.dist2());
    uint64_t coord2 = (uint64_t)(xmax - (scal(dir, normalv02)/sqrtl(normalv02.dist2()))) % xmax;
    return texture[coord2][coord1];
}

Color Sphere::calcTextureColor(Point intersection, Picture& texture) {
    Color textureColor;
    Point offset = intersection - centr;
    Point start = centr + Point(radius, 0, 0);
    uint64_t xmax = texture.size();
    uint64_t ymax = texture[0].size();
    Point proj = offset;
    proj.z = 0;
    ld cosfi = scal(proj, start)/(sqrtl(proj.dist2() * start.dist2()));
    ld fi = 0;
    Point vc = vect(start, proj);
    fi = acos(cosfi);
    if(vc.z < 0) {
        fi = 2*PI - fi;
    }
    
    uint64_t coord2 = (uint64_t)(fi/(2*PI)*ymax);
    fi = asinl(offset.z/radius);
    fi += PI/2;
    uint64_t coord1 = (uint64_t)((PI-fi)/(PI)*xmax);
    
    return texture[coord1][coord2];
}

std::tuple<ld,ld,ld> solveMatrix(ld m[3][3], ld v[3]) {
    ld d = det(m[0], m[1], m[2]);
    ld d0 = det(v, m[1], m[2]);
    ld d1 = det(m[0], v, m[2]);
    ld d2 = det(m[0], m[1], v);
    return std::make_tuple(d0/d, d1/d, d2/d);
}

bool sgnP(std::pair<ld,ld> p, ld line[3]) {
    ld res = line[0] * p.first + line[1] * p.second  + line[2];
    if(res > -EPS*EPS) {
        return true;
    } else {
        return false;
    }
}

ld det(ld a, ld b, ld c, ld d) {
    return a * d - b * c;
}

ld det(ld a0[3], ld a1[3], ld a2[3]) {
    return a0[0] * det(a1[1], a1[2], a2[1], a2[2]) - a0[1] * det(a1[0], a1[2], a2[0], a2[2]) + a0[2] * det(a1[0], a1[1], a2[0], a2[1]);
}

ld scal(Point p1, Point p2) {
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

void packingRatio(pair<ld,ld>& r) {
    if(r.first < 0 && r.second < 0) {
        return;
    }
    
    if((r.first > r.second && r.second >= 0) || r.first < 0) {
        std::swap(r.first, r.second);
    }
}

Point vect(Point a, Point b) {
    Point p;
    p.x = det(a.y, a.z, b.y, b.z);
    p.y = det(a.z, a.x, b.z, b.x);
    p.z = det(a.x, a.y, b.x, b.y);
    return p;
}

ld getSurface(Point l, Point r) {
    Point len = r - l;
    return 2*(len[0]*len[1] + len[0]*len[2] + len[1]*len[2]);
}

ld getIntersectionFlatRatio(Point ray, Point start, Point norm, Point v0, Point v_01, Point v_02) {
    ld ratio = -1;
    //case if flat has measure 0
    if(vect(v_01, v_02) == Point(0,0,0)) {
        return ratio;
    }
    
    ld offset = -scal(norm, v0);
    
    //case if ray in flat
    if(std::fabs(scal(norm,ray)) < EPS*EPS) {
        return ratio;
    }
    
    ratio = -(scal(norm, start) + offset)/(scal(norm,ray));
    
    return ratio;
}

Point getReflectionRay(Point ray, Point normal) {
    if(scal(ray,normal) < 0) {
        normal = normal*(-1);
    }
    
    ld projLenQuad = powl(scal(ray,normal),2)/normal.dist2();
    normal = normal * sqrtl(projLenQuad/normal.dist2());
    Point offset = normal - ray;
    return (ray + offset * 2) * (-1);
}



