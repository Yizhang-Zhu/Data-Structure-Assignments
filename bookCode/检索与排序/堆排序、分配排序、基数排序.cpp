//堆排序
template<typename E>
void heapsort(E A[], int n){
    E maxval;
    heap<E> H(A, n, n);//建堆
    for(int i = 0; i<n; i++){
        maxval = H.removefirst();
    }
}


//分配排序
template<typename E, class getKey>
void binsort(E A[], int n){
    List<E> B[MaxKeyValue];
    E item;
    for(int i = 0; i<n; i++){
        B[A[i]].append(getKey::key(A[i]));
    }
    for(int i = 0; i<maxKeyValue; i++){
        for(B[i].setStart(); B[i].getValue(item); B[i],next()){
            output(item);
        }
    }
}


//基数排序
template<typename E, typename getKey>
//r 表示进制，如10
//cnr[i]存储bin[i]中记录的数目
void radix(E A[], E B[], int n, int k, int r, int cnt[]){
    int j;
    for(int i = 0, rtoi = 1; i<k; i++, rtoi *= r){//k个数字,常数级
        for(j = 0; j<r; j++){
            cnt[j] = 0;//初始化
        }
        for(j = 0; j<n; j++){
            cnt[(getKey::key(A[j])/rtoi)%r]++;//统计各桶内放元素个数
        }
        for(j = 1; j<r; j++){
            cnt[j] = cnt[j-1] + cnt[j];
        }
        for(j = n-1; j>=0; j--){
            B[--cnt[(getKey::key(A[j])/rtoi)%r]] = A[j];
        }
        for(j = 0; j<n; j++){
            A[j] = B[j];
        }
    }
}