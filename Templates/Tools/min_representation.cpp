int get_min(string s){ //两个字符串之间求相同最小字典序 , s = s + s
    int i = 0, j = 1, n = s.size() / 2;
    while(i < n && j < n){
        int k = 0;
        while(k < n && s[i + k] == s[j + k]) k++;
        if(k == n) break;
        if(s[i + k] > s[j + k]) i += k + 1;
        else j += k + 1;
        if(i == j) j++;
    }
    int t = chmin(i, j);
    s[t + n] = 0;
    return t;
}