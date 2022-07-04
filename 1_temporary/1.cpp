#include <iostream>

class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) { }
    void set(int a, int b) { x = a; y = b; }
};

int main() {
    Point pt(1, 2);
    pt.x = 10; // ok
    // Point(1,2).x = 10; // Temporary에서의 값 넣기 -> 불가능. 
    Point(1, 2).set(10, 20); // ok

    Point* p1 = &pt;
    Point* p2 = &Point(1, 2); // error

    Point& r1 = pt; // ok
    // Point& r2 = Point(1, 2); // error 

    // 상수 참조로는 가능하다. 
    const Point& r3 = Point(1, 2); // ok


    std::cout << "=======" << std::endl;
}