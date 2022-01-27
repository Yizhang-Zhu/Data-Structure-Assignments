#include<iostream>

using namespace std;

//doubly linked list link node with freelist support
template <typename E> class Link{
private:
    static Link<E>* freelist;
public:
    E element;
    Link<E>* next;
    Link<E>* prev;
    //constructors
    Link(const E& it, Link<E>* prevp = nullptr, Link<E>* nextp = nullptr){
        element = it;
        prev = prevp;
        next = nextp;
    }
    Link(Link<E>* prevp = nullptr, Link<E>* nextp = nullptr){
        prev = prevp;
        next = nextp;
    }
    Link(const Link<E> &l){
        element = l.element;
        next = l.next;
        prev = l.prev;
    }
    //overloaded new operator
    void* operator new(size_t){
        if(freelist == nullptr) return ::new Link;
        Link<E>* temp = freelist;
        freelist = freelist->next;
        return temp;
    }
    //overloaded delete oprator
    void operator delete(void* ptr){
        ((Link<E>*)ptr)->next = freelist; // Put on freelist
        freelist = (Link<E>*)ptr;
    }
};

// The freelist head pointer is actually created here
template <typename E>
Link<E>* Link<E>::freelist = nullptr;

//doubly linked list
template <typename E> class LList{
private:
    Link<E>* head;
    Link<E>* tail;
    Link<E>* curr;
    int cnt;
    //initialization helper method
    void init(){
        curr = tail = head = new Link<E>;
        cnt = 0;
    }
    //return link nodes to free store
    void removeall(){
        while(head != nullptr){
            curr = head;
            head = head->next;
            delete curr;
        }
    }
public:
    LList(){
        init();
    }
    ~LList(){
        removeall();
    }
    void clear(){
        removeall();
        init();
    }
    void moveToStart(){
        curr = head;
    }
    void moveToEnd(){
        curr = tail;
    }
    void prev(){
        curr = curr->prev;
    }
    void next(){
        curr = curr->next;
    }
    void moveToPos(int pos){
        //Assert((pos>=0)&&(pos<=cnt), "Position out of range!");
        curr = head;
        for(int i = 0; i<pos; i++) curr = curr->next;
    }
    const E& getValue() const{
        //Assert(curr->next != NULL, "No value!");
        return curr->element;
    }
    //insert "it" at current position
    void insert(const E& it){
        curr = new Link<E>(it, curr, curr->next);
        if (tail == curr) tail = curr;
        cnt++;
    }
    //append "it" to the end of the list
    void append(const E& it){        
        tail->next = new Link<E>(it, tail, nullptr);
        tail = tail->next;
        cnt++;
    }
    //remove and return current element
    E remove() {
        // Assert(curr->next != NULL, "No element");
        E it = curr->element;
        Link<E>* temp = curr;
        if (curr == tail) {
            tail = curr->prev;
            tail->next = nullptr;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete temp;
        cnt--;
        return it;
    }
    //judge if the curr pointer at the start/end or not
    bool atStart() const{
        return (curr == head);
    }
    bool atEnd() const{
        return (curr == tail->next);
    }
    //return the length of the list
    int length() const{
        return cnt;
    }
};

//term of a polynomial
class term{
public:
    int c;//coefficient
    int e;//exponent
    term(){}
    term(int c, int e){
        this->c = c;
        this->e = e;
    }
};

//addition
void add(LList<term> &p1, LList<term> &p2, LList<term> &res_add) {
    p1.moveToStart();
    p1.next();
    p2.moveToStart();
    p2.next();
    while(!p1.atEnd() || !p2.atEnd()){
        //p1的指数大，或者p1还没遍历完，p2就遍历完了
        while((!p1.atEnd() && p2.atEnd()) or (!p1.atEnd() && !p2.atEnd() && p1.getValue().e > p2.getValue().e)){
            if(p1.getValue().c != 0){
                res_add.append(term(p1.getValue().c, p1.getValue().e));
            }
            p1.next();
        }
        //p2的指数大，或者p2还没遍历完，p1就遍历完了
        while((p1.atEnd() && !p2.atEnd()) or (!p1.atEnd() && !p2.atEnd() && p1.getValue().e < p2.getValue().e)){
            if(p2.getValue().c != 0){
                res_add.append(term(p2.getValue().c, p2.getValue().e));
            }
            p2.next();
        }
        //p1、p2的指数相同
        while(!p1.atEnd() && !p2.atEnd() && p1.getValue().e == p2.getValue().e){
            if(p1.getValue().c != 0 && p2.getValue().c != 0){
                res_add.append(term(p1.getValue().c + p2.getValue().c, p1.getValue().e));
            }
                p1.next();
                p2.next();
        }

    }
}

//multiplication
void mul(LList<term> &p1, LList<term> &p2, LList<term> &res_mul) {
    LList<term> mid_term; //存储中间项的系数和指数
    LList<term> mid_sum[999]; //存储每次求和后的结果
    int i = 0;
    p1.moveToStart();
    p1.next();
    p2.moveToStart();
    p2.next();
    while(!p1.atEnd()){
        i++;
        mid_term.clear();
        while(!p2.atEnd()){
            if(p1.getValue().c != 0 && p2.getValue().c != 0){
                mid_term.append(term(p1.getValue().c * p2.getValue().c, p1.getValue().e + p2.getValue().e));
            }
            p2.next();
        }
        add(mid_sum[i - 1], mid_term, mid_sum[i]);
        p1.next();
        p2.moveToStart();
        p2.next();
    }
    add(mid_sum[i], mid_sum[i+1], res_mul);
}

//print the list
void printlist(LList<term> &list){
    list.moveToStart();
    list.next();
    while(!list.atEnd()){
        cout << list.getValue().c<<" "<<list.getValue().e<<endl;
        list.next();
    }
}

//main
int main(){
    LList<term> p1;//polynomial no.1
    LList<term> p2;//polynomial no.2
    int n1, n2;//number of terms of 2 polynomials
    int a, b;
    cin>>n1>>n2;
    //read numbers into the program
    for(int i = 0; i<n1; i++){
        cin>>a>>b;
        p1.append(term(a,b));
    }
    for(int i = 0; i<n2; i++){
        cin>>a>>b;
        p2.append(term(a,b));
    }
    //addition
    LList<term> sum;//sum of 2 polynomials
    add(p1, p2, sum);
    cout<<sum.length()<<endl;
    printlist(sum);
    //multiplication
    LList<term> product;//product of 2 polynomials
    mul(p1, p2, product);
    cout<<product.length()<<endl;
    printlist(product);
}
