#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>

#define INF 9999999
#define UNVISITED 0
#define VISITED 1

using namespace std;

// Simple class to store data in the heap: edge and its distance
class KruskElem
{ // An element for the heap
public:
    int from, to, distance; // The edge being stored
    KruskElem()
    {
        from = -1;
        to = -1;
        distance = -1;
    }
    KruskElem(int f, int t, int d)
    {
        from = f;
        to = t;
        distance = d;
    }
    //overload "<"
    friend bool operator<(const KruskElem &x, const KruskElem &y)
    {
        return x.distance > y.distance;
    }
};

// Comparator to compare two KruskElem's
class Comp
{
public:
    static bool prior(KruskElem x, KruskElem y)
    {
        return x.distance < y.distance;
    }
};

// General tree representation for UNION/FIND
class ParPtrTree
{
private:
    int *array;          // Node array
    int size;            // Size of node array
    int FIND(int) const; // Find root
public:
    ParPtrTree(int);                  // Constructor
    ~ParPtrTree() { delete[] array; } // Destructor
    void UNION(int, int);             // Merge equivalences
    bool differ(int, int);            // True if not in same tree
};
ParPtrTree::ParPtrTree(int sz)
{ // Constructor
    size = sz;
    array = new int[sz]; // Create node array
    for (int i = 0; i < sz; i++)
        array[i] = i;
}

// Return True if nodes are in different trees
bool ParPtrTree::differ(int a, int b)
{
    int root1 = FIND(a);   // Find root of node a
    int root2 = FIND(b);   // Find root of node b
    return root1 != root2; // Compare roots
}

void ParPtrTree::UNION(int a, int b)
{                        // Merge subtrees
    int root1 = FIND(a); // Find root of node a
    int root2 = FIND(b); // Find root of node b
    if (root1 != root2)
        array[root2] = root1; // Merge
}
// FIND with path compression
int ParPtrTree::FIND(int curr) const
{
    if (array[curr] == curr)
        return curr; // At root
    array[curr] = FIND(array[curr]);
    return array[curr];
}

//Graph ADT
class Graph
{
private:
    void operator=(const Graph &) {} // Protect assignment
    Graph(const Graph &) {}          // Protect copy constructor

public:
    Graph() {}          // Default constructor
    virtual ~Graph() {} // Base destructor

    // Initialize a graph of n vertices
    virtual void Init(int n) = 0;

    // Return: the number of vertices and edges
    virtual int n() = 0;
    virtual int e() = 0;

    // Return v's first neighbor
    virtual int first(int v) = 0;

    // Return v's next neighbor
    virtual int next(int v, int w) = 0;

    // Set the weight for an edge
    // i, j: The vertices
    // wgt: Edge weight
    virtual void setEdge(int v1, int v2, int wght) = 0;

    // Delete an edge
    // i, j: The vertices
    virtual void delEdge(int v1, int v2) = 0;

    // Determine if an edge is in the graph
    // i, j: The vertices
    // Return: true if edge i,j has non-zero weight
    virtual bool isEdge(int i, int j) = 0;

    // Return an edge's weight
    // i, j: The vertices
    // Return: The weight of edge i,j, or zero
    virtual int weight(int v1, int v2) = 0;

    // Get and Set the mark value for a vertex
    // v: The vertex
    // val: The value to set
    virtual int getMark(int v) = 0;
    virtual void setMark(int v, int val) = 0;
};

//Graphm, extends from Graph
class Graphm : public Graph
{
private:
    int numVertex, numEdge; // Store number of vertices, edges
    int **matrix;           // Pointer to adjacency matrix
    int *mark;              // Pointer to mark array

    //判断是否联通
    bool existCircleHelp(int v, int *father);
    //寻找未访问顶点的最小D值
    int minVertex(const int *D);

public:
    int cnt = 0;        //帮助输出格式化
    Graphm(int numVert) // Constructor
    {
        Init(numVert);
    }

    ~Graphm()
    {                  // Destructor
        delete[] mark; // Return dynamically allocated memory
        for (int i = 0; i < numVertex; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    void Init(int n)
    { // Initialize the graph
        int i;
        numVertex = n;
        numEdge = 0;
        mark = new int[n + 1]; // Initialize mark array
        for (i = 0; i < numVertex + 1; i++)
            mark[i] = UNVISITED;
        matrix = (int **)new int *[numVertex + 1]; // Make matrix
        for (i = 0; i < numVertex + 1; i++)
            matrix[i] = new int[numVertex + 1];
        for (i = 0; i <= numVertex; i++) // Initialize to 0 weights
            for (int j = 0; j <= numVertex; j++)
                matrix[i][j] = 0;
    }

    int n() { return numVertex; } // Number of vertices
    int e() { return numEdge; }   // Number of edges

    // Return first neighbor of "v"
    int first(int v)
    {
        for (int i = 1; i <= numVertex; i++)
            if (matrix[v][i] != 0)
                return i;
        return numVertex + 1; // Return n if none
    }

    // Return v's next neighbor after w
    int next(int v, int w)
    {
        for (int i = w + 1; i < numVertex + 1; i++)
            if (matrix[v][i] != 0)
                return i;
        return numVertex + 1; // Return n if none
    }

    // Set edge (v1, v2) to "wt"
    void setEdge(int v1, int v2, int wt)
    {
        //Assert(wt>0, "Illegal weight value");
        if (matrix[v1][v2] == 0)
            numEdge++;
        matrix[v1][v2] = wt;
        matrix[v2][v1] = wt;
    }

    void delEdge(int v1, int v2)
    { // Delete edge (v1, v2)
        if (matrix[v1][v2] != 0)
            numEdge--;
        matrix[v1][v2] = 0;
    }

    bool isEdge(int i, int j) // Is (i, j) an edge?
    {
        return matrix[i][j] != 0;
    }

    int weight(int v1, int v2) { return matrix[v1][v2]; }
    int getMark(int v) { return mark[v]; }
    void setMark(int v, int val) { mark[v] = val; }

    //实验要求的五个功能，按要求将这些功能封装成图操作类的成员函数。
    void DFS(int v);
    void BFS(int start);
    void Dijkstra();
    void Kruskel(KruskElem *minTree); //参数KruskElem类型数据的数组
    bool existCircle();
};

//Graphm成员函数，实验要求功能函数的实现
//DFS
void Graphm::DFS(int v)
{
    setMark(v, VISITED); //enter
    cnt++;
    //格式化输出: 输出用空格间隔，最后不留空格
    if (cnt <= numVertex - 1)
    {
        cout << v << " ";
    }
    else
    {
        cout << v;
    }
    //递归
    for (int w = first(v); w < n() + 1; w = next(v, w))
    {
        if (getMark(w) == UNVISITED)
        {
            DFS(w);
        }
    }
}

//BFS
void Graphm::BFS(int start)
{
    int v, w;
    queue<int> Q;
    Q.push(start);
    setMark(start, VISITED);
    while (Q.size() != 0)
    {
        v = Q.front();
        Q.pop();
        //格式化输出: 输出用空格间隔，最后不留空格
        cnt++;
        if (cnt <= numVertex - 1)
        {
            cout << v << " ";
        }
        else
        {
            cout << v;
        }
        for (w = first(v); w < n() + 1; w = next(v, w))
        {
            if (getMark(w) == UNVISITED)
            {
                setMark(w, VISITED);
                Q.push(w);
            }
        }
    }
}

//Dijkstra
void Graphm::Dijkstra()
{
    int i, v, w;
    int D[n()];
    int pre[n()];
    for (i = 0; i < n() + 1; i++)
    {
        D[i] = INF;
        pre[i] = -1; //存储前驱结点
        setMark(i, UNVISITED);
    }
    D[1] = 0; //1为顶点
    for (i = 0; i < n(); i++)
    {
        v = minVertex(D);
        if (D[v] == INF)
            return;
        setMark(v, VISITED);
        for (w = first(v); w < n() + 1; w = next(v, w))
        {
            if (D[w] > (D[v] + weight(v, w)))
            {
                D[w] = D[v] + weight(v, w);
                pre[w] = v; //Dw > Dv时,前驱结点更新
            }
        }
    }
    for (i = 2; i < n() + 1; i++)
    {
        stack<int> w;
        if (D[i] != INF)
        {
            for (int j = i; j != -1; j = pre[j])
            {
                w.push(j);
            }
            while (w.size() != 0)
            {
                int a1 = w.top();
                w.pop();
                cout << a1 << " "; //输出路径
            }
            cout << D[i] << endl; //输出长度
        }
        else
        {
            cout << 0 << endl; //不存在路径
        }
    }
}

//minVertex
int Graphm::minVertex(const int *D)
{
    int i = -1;
    int v = -1;
    for (i = 0; i < n() + 1; i++)
    {
        if (getMark(i) == UNVISITED)
        {
            v = i;
            break;
        }
    }
    for (i++; i < n() + 1; i++)
    {
        if ((getMark(i) == UNVISITED) && (D[i] < D[v]))
        {
            v = i;
        }
    }
    return v;
}

//Kruskel's MST algorithm
void Graphm::Kruskel(KruskElem *minTree)
{
    ParPtrTree A(n() + 1); //G等价类
    priority_queue<KruskElem> H;
    for (int i = 1; i < n() + 1; i++)
        for (int w = first(i); w < n() + 1; w = next(i, w))
        {
            H.push({i, w, weight(i, w)});
        }

    int numMST = 0;
    for (int i = 0; numMST < numVertex - 1; i++)
    {
        KruskElem temp;
        temp = H.top();
        H.pop();
        int v = temp.from;
        int u = temp.to;
        if (A.differ(v, u))
        {
            A.UNION(v, u);
            if (temp.from < temp.to)
            {
                minTree[numMST] = {temp.from, temp.to, temp.distance};
            }
            else
            {
                minTree[numMST] = {temp.to, temp.from, temp.distance};
            }
            numMST++;
        }
    }
}

//判断连通性
bool Graphm::existCircle()
{
    int *father = new int[n() + 1];
    int v = 1;
    if (numEdge >= numVertex)
    {
        //边数大于等于结点数，则必有环路
        return true;
    }
    else
    {
        return existCircleHelp(v, father); //边数小于节点数，利用BFS遍历
    }
}
bool Graphm::existCircleHelp(int v, int *father)
{
    setMark(v, VISITED);
    for (int w = first(v); w <= n(); w = next(v, w))
    {
        father[w] = v; //父节点传入参数
        if (getMark(w) == UNVISITED)
        {
            existCircleHelp(w, father);
        }
        else if (getMark(w) == VISITED && w != father[v])
        { //遇到一个VISITED结点，并且不是父节点，则有环路
            return true;
        }
    }
    return false;
}

//初始化
void init(Graphm *G)
{
    for (int i = 0; i < G->n() + 1; i++)
    {
        G->setMark(i, UNVISITED);
    }
    G->cnt = 0;
}


//main
int main()
{
    int n, e; // 结点数，边数
    int i;
    cin >> n >> e;
    int D[n];
    Graphm G(n);
    int a, b, wt;
    for (i = 0; i < e; i++)
    {
        cin >> a >> b >> wt;
        G.setEdge(a, b, wt);
    }
    //BFS
    G.BFS(1);
    cout << endl;
    //初始化
    init(&G);
    //DFS
    G.DFS(1);
    cout << endl;
    //最短路径
    G.Dijkstra();
    //最小生成树
    KruskElem *minTree = new KruskElem[n - 1]; //n-1为最小生成树的边集数！
    G.Kruskel(minTree);
    for (i = 0; i < n - 1; i++)
    {
        cout << minTree[i].from << " " << minTree[i].to << " " << minTree[i].distance << endl;
    }
    init(&G);
    //判断是否有回路
    if (G.existCircle())
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}
