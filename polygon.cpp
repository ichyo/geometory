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

//多角形の相似判定
bool isSimilar(const Polygon& P, const Polygon& Q){
  const int n = P.size();
  if(Q.size() != n) return false;
  vector<double> d1(n), d2(n);
  for(int i = 0; i < n; i++){
    d1[i] = sqrt(NEXT(P,i) - CURR(P,i));
    d2[i] = sqrt(NEXT(Q,i) - CURR(Q,i));
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j <= n; j++){
      if(j == n) return true;
      if(abs(NEXT(d1, i)/NEXT(d2, i+j) - CURR(d1, i)/CURR(d2, i+j)) > EPS){
        break;
      }
    }
  }
  return false;
}

//多角形の合同判定
bool isCongruence(const Polygon& P, const Polygon& Q){
  const int n = P.size();
  if(Q.size() != n) return false;
  vector<double> d1(n), d2(n);
  for(int i = 0; i < n; i++){
    d1[i] = sqrt(NEXT(P,i) - CURR(P,i));
    d2[i] = sqrt(NEXT(Q,i) - CURR(Q,i));
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j <= n; j++){
      if(j == n) return true;
      if(abs(CURR(d1, i) - CURR(d2, i+j)) > EPS){
        break;
      }
    }
  }
  return false;
}

//pをm中心にtだけ回転
Point rotate(Point p, Point m, double t){
  p -= m;
  p = Point(p.real() * cos(t) - p.imag() * sin(t),
            p.real() * sin(t) + p.imag() * cos(t));
  return p + m;
}
//Pをm中心にtだけ回転
Polygon rotate(Polygon P, Point m, double t){
  REP(i, P.size()){
    P[i] = rotate(P[i], m, t);
  }
  return P;
}
