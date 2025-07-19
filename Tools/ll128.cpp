using i128 = __int128;

ostream &operator<<(std::ostream &os, i128 n) {
    std::string s;
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}


ll ceil_div(ll n, ll m) {
    if(n >= 0){
        return (n + m - 1) / m;
    } 
    else{
        return n / m;
    }
}
 
ll floor_div(ll n, ll m) {
    if (n >= 0){
        return n / m;
    } 
    else{
        return (n - m + 1) / m;
    }
}

template<class T>
void chmax(T &a, T b) {
    if(a < b) {
        a = b;
    }
}

i128 gcd(i128 a, i128 b) {
    return b ? gcd(b, a % b) : a;
}