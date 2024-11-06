ll exgcd(ll a, ll b, ll& x, ll& y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll crt(vector<ll> a, vector<ll> m){
    ll x = 0, m1 = m[0], a1 = a[0];

    for(int i = 1; i < a.size(); i++){
        ll m2 = m[i], a2 = a[i], k1 = 0, k2 = 0;
        ll d = exgcd(m1, m2, ref k1, ref k2);
        if((a2 - a1) % d > 0){
            x = -1;s
            break;
        }
        k1 *= (a2 - a1) / d;
        k1 = (k1 % (m2 / d) + m2 / d) % (m2 / d);
        x = k1 * m1 + a1;
        ll c = fabs(m1 / d * m2);
        a1 = k1 * m1 + a1;
        m1 = c;
    }

    if(x != -1){
        x = (a1 % m1 + m1) % m1;
    }
    return x;
}