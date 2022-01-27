#include<iostream>

using namespace std;

#define defaultSize 1000;


//ADT 
template <typename E>
class Stack{
private:
    void operator= (const Stack&) {}
    Stack(const Stack&) {}
public:
    Stack() {}
    virtual ~Stack() {}
    virtual clear() = 0;
    virtual push(const E& it) = 0;
    virtual E pop() = 0;
    virtual const E& topValue const = 0;
    virtual int length() const = 0;
};

template <typename E>
class Astack : public Stack<E>{
private:
    int maxSize;
    int top;//indext of top element 
    E* listArray;
public:
    AStack(int size = defaultSize){
        maxSize = size;
        top = 0;
        listArray = new E[size];
    }
    ~Astack(){
        delete [] listArray;
    }
    void clear(){
        top = 0;
    }
    E push(const E& it){
        listArray[top++] = it;
    }
    E pop(){
        return listArray[--top];
    }
    const E& topValue() const{
        return listArray[top-1];
    }
    int length() const{
        return top;
    }
};