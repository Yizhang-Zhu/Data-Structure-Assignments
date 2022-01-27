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



//前序遍历
template<typename E>
void preorder(BinNode<E>* root){
    if(root == nullptr) return nullptr;
    visit(root);
    preorder(root->left());
    preorder(root->right());
}

template<typename E>
void preorder2(BinNode<E>* root){
    visit(root);
    if(root->left() != nullptr) preorder(root->left());
    if(root->right() != nullptr) preorder(root->right());
}

//计算二叉树结点个数
template<typename E>
void count(BinNode<E>* root){
    int cnt;
    cnt = 1+count(root->left())+count(root->right());
    return cnt;
}

//判断一棵二叉树是不是BST
template<typename Key, typename E>
void checkBST(BinNode<Key, E>* root, Key low, Key high){
    if(root == nullptr) return true;
    Key rootkey = root->key();
    if((rootkey < low) || (rootkey > high)){
        return false;//out of range
    }
    if(!checkBST<Key, E>(root->left(), low, rootkey)){
        return false;
    }

    return checkBST<Key, E>(root->right(), rootkey, high);
}