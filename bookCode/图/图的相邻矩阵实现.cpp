#define UNVISITED 0;
#define VISITED 1;


//ADT
class Graph{
private:
    void operator=(const Graph&) {}
    Graph(const Graph&) {}

public:
    Graph() {}
    virtual ~Graph() {}

    virtual void Init(int n) = 0;

    virtual int n() = 0;
    virtual int e() = 0;

    //返回v的第一个邻居
    virtual int first(int v) = 0;

    //返回v的下一个邻居
    virtual int next(int v, int w) = 0;

    virtual void setEdge(int v1, int v2, int wgt) = 0;

    virtual void delEdge(int v1, int v2) = 0;

    virtual bool isEdge(int v1, int v2) = 0;

    virtual int weight(int v1, int v2) = 0;

    virtual int getMark(int v) = 0;
    virtual int setMark(int v, int val) = 0;
};

//图的相邻矩阵实现
class Graphm:public Graph{
private:
    int numVertex, numEdge;
    int **matrix;
    int *mark;//mark是用来标记结点是否访问过的数组
public:
    Graphm(int numVertex){
        Init(numVertex);
    }
    ~Graphm(){
        delete [] mark;
        for(int i = 0; i<numVertex; i++){
            delete [] matrix[i];
        }
        delete [] matrix;
    }

    void Init(int n){
        numVertex = n;
        numEdge = 0;
        mark = new int[n];
        for(int i = 0; i<numVertex; i++){
            mark[i] = UNVISITED;
        }
        matrix = (int**) new int*[numVertex];
        for(int i = 0; i<numVertex; i++){
            matrix[i] = new int[numVertex];
        }
        for(int i = 0; i<numVertex; i++){
            for(int j = 0; j<numVertex; j++){
                matrix[i][j] = 0;
            }
        }
    }

    int n(){
        return numVertex;
    }

    int e(){
        return numEdge;
    }

    int first(int v){
        for(int i = 0; i<numEdge; i++){
            if(matrix[v][i] != 0){
                return i;
            }
        }
        return numVertex;//return n if none（正常下标只有0~n-1，返回n表示此顶点无邻居）
    }

    int next(int v, int w){
        for(int i = w+1; i<numVertex; i++){
            if(matrix[v][i] != 0){
                return i;
            }
        }
        return numVertex;
    }

    void setEdge(int v1, int v2, int wgt){
        if(matrix[v1][v2] == 0){
            numEdge++;
        }
        matrix[v1][v2] = wgt;
    }

    void delEdge(int v1, int v2){
        if(matrix[v1][v2] != 0){
            numEdge--;
        }
        matrix[v1][v2] = 0;
    }

    bool isEdge(int v1, int v2){
        return (matrix[v1][v2] != 0);
    }

    int weight(int v1, int v2){
        return matrix[v1][v2];
    }

    int getMark(int v){
        return mark[v];
    }

    int setMark(int v, int val){
        mark[v] = val;
    }
};