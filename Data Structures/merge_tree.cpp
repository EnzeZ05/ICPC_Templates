template<class Operation>
struct MergeTree{
    const int n;

    vector<vector<Operation>> merge;
    vector<Operation> vec;

    MergeTree(int n) : n(n), vec(n), merge(__lg(n)){
        for(int i = 0; i < merge.size(); i++){
            merge[i] = vector<Operation>(n);
        }
    }

    void build(int dep, int l, int r){ 
        if(l == r){
            merge[dep][l] = vec[l];
            return;
        } 

        int mid = (l + r) >> 1;
        build(dep + 1, l, mid);
        build(dep + 1, mid + 1, r);

        for(int i = l, j = mid + 1, k = l; i <= mid || j <= r;){
            if(j > r){
                merge[dep][k++] = merge[dep + 1][i++];
            }
            else if(i > mid || merge[dep + 1][i] > merge[dep + 1][j]){
                merge[dep][k++] = merge[dep + 1][j++];
            }
            else{
                merge[dep][k++] = merge[dep + 1][i++];
            }
        }
    }

    void build(){
        build(0, 1, n);
    }

    void init(int u, Operation &v){
        vec[u] = v;
    }

    Operation compute(){

    }

    Operation calc(int dep, int l, int r, int x, int y, int v){
        if(l >= x && y <= r){
            return compute();
        }

        int mid = (l + r) >> 1;
        Operation qwq;
        if(mid >= x){
            qwq = calc(dep + 1, l, mid, x, y, v);
        }
        if(mid < y){
            qwq += calc(dep + 1, mid + 1, r, x, y, v);
        }
        return qwq;
    }

    Operation query(int x, int y, int k){
        
    }
};