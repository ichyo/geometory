//直線と直線の交差判定
bool intersectLL(const Line &l, const Line &m) {
  return abs(cross(l[1] - l[0], m[1] - m[0])) > EPS || // non-parallel
         abs(cross(l[1] - l[0], m[0] - l[0])) < EPS;   // same-line
}
//直線と線分の交差判定
bool intersectLS(const Line &l, const Line &s) {
  return cross(l[1] - l[0], s[0] - l[0]) *
         cross(l[1] - l[0], s[1] - l[0]) < EPS;
}
//直線と点の交差判定
bool intersectLP(const Line &l, const Point &p) {
  return abs(ccw(p, l[0], l[1])) != 1;
}
//線分と線分の交差判定
bool intersectSS(const Line &s, const Line &t) {
  return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 &&
    ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0;
}
//線分と点の交差判定
bool intersectSP(const Line &s, const Point &p) {
  return abs(s[0] - p) + abs(s[1] - p) - abs(s[1] - s[0]) < EPS;
}
//pからlへの射影の長さ(?)
Point projection(const Line &l, const Point &p) {
  double t = dot(p - l[0], l[0] - l[1]) / norm(l[0] - l[1]);
  return l[0] + t * (l[0] - l[1]);
}

Point reflection(const Line &l, const Point &p) {
  return p + 2.0 * (projection(l, p) - p);
}
//直線と点の距離
double distanceLP(const Line &l, const Point &p) {
  return abs(p - projection(l, p));
}
//直線と直線の距離
double distanceLL(const Line &l, const Line &m) {
  return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
//直線と線分の距離
double distanceLS(const Line &l, const Line &s) {
  if (intersectLS(l, s)) return 0; 
  return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
//線分と点の距離
double distanceSP(const Line &s, const Point &p) {
  const Point r = projection(s, p);
  if (intersectSP(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}
//線分と線分の距離
double distanceSS(const Line &s, const Line &t) {
  if (intersectSS(s, t)) return 0;
  return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
             min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}
//二直線の交点
Point crosspoint(const Line &l, const Line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // 同じ直線
  if (abs(A) < EPS) assert(false); // !!交わらない!!
  return m[0] + B / A * (m[1] - m[0]);
}
