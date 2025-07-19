
struct Point{
    ld x, y;
}p[N], stk[N];

vector<Point> a;
int n, tp;

ld cross(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b){
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

void convex_hull(){
    sort(p, p + n, cmp);
    tp = 0;

    for(int i = 0; i < n; i++){
        while(tp > 1 && cross(stk[tp - 1], stk[tp], p[i]) <= 0){
            tp--;
        }
        stk[++tp] = p[i];
    }

    int lim = tp;
    for(int i = n - 2; i >= 0; i--){
        while(tp > lim && cross(stk[tp - 1], stk[tp], p[i]) <= 0){
            tp--;
        }
        stk[++tp] = p[i];
    }
}
