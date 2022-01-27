#include <iostream>

using namespace std;

//Swap 2 elements in a generic array
template <typename E>
inline void swap(E A[], int i, int j)
{
    E temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

//有理数类
class Rational
{

    //运算符重载
    friend bool operator<(const Rational &r1, const Rational &r2) { return r1.N * r2.D < r2.N * r1.D; }
    friend bool operator<=(const Rational &r1, const Rational &r2) { return r1.N * r2.D <= r2.N * r1.D; }
    friend bool operator>(const Rational &r1, const Rational &r2) { return r1.N * r2.D > r2.N * r1.D; }
    friend bool operator>=(const Rational &r1, const Rational &r2) { return r1.N * r2.D >= r2.N * r1.D; }
    friend bool operator==(const Rational &r1, const Rational &r2) { return r1.N * r2.D == r2.N * r1.D; }
    friend bool operator!=(const Rational &r1, const Rational &r2) { return r1.N * r2.D != r2.N * r1.D; }

public:
    int N; //分子
    int D; //分母， 要求大于0

    //寻找最大公约数
    int gcd(int x, int y)
    {
        if (y == 0)
        {
            return x;
        }
        else
        {
            return gcd(y, x % y);
        }
    }

    Rational()
    {
        N = 0;
        D = 1;
    } //default constructor

    Rational(int n)
    {
        N = n;
        D = 1;
    } //constructor for integer value

    Rational(int n, int d)
    {
        int divisor = gcd(n, d);
        N = n / divisor;
        D = d / divisor;
    } //normal constructor

    Rational(const Rational &r)
    {
        N = r.N;
        D = r.D;
    } //copy constructor

    Rational &operator=(const Rational &r)
    {
        N = r.N;
        D = r.D;
        return *this;
    } // assignment override
};

// Heap class
class heap
{
private:
    Rational *Heap; // Pointer to the heap array
    int maxsize;    // Maximum size of the heap
    int n;          // Number of elements now in the heap

    // Helper function to put element in its correct place
    void siftdown(int pos)
    {
        while (!isLeaf(pos))
        { // Stop if pos is a leaf
            int j = leftchild(pos);
            int rc = rightchild(pos);
            if ((rc < n) && Heap[rc] < Heap[j])
                j = rc; // Set j to greater child's value
            if (Heap[pos] < Heap[j])
                return; // Done
            swap(Heap, pos, j);
            pos = j; // Move down
        }
    }

    //siftup
    void siftup(int pos)
    {
        while (pos != 0 && (Heap[pos] < Heap[parent(pos)]))
        {
            swap(Heap, pos, parent(pos));
            pos = parent(pos);
        }
    }

public:
    heap(Rational *h, int num, int max) // Constructor
    {
        Heap = h;
        n = num;
        maxsize = max;
        buildHeap();
    }
    int size() const // Return current heap size
    {
        return n;
    }
    bool isLeaf(int pos) const // True if pos is a leaf
    {
        return (pos >= n / 2) && (pos < n);
    }
    int leftchild(int pos) const
    {
        return 2 * pos + 1;
    } // Return leftchild position
    int rightchild(int pos) const
    {
        return 2 * pos + 2;
    }                         // Return rightchild position
    int parent(int pos) const // Return parent position
    {
        return (pos - 1) / 2;
    }
    void buildHeap() // Heapify contents of Heap
    {
        for (int i = n / 2 - 1; i >= 0; i--)
            siftdown(i);
    }

    // Insert "it" into the heap
    void insert(const Rational &it)
    {
        //Assert(n < maxsize, "Heap is full");
        int curr = n++;
        Heap[curr] = it; // Start at end of heap
        // Now sift up until curr's parent > curr
        // while ((curr != 0) &&
        //        (Heap[curr] < Heap[parent(curr)]))
        // {
        //     swap(Heap, curr, parent(curr));
        //     curr = parent(curr);
        // }
        siftup(curr);
    }
    // Remove first value
    Rational removefirst()
    {
        //Assert(n > 0, "Heap is empty");
        swap(Heap, 0, --n); // Swap first with last value
        if (n != 0)
            siftdown(0); // Siftdown new root val
        return Heap[n];  // Return deleted value
    }

    // Remove and return element at specified position
    Rational remove(int pos)
    {
        //Assert((pos >= 0) && (pos < n), "Bad position");
        if (pos == (n - 1))
            n--; // Last element, no work to do
        else
        {
            swap(Heap, pos, --n); // Swap with last value
            while ((pos != 0) &&
                   (Heap[pos] < Heap[parent(pos)]))
            {
                swap(Heap, pos, parent(pos)); // Push up large key
                pos = parent(pos);
            }
            if (n != 0)
                siftdown(pos); // Push down small key
        }
        return Heap[n];
    }

    //打印分数的帮助函数 - 打印有理数堆
    void print_help(int i)
    {
        if (i >= 0 && i < maxsize)
        {
            if (Heap[i].D == 1)
            {
                cout << Heap[i].N << "  ";
            }
            else
            {
                cout << Heap[i].N << "/" << Heap[i].D << "  ";
            }
        }
    }

    //打印分数的帮助函数 - 打印排序后的有理数堆
    void print_help_sorted(Rational r)
    {
        //Rational r = H.removefirst();
        if (r.D == 1)
        {
            cout << r.N << "  ";
        }
        else
        {
            cout << r.N << "/" << r.D << "  ";
        }
    }
};

//main函数
int main()
{
    int t; //提示接下来要输入的t行

    cin >> t; //读入分子

    int n; //输入分子
    int d; //输入分母

    Rational r;        //有理数
    Rational rList[t]; //有理数列表

    for (int i = 0; i < t; i++)
    {
        cin >> n >> d;
        r = Rational(n, d);
        rList[i] = r;
    }

    heap rHeap(rList, t, t); //有理数堆
    //输出有理数堆
    for (int i = 0; i < t; i++)
    {
        rHeap.print_help(i);
    }

    cout << endl;

    //输出排序后的有理数堆
    for (int i = 0; i < t; i++)
    {
        Rational r = rHeap.removefirst();
        rHeap.print_help_sorted(r);
    }
}

/*
测试用例：

5
3  2
1  3
4  2
12  10
4  6


*/