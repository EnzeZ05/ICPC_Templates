ll qpow(ll a, ll b, ll m){
    ll res = 1;  
    a = a % m;  
    
    while(b > 0){
        if(b % 2 == 1){
            res = (res * a) % m; 
        }
        a = (a * a) % m; 
        b /= 2;  
    }
    
    return res;
}