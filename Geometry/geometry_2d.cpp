template<typename T>
struct Point{
    T x, y;
    ld eps;

    Point() : x(0), y(0), eps(1e-9) {}
    Point(T x, T y) : x(x), y(y), eps(1e-9) {}

    void set_eps(T eps){
        this->eps = eps;
    }

    Point operator+ (const Point& b){
        return Point(x + b.x, y + b.y);
    }

    Point operator- (const Point& b){
        return Point(x - b.x, y - b.y);
    }

    Point operator- (){
        return Point(-x, -y);
    }

    Point operator* (T t) const{
        return Point(x * t, y * t);
    }

    Point operator/ (T t) const{
        return Point(x / t, y / t);
    }

    Point &operator+=(Point p) &{
        x += p.x;
        y += p.y;
        return *this;
    }

    Point &operator-=(Point p) &{
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point &operator*=(T v) &{
        x *= v;
        y *= v;
        return *this;
    }

    Point &operator/=(T v) &{
        x /= v;
        y /= v;
        return *this;
    }

    Point &operator=(const Point& b) &{
        x = b.x;
        y = b.y;
        return *this;
    }

    friend Point operator+ (const Point& a, const Point& b){
        return {a.x + b.x, a.y + b.y};
    }

    friend Point operator- (const Point& a, const Point& b){
        return {a.x - b.x, a.y - b.y};
    }

    friend bool operator==(Point a, Point b){
        return a.x == b.x && a.y == b.y;
    }

    int sign(T x){
        if(fabs(x) < eps){
            return 0;
        }
        if(x < 0){
            return -1;
        }
        return 1;
    }

    bool cmp(T x, T y){
        if(fabs(x - y) > eps){
            return 0;
        }
        return 1;
    }

    bool cmp(const Point& a, const Point& b){
        return cmp(a.x, b.x) && cmp(a.y, b.y);
    }

    T dot(const Point& a, const Point& b){
        return a.x * b.x + a.y * b.y;
    }

    T square(Point a){
        return dot(a, a);
    }

    T cross(const Point& a, const Point& b){
        return a.x * b.y - a.y * b.x;
    }

    T cross(const Point& a, const Point& b, const Point& p){
        return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    }

    T get_len(const Point& a){
        return sqrt(dot(a, a));
    }

    T get_angle(const Point& a, const Point& b){
        return acos(dot(a, b) / get_len(a) / get_len(b));
    }

    T area(const Point& a, const Point& b, const Point& c){
        return cross(b - a, c - a);
    }

    Point rotate(const Point& a, T angle){ //两个点就 b - a (b按a转)
        T dx = a.x * cos(angle) + a.y * sin(angle); 
        T dy = -a.x * sin(angle) + a.y * cos(angle);
        return Point(dx, dy);
    }

    Point intersect(const Point& p, const Point& v, const Point& q, const Point& w){
        Point u = p - q;
        T t = cross(w, u) / cross(v, w);
        return p + v * t;
    }

    T point_dist(const Point& a, const Point& b){
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    T line_dist(const Point& a, const Point& b, const Point& p){
        Point u = b - a, v = p - a;
        return fabs(cross(u, v)) / get_len(u);
    }

    T get_slope(const Point& a, const Point& b){
        if(b.y == a.y) return INF;
        if(b.x == a.x) return 0;
        return (b.y - a.y) / (b.x - a.x);
    }

    T circle_intersect(const Point& p1, const Point& p2, const T r1, const T r2){
        ld d = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

        if(d > r1 + r2 || d + chmin(r1, r2) <= chmax(r1, r2)){
            return 0;
        }
        else if(d == r1 + r2){
            return 1;
        }
        else{
            return 2;
        }
    }

    T seg_dist(const Point& a, const Point& b, const Point& p){
        if(a == b){
            return get_len(p - a);
        }
        Point u = b - a, v = p - a, w = p - b;

        if(sign(dot(u, v)) < 0){
            return get_len(v);
        }
        if(sign(dot(u, w)) > 0){
            return get_len(w);
        }
        return line_dist(a, b, p);
    }

    Point projection(const Point& a, const Point& b, const Point& p){
        Point v = b - a;
        return a + v * dot(v, p - a) / dot(v, v);
    }

    bool on_segment(const Point& a, const Point& b, const Point& p){
        bool u = sign(cross(p - a, p - b)) == 0;
        bool v = sign(dot(p - a, p - b)) <= 0;
        return u && v;
    }

    bool seg_intersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2){
        T c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
        T c3 = cross(b2 - b1, a2 - b1), c4 = cross(b2 - b1, a1 - b1);
        return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
    }

    vector<Point> get_circle_intersection(const Point& p1, const Point& p2, const T r1, const T r2){
        ld d = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

        Point bv = {(p2.x - p1.x) / d, (p2.y - p1.y) / d};

        if(d >= r1 + r2){
            return {};
        }
        else if(d + chmin(r1, r2) <= chmax(r1, r2)){
            return {};
        }
        else{
            Point<T> center;
            ld a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
            ld b = (r2 * r2 - r1 * r1 + d * d) / (2 * d);

            center.x = p1.x + a * bv.x;
            center.y = p1.y + a * bv.y;

            ld h = sqrt(r1 * r1 - a * a);
            Point it1 = {center.x + h * bv.y, center.y - h * bv.x};
            Point it2 = {center.x - h * bv.y, center.y + h * bv.x};

            return {it1, it2};
        }
    }

    T angle_centroid(Point centroid, Point p){ // 计算两个点的角度
        return atan2(p.y - centroid.y, p.x - centroid.x);
    }

    Point get_centroid(const vector<Point>& p) {
        Point centroid = {0, 0};
        for (const auto& pt : p) {
            centroid.x += pt.x;
            centroid.y += pt.y;
        }

        centroid.x /= p.size();
        centroid.y /= p.size();
        return centroid;
    }

    void sort_cw(vector<Point>& p) {
        Point centroid = get_centroid(p);
        sort(p.begin(), p.end(), [&](const Point& a, const Point& b) {
            return angle_centroid(centroid, a) < angle_centroid(centroid, b);
        });
    }

    friend std::ostream &operator<<(ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

//S = a + b / 2 - 1, S = area, a = lattice points inside, b = lattice point on boundary