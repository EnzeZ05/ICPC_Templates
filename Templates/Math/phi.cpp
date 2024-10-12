ll phi(ll n){
    ll qwq = n;
    for(ll i = 2; i * i <= n; i++){
        if(n % i == 0) {
            qwq = qwq / i * (i - 1);
            while(!(n % i)) n /= i;
        }
    }
    if(n > 1) qwq = qwq / n * (n - 1);
    return qwq;
}