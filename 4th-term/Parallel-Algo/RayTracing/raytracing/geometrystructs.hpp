#ifndef geometrystructs_hpp
#define geometrystructs_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>

typedef long double ld;

using std::fmax;
using std::fmin;
using std::pair;
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;

#define PI (ld)acos(-1)
#define EPS (ld)1e-9
#define Picture std::vector <std::vector<Color> >


enum Status {
    NOT_INTERSECT,
    FRONT_SIDE_INTERSECT,
    BACK_SIDE_INTERSECT
};

struct Point;
struct Color;
class Figure;
class Point;
class Sphere;


#define x d[0]
#define y d[1]
#define z d[2]

struct Point {
    ld d[3];
    Point(){
        d[0] = d[1] = d[2] = 0;
    }
    Point(ld _x, ld _y, ld _z) {
        d[0] = _x;
        d[1] = _y;
        d[2] = _z;
    }
    Point(ld _d[3]) {
        d[0] = _d[0];
        d[1] = _d[1];
        d[2] = _d[2];
    }
    const Point operator +(const Point& p) const{
        return Point(x + p.x, y + p.y, z + p.z);
    }
    
    const Point operator -(const Point& p) const{
        return Point(x - p.x, y - p.y, z - p.z);
    }
    
    const Point operator *(const ld& m) const{
        return Point(m * x, m * y, m * z);
    }
    
    const ld operator[](const int i) const {
        return d[i];
    }
    
    ld dist2() {
        return x*x + y*y + z*z;
    }
    
    const bool operator ==(const Point& p) const {
        Point d = *this - p;
        return d.dist2() < (EPS * EPS);
    }
    void printPoint() {
        cout << "***********" << endl;
        cout << x << " " << y << " " << z << endl;
        cout << "***********" << endl << endl;
    }
};

struct Color {
    int R,G,B;
    Color() {
        R = G = B = 1;
    }
    Color(int _R, int _G, int _B): R(_R), G(_G), B(_B) {}
    Color(int c[3]) {
        R = c[0];
        G = c[1];
        B = c[2];
    }
    
    const Color operator +(const Color& c) const{
        return Color(R + c.R, G + c.G, B + c.B) * 1;
    }
    
    void operator =(const Color& color) {
        R = color.R;
        G = color.G;
        B = color.B;
    }
    const Color operator *(const ld& m) const{
        return Color(int(fmax(1,fmin(255,m * R))),
                     int(fmax(1,fmin(255,m * G))),
                     int(fmax(1,fmin(255,m * B))));
    }
};

class Figure{
public:
    virtual pair <Status,Point> checkIntersect(Point ray, Point start) = 0;
    virtual Point getFrontSideNormalInPoint(Point p) = 0;
    virtual Color calcTextureColor(Point intersection, Picture& texture) = 0;
    Color getColor() {return color;}
    ld getRightBound(int dim) {return rightBound[dim];}
    ld getLeftBound(int dim) {return leftBound[dim];}
    Point getRightBound() {return rightBound;}
    Point getLeftBound() {return rightBound;}
    int getReflectAlpha() {return reflectAlpha;}
    int getTextureAlpha() {return textureAlpha;}
    int getTransparentAlpha() {return transparentAlpha;}
    int getTextureId() {return textureId;}
    void setTexture(int _textureId, int _textureAlpha) { textureId = _textureId; textureAlpha = _textureAlpha; }
protected:
    int textureAlpha;
    int reflectAlpha;
    int transparentAlpha;
    int textureId;
    Color color;
    Point rightBound;
    Point leftBound;
};

class Triangle: public Figure{
public:
    Triangle(Color color, Point _v[3], Point norm = Point(0,0,0), int _reflectAlpha = 0, int _transparentAlpha = 0);
    pair <Status,Point> checkIntersect(Point ray, Point start);
    Point getFrontSideNormalInPoint(Point p);
    Color calcTextureColor(Point intersection, Picture& texture);
private:
    Point normalToFrontSide;
    Point v[3];
};

class Sphere: public Figure{
public:
    Sphere(Color color,Point _centr, ld _radius, int _reflectAlpha = 0, int _transparentAlpha = 0);
    pair <Status,Point> checkIntersect(Point ray, Point start);
    Point getFrontSideNormalInPoint(Point p);
    Color calcTextureColor(Point intersection, Picture& texture);
private:
    Point centr;
    ld radius;
};

ld det(ld a, ld b, ld c, ld d);
ld det(ld a0[3], ld a1[3], ld a2[3]);
ld scal(Point p1, Point p2);
Point vect(Point a, Point b);

bool sgnP(std::pair<ld,ld> p, ld line[3]);

std::tuple<ld,ld,ld> solveMatrix(ld m[3][3], ld v[3]);

Point getReflectionRay(Point ray, Point normal);

ld getIntersectionFlatRatio(Point ray, Point start, Point norm, Point v0, Point v_01, Point v_02);

ld getSurface(Point l, Point r);

void packingRatio(pair<ld,ld>& r);

typedef std::tuple<Status,Point,std::shared_ptr<Figure>> IntersectionData;

#define status(inter) std::get<0>(inter)
#define point(inter) std::get<1>(inter)
#define figure(inter) std::get<2>(inter)

#endif /* geometrystructs_hpp */
