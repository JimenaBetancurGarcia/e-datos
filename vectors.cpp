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

        void insert(size_t i, const T& x) {
            if (count == capacity) grow();
            for (size_t j = count; j > i; --j) data[j] = data[j - 1];
            data[i] = x;
            ++count;
        }

        void erase(size_t i) {
            if (i >= count) return;
            for (size_t j = i; j + 1 < count; ++j) data[j] = data[j + 1];
            --count;
        }

        void erase_from_to(size_t from, size_t to) {
            if (from > to || to > count) return;
            size_t k = to - from;
            for (size_t j = to; j < count; ++j) data[j - k] = data[j];
            count -= k;
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
            if (i >= count) {
                return;
            }
            data[i] = element;
        }

        void replace_all(T oldValue, T newValue){
            for (size_t j = 0; j < count; ++j) {
                if(data[j] == oldValue) data[j] = newValue;
            }
        }

        int count_element(T element){
            int times = 0;
            for (size_t j = 0; j < count; ++j) {
                if(data[j] == element) times++;
            }
            return times;
        }

        void clear() {
            count = 0;
        }

        bool contains(T& element) const { return find(element) != -1; }

        int find(T element){
            for (size_t j = 0; j < count; ++j) {
                if(data[j] == element) return j;
            }
            return -1;
        }

        void remove(T element){
            for (size_t j = 0; j < count; ++j) {
                if(data[j] == element) {
                    erase(j);
                    return;
                }
            }
        }

        void remove_all(T element){
            size_t w = 0;
            for (size_t j = 0; j < count; ++j) {
                if (!(data[j] == element)) {
                    data[w] = data[j];
                    w++;
                }
            }
            count = w;
        }

        Vec<int> indices_of(T element){
            Vec<int> indices;
            for (size_t j = 0; j < count; ++j) {
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

        void reverse()
        {
            if (count < 2) return;
            size_t i = 0, j = count - 1;
            while (i < j)
            {
                swap(i, j);
                i++;
                j--;
            }
        }

        void reverse_range(size_t from, size_t to) {
            if (from >= to || to > count) return;
            size_t i = from;
            size_t j = to - 1;
            while (i < j) {
                swap(i, j);
                i++;
                j--;
            }
        }

        void rotate_left(size_t k) {
            if (count == 0) return;
            k = k % count;
            if (k == 0) return;
            reverse_range(0, k);
            reverse_range(k, count);
            reverse_range(0, count);
        }

        void rotate_right(size_t k) {
            if (count == 0) return;
            k = k % count;
            if (k == 0) return;
            rotate_left(count - k);
        }

        void sort() {
            if (count < 2) return;
            quick_sort(0, (int)count - 1);
        }
 
        void quick_sort(int low, int high) {
            if (low >= high) return;
            int p = partition(low, high);
            quick_sort(low, p - 1);
            quick_sort(p + 1, high);
        }

        int partition(int low, int high) {
            T pivot = data[high];
            int i = low;
            for (int j = low; j < high; j++) {
                if (data[j] < pivot) {
                    swap(i, j);
                    i++;
                }
            }
            swap(i, high);
            return i;
        }

        void append(const Vec<T>& other) {
            size_t n = other.count;
            reserve(count + n);
            for (size_t i = 0; i < n; i++) {
                push_back(other.data[i]);
            }
        }

        Vec<T> slice(size_t from, size_t to) const {
            Vec<T> result;
            if (from > to || to > count) return result;
            for (size_t i = from; i < to; i++) {
                result.push_back(data[i]);
            }
            return result;
        }
};


template <typename T>
void mostrar(Vec<T>& v) {
    cout << "{";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v.at(i);
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << "}  size: " << v.size() << " cap: " << v.cap() << endl;
}
 
void prueba_1_1() {
    cout << "--- 1.1 Operaciones basicas ---" << endl;
    Vec<int> v;
    for (int i = 1; i <= 10; i++) v.push_back(i);
    mostrar(v);                     
    v.pop_front();
    v.pop_back();
    mostrar(v);                     
    v.insert(2, 99);
    mostrar(v);                     
}
 
void prueba_1_2() {
    cout << "--- 1.2 Metodos de acceso ---" << endl;
    Vec<int> v;
    v.push_back(5); v.push_back(10); v.push_back(15); v.push_back(20); v.push_back(25);
    cout << "front: " << v.front() << endl;   
    cout << "back: " << v.back() << endl;     
    cout << "at(2): " << v.at(2) << endl;     
    v[1] = 100;
    mostrar(v);                     
}
 
void prueba_1_3() {
    cout << "--- 1.3 Strings ---" << endl;
    Vec<string> v;
    v.push_back("the"); v.push_back("quick"); v.push_back("brown");
    v.push_back("fox"); v.push_back("jumps");
    mostrar(v);                     
    v.pop_front();
    v.pop_back();
    mostrar(v);                     
    v.insert(2, "lazy");
    mostrar(v);                     
}
 
void prueba_erase() {
    cout << "--- 2.1 erase(pos) ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(40);
    v.erase(1);
    mostrar(v);                     
    v.erase(2);                     
    mostrar(v);                     
    v.erase(10);                    
    mostrar(v);                     
}
 
void prueba_erase_from_to() {
    cout << "--- 2.2 erase(from, to) ---" << endl;
    Vec<int> v;
    for (int i = 0; i <= 50; i += 10) v.push_back(i);
    mostrar(v);                     
    v.erase_from_to(1, 4);
    mostrar(v);                     
    v.erase_from_to(1, 1);          
    mostrar(v);                     
    v.erase_from_to(0, v.size());   
    mostrar(v);                     
}
 
void prueba_clear() {
    cout << "--- 2.3 clear ---" << endl;
    Vec<int> v;
    for (int i = 1; i <= 5; i++) v.push_back(i);
    mostrar(v);                     
    v.clear();
    mostrar(v);                     
    v.push_back(7);                 
    mostrar(v);                     
}
 
void prueba_contains() {
    cout << "--- 2.4 contains ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30);
    cout << "contains(10): " << (v.contains(10) ? "true" : "false") << endl;  
    cout << "contains(30): " << (v.contains(30) ? "true" : "false") << endl;  
    cout << "contains(99): " << (v.contains(99) ? "true" : "false") << endl;  
}
 
void prueba_find() {
    cout << "--- 2.5 find ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(20);
    cout << "find(20): " << v.find(20) << endl;   
    cout << "find(10): " << v.find(10) << endl;   
    cout << "find(30): " << v.find(30) << endl;   
    cout << "find(99): " << v.find(99) << endl;   
}
 
void prueba_remove() {
    cout << "--- 2.6 remove ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(20);
    v.remove(20);
    mostrar(v);                     
    v.remove(99);                   
    mostrar(v);                     
    v.remove(20);                   
    mostrar(v);                     
}
 
void prueba_replace() {
    cout << "--- 2.7 replace ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(20);
    
    v.replace(2, 99);
    mostrar(v);                     
    v.replace(5, 100);               
    mostrar(v);                     
}
 
void prueba_remove_all() {
    cout << "--- 2.8 remove_all ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(20); v.push_back(20);
    v.remove_all(20);
    mostrar(v);                     
    v.remove_all(99);               
    mostrar(v);                     
    Vec<int> w;                     
    w.push_back(5); w.push_back(5); w.push_back(1); w.push_back(5);
    w.remove_all(5);
    mostrar(w);                     
}
 
void prueba_replace_all() {
    cout << "--- 2.9 replace_all ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(20); v.push_back(20);
    v.replace_all(20, 99);
    mostrar(v);                     
    v.replace_all(55, 0);           
    mostrar(v);                     
}
 
void prueba_count() {
    cout << "--- 2.10 count ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(20); v.push_back(20);
    cout << "count(20): " << v.count_element(20) << endl;   
    cout << "count(10): " << v.count_element(10) << endl;   
    cout << "count(99): " << v.count_element(99) << endl;   
}
 
void prueba_indices_of() {
    cout << "--- 2.11 indices_of ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(20); v.push_back(20);
    Vec<int> idx = v.indices_of(20);
    mostrar(idx);                   
    Vec<int> idx2 = v.indices_of(99);
    mostrar(idx2);                  
    mostrar(v);                     
}
 
void prueba_swap() {
    cout << "--- 2.12 swap ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(40);
    v.swap(0, 3);
    mostrar(v);                     
    v.swap(1, 1);                   
    mostrar(v);                     
    v.swap(0, 10);                  
    mostrar(v);                     
}
 
void prueba_reverse() {
    cout << "--- 2.13 reverse ---" << endl;
    Vec<int> v;                     
    for (int i = 1; i <= 5; i++) v.push_back(i);
    v.reverse();
    mostrar(v);                     
    Vec<int> w;                     
    for (int i = 1; i <= 4; i++) w.push_back(i);
    w.reverse();
    mostrar(w);                     
    Vec<int> u;                     
    u.push_back(7);
    u.reverse();
    mostrar(u);                     
}
 
void prueba_rotate_left() {
    cout << "--- 2.14 rotate_left ---" << endl;
    Vec<int> v;
    for (int i = 1; i <= 5; i++) v.push_back(i);
    v.rotate_left(2);
    mostrar(v);                     
    v.rotate_left(5);               
    mostrar(v);                     
    v.rotate_left(7);               
    mostrar(v);                     
}
 
void prueba_rotate_right() {
    cout << "--- 2.15 rotate_right ---" << endl;
    Vec<int> v;
    for (int i = 1; i <= 5; i++) v.push_back(i);
    v.rotate_right(2);
    mostrar(v);                     
    v.rotate_right(5);              
    mostrar(v);                     
    Vec<int> vacio;
    vacio.rotate_right(3);      
    mostrar(vacio);               
}
 
void prueba_sort() {
    cout << "--- 2.16 sort ---" << endl;
    Vec<int> a;                    
    a.push_back(5); a.push_back(1); a.push_back(4); a.push_back(2); a.push_back(3);
    a.sort();
    mostrar(a);         
    Vec<int> b;
    for (int i = 1; i <= 5; i++) b.push_back(i);
    b.sort();
    mostrar(b);         
    Vec<int> c;       
    for (int i = 5; i >= 1; i--) c.push_back(i);
    c.sort();
    mostrar(c);         
    Vec<int> d;        
    d.push_back(3); d.push_back(1); d.push_back(3); d.push_back(2); d.push_back(1);
    d.sort();
    mostrar(d);           
    Vec<int> e;       
    e.push_back(7);
    e.sort();
    mostrar(e);
}
 
void prueba_append() {
    cout << "--- 2.17 append ---" << endl;
    Vec<int> a, b;
    a.push_back(1); a.push_back(2); a.push_back(3);
    b.push_back(4); b.push_back(5);
    a.append(b);
    mostrar(a);
    mostrar(b);
    b.append(b);
    mostrar(b);
}
 
void prueba_slice() {
    cout << "--- 2.18 slice ---" << endl;
    Vec<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(40); v.push_back(50);
    Vec<int> s = v.slice(1, 4);
    mostrar(s);
    mostrar(v);
    Vec<int> s2 = v.slice(2, 2);
    mostrar(s2);
}
 
void prueba_asignacion() {
    cout << "--- 2.19 operator= ---" << endl;
    Vec<int> a, b;
    a.push_back(1); a.push_back(2); a.push_back(3);
    b.push_back(9);
    b = a;
    mostrar(b);
    a.at(0) = 100;
    mostrar(a);
    mostrar(b);
    a = a;
    mostrar(a);
}
 
int main() {
    
    // prueba_1_1();
    // prueba_1_2();
    // prueba_1_3();
    // prueba_erase();
    // prueba_erase_from_to();
    // prueba_clear();
    // prueba_contains();
    // prueba_find();
    // prueba_remove();
    // prueba_replace();
    // prueba_remove_all();
    // prueba_replace_all();
    // prueba_count();
    // prueba_indices_of();
    // prueba_swap();
    // prueba_reverse();
    // prueba_rotate_left();
    // prueba_rotate_right();
    // prueba_sort();
    // prueba_append();
    // prueba_slice();
    // prueba_asignacion();
 
    return 0;
}
