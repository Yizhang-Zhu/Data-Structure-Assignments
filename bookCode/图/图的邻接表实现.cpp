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

//边
class Edge{
    int vert, wt;
public:
    Edge(){
        vert = -1;
        wt = -1;
    }
    Edge(int v, int w){
        vert = v;
        wt = w;
    }
    //返回顶点编号
    int vertex(){
        return vert;
    }
    //返回权重
    int weight(){
        return wt;
    }
};

//图的邻接表实现
class Graphl:public Graph{
private:
    List<Edge>** vertex;
    int numVertex;
    int numEdge;
    int* mark;
public:
    Graphl(int numVertex){
        Init(numVertex);
    }
    ~Graphl(){
        delete [] mark;
        for(int i = 0; i<numVertex; i++){
            delete [] vertex[i];
        }
        delete [] vertex;
    }

    void Init(int n){
        numVertex = 0;
        numEdge = 0;
        mark = new int[n];
        for(int i = 0; i<numVertex; i++){
            mark[i] = UNVISITED;
        }
        vertex = (List<Edge>**) new List<Edge>* [numVertex];
        for(int = 0; i<numVertex; i++){
            vertex[i] = new LList<Edge>();
        }
    }

    int e(){
        return numEdge;
    }

    int n(){
        return numVertex;
    }

    int first(int v){
        if(vertex[v]->length() == 0){
            return numVertex;//no neighbor
        }
        vertex[v]->moveToStsrt();
        Edge it = vertex[v]->getValue();
        return it.vertex();
    }

    //············重要功能·························
    int next(int v, int w){
        Edge it;
        if(isEdge(v, w)){//调用i是Edge时除了判断是否为edge之外，返回的时候也会把currPos放在w处。之后的操作中currPos就正好在w后开始后移
            if((vertex[v]->currPos()+1) < vertex[v]->length()){
                vertex[v]->next();
                it = vertex[v]->getValue();
                return it.vertex();
            }
        }
        return n();
    }

    void setEdge(int i, int j, int weight){
        Edge currEdge(j, weight);
        if(isEdge(i, i)){
            vertex[i]->remove();
            vertex[i]->insert(currEdge);
        }else{
            numEdge++;
            for(vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next()){
                Edge temp = vertex[i]->getValue();
                if(temp.vertex() > j){
                    break;
                }
            }
            vertex[i]->insert(currEdge);
        }
    }

    void delEdge(int i, int j){
        if(isEdge(i, j)){
            vertex[i]->remove();
            numEdge--;
        }
    }

    bool isLeaf(int i, int j){
        Edge it;
        for(vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next){
            Edge temp = vertex[i]->getValue();
            if(temp.vertex() == j){
                return true;//注意！返回的时候currPos仍然保留在j结点位置
            }
        }
        return false;
    }

    int weight(int i, int j){
        Edge curr;
        if(isEdge(i, j)){
            curr = vertex[i]->getValue();
            return curr.weight();
        }else{
            return 0;
        }
    }
        
    int getMark(int v){
        return mark[v];
    }

    int setMark(int v, int val){
        mark[v] = val;
    }
};