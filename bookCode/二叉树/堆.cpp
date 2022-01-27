//最大堆的实现 -- 数组实现
template<typename E>
class heap{
private:
    E* Heap;
    int n;
    int maxSize;

    void siftdown(int pos){//注意：pos j rc都是数组下标，int类型。
        while(!isLeaf()){
            int j = leftchild(pos);
            int rc = rightchild(pos);
            if((rc < n) && (Heap[rc] > Heap[j])){
                j = rc;//j设置成更大的那个孩子
            }
            if(Heap[pos] > Heap[j]) return;//完成
            swap(Heap[j], Heap[pos]);//交换
            pos = j;//下移
        }
    }

    void siftup(int pos){
        while((pos != 0) && (Heap[pos] < Heap[parent(pos)])){
            swap(Heap[pos], Heap[parent(pos)]);//交换
            pos = parent(pos);//上移
        }
    }

public:
    //构造函数
    heap(E* h, int num, int max){
        Heap = h;
        n = num;
        maxSize = max;
    }

    //根据完全二叉树的性质，有：
    int size() const{
        return n;
    }
    bool isLeaf(int pos) const{
        return (pos >= n/2) && (pos < n);
    }
    int leftchild(int pos) const{
        return 2*pos + 1;
    }
    int rightchild(int pos) const{
        return 2*pos + 2;
    }
    int parent(int pos) const{
        return (pos-1)/2;
    }

    //heapify 堆化 -- 建堆
    void buildheap(){
        for(int i = n/2-1; i>=0; i--){//反着siftdown，即建堆
            siftdown(i);
        }
    }

    void insert(const E& it){
        int curr = n++;
        Heap[curr] = it;//先放在最后位置，再往上换到正确的位置
        siftup(curr);
    }

    void removefirst(){
        swap(Heap[0], Heap[--n]);
        if(n != 0) siftdown(0);
        return Heap[n];
    }

    void remove(int pos){
        if(pos == (n-1)){
            n--;
        }else{
            swap(Heap[pos], Heap[--n]);//要删除的元素和最后一个交换
            while((pos != 0) && (Heap[pos] > Heap(parent(pos)))){
                swap(Heap[pos], Heap[parent(pos)]);
                pos = parent(pos);
            }
            if(n != 0) siftdown(pos);
        }
        return Heap[n];
    }
};