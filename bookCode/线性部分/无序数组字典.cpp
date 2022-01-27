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


//无序数组字典-利用顺序表
template<typename Key, typename E>
class UALdict:public Dictionary<Key, E> {
private:
    Alist<KVpair<Key, E>>* list;
public:
    //构造函数
    UALdict(int size = defaultSize){
        list = new Alist<KVpair<Key, E>>(size);
    }

    //析构函数
    ~UALdict() {delete list;}

    void clear(){
        list->ckear();
    }

    //*****insert O(1)
    void insert(const Key& k, const E& e){
        KVpair<Key, E> temp(k, e);
        list->append(temp);
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

    //*****find O(n)
    E find(const Key& k) const{
        for(list->moveToStart(); list->currPos() < list->length(); list->next()){
            KVpair<Key, E> temp = list->getVaule();
            if(k == temp.key()){
                return temp.value();
            }
            return nullptr;
        }
    }

    int size(){
        return list->length();
    }
};