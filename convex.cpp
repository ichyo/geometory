Polygon convexHull(Polygon ps) {
  int n = ps.size();
  int k = 0;
  sort(ps.begin(), ps.end());
  vector<Point> ch(2 * n);
  for (int i = 0; i < n; ch[k++] = ps[i++])
    while (k >= 2 && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
  for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = ps[i--])
    while (k >= t && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
  ch.resize(k - 1);
  return ch;
}

#define PREV(P, i) P[(i+P.size()-1) % P.size()]
#define CURR(P, i) (P[i])
#define NEXT(P, i) (P[(i + 1) % P.size()])
bool isConvex(const Polygon &P) {
  for (int i = 0; i < P.size(); ++i)
    if (ccw(PREV(P, i), CURR(P, i), NEXT(P, i)) > 0) return false;
  return true;
}

Polygon convexCut(const Polygon &P, const Line &l) {
  Polygon Q;
  for (int i = 0; i < (int)P.size(); i++) {
    Point A = CURR(P, i), B = NEXT(P, i);
    if (ccw(l[0], l[1], A) != -1) { Q.push_back(A); }
    if (ccw(l[0], l[1], A) * ccw(l[0], l[1], B) < 0) {
      Q.push_back(crosspointSS(Line(A, B), l));
    }
  }
  return Q;
}

