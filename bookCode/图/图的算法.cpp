#define UNVISITED 0;
#define VISITED 1;
#define INF 99999;


//图的遍历 - DFS/BFS/拓扑排序
//图的遍历函数
void graphTraverse(Graph* G){
    int v;
    for(v = 0; v<G->n(); v++){
        G->setMark(v, UNVISITED);//初始化
    }
    for(v = 0; v<G->n(); v++){
        if(G->getMark(v) == UNVISITED){
            //doTraverse(G, v);//doTraverse调用次数正好等于连通分量个数,可以DFS/BFS....
            DFS(G, v);
        }
    }
}
//DFS - 栈
void DFS(Graph* G, int v){
    //previsit action
    G->setMark(v, VISITED);
    fot(int w = G->first(v); w<G->n(); w = G->next(v,w)){
        if(G->getMark(w) == UNVISITED){
            DFS(G,w);
        }
    }
    //postvisit action
}
//BFS - 队列
void BFS(Graph* G, int start, Queue<int>* Q){
    int v, w;
    Q->enqueue(start);
    G->setMark(start, VISITED);
    while(Q->length() != 0){
        v = Q->dequeue();
        //previsit action
        for(w = G->first(v); w < G->n(); w = G->next(v,w)){
            if(G->getMark(w) == UNVISITED){
                G->setMark(w, VISITED);
                Q->enqueue(w);
            }
        }
    }
}
//递归拓扑排序
void topsort(Graph* G){
    for(int i = 0; i<G->n(); i++){
        G->setMark(i, UNVISITED);//初始化
    }
    for(int i = 0; i<G->n(); i++){
        if(G->getMark(i) == UNVISITED){
            tophelp(G, i);
        }
    }
}
void tophelp(Graph* G, int v){
    G->setMark(v, VISITED);
    for(int w = G->first(v); w<G->n(); w = G->next(v, w)){
        if(G->getMark(w) == UNVISITED){
            tophelp(G, w);//其实就是DFS
        }
    }
    printout(v);//postvisit action: print out the vertex
}//注意，按照这个算法打印出来的顺序是颠倒的，反过来才是一个符合要求的拓扑排序
//基于队列的拓扑排序
void topsort(Graph* G, Queue<int>* Q){
    int count[G->n()];
    int v, w;
    for(v = 0; v<G->n(); v++){
        count[v] = 0;//初始化
    }
    for(v = 0; v<G->n(); v++){
        for(w = G->first(v); w<G->n(); w = next(v,w)){
            count[w]++;//in degree +1
        }
        for(v = 0; v<G->n(); v++){
            if(count[w] == 0){
                Q->enqueue(v);
            }
        }
        while(Q->length() != 0){
            v = Q->dequeue();
            printout(v);
            for(w = G->first(v); w<G->n(); w = next(v,w)){
                count[w]--;
                if(count[w] == 0){
                    Q->enqueue(w);
                }
            }
        }
    }
}


//最短路径 - Dijkstra算法
void Dijkstra(Graph* G, int *D, int s){
    int i, v, w;
    //初始化
    for(int i = 0; i<G->n(); i++){
        D[i] = INF;
    }
    D[0] = 0;
    for(int i = 0;i<G->n(); i++){
        v = minVertex(G, D);
        if(D[v] == INF) return;
        G->setMark(v, VISITED);
        for(w = G->first(v); w<G->n(); w = next(v, w)){
            if(D[w] > (D[v] + weight(v, w))){
                D[w] = D[v] + weight(v, w);
            }
        }
    }
}
int minVertex(Graph* G, int* D){
    int i;
    int v = -1;
    for(i = 0; i<G->n(); i++){
        if(G->getMark(i) == UNVISITED){
            v = i;
            break;
        }
    }
    for(i = 0; i<G->n(); i++){
        if((G->getMark(i) == UNVISITED) && (D[i] < D[v])){
            v = i;
        }
    }
    return v;
}

//利用优先队列实现Dijkstra算法
class DijkElem{
public:
    int vertex, distance;
    DijkElem(){vertex = -1; distance = -1;}
    DijkElem(int v, int d){vertex = v; distance = d;}
};
void Dijkstra(Graph* G, int *D, int s){
    int i, v, w;
    DijkElem temp;
    DijkElem E[G->e()];
    temp.distance = 0;
    temp.vertex = s;
    E[0] = temp;
    heap<DijkElem> H(E, 1, G->e());//建堆
    //初始化
    for(i = 0; i<G->n(); i++){
        D[i] = INF;
    }
    D[0] = 0;
    for(i = 0; i<G->n(); i++){
        do{
            if(H.size() == 0) return;
            temp = H.removefirst();
            v = temp.vertex;
        }while(G->getMark(v) == UNVISITED);
        G->setMark(v, VISITED);
        for(w = G->first(v); w<G->n(); w = G->next(v,w)){
            if(D[w] > D[v] + G->weight(v,w)){
                D[w] = D[v] + G->weight(v,w);
                temp.distance = D[w];
                temp.vertex = w;
                H.insert(temp);
            }
        }
    }
}




//最小生成树 - Prim算法/Kruskal算法
//Prim - 扩点法
void Prim(Grap* G, int *D, int s){
    int V[G->n()];
    int i, w;
    for(int i = 0; i<G->n(); i++){
        D[i] = INF;
    }
    D[0] = 0;
    fo(int i = 0; i<G->n(); i++){
        int v = minVertext(G, D);
        G->setMark(v, VISITED);
        if(v != s){
            AddEdgetoMST(V[v], v);
        }
        if(D[v] == INF) return;
        for(w = G->first(v); w<G->n(); w = G->next(v,w)){
            if(D[w] > G->weight(v,w)){
                D[w] = G->weight(v,w);
                V[w] = v; 
            }
        }
    }
}
//Prim(用优先队列来寻找最近的顶点)
void Prim(Graph* G, int *D, int s){
    int i, v, w;
    int V[G->n()];
    DijkElem temp;
    DijkElem E[G->e()];
    temp.distance = 0;
    temp.vertex = s;
    E[0] = temp;
    heap<DijkElem> H(E,1,G->e());
    for(int i = 0; i<G->n(); i++){
        D[i] = INF;
    }
    D[0] = 0;
    for(i = 0; i<G->n(); i++){
        do{
            if(H.size() == 0) return;
            temp = H.removefirst();
            v= temp.vertex;
        }while(G->getMark(v) == VISITED);
        G->setMark(v, VISITED);
        if(v != s) AddEdgetoMST(V[v], v);
        if(D[v] == INF) return;
        for(w = G->first(v); w<G->n(); w = G->next(v,w)){
            if(D[w] > G->weight(v,w)){
                D[w] = G->weight(v,w);
                V[w] = v;
                temp.distance = D[w];
                temp.vertex = w;
                H.insert(temp);
            }
        }
    }

}

//Kruskal - 用最小堆来实现按照权的大小顺序处理每一条边，用并查算法判断两个顶点是否属于同一个等价类
class KrusKElem{
public:
    int from, to, distance;
    KrusKElem() {from = -1; to = -1; distance = -1;}
    KrusKElem(int f, int t, int d){
        from = f;
        to = t;
        distance = d;
    }
};
void Kruskal(Graph* G){
    ParPtrTree A(G->n());//并查树
    KruskElem E[G->e()];
    int i;
    int edgecnt = 0;
    for(int i = 0; i<G->n(); i++){//0号顶点开始
        for(int w = G->first(w); w<G->n(); w = G->next(i,w)){//找i的邻居
            E[edgecnt].distance = G->weight(i,w);
            E[edgecnt].from = i;
            E[edgecnt].to = w;
        }
    }
    //edge堆化
    heap<KruskElem> H(E, edgecnt, edgecnt);
    int numMST = G->n();//初始化位n个等价类
    //合并等价类
    for(int i = 0; numMST>1; i++){
        KruskElem temp;
        temp = H.removefirst();//min
        int v = temp.from;
        int u = temp.to;
        if(A.differ(v,u)){
            //如果在不同的等价类
            A.UNION(v,u);//合并为同一个等价类
            AddEdgetoMST(temp.from, temp.to);
            numMST--;//合并后等价类数量-1                                                        
        }
    }
}