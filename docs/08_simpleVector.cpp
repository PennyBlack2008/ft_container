// https://www.crocus.co.kr/1141

class vector
{
public:
    int capacity, sz;
    int* vc;

    vector()
    {
        capacity = 8;
        sz = 0;
        vc = new int[capacity];
    }
    ~vector() { delete[] vc; }
    void push_back(int val)
    {
        if (capacity == sz)
        {
            capacity *= 2;
            int* tmp = new int[capacity];
            for (int i = 0; i < sz; i++)
                tmp[i] = vc[i];
            delete[]  vc;
            vc = tmp;
        }
        vc[sz++] = val;
    }
    int size() { return sz; }
    bool empty() { return !sz; }
    void clear() { sz = 0; }
    int& operator[](int i) { return vc[i]; }
};