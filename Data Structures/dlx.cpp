int l[N], r[M], u[N], d[N], s[N];
int row[N], col[N], ans[N], top;
int n, m, idx;

void init(){
    // 稀疏链表，只链接关键位置
    for(int i = 0; i <= m; i++){
        l[i] = i - 1, r[i] = i + 1;
        u[i] = d[i] = i;
    }

    l[0] = m, r[m] = 0;
    idx = m + 1;
}

void add(int& x, int& y, int _r, int _c){
    // DLX每次插入行都是从0插，之前的往下移动
    // 1 2 3 4 5 (虚拟列编号，哨兵)
    // 插这里(其他点.往下移)
    // . . .   .
    // .   . . 
    // .     . .

    row[idx] = _r, col[idx] = _c, s[_c]++; // 当前点编号为idx，记录行列情况 
    u[idx] = _c, d[idx] = d[_c]; // 当前点的上面是哨兵
    u[d[_c]] = idx, d[_c] = idx; // 哨兵之前下面的点的上面变为idx, 哨兵下面变idx
    r[idx] = y, l[idx] = x; // 在x和y之间连上idx, x - y -> x - idx - y
    r[x] = l[y] = idx;
    y = idx++;
}

void remove(int p){
    //删除col p和他有连接的行
    r[l[p]] = r[p], l[r[p]] = l[p];

    for(int i = d[p]; i != p; i = d[i]){
        for(int j = r[i]; j != i; j = r[j]){
            u[d[j]] = u[j], d[u[j]] = d[j];
            s[col[j]]--;
        }
    }
}

void resume(int p){
    //回复col p和他有连接的行
    for(int i = u[p]; i != p; i = u[i]){
        for(int j = l[i]; j != i; j = l[j]){
            u[d[j]] = d[u[j]] = j;
            s[col[j]]++;
        }
    }

    r[l[p]] = l[r[p]] = p;
}