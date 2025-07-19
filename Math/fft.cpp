template<typename T>
struct Polynomial{
    using Complex = complex<T>;

    vector<Complex> fft_conv(const vector<Complex>& a, const vector<Complex>& b, int tot){
        vector<Complex> c(tot);
        for (int i = 0; i < tot; i++) {
            c[i] = a[i] * b[i];
        }
        return c;
    }

    void fft_(vector<Complex>& a, const vector<int>& rev, int inv, int tot){
        for(int i = 0; i < tot; i++){
            if(i < rev[i]){
                swap(a[i], a[rev[i]]);
            }
        }
        for(int mid = 1; mid < tot; mid <<= 1){
            Complex w1 = {cos(pi / mid), inv * sin(pi / mid)};
            for(int i = 0; i < tot; i += mid * 2){
                Complex wk = {1, 0};
                for (int j = 0; j < mid; j++, wk *= w1){
                    Complex x = a[i + j];
                    Complex y = wk * a[i + j + mid];
                    a[i + j + mid] = x - y;
                    a[i + j] = x + y;
                }
            }  
        }
    }
};