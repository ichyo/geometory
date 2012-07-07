#include <complex>
#define CURR(P, i) (P[(i) % P.size()])
#define NEXT(P, i) (P[((i) + 1) % P.size()])

typedef complex<double> Point;
typedef vector<Point> Polygon;
struct Line : public vector<Point> {
  Line() {;}
  Line(Point a, Point b) { push_back(a); push_back(b); }
};
struct Circle {
  Point p;
  double r;
  Circle() {;}
  Circle(Point p, double r) : p(p), r(r) {;}
};

namespace std{
  bool operator < (const Point& a, const Point& b){
    return a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag();
  }
}

inline double cross(const Point& a, const Point& b){
  return imag(conj(a) * b);
}

inline double dot(const Point& a, const Point& b){
  return real(conj(a) * b);
}

int ccw(Point a, Point b, Point c){
  b -= a; c -= a;
  double len = abs(b) * abs(c);
  if(cross(b, c) > +EPS * len) return +1; // counter-clockwise
  if(cross(b, c) < -EPS * len) return -1; // clockwise
  if(dot(b, c) < 0) return +2; // c--a--b
  if(norm(b) < norm(c)) return -2; // a--b--c
  return 0; // a--c--b 
}

