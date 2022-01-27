//哈夫曼树的实现。树的分支节点和叶子节点分别由不同的类实现，它们都是从同一个基类中派生得到的

//哈夫曼节点
template<typename E>
class HuffNode{
    virtual ~HuffNode() {}
    virtual int weight() = 0;
    virtual bool isLeaf() = 0;
};
//叶子结点
template<typename E>
class LeafNode:public HuffNode<E>{
private:
    E it;//value
    int wgt;//weight
public:
    LeafNide(const E& val, int freq){
        it = val;
        wgt = val;
    }
    int weight(){
        return wgt;
    }
    E value(){
        return it
    }
    bool isLeaf(){
        return true;
    }
};
//分支结点
template<typename E>
class IntlNode:public HuffNode<E>{
private:
    HuffNode<E>* lc;//左孩子
    HuffNode<E>* rc;//右孩子
    int wgt;
public:
    IntlNode(HuffNode<E>* l, HuffNode<E>* r){
        lc = l;
        rc = r;
        wgt = l->weight() + r->weight();//分支节点的权重是两个子节点的权重之和
    }
    int weight(){
        return wgt;
    }
    bool isLeaf(){
        return false;
    }
    HuffNode<E>* left() const{
        return lc;
    }
    void setLeft(HuffNode<E>* b){
        lc = (HuffNode<E>*)b;
    }
    HuffNode<E>* right() const{
        return rc;
    }
    void setRight(HuffNode<E>* b){
        rc = (HuffNode<E>*)b;
    }
};

//哈夫曼树的实现
//哈夫曼树的类说明
template<typename E>
class HuffTree{
private:
    HuffNode<E>* Root;
public:
    //叶子构造函数
    HuffTree(E& val, int freq){
        Root = new LeafNode<E>(val, freq);
    }
    //分支节点构造函数
    HuffTree(HuffNode<E>* l, HuffNode<E>* r){
        Root = new IntlNode<E>(l->root(), r->root());
    }
    //析构函数
    ~HuffTree() {}
    HuffTree<E>* root(){
        return Root;
    }
    int weight(){
        return Root->weight();
    }
};
//``````````````````````````````````有疑问````````````````````````````````````````
//哈夫曼树构造函数实现（建树）
template<typename E> 
HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count){
    heap<HuffTree<E>*>* forest = new heap<HuffTree<E>*>(TreeArray, count, count);
    HuffTree<char> *temp1, *temp2, *temp3 = nullptr;
    while(forest->size() > 1){
        temp1 = forest->removefirst();
        temp2 = forest->removefirst();
        temp3 = new HuffTree<E>(temp1, temp2);
        forest->insert(temp3);
        delete temp1;
        delete temp2;
    }
    return temp3;
}