#include <iostream>

using namespace std;

#define defaultSize 1000;


//Dictionary ADT 
template<typename Key, typename E>
class Dictionary{
private:
    void operater= (const Dictionary&) {}
    Dictionary (const Dictionary&)
public:
    Dictionary() {}//构造函数

    virtual ~Dictionary() {}//析构函数

    virtual void clear() = 0;

    virtual void insert(const Key& k, const E& e) = 0;

    virtual E remove(const Key& k) = 0;

    virtual E removeAny() = 0;

    virtual E find(const Key& k) const = 0;

    virtual int size() = 0;
};

//实现键值对
template<typename Key, typename E>
class KVpair{
private:
    Key k;
    E e;
public:
    KVpair() {}
    KVpair(Key kval, E eval){
        k = kval;//kval: k value
        e = eval;//eval: e value
    }
    //拷贝构造函数
    KVpair(const KVpair& o){
        k = o.k;
        e = o.e;
    }
    void operator=(const KVpair& o){
        k = o.k;
        e = o.e;
    }

    Key key(){
        return k;
    }
    void setKey(Key ink){
        k = ink;
    }
    E value(){
        return e;
    }
};



//Sorted array-based list
template<typename Key, typename E>
class SAList:protected Alist<KVpair<Key, E>>{
private:

public:
    SAList(int size = defaultSize):Alist<KVpair<Key, E>>(size) {}
    ~SAList() {}

    void insert(KVpair<Key, E>& it){
        KVpair<Key, E> curr;
        for(moveToStart(); currPos < length(); next){
            curr = getValue();
            if(curr.key() > it.key()){
                break;
            }
        }
        Alist<KVpair<Key, E>>::insert(it);
    }

    Alist<KVpair<Key, E>>::clear;
    Alist<KVpair<Key, E>>::remove;
    Alist<KVpair<Key, E>>::moveToStart;
    Alist<KVpair<Key, E>>::moveToEnd;
    Alist<KVpair<Key, E>>::prev;
    Alist<KVpair<Key, E>>::next;
    Alist<KVpair<Key, E>>::length;
    Alist<KVpair<Key, E>>::currPos;
    Alist<KVpair<Key, E>>::moveToPos;
    Alist<KVpair<Key, E>>::getValue;

};


//有序数组字典
template<typename Key, typename E> 
class SALDict:public Dictionary<Key, E>{
private:
    SAList<Key, E>* list;
public:
    SALDict(int size = defaultSize){
        list = new SAList<Key, E>(size);
    }
    ~SALDict(){ delete list; }

    //*****insert O(n)
    void insert(const Key& k, const E& e){
        KVpair<Key, E> temp(k, e);
        list->insert(temp);
    }

    E remove(const Key& k){
        E temp = find(k);
        if(temp != nullptr){
            list->remove();
        }
        return temp;
    }

    E removeAny(){
        list->moveToEnd();
        list->prev();
        KVpair<Key, E> e = list->remove();
        return e.value();
    }

    //*****find O(logn)
    E find(const Key& k) const{
        int l = -1;//left
        int r = list->length();//right
        while(l+1 != r){
            int i = (l+r)/2;
            list->moveToPos(i);
            KVpair<Key, E> temp = list->getValue();
            if(k < temp.key()) r = i;//in left side
            if(k > temp.key()) l = i;//in right side
            if(k == temp.key()) return temp.value();
        }
        return nullptr;
    } 

    int size(){
        return list->length();
    }

};