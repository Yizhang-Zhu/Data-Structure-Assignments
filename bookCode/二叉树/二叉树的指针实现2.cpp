#include<iostream>

using namespace std;



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



//二叉树的指针实现

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


//``````````````实现方式二`````````````````````````
class VarBinNode{
public:
    virtual ~VarBinNode() {}
    virtual bool isLeaf() = 0;
    virtual void traverse() = 0;
};

//叶子节点
class LeafNode:public VarBinNode{
private:
    Operand var;//operand value
public:
    LeafNode(const Operand& val){
        var = val;
    }
    bool isLeaf() {return true;}
    Operand value() {return var;}
    void traverse() {
        cout<<"Leaf: "<<value()<<endl;
    }
};

//分支结点
class IntlNode:public VarBinNode{
private:
    VarBinNode* lc;//左孩子
    VarBinNode* rc;//右孩子
    Operator opx;//Operator value
public:
    IntlNode(const Oprator& op, VarBinNode* l, VarBinNode* r){
        lc = l;
        rc = r;
        opx = op;
    }
    bool isLeaf() {return false;}
    VarBinNode* left() {return lc;}//左孩子
    VarBinNode* right() {return rc;}//右孩子
    Operator value() {return opx;}//value

    void traverse(){
        cout<<"Internal:"<<value()<<endl;
        if(left() != nullptr) left()->traverse();
        if(right() != nullptr) right()->traverse();
    }
};

//做一次前序遍历
void traverse(const VarBinNode* root){
    if(root != nullptr) root->traverse();
}