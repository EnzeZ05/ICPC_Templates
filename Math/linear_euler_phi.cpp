const int N = 1e7 + 5, M = 1e6 + 5;
int n, tot, p[N], phi[N], flg[N];
long long sum[N];

void get_phi(int n) {
    phi[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!flg[i]){
            p[++tot] = i,phi[i] = i - 1;
        }
        for(int j = 1; j <= tot && i * p[j] <= n; ++j) {
            flg[i * p[j]] = 1;
            if(i % p[j] == 0){
                phi[i * p[j]] = phi[i] * p[j];
                break;
            } 
            else{
                phi[i * p[j]] = phi[i] * phi[p[j]];
            }
        }
    }
    for(int i = 1; i <= n; ++i){
        sum[i] = sum[i - 1] + phi[i];
    }
}