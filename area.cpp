// verified by AOJ 1100
double polygonArea(const Polygon& P) {
  double A = 0;
  for (int i = 0; i < P.size(); ++i) 
    A += cross(CURR(P, i), NEXT(P, i));
  return abs(A) / 2.0;
}
