class Point {
    int x{ 0 };
    int y{ 0 };
public:
    void set(int a, int b) {
        x = a;
        y = b;
    }

    // static 멤버 함수들은 객체 없이 부를 수 있다. 일반적으로.
    // 객체의 주소가 전달되지 않는다. this call 이 안디ㅏ. 
    // 객체의 주소를 알 수 없기 때문에, x, y 에 접근이 불가능 했던 것.
    static void foo(int a) {
        x = a; // this->x = a 가 되어야하는데, this가 없다. error.
    }

};

int main() {
    Point pt1;
    Point pt2;

    pt1.set(10, 20);
    pt2.set(10, 20);

    // 객체없이 호출이 가능한데. 즉, 
    // 객체의 주소가 전달되지 않는다. this call 이 안디ㅏ. 
    // 객체의 주소를 알 수 없기 때문에, x, y 에 접근이 불가능 했던 것.
    Point::foo(10);
    pt1.foo(10);
}
