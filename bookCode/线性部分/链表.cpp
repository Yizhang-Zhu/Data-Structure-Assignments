//链表

#define defaultSize 100

#include<iostream>

template<typename E> class Link {
public:
	E element;
	Link* next;
	Link(const E& elemval, Link* nextval = nullptr) {
		element = elemval;
		next = nextval;
	}
	Link(Link* nextval = nullptr) { next = nextval; }
};

//链表的实现声明
template<typename E> class LList : public List<E> {
private:
	Link<E>* head;
	Link<E>* tail;
	Link<E>* curr;
	int cnt;//size of the list

	void init(){//initialization helper method
		curr = tail = head = new Link<E>;
	}

	void removeall(){
		while(head != nullptr){
			curr = head;
			head = head->next;
			delete curr;
		}
	}
public:
	LList(int size = defaultSize){init();}
	~LList(){removeall();}

	void print() const;

	void clear(){
		removeall();
		init();
	}

	//insert "it" at current position
	void insert(const E& it){
		curr->next = new Link<E>(it, curr->next);
		if(tail == curr) tail = curr->next;
		cnt++;
	}

	//append "it" to the list
	void append(const E& it){
		tail = tail->next;
		tail = new List<E>(it, nullptr);
	}

	//remonve and return current element
	E remove(){
		//Assert(curr->next != nullptr, "No elements");
		E it = 
	}
};