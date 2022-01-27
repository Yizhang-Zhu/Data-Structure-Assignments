class ParPtrTree{
private:
    int *array;
    int size;
    int FIND(int) const;
public:
    ParPtrTree(int);
    ~ParPtrTree(){
        delete [] array;
    }
    void UNION(int, int);
    bool differ(int, int);
};

int ParPtrTree::FIND(int curr) const{
    while(array[curr] != ROOT){
        curr = array[curr];
    }
    return curr;
}