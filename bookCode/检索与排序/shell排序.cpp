//shell排序（缩小增量排序）
template<typename E>
void insertsort2(E A[], int n, int step){
    for(int i = 0; i<n; i+=step){
        for(int j = i; (j>step)&&(A[j]<A[j-step]); j-=step){
            swap(A[j], A[j-step]);
        }
    }
}
template<typename E>
void shellsort(E A[], int n){
    //step: n/2 -> n/4 ->.... -> 4 -> 2 -> 1
    for(int i = n/2; i>2; i /= 2){
        for(int j = 0; j<i; j++){
            insertsort2(A[j], n-j, i);
        }
    }
    insertsort2(A, n, 1);//最后一次退化成标准的insert sort
}