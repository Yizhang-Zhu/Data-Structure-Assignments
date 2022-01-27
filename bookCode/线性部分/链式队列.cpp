#include<iostream>

using namespace std;

#define defaultSize 1000;

//队列ADT
template<typename E>
class Queue{
private:
    void operator= (const Queue&) {}
    Queue(const Queue&) {}//拷贝构造函数

public:
    Queue() {}
    virtual ~Queue() {}

    virtual void clear() = 0;

    virtual void enqueue(const E&) = 0;

    virtual E dequeue(const) = 0;

    virtual const E& frontValue() const = 0;

    virtual int length() const = 0;

};


//链式队列
template<typename E>
class LQueue:public Queue<E>{
private:
    Link<E>* front;
    Link<E>* rear;
    int size;
public:
    LQueue(int sz = defaultSize){
        front = rear = new Link<E>();
        size = 0;
    }

    ~LQueue() {
        clear();
        delete front;
    }

    void clear(){
        while(front->next != nullptr){//删除链表节点
            rear = front;
            front = front->next;
            delete rear;
        }
        rear = front;
        size = 0;
    }

    void enqueue(const E& it){
        rear->next = new Link<E> (it, nullptr);//新插入的it在尾部，next为nullptr
        rear = rear->next;
        size++;
    }

    void dequeue(){
        E it = front->next->element;
        Link<E>* ltemp = front->next;
        front->next = ltemp->next;
        if(rear == ltemp) rear = front;
        delete ltemp;
        size--;
        return it;
    }

    const E& frontValue() const{
        return front->next->element;
    }

    virtual int length() const{
        return size;
    }
};