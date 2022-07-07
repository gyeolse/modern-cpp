# Modern C++

## 4. This call

### `this call` 이란

멤버 데이터는 객체당 한 개 씩 생성된다.
멤버 함수는 코드 메모리에 "한 개 만" 만들어져 있다.
멤버 함수 호출 시 객체의 주소가 같이 전달된다. 이것을 _this call_ 이라고 부른다.

```cpp
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

int main() {
    Point pt1;
    Point pt2;

    // 객체인 pt1도 인자인 것처럼 전달이 된다.
    // 컴파일러가 set(&pt1, 10, 20); 이렇게
    pt1.set(10, 20);
    pt2.set(10, 20);
```

### `static` function 일 경우,

`static` 멤버 함수들은 객체 없이 호출이 가능하다. 때문에 객체의 주소가 전달이 될 수 없다. 그러므로, `this call`이 불가능하다. 객체 주소를 알 수 없으므로, 당연히 x, y 접근도 불가능하다.

```cpp
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

```
