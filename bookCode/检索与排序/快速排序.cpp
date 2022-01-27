//快速排序
template<typename E>
void quicksort(E A[], int i, int j){
    if(j<=i) return;
    int pivotindex = findpivot(A, i, j);
    swap[A[pivotindex], j];//把轴值放到最后面，即j位置
    //k将是右边子列的首位
    int k = partition<E>(A, i-1, j, A[j]);
    swap(A[k], A[j]);//放回轴值
    quicksort<E>(A, i, k-1);
    quicksort<E>(A, k+1, j);
}
//找轴值
template<typename E>
void findpivot(E A[], int i, int j){
    return (i+j)/2;
}
//划分
template<typename E>
inline int partition(E A[], int l, int r, E& pivot){
    do{
        while(A[++l] > pivot);//找到左侧比pivot大的值，停
        while((l<r) && (pivot > A[--r]));//找到右侧比pivot小的值，停
        swap(A[l], A[r]);
    }while(l < r);
    return l;//结束后返回是是右边部分的首个位置
}