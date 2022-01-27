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

//顺序队列
template<typename E>
class AQueue:public Queue<E>{
private:
    int maxSize;//max size,也是取模操作的基数
    int front;
    int rear;
    E* listArray;
public:
    AQueue(int size = defaultSize){
        maxSize = size + 1;
        front = 0;
        rear = 0;
        listArray = new E[maxSize];
    }

    ~AQueue() {
        delete [] listArray;
    }

    void clear(){
        front = 1;
        rear = 0;
    }

    void enqueue(const E& it){
        rear = (rear+1)%maxSize;
        listArray[rear] = it;
    }

    E dequeue(){
        E it = listArray[front];
        front = (front+1)%maxSize;
        return it;
    }

    const E& frontValue const(){
        return listArrayp[front];
    }

    virtual int length const(){
        return ((real+maxSize)-front+1)%maxSize;
    }
};