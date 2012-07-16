enum { OUT, ON, IN };
int contains(const Circle& C, Point p){
  p -= C.p;
  if(abs(C.r - abs(p)) < EPS) return ON;
  if(C.r > abs(p)) return IN;
  if(C.r < abs(p)) return OUT;
  assert(false);
}
