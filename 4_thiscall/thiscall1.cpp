class Point {
    int x{ 0 };
    int y{ 0 };
public:
    void set(int a, int b) {
        x = a;
        y = b;
    }

    // 컴파일러는
    // void set(Point* this, int a, int b) 
    // this->x = a;
    // this->y = b;
};

// 1. 멤버 데이터는 객체당 한 개 씩 생성된다. 
// 2. 멤버 함수는 코드 메모리에 "한 개 만" 만들어져 있다.
//      객체가 여러개 생성되어도 멤버 함수는 한 개만 있다. 
//      멤버 함수 호출 시 객체의 주소가 같이 전달된다. this call 이라고 함. 

int main() {
    Point pt1;
    Point pt2;

    // 객체인 pt1도 인자인 것처럼 전달이 된다. 
    // 컴파일러가 set(&pt1, 10, 20); 이렇게
    pt1.set(10, 20);
    pt2.set(10, 20);
}
