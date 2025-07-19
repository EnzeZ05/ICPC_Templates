vector<int> manacher(string s){
    char b[s.length() * 2 + 1];
    int k = 0;
    
    b[k++] = '^', b[k++] = '#';
    for(int i = 0; i < s.length(); i++){
        b[k++] = s[i], b[k++] = '#';
    }
    b[k++] = '$';
    
    vector<int> a(k);
    
    int mid = 0, r = 0;
    for(int i = 1; i < k; i++){
        a[i] = (i < r ? chmin(a[(mid << 1) - i], r - i) : 1);
        
        while(b[i - a[i]] == b[i + a[i]]){
            a[i]++;
        }
        if(i + a[i] > r){
            r = i + a[i];
            mid = i;
        }
    }
    return a;
} // mapping: i -> 2 * i + 2 