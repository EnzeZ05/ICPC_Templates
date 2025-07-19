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

void diophantine(){ //TODO: limited bounds
    ll a, b, c;
    cin >> a >> b >> c;

    ll x, y;
    ll d = exgcd(a, b, x, y);

    if(c % d){
        cout << -1 << endl;
    }
    else{
        ll k = c / d;
        x *= k, y *= k;
        ll t = 0, sign = 0;
        if(x < 0){
            t = (1 - x + b / d - 1) / (b / d);
            sign = 1;
        }
        else{
            t = (x - 1) / (b / d);
            sign = -1;
        }

        ll dx = x + sign * b / d * t; // 找到解为x时能取得最小整数解
        ll dy = y - sign * a / d * t;

        ll dt = 0, dsign = 0;
        if(y < 0){
            dt = (1 - y + a / d - 1) / (a / d);
            dsign = -1;
        }
        else{
            dt = (y - 1) / (a / d);
            dsign = 1;
        }

        ll ddy = y - dsign * (a / d) * dt;
        if(dy <= 0){ // 如果x为最小正数解且y小于0，说明x要变负数y才能继续趋近正数，所以没有两个都是正数的解
            cout << dx << " " << ddy << endl;
        }
        else{ // 如果dy为正(x为最小值时的对), 说明存在1组以上的正数解
            ll ddt = (dy - 1) / (a / d);
            cout << ddt + 1 << " " << dx << " " << ddy << " " << dx + ddt * (b / d) << " " << dy << endl;
        }
    }
}