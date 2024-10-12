#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;

typedef long long ll;  
const double pi = acos(-1);

template<typename T>
struct Polynomial{
    using Complex = complex<T>;
    static const int mod = 998244353;
    static const int g = 3;

    vector<Complex> fft_conv(const vector<Complex>& a, const vector<Complex>& b, int tot){
        vector<Complex> c(tot);
        for (int i = 0; i < tot; i++) {
            c[i] = a[i] * b[i];
        }
        return c;
    }

    void FFT_(vector<Complex>& a, const vector<int>& rev, int inv, int tot){
        for(int i = 0; i < tot; i++){
            if(i < rev[i]){
                swap(a[i], a[rev[i]]);
            }
        }
        for(int mid = 1; mid < tot; mid <<= 1){
            Complex w1 = {cos(pi / mid), inv * sin(pi / mid)};
            for(int i = 0; i < tot; i += mid * 2){
                Complex wk = { 1, 0 };
                for (int j = 0; j < mid; j++, wk *= w1){
                    Complex x = a[i + j];
                    Complex y = wk * a[i + j + mid];
                    a[i + j + mid] = x - y;
                    a[i + j] = x + y;
                }
            }
        }
    }

    ll qpow(ll x, ll k){
        ll res = 1;
        while(k > 0){
            if(k & 1){
                res = res * x % mod;
            }
            x = x * x % mod;
            k >>= 1;
        }
        return res;
    }

    vector<ll> ntt_conv(const vector<ll>& a, const vector<ll>& b, int tot){
        vector<ll> c(tot);
        for (int i = 0; i < tot; i++){
            c[i] = a[i] * b[i] % mod;
        }
        return c;
    }

    void ntt_(vector<ll>& a, const vector<int>& rev, int inv, int tot){
        for(int i = 0; i < tot; i++){
            if(i < rev[i]){
                swap(a[i], a[rev[i]]);
            }
        }
        for(int mid = 1; mid < tot; mid <<= 1){
            ll tmp = qpow(g, (mod - 1) / (mid * 2));
            if(inv == -1){
                tmp = qpow(tmp, mod - 2);
            }
            for(int i = 0; i < tot; i += mid * 2) {
                ll w = 1;
                for(int j = 0; j < mid; j++, w = w * tmp % mod){
                    ll x = a[i + j], y = w * a[i + j + mid] % mod;
                    a[i + j] = (x + y) % mod;
                    a[i + j + mid] = (x - y + mod) % mod;
                }
            }
        }
    }
};