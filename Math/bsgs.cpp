ll bsgs(ll a, ll b, ll p){
    if(1 % p == b % p){
        return 0;
    }

    ll k = (ll)sqrt(p) + 1;
    map<ll, ll> mp;

    for(lli = 0, j = b % p; i < k; i++){
        j = 1ll * j * a % p;
        mp[j] = i;
    }

    ll ak = 1;
    for(ll i = 0; i < k; i++){
        ak = 1ll * ak * a % p;
    }

    for(ll i = 1, j = ak; i <= k; i++){
        if(mp[j]) return 1ll * i * k - mp[j];
        j = 1ll * j * ak % p;
    }
    return -1;
}

ll exbsgs(ll a, ll b, ll p) {
    b = (b % p + p) % p;
    if(1 % p == b % p){
        return 0;
    }

    ll x, y, d = exgcd(a, p, x, y);
    if(d > 1){
        if(b % d) return -2e9;
        exgcd(a / d, p / d, x, y);
        return exbsgs(a, b / d * x % (p / d), p / d) + 1;
    }
    return bsgs(a, b, p);
}