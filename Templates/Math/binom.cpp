template <typename T>
struct Binom {
public:
    vector<Z<T>> ft;  
    vector<Z<T>> ift; 
 
    Binom(int n) : ft(n + 1), ift(n + 1) {
        ft[0] = Z<T>(1);
 
        for (int i = 1; i <= n; i++) {
            ft[i] = ft[i - 1] * Z<T>(i);
        }
        ift[n] = Z<T>::inverse(ft[n]);
 
        for (int i = n - 1; i >= 0; i--) {
            ift[i] = ift[i + 1] * Z<T>(i + 1);
        }
        ift[0] = ift[1];
    }
 
    Z<T> operator()(int n, int r) const {
        if (n < 0 || n >= ft.size() || r < 0 || r > n) return Z<T>(0);
        return ft[n] * ift[n - r] * ift[r];
    }
 
    Z<T> comb(int n, int k) const {
        if (k == 0) return Z<T>(1);
        return (*this)(n, k);
    }
 
    Z<T> sumComb(int n) const {
        return Z<T>::pow(Z<T>(2), n) - Z<T>(2);
    }
 
    Z<T> perm(int n, int k) const {
        if (k == 0) return Z<T>(1);
        return (*this)(n, k) * ft[k];
    }
 
    Z<T> fact(int n) const {
        if (n == 0) return Z<T>(1);
        return ft[n];
    }
 
    Z<T> cata(int n) const {
        return (*this)(2 * n, n) / Z<T>(n + 1);
    }
};