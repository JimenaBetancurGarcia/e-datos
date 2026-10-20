#include <iostream>
//g++ -o taller vectors.cpp
using namespace std;

template <typename T>
class Vec {
    private:
        T* data;
        size_t count;
        size_t capacity;
    public:
        Vec() : data(nullptr), count(0), capacity(0) {}
        Vec(size_t c) : data(new T[c]), count(0), capacity(c) {}
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
            T* newBlock = new T[newcap];
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

        void erase_from_to(size_t from, size_t to) {
            for (size_t j = from; j + 1 < to; ++j) data[j] = data[j + 1];
            --count;
        }

        void pop_front() {
            erase(0);
        }

        void pop_back() {
            erase(count-1);
        }

        T& at (size_t i){ 
            return data[i];
        }

        T& front(){
            return data[0];
        }

        T& back(){
            return data[count - 1];
        }

        void replace(size_t i, T element){
            data[i] = element;
        }

        void replace_all(T oldValue, T newValue){
            for (size_t j = 0; j + 1 < count; ++j) {
                if(data[j] == oldValue) data[j] = newValue;
            }
        }

        int count(T element){
            int times = 0;
            for (size_t j = 0; j + 1 < count; ++j) {
                if(data[j] == element) times++;
            }
            return times;
        }

        void clear() {
            delete [] data;
            count = 0;
        }

        bool contains(T element){
            for (size_t j = 0; j + 1 < count; ++j) {
                if(data[j] == element) return true;
            }
            return false;
        }

        int find(T element){
            for (size_t j = 0; j + 1 < count; ++j) {
                if(data[j] == element) return j;
            }
            return -1;
        }

        void remove(T element){
            for (size_t j = 0; j + 1 < count; ++j) {
                if(data[j] == element) {
                    erase(j);
                    return;
                }
            }
        }

        void remove_all(T element){
            for (size_t j = 0; j + 1 < count; ++j) {
                if(data[j] == element) {
                    erase(j);
                }
            }
        }

        Vec<int> indices_of(T element){
            Vec<int> indices;
            for (size_t j = 0; j + 1 < count; ++j) {
                if(data[j] == element) {
                    indices.push_back(j);
                }
            }
            return indices;
        }

        void swap(size_t i, size_t j){
            if (i == j) return;
            if (i < count && j < count){
                T elementI = data[i];
                T elementJ = data[j];
                data[i] = elementJ;
                data[j] = elementI;
            }
        }

        void reverse(){
            
        }
};



int main() {
    cout << "Vectors" << endl;
    Vec<int> x;
    Vec<double> y;
    for(int i = 0; i < 10; i++){
        x.push_back(i);
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

    //cout << "elemento 5 en X " << x.at(5) << endl;

    cout << "primer elemento en X " << x.at(0) << endl;
    //x.pop_front();
    x.replace(0, 1800);
    
    cout << "primer elemento en X " << x.at(0) << endl;
    //x.insert(5,3);

    cout << "elemento 5 en X " << x.at(5) << endl;

    return 0;
}