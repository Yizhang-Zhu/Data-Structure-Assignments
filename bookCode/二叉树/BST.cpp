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

template<typename E> 
class BinNode{
public:
    virtual ~BinNode() {}

    virtual E& element() = 0;

    virtual void setElement(const E&) = 0;
    
    virtual BinNode* left() const = 0;

    virtual void setLeft(BinNode*) = 0;

    virtual BinNode* right() const = 0;

    virtual void setRight(BinNode*) = 0;

    virtual bool isLeaf() = 0;
};


//二叉树结点的实现
template<typename Key, typename E>
class BSTNode:public BinNode<E>{
private:
    Key k;
    E it;
    BSTNode* lc;//指向左孩子的指针
    BSTNode* rc;//指向右孩子的指针
public:
    //2种构造函数
    BSTNode() {
        lc = rc = nullptr;
    }
    BSTNode(Key _k, E e, BSTNode* l = nullptr, BSTNode* r = nullptr){
        k = _k;
        it = e;
        lc = l;
        rc = r;
    }
    //析构函数
    ~BinNode() {}

    //functions
    E& element(){
        return it;
    }
    void setElement(const E& e){
        it = e;
    }

    Key& key(){
        return k;
    }
    void setKey(const Key& _k){
        k = _k;
    }

    inline BSTNode* left() const{
        return lc;
    }
    void setLeft(BinNode<E>* b){
        lc = (BSTNode*)b;
    }

    inline BSTNode* right() const{
        return rc;
    }
    void setRight(BinNode<E>* b){
        rc = (BSTNode*)b;
    }

    bool isLeaf(){
        return ((lc == nullptr) && (rc == nullptr));
    }

};


//```````````````````BST````````````````````````````````

template<typename Key, typename E>
class BST:public Dictionary<Key,E>{
private:
    BSTNode<Key, E>* root;
    int nodecount;

    //私有的helper函数
    void clearhelp(BSTNode<Key,E>*);
    BSTNode<Key,E>* inserthelp(BSTNode<Key,E>*, const Key&, const E&);
    BSTNode<Key,E>* deletemin(BSTNode<Key,E>*);
    BSTNode<Key,E>* getmin(BSTNode<Key,E>*);
    BSTNode<Key,E>* removehelp(BSTNode<Key,E>*, const Key&);
    E findhelp(BSTNode<Key,E>*, const Key&) const;
    void printhelp(BSTNode<Key,E>*, int) const;

public:
    BST(){
        root = nullptr;
        nodecount = 0;
    }
    ~BST(){ clearhelp(root); }

    void clear(){
        clearhelp(root);
        root = nullptr;
        nodecount = 0;
    }

    void insert(const Key& k, const E& e){
        root = inserthelp(root, k ,e);
        nodecount++;
    }

    E remove(const Key& k){
        E temp = findhelp(k);
        if(temp != nullptr){
            root = removehelp(root, k);
            nodecount--;
        }
        return temp;
    }

    //remove and return root node from the dict
    E removeAny(){
        if(root != nullptr){
            E temp = root->element();
            root = removehelp(root, root->key());
            nodecount--;
            return temp;
        }
        else{
            return nullptr;
        }
    }

    E find(const Key& k) const{
        return findhelp(root,k);
    }

    void print() const{
        if(root != nullptr){
            cout<<"Empty BST."<<endl;
        }else{
            printhelp(root, 0);
        }
    }
    
};


//help函数实现

template<typename Key, typename E>
E BST<Key,E>::findhelp(BSTNode<Key, E>* root, const Key& k) const{
    if(root == nullptr) return nullptr;
    if(k < root->key()){
        return findhelp(root->left(), k);//左子树
    }else if(k > root->key()){
        return finghelp(root->right(), k);//右子树
    }else{
        return root->element();
    }
}

template<typename Key, typename E>
BSTNode<Key,E>* BST<Key,E>::inserthelp(BSTNode<Key,E>* root, const Key& k, const E& it){
    if(root == nullptr) return new BSTNode<Key,E>(k, it, nullptr, nullptr);//空BST，创建一个结点
    if(k < root->key()){
        root->setLeft(inserthelp(root->left(), k, it));//递归左子树
    }else{
        root->setRight(inserthelp(root->right(), k, it));//递归右子树
    }
    return root;
}

template<typename Key, typename E>
BSTNode<Key,E>* BST<Key,E>::deletemin(BSTNode<Key,E>* rt){
    if(rt->left() == nullptr){//找到min，就是这里
        return rt->right();
    }else{
        rt->setLeft(deletemin(rt->left()));//找min在左子树中递归
        return rt;
    }
}

template<typename Key, typename E>
BSTNode<Key,E>* BST<Key,E>::getmin(BSTNode<Key,E>* rt){
    if(rt->left() == nullptr){
        return rt;
    }else{
        return getmin(rt->left());
    }
}

template<typename Key, typename E>
BSTNode<Key,E>* BST<Key,E>::removehelp(BSTNode<Key,E>* rt, const Key& k){
    if(rt == nullptr){
        return nullptr;
    }else if(k < rt->key()){
        rt->setLeft(removehelp(rt->left(), k));
    }else if(k > rt->key()){
        rt->setRight(removehelp(rt->right(), k));
    }else{
        BSTNode<Key,E>* temp = rt;
        if(rt->left() == nullptr){//只有一个右孩子
            rt = rt->right();
            delete temp;
        }else if(rt->right() == nullptr){//只有一个左孩子
            rt = rt->left();
            delete temp;
        }else{//两边的孩子都不为空
            BSTNode<Key,E>* temp = getmin(rt->right());//得到右边的最小值
            rt->setElement(temp->element());
            rt->setKey(temp->key());
            rt->setRight(deletemin(rt->right()));
            delete temp;
        }
    }
    return it;
}  

template<typename Key, typename E>
void BST<Key, E>::clearhelp(BSTNode<Key,E>* root){
    if(root == nullptr) return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}

template<typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key,E>* root, int level) const{
    if(root == nullptr) return;
    printhelp(root->left(), level+1);
    for(int i = 0; i<level; i++){
        cout<<" ";
    }
    cout<<root->key()<<endl;
    printhelp(root->right(), level+1);
}