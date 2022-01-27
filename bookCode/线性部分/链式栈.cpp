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
class Lstack:public Stack<E>{
private:
    Link<E>* top;//pointer to the firsr element
    int size;
public:
    Lstack(int sz = defaultSize){
        top = nullptr;
        size = 0
    }
    ~Lstack() {
        clear();
    }
    void clear(){
        while(top != nullptr){
            Link<E>* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }
    void push(const E& it){
        top = new Link<E>(it, top);
        size++;
    }
    E pop(){
        E it = top->element;
        Link<E>* ltemp = top->next;
        delete top;
        top = ltemp;
        size--;
        return it;
    }
    const E& topValue() const{
        return top->element;
    }
    int length() const{
        return size;
    }
};



//利用栈实现阶乘函数
long fact(int n, Stack<int>& S){
    long res = 1;
    while(n > 1){
        S.push(n--);
    }
    while(S.length() > 0){
        res = res * S.pop();
    }
    return res;
}
