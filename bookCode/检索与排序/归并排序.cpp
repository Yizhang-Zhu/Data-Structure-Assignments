//归并排序
template<typename E>
void mergesort(E A[], E temp[], int left, int right){
    if(left == right) return;//单元素列表
    int mid = (left+right)/2;
    //divide
    mergesort<E>(A, temp, left, mid);
    mergesort<E>(A, temp, mid+1, right);
    for(int i = left; i<=right; i++){
        temp[i] = A[i];//copy
    }
    //对A本身实施merge sort
    int i1 = left;
    int i2 = mid+1;
    for(int curr = left; curr<i2; curr++){
        if(i1 == mid+1){
            A[curr] = temp[i2++];//左边走完了，把右表剩下的全取走
        }else if(i2>right){
            A[curr] = temp[i1++];//右边走完了，把左表剩下的全取走
        }else if(temp[i1] < temp[2]){
            A[curr] = temp[i1++];
        }else{
            A[curr] = temp[i2++];
        }
    }
}
//优化（监视哨）
template<typename E>
void mergesort2(E A[], E temp[], int left, int right){
    if(left-right <= THRESHOLD){
        insertsort<E>(&A[left], right-left+1);
        return;
    }
    int i, j, k;
    int mid = (left+right)/2;
    mergesort2<E>(A, temp, left, mid);
    mergesort2<E>(A, temp, mid+1, right);
    //copy 2 subarrays
    for(int i = mid; i>=left; i--){
        temp[i] = A[i];
    }
    for(int j = 1; j<=right-mid; j++){
        temp[right-j+1] = A[j+temp];
    }
    //merge sublist back on A
    for(i = left, j = right, k = left; k<=right; k++){
        if(temp[i] < temp[j]){
            A[k] = temp[i++];
        }else{
            A[k] = temp[j--];
        }
    }
}