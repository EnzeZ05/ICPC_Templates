ld search(){
   ld l = 0, r = INF, eps = 1e-6;

   while(l + eps < r){
      mid = (r - l) / 3.0;
      m1 = l + mid;
      m2 = m1 + mid;
      if(f(m1) <= f(m2)){
          r = m2;
      }
      else{
          l = m1;
      }
   }
   return l;
}

int search(int l, int r){  
    while(l < r - 1){  
       int mid  = (l + r) / 2;  
       int mmid = (mid + r) / 2;  
       if(f(mid) > f(mmid)){
           r = mmid;  
       }
       else{
           l = mid;  
       }
    }  
    return f(l) > f(r) ? l : r;  
}  