#include<iostream>
using namespace std;


//插入排序：Θ(n^2)，最佳情况：：Θ(n)
//插入排序对已经几乎有序的情况十分合适
template<typename E>
void insertsort(E A[], int n){
    for(int i = 1; i<n; i++){
        for(int j = i; (j>0) && (A[j] < A[j-1]); j--){
            swap(A[j], A[j-1]);
        }
    }
}


//冒泡排序：Θ(n^2)
//生活中几乎没有什么对应的使用场景
template<typename E>
void bubblesort(E A[], int n){
    for(int i = 0; i<n; i++){
        for(int j = n-1; j>i; j--){
            if(A[j] < A[j-1]){
                swap(A[j], A[j-1]);
            }
        }
    }
}


//选择排序：Θ(n^2)
template<typename E>
void selectionsort(E A[], int n){
    for(int i = 0; i<n-1; i++){
        int lowindex = i;//记住无序部分的当前最小值下标
        for(int j = i+1; j<n; j++){
            if(A[j] < A[lowindex]){
                lowindex = j;
            }
            swap(A[j], A[lowindex]);
        }
    }
}
template<typename E>
void selectionsort2(E A[], int n){
    for(int i = 0; i<n-1; i++){
        int lowindex = i;
        for(int j = n-1; j>i; j--){
            if(A[j] < A[lowindex]){
                lowindex = j;
            }
            swap(A[j], A[lowindex]);
        }
    }
}