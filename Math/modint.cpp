template <typename T>
struct Z{
    static const T Mod = (T)1e9 + 7;
    T num;
 
    Z() : num(0) {}
 
    Z(T n) : num(n % Mod) {
        if (num < 0) num += Mod;
    }
 
    Z operator+(const Z& other) const{
        T res = num + other.num;
        if (res >= Mod) res -= Mod;
        return Z(res);
    }
 
    Z operator-(const Z& other) const{
        T res = num - other.num;
        if (res < 0) res = (res + Mod) % Mod;
        return Z(res);
    }
 
    Z operator*(const Z& other) const{
        return Z(num * other.num % Mod);
    }
 
    Z operator/(const Z& other) const{
        return *this * qpow(other, Mod - 2);
    }
 
    bool operator >=(const Z& other) const{
        return num >= other.num;
    }
 
    bool operator <=(const Z& other) const{
        return num <= other.num;
    }
 
    bool operator >(const Z& other) const{
        return num > other.num;
    }
 
    bool operator <(const Z& other) const{
        return num < other.num;
    }
 
    friend constexpr bool operator==(Z a, Z b){
        return a.num == b.num;
    }
 
    friend constexpr bool operator!=(Z a, Z b){
        return a.num != b.num;
    }
 
    constexpr Z &operator*=(Z z) &{
        num = 1LL * num * z.num % Mod;
        return *this;
    }
 
    constexpr Z &operator+=(Z z) &{
        num = (num + z.num + Mod) % Mod;
        return *this;
    }
 
    constexpr Z &operator-=(Z z) &{
        num = (num - z.num + Mod) % Mod;
        return *this;
    }
 
    constexpr Z &operator/=(Z z) &{
        return *this *= inverse(z);
    }
 
    static Z qpow(const Z& v, T k){
        T val = v.num;
        T ret = 1;
        for(k %= Mod - 1; k > 0; k >>= 1, val = val * val % Mod){
            if(k & 1){
                ret = ret * val % Mod;
            }
        }
        return Z(ret);
    }
 
    static Z inverse(const Z& v){
        return qpow(v, Mod - 2);
    }
 
    friend ostream& operator<<(ostream& os, const Z& z){
        os << z.num;
        return os;
    }
};