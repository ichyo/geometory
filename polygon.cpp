// verified by AOJ 1100
//多角形の面積
double polygonArea(const Polygon& P) {
  double A = 0;
  for (int i = 0; i < P.size(); ++i) 
    A += cross(CURR(P, i), NEXT(P, i));
  return abs(A) / 2.0;
}

//点が多角形に含まれるか否か
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
