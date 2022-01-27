#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

//城市类，包括城市名称，x、y坐标
class City{
public:
    string name;
    int x;
    int y;
    //constructors
    City(){
        x = 0;
        y = 0;
    }
    City(string name, int x, int y){
        this->name = name;
        this->x = x;
        this->y = y;
    }
};

//重载运算符 > 和 <，用于城市名称string之间的大小比较
// >
bool operator>(string s1, string s2){
    if((s1[0]-'a') > (s2[0]-'a')){
        return true;
    }else if((s1[0]-'a') == (s2[0]-'a')){
        for(int i = 1; i<s1.length(); i++){
            if((s1[i]-'a') > (s2[i]-'a')){
                return true;
            }else if((s1[0]-'a') < (s2[0]-'a')){
                return false;
            }else if(i == s1.length()-1){
                return false;
            }
        }
    }
}
// <
bool operator<(string s1, string s2){
    if((s1[0]-'a') < (s2[0]-'a')){
        return true;
    }else if((s1[0]-'a') == (s2[0]-'a')){
        for(int i = 1; i<s1.length(); i++){
            if((s1[i]-'a') < (s2[i]-'a')){
                return true;
            }else if((s1[0]-'a') > (s2[0]-'a')){
                return false;
            }else if(i == s1.length()-1){
                return false;
            }
        }
    }
}
//重载运算符 == ，判断一个城市是不是以char a 为首字母的
bool operator==(string city, char a){
    if(city[0] == a){
        return true;
    }else{
        return false;
    }
}

// 书本上BST相关代码。Dictionary BSTNode BST
// The Dictionary abstract class.
template <typename Key, typename E>
class Dictionary
{
private:
    void operator=(const Dictionary &) {}
    Dictionary(const Dictionary &) {}

public:
    Dictionary() {}          // Default constructor
    virtual ~Dictionary() {} // Base destructor

    // Reinitialize dictionary
    virtual void clear() = 0;

    // Insert a record
    // k: The key for the record being inserted.
    // e: The record being inserted.
    virtual void insert(const Key &k, const E &e) = 0;

    // Remove and return a record.
    // k: The key of the record to be removed.
    // Return: A maching record. If multiple records match
    // "k", remove an arbitrary one. Return NULL if no record
    // with key "k" exists.
    virtual E remove(const Key &k) = 0;

    // Remove and return an arbitrary record from dictionary.
    // Return: The record removed, or NULL if none exists.
    virtual E removeAny() = 0;

    // Return: A record matching "k" (NULL if none exists).
    // If multiple records match, return an arbitrary one.
    // k: The key of the record to find
    virtual E find(const Key &k) const = 0;

    // Return the number of records in the dictionary.
    virtual int size() = 0;
};

// BSTNode
// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode
{
private:
    Key k;       // The node's key
    E it;        // The node's value
    BSTNode *lc; // Pointer to left child
    BSTNode *rc; // Pointer to right child

public:
    // Two constructors -- with and without initial values
    BSTNode() { lc = rc = NULL; }
    BSTNode(Key K, E e, BSTNode *l = NULL, BSTNode *r = NULL)
    {
        k = K;
        it = e;
        lc = l;
        rc = r;
    }
    ~BSTNode() {} // Destructor

    // Functions to set and return the value and key
    E &element() { return it; }
    void setElement(const E &e) { it = e; }
    Key &key() { return k; }
    void setKey(const Key &K) { k = K; }

    // Functions to set and return the children
    inline BSTNode *left() const { return lc; }
    void setLeft(BSTNode<Key, E> *b) { lc = b; }
    inline BSTNode *right() const { return rc; }
    void setRight(BSTNode<Key, E> *b) { rc = b; }

    // Return true if it is a leaf, false otherwise
    bool isLeaf() { return (lc == NULL) && (rc == NULL); }
};

// BST
// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST// : public Dictionary<Key, E>
{
private:
    BSTNode<Key, E> *root; // Root of the BST
    int nodecount;         // Number of nodes in the BST

    // Private "helper" functions
    void clearhelp(BSTNode<Key, E> *);
    BSTNode<Key, E> *inserthelp(BSTNode<Key, E> *,
                                const Key &, const E &);
    BSTNode<Key, E> *deletemin(BSTNode<Key, E> *);
    BSTNode<Key, E> *getmin(BSTNode<Key, E> *);
    BSTNode<Key, E> *removehelp(BSTNode<Key, E> *, const Key &);
    E findhelp(BSTNode<Key, E> *, const Key &) const;
    void printhelp(BSTNode<Key, E> *) const;
    void printhelp1(BSTNode<string, City> *root, char a);
    void printhelp2(BSTNode<string, City> *root, int x0, int y0, int d);

public:
    BST()
    {
        root = NULL;
        nodecount = 0;
    }                           // Constructor
    ~BST() { clearhelp(root); } // Destructor

    void clear() // Reinitialize tree
    {
        clearhelp(root);
        root = NULL;
        nodecount = 0;
    }

    // Insert a record into the tree.
    // k Key value of the record.
    // e The record to insert.
    void insert(const Key &k, const E &e)
    {
        root = inserthelp(root, k, e);
        nodecount++;
    }

    // Remove a record from the tree.
    // k Key value of record to remove.
    // Return: The record removed, or NULL if there is none.
    E remove(const Key &k)
    {
        E temp = findhelp(root, k); // First find it
        root = removehelp(root, k);
        nodecount--;
        return temp;
    }
    // Remove and return the root node from the dictionary.
    // Return: The record removed, null if tree is empty.
    E removeAny()
    { // Delete min value
        if (root != NULL)
        {
            E temp = root->element();
            root = removehelp(root, root->key());
            nodecount--;
            return temp;
        }
        else
            return NULL;
    }

    // Return Record with key value k, NULL if none exist.
    // k: The key value to find. */
    // Return some record matching "k".
    // Return true if such exists, false otherwise. If
    // multiple records match "k", return an arbitrary one.
    E find(const Key &k) const { return findhelp(root, k); }

    // Return the number of records in the dictionary.
    int size() { return nodecount; }

    void print() const
    { // Print the contents of the BST
        if (root == NULL)
            cout << "The BST is empty.\n";
        else
            printhelp(root);
    }

    void print1(char a)
    { //打印指定字母开头的城市 城市名 x y
        if (root != NULL)
            printhelp1(root, a);
    }

    void print2(int x, int y, int d)
    { //打印指定点在给定距离内的所有城市 城市名 x y
        if (root != NULL)
        {
            printhelp2(root, x, y, d);
        }
    }
};

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
    clearhelp(BSTNode<Key, E> *root)
{
    if (root == NULL)
        return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E> *BST<Key, E>::inserthelp(
    BSTNode<Key, E> *root, const Key &k, const E &it)
{
    if (root == NULL) // Empty tree: create node
        return new BSTNode<Key, E>(k, it, NULL, NULL);
    if (k < root->key())
        root->setLeft(inserthelp(root->left(), k, it));
    else
        root->setRight(inserthelp(root->right(), k, it));
    return root; // Return tree with node inserted
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E> *BST<Key, E>::
    getmin(BSTNode<Key, E> *rt)
{
    if (rt->left() == NULL)
        return rt;
    else
        return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E> *BST<Key, E>::
    deletemin(BSTNode<Key, E> *rt)
{
    if (rt->left() == NULL) // Found min
        return rt->right();
    else
    { // Continue left
        rt->setLeft(deletemin(rt->left()));
        return rt;
    }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E> *BST<Key, E>::
    removehelp(BSTNode<Key, E> *rt, const Key &k)
{
    if (rt == NULL)
        return NULL; // k is not in tree
    else if (k < rt->key())
        rt->setLeft(removehelp(rt->left(), k));
    else if (k > rt->key())
        rt->setRight(removehelp(rt->right(), k));
    else
    { // Found: remove it
        BSTNode<Key, E> *temp = rt;
        if (rt->left() == NULL)
        {                     // Only a right child
            rt = rt->right(); //  so point to right
            delete temp;
        }
        else if (rt->right() == NULL)
        {                    // Only a left child
            rt = rt->left(); //  so point to left
            delete temp;
        }
        else
        { // Both children are non-empty
            BSTNode<Key, E> *temp = getmin(rt->right());
            rt->setElement(temp->element());
            rt->setKey(temp->key());
            rt->setRight(deletemin(rt->right()));
            delete temp;
        }
    }
    return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E BST<Key, E>::findhelp(BSTNode<Key, E> *root,
                        const Key &k) const
{
    // if (root == NULL)
    //     return NULL; // Empty tree
    if (k < root->key())
        return findhelp(root->left(), k); // Check left
    else if (k > root->key())
        return findhelp(root->right(), k); // Check right
    else
        return root->element(); // Found it
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::
    printhelp(BSTNode<Key, E> *root) const
{
    if (root == NULL)
        return;                         // Empty tree
    printhelp(root->left()); // Do left subtree
    // for (int i = 0; i < level; i++)     // Indent to level
    //     cout << "  ";
    cout << root->key() << "\n";         // Print node value
    printhelp(root->right()); // Do right subtree
}



template <typename Key, typename E>
void BST<Key, E>::printhelp1(BSTNode<string, City> *root, char a)
{
    if (root != NULL)
    {
        printhelp1(root->left(), a);
        //首字母为输入的a
        if (root->key()[0] == a)
        {
            City city = root->element();
            cout << city.name << ' ' << city.x << ' ' << city.y << endl;
        }
        printhelp1(root->right(), a);
    }
}

template <typename Key, typename E>
void BST<Key, E>::printhelp2(BSTNode<string, City> *root, int x, int y, int d)
{
    if (root != NULL)
    {
        printhelp2(root->left(), x, y, d);
        City city = root->element();
        //利用两点间的距离公式，判断距离是否小于等于d
        if (pow((city.x - x), 2)+ pow((city.y - y), 2) < pow(d, 2) || pow((city.x - x), 2)+ pow((city.y - y), 2) == pow(d, 2))
            cout << city.name << ' ' << city.x << ' ' << city.y << endl;
        printhelp2(root->right(), x, y, d);
    }
}



//main函数
int main(){
    int m = 0;//输入m行记录
    int n = 0;//输入操作 0（删除）/1（插入）/2（结束）
    int x = 0, y = 0, d = 0;//x、y坐标，d距离
    char a;//输入的首字母
    string cityName;
    City city;
    BST<string, City> cityTree;//关于城市的BST，以城市名为key
    //数据读取：m条记录
    cin>>m;
    for(int i = 0; i<m; i++){
        cin>>city.name>>city.x>>city.y;
        cityTree.insert(city.name, city);
    }
    //操作：不定行数条操作
    cin>>n;
    while(n != 2){
        if(n == 0){
            cin>>cityName;
            cityTree.remove(cityName);
        }else if(n == 1){
            cin>>city.name>>city.x>>city.y;
            cityTree.insert(city.name, city);
        }
        cin>>n;
    }
    //打印城市树
    cityTree.print();
    //输入要检索的首字母
    cin>>a;
    cityTree.print1(a);
    //打印与指定点的距离在给定值之内的所有城市记录
    cin>>x>>y>>d;
    cityTree.print2(x,y,d);

    return 0;

}


/*
 *
4
chongqing 1 1
chengdu 1 2
shenyang 2 2
changchun 2 3
1 shanghai 2 3
0 changchun
0 shenyang
1 beijing 2 2
2
c
0 0 3

*/
