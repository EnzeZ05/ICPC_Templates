struct CartesianTree{
    int n;
    vector<int> a, l, r;

    CartesianTree(int _n) : n(_n), a(_n), l(_n, -1), r(_n, -1){

    }

    int work(){
        stack<int> s;
        for(int i = 0; i < n; i++){
            int last = -1;
            while(!s.empty() && a[s.top()] < a[i]){
                last = s.top();
                s.pop();
            }
            if(!s.empty()){
                r[s.top()] = i;
            }
            if(last != -1){
                l[i] = last;
            }
            s.push(i);
        }

        int rt = 0;
        while(!s.empty()){
            rt = s.top();
            s.pop();
        }
        return rt;
    }
};