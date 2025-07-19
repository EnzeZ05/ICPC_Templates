Point c;

bool cmp(Point a, Point b){
    ll dx1 = a.x - c.x, dy1 = a.y - c.y;
    ll dx2 = b.x - c.x, dy2 = b.y - c.y;
    int quad1 = (dy1 > 0 || (dy1 == 0 && dx1 > 0)) ? 0 : 1;
    int quad2 = (dy2 > 0 || (dy2 == 0 && dx2 > 0)) ? 0 : 1;
    if(quad1 != quad2){
        return quad1 < quad2;
    }
    else{
        return dx1 * dy2 - dy1 * dx2 > 0;
    }
}
