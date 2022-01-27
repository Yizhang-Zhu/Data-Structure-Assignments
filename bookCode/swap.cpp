#include <bits/stdc++.h>

using namespace std;

int main(){
    int p1;
    int p2;
    cin>>p1>>p2;
    swap(p1, p2);
    cout<<p1<<" "<<p2;
}

void swap(int p1, int p2){
    int p;
    p = p2;
    p2 = p1;
    p1 = p;
}