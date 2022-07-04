#include <iostream>

class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) { std::cout << "Point (int, int) " << std::endl; }
    ~Point() { std::cout << "~ Point()" << std::endl; }
};

// call by value
void f1(Point p1) {}

// call by reference
void f2(Point& p2) {}

Point pt(1, 2);

Point f3() {  // return by value. 
    return pt;
}

Point& f4() { // return by ref
    return pt;
}

Point& f5() {
    // Point pt(1,2); // 불가능. 
    return pt;
}

int main() {
    // Point pt(1, 2);

    f3();

    // f3().x = 10; // error. 임시객체 왼쪽에 올 수 없음. 
    f4().x = 10; // 에러안남. 임시객체 만드니까
    f1(pt);
    f2(pt);
}