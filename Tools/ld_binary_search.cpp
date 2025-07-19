auto check = [&](ld t){
  
};

ld l = 0, r = 1e12;
while(r - l > chmax(1.0, l) * eps){
    ld x = (l + r) / 2;
    if(check(x)) r = x;
    else l = x;
}