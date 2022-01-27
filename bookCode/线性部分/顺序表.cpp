//顺序表

#include<iostream>

#define defaultSize 100

//线性表的抽象类声明
template <typename E> class List {
private:
    void operator = (const List&) {}
    List(const List&) {}
public:
    //构造函数和析构函数
    List() {}
    virtual ~List() {}

    //方法
    virtual void clear() = 0;
    virtual void insert(const E& item) = 0;
    virtual void append(const E& item) = 0;
    virtual E remove() = 0;
    virtual void moveToStart() = 0;
    virtual void moveToEnd() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual int length() const = 0;
    virtual int currPos() const = 0;
    virtual void moveToPos(int pos) = 0;
    virtual const E& getValue() const = 0;
};

template <typename E>//Array-based
class Alist : public List<E> {
private:
    int maxSize;
    int listSize;
    int curr;
    E* listArray;
public:
    Alist(int size = defaultSize) {
        maxSize = size;
        listSize = curr = 0;
        listArray = new E[maxSize];
    }

    ~Alist() { delete[] listArray; }

    void clear() {
        delete[] listArray;
        curr = 0;
        listSize = 0;
        listArray = new E[maxSize];
    }

    //insert "it" at current position
    void insert(const E& it) {
        //Assert(listSize < maxSize, "list capacity exceeded.");
        for (int i = listSize; i > 0; i--) {
            listArray[i] = listArray[i - 1];
        }
        listArray[curr] = it;
        listSize++;
    }

    void append(const E& it) {
        //Assert(listSize < maxSize, "list capacity exceeded.");
        listArray[listSize++] = it;
    }

    E remove(){}

    void moveToStart() { curr = 0; }

    void moveToEnd() { curr = listSize; }

    void prev() { if(curr != 0 ) curr--; }

    void next() { if (listSize < maxSize) curr++; }

    int length() const { return listSize; }

    int currPos() const { return curr; }

    //set current list position to "pos"
    void moveToPos(int pos) {
        //Assert((pos>=0)&&(pos<=listSize), "pos out of range.");
        curr = pos;
    }

    //return current element
    const E& getValue() const{
        return listArray[curr];
    }
};

int main(){


}
