const int N = 3;
ll n;

void mul(int c[], int a[], int b[][N]){
    int t[N] = {0};
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            t[i] = (t[i] + (ll)a[j] * b[j][i]) % mod;
        }
    }
    memcpy(c, t, sizeof t); //赋值跟换f，这列可以传ref
}

void mul(int c[][N], int a[][N], int b[][N]){
    int t[N][N] = {0};
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                t[i][j] = (t[i][j] + (ll)a[i][k] * b[k][j]) % mod;
            }
        }
    }
    memcpy(c, t, sizeof t);  
}

int main(){
    cin >> n;

    int f[N] = {//初始状态};
    int a[N][N] = {
        //定义
    };

    n--;
    while(n){ //矩阵快速幂
        if(n & 1) mul(f, f, a);   
        mul(a, a, a);   
        n >>= 1;
    }
    cout << f[0] << endl;  
    return 0;
}
 