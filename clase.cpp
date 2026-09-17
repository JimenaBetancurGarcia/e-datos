/*

Para compilar:
g++ -o clases clase.cpp
Para ejecutar:
./clases


*/
#include <iostream>

using namespace std;

class Point {
private:
    int x;
    int y;
public:
    Point (int px, int py) : x (px), y(py) {}
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

int main () {
    Point p (3, 7);
    p.move(1, 1 );
    cout << "Jimena" <<  endl;
}