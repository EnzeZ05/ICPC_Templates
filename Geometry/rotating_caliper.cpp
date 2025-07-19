struct Point {
    int x, y;
    Point operator-(const Point& b) const {
        return {x - b.x, y - b.y};
    }
    int operator*(const Point& b) const {
        return x * b.y - y * b.x;
    }
};

int n;
vector<Point> q;
vector<int> stk;
vector<bool> used;
int top = 0;

int area(const Point& a, const Point& b, const Point& c) {
    return (b - a) * (c - a);
}

int get_dist(const Point& a, const Point& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

void get_convex() {
    sort(q.begin(), q.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    stk.clear();
    used.assign(n, false);
    top = 0;

    for (int i = 0; i < n; i++) {
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0) {
            if (area(q[stk[top - 2]], q[stk[top - 1]], q[i]) < 0)
                used[stk[--top]] = false, stk.pop_back();
            else
                top--, stk.pop_back();
        }
        stk.pb(i);
        top++;
        used[i] = true;
    }

    used[0] = false;
    int k = top;
    for (int i = n - 1; i >= 0; i--) {
        if (used[i]) continue;
        while (top >= k + 1 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
            top--, stk.pop_back();
        stk.pb(i);
        top++;
    }
    top--;
}

int rotating_calipers() {
    if (top <= 2) return get_dist(q[0], q[n - 1]);

    int res = 0;
    for (int i = 0, j = 2; i < top; i++) {
        auto d = q[stk[i]], e = q[stk[(i + 1) % top]];
        while (area(d, e, q[stk[j]]) < area(d, e, q[stk[(j + 1) % top]]))
            j = (j + 1) % top;
        res = chmax(res, chmax(get_dist(d, q[stk[j]]), get_dist(e, q[stk[j]])));
    }
    return res;
}