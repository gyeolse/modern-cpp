# Modern C++

## 1. Temporary

Temporary 는 임시 객체를 뜻한다.

#### named object VS unnamed object

- named object : 자신을 선언한 블록을 벗어날 때 파괴
- unnamed object : 자신을 선언한 문장의 끝에서 파괴. **"임시 객체"**

```c++
// 예제 1
#include <iostream>

class Point {
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) { std::cout << "Point (int, int)" << std::endl; }
    ~Point()
};

int main() {
    Point pt(1, 2); //named object
    Point (1,2);  //unnamed object

    std::cout << "=======" << std::endl;
}
```

#### Temporary 의 특징

- 등호에 왼쪽에 놓을 수 없다. `temporary` 는 **rvalue** 이다.
- 상수는 아니고, 멤버 함수를 호출할 수 있다. (`setter` 호출은 가능함)
- 주소 연산자로 주소를 구할 수 없다. 생성자에서 `this`를 사용할 순 있다.
- temporary 와 reference. 첫번째, 두번째는 기억해두자
  - `Point& r = Point(1, 2); //error`
  - `const Point& r = Point(1, 2); //ok `
  - `Point&& r = Point(1,2); // ok, C++11`

```c++
// 예제 2
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
    Point& r2 = Point(1, 2); // error

    // 상수 참조로는 가능하다.
    const Point& r3 = Point(1, 2); // ok


    std::cout << "=======" << std::endl;
}
```

#### Temporary 와 함수 인자

- 객체를 함수 인자로만 사용한다면, temporary 로 전달하는게 효율적일 수 있음.
- 이 때 반드시 `const Point&` 로 받아야 한다.

​

#### Temporary 와 함수 반환값

- 함수가 객체를 값으로 반환하는 경우, return용 임시객체가 생성된 후 반환됨.
- 즉, return by value일 경우, 리턴용 임시객체 생성. return by reference일 경우, 리턴용 임시객체가 생성되지 않음.
- **단, 지역변수로 만들어진 객체는 절대 참조 반환 하면 안됨.**

#### Temporary castring

```cpp
#include <iostream>

struct Base {
    int value = 10;
};

struct Derived : public Base {
    int value = 20;
};

int main() {
    Derived d;
    std::cout << d.value << std::endl; // 20
    // Base 로 생각하게
    std::cout << static_cast<Base&>(d).value << std::endl; // 10

    // 값으로 캐스팅한다면? 그래도 잘 나옴. 값으로 캐스팅한다면 임시객체 만듦.
    // Base 타입의 임시객체 생성 후, temporary의 value에 접근.
    std::cout << static_cast<Base>(d).value << std::endl; // 10

    // 그래서,
    static_cast<Base&>(d).value = 100; // ok
    static_cast<Base>(d).value = 100; // error
}
```

#### 요약

- 사용자가 명시적으로 만드는 경우가 있다.
  - 함수 인자로 객체를 전달할 때
    `foo (point (1,2));`
- 컴파일러에 의해 생성될 때도 있다.
  - 함수 인자로 객체가 아닌 생성자 인자로 전달할 때
  - 함수가 값으로 객체를 반환할 때
  - 객체를 값으로 캐스팅 할 때
