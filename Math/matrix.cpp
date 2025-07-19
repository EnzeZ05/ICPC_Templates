struct matrix{
    int n, m;
    vector<vector<double>> a;

    matrix() : n(0), m(0) {}
    matrix(int n, int m, double init = 0.0) : n(n), m(m), a(n, vector<double>(m, init)) {}

    matrix operator+(const matrix &other) const{
        assert(n == other.n && m == other.m);
        matrix res(n, m);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                res.a[i][j] = a[i][j] + other.a[i][j];
            }
        }
        return res;
    }

    matrix operator-(const matrix &other) const{
        assert(n == other.n && m == other.m);
        matrix res(n, m);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                res.a[i][j] = a[i][j] - other.a[i][j];
            }
        }
        return res;
    }

    matrix operator*(const matrix &other) const{
        assert(m == other.n); 
        matrix res(n, other.m, 0.0);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < other.m; j++){
                for(int k = 0; k < m; k++){
                    res.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return res;
    }

    matrix operator*(double scalar) const{
        matrix res(n, m);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                res.a[i][j] = a[i][j] * scalar;
            }
        }
        return res;
    }

    matrix operator/(const matrix &other) const{
        return (*this) * other.inv();
    }

    matrix transpose() const{
        matrix res(m, n);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                res.a[j][i] = a[i][j];
            }
        }
        return res;
    }

    double trace() const{
        assert(n == m);
        double res = 0.0;

        for (int i = 0; i < n; i++){
            res += a[i][i];
        }
        return res;
    }

    int rank() const {
        matrix tmp = *this;
        int r = 0;
        const double EPS = 1e-9;

        for(int c = 0; c < m; c++){
            int pivot = -1;
            for(int i = r; i < n; i++){
                if(fabs(tmp.a[i][c]) > EPS){
                    pivot = i; 
                    break;
                }
            }

            if(pivot == -1){
                continue;
            }

            swap(tmp.a[r], tmp.a[pivot]);
            for(int i = 0; i < n; i++){
                if(i != r && fabs(tmp.a[i][c]) > EPS){
                    double factor = tmp.a[i][c] / tmp.a[r][c];
                    for(int j = c; j < m; j++){
                        tmp.a[i][j] -= factor * tmp.a[r][j];
                    }
                }
            }
            r++;
        }
        return r;
    }

    matrix inv() const{
        assert(n == m);
        int sz = n;

        matrix res(sz, sz, 0.0);
        matrix tmp = *this;
 
        for(int i = 0; i < sz; i++){
            res.a[i][i] = 1.0;
        }

        const double EPS = 1e-9;

        for(int i = 0; i < sz; i++){
            int pivot = i;
            for(int j = i; j < sz; j++){
                if(fabs(tmp.a[j][i]) > fabs(tmp.a[pivot][i])){
                    pivot = j;
                }
            }

            swap(tmp.a[i], tmp.a[pivot]);
            swap(res.a[i], res.a[pivot]);
            double div = tmp.a[i][i];

            for(int j = 0; j < sz; j++){
                tmp.a[i][j] /= div;
                res.a[i][j] /= div;
            }

            for(int j = 0; j < sz; j++){
                if(j != i){
                    double factor = tmp.a[j][i];
                    for(int k = 0; k < sz; k++){
                        tmp.a[j][k] -= factor * tmp.a[i][k];
                        res.a[j][k] -= factor * res.a[i][k];
                    }
                }
            }
        }
        return res;
    }

    matrix qpow(long long exp) const{
        assert(n == m); 
        matrix res(n, n, 0.0);
       
        for(int i = 0; i < n; i++){
            res.a[i][i] = 1.0;
        }

        matrix base = *this;
        while(exp > 0){
            if(exp & 1){
                res = res * base;
            }
            base = base * base;
            exp >>= 1;
        }
        return res;
    }

    void print() const{
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << setw(10) << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
};
 