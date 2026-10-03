#include <iostream>

using namespace std;

template <typename T>
class Vec {
    private:
        T* data;
        size_t count;
        size_t capacity;
    public:
        Vec() : data(nullptr, count(0), capacity(0)) {}
        Vec(size_t c) : data(new T[c], count(0), capacity(c)) {}
        ~Vec() {
            delete [] data;
        }

        size_t size() const { return count; }
        size_t cap() const { return capacity; }

        void push_back(const T& elem) {
            if (count == capacity){
                grow();
            }
            data[count] = elem;
            count++;
        }

        void grow() {
            size_t newcap = 1;
            if (capacity != 0) {
                newcap = capacity * 2;
            }
            reserve(newcap);
        }

        void reserve(size_t newcap) {
            cout << "reserve" << newcap << " " << capacity << endl;
            if(newcap <= capacity) {
                return;
            }
            cout << "Reservando memoria" << newcap << endl;
            int* newBlock = new int[newcap];
            for (size_t i = 0; i < count; i++) {
                newBlock[i] = data[i];
            }
            delete [] data;
            data = newBlock;
            capacity = newcap;
        }

        void insert(size_t i, const T& x) { // O(n - i): everything right of i shifts
            if (count == capacity) grow();
            for (size_t j = count; j > i; --j) data[j] = data[j - 1];
            data[i] = x;
            ++count;
        }

        void erase(size_t i) { // O(n - i)
            for (size_t j = i; j + 1 < count; ++j) data[j] = data[j + 1];
            --count;
        }
};



int main() {
    cout << "Vectors" << endl;
    Vec<int> x;
    Vec<double> y;
    for(int i = 0; i < 10; i++){
        x.push_back(10);
        y.push_back(i*3.1415);
    }
    cout << "elementos actuales" << x.size() << endl;
    cout << "elementos actuales" << y.size() << endl;
    //x.reserve(1000 + x.size());
    //for(int i = 0; i < 1000; i++){
    //    x.push_back(10);
    //    y.push_back(i*3.1415);
    //}
    //cout << "elementos finales" << x.size() << endl;
    //cout << "elementos finales" << y.size() << endl;

    //cout << y[100] << endl;

    cout << "elemento 5 en X " << x[5] << endl;

    x.insert(5);

    cout << "elemento 5 en X " << x[5] << endl;

    return 0;
}