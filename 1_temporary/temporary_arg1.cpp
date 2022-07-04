#include <iostream>

class Point {
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) { std::cout << "Point (int, int) " << std::endl; }
    ~Point() { std::cout << "~ Point()" << std::endl; }
};

void foo(const Point& pt) { std::cout << "foo" << std::endl; }

int main() {
    // 1. 이와 같은 방법으로 하면, 지역 변수이기 때문에 블럭이 지나갈 때까지 사라지지 않는다. 
    // Point pt(1, 2); // 지역 변수. 
    // foo(pt);

    // 2. 임시 객체를 받아오도록
    foo(Point(1, 2)); // 또는 foo ( Point {1,2})

    // 3. 이와 같이 사용도 할 수 있음. 
    foo({ 1,2 }); // foo (  Point { 1, 2 });

    std::cout << "=======" << std::endl;
}