bool intersectLL(const Line &l, const Line &m) {
  return abs(cross(l[1] - l[0], m[1] - m[0])) > EPS || // non-parallel
         abs(cross(l[1] - l[0], m[0] - l[0])) < EPS;   // same-line
}

bool intersectLS(const Line &l, const Line &s) {
  return cross(l[1] - l[0], s[0] - l[0]) *
         cross(l[1] - l[0], s[1] - l[0]) < EPS;
}

bool intersectLP(const Line &l, const Point &p) {
  return abs(ccw(p, l[0], l[1])) != 1;
}

bool intersectSS(const Line &s, const Line &t) {
  return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 &&
    ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0;
}

bool intersectSP(const Line &s, const Point &p) {
  return abs(s[0] - p) + abs(s[1] - p) - abs(s[1] - s[0]) < EPS;
}

enum { OUT, ON, IN };
int contains(const Polygon& P, const Point& p) {
  bool in = false;
  for (int i = 0; i < (int)P.size(); ++i) {
    Point a = CURR(P,i) - p, b = NEXT(P,i) - p;
    if (imag(a) > imag(b)) swap(a, b);
    if (imag(a) <= 0 && 0 < imag(b))
      if (cross(a, b) < 0) in = !in;
    if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}
