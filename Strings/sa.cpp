struct SA{
    vector<int> sa, height;

    int n, m = 122;
    string s;                      
    vector<int> rk, x, y, c;

    explicit SA(const string& t) : n((int)t.size()), s(" " + t) {
        sa.resize(2 * n + 2); rk.resize(2 * n + 2); height.resize(2 * n + 2);
        x.resize(2 * n + 2);  y.resize(2 * n + 2);  c.assign(chmax(n, m) + 2, 0);
        build_sa();
        build_lcp();
    }

    void build_sa(){
        for(int i = 1; i <= n; ++i) c[x[i] = (unsigned char)s[i]]++;
        for(int i = 2; i <= m; ++i) c[i] += c[i - 1];
        for(int i = n; i; --i) sa[c[x[i]]--] = i;

        for(int k = 1, num; k <= n; k <<= 1) {
            num = 0;
            for(int i = n - k + 1; i <= n; ++i) y[++num] = i;
            for(int i = 1; i <= n; ++i){
                if(sa[i] > k) y[++num] = sa[i] - k;
            }

            fill(c.begin(), c.begin() + m + 1, 0);
            for(int i = 1; i <= n; ++i) ++c[x[i]];
            for(int i = 2; i <= m; ++i) c[i] += c[i - 1];
            for(int i = n; i; --i) sa[c[x[y[i]]]--] = y[i];

            swap(x, y);
            x[sa[1]] = num = 1;
            for(int i = 2; i <= n; ++i) {
                int same1 = (y[sa[i]] == y[sa[i - 1]]);
                int same2 = (y[sa[i] + k] == y[sa[i - 1] + k]);
                x[sa[i]] = (same1 && same2 ? num : ++num);
            }
            if (num == n) break;
            m = num;                
        }
    }

    void build_lcp(){
        for(int i = 1; i <= n; ++i) rk[sa[i]] = i;
        for(int i = 1, k = 0; i <= n; ++i) {
            if(rk[i] == 1) continue;
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }
};
 