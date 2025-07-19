int n;
double a[N][N], b[N][N];

void gauss(){
    int c, r;
    for(c = 1, r = 1; c <= n; c++){
        int t = r;
        for(int i = r + 1; i <= n; i++){
            if(fabs(b[i][c]) > fabs(b[t][c])){
                t = i;
            }
        }

        if(fabs(b[t][c]) < eps){
            continue;
        }

        for(int i = c; i <= n + 1; i++){
            swap(b[t][i], b[r][i]);
        }
        for(int i = n + 1; i >= c; i--){
            b[r][i] /= b[r][c];
        }

        for(int i = r + 1; i <= n; i++){
            if(fabs(b[i][c]) > eps){
                for(int j = n + 1; j >= c; j--){
                    b[i][j] -= b[r][j] * b[i][c];
                }
            }
        }
        r++;
    }

    for(int i = n; i > 0; i--){
        for(int j = i + 1; j <= n; j++){
            b[i][n + 1] -= b[i][j] * b[j][n + 1];
        }
    }
}