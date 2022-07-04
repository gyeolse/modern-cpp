# Modern C++

## 2. Conversion

### 변환 연산자

객체가 다른 타입으로 변환될 때 호출되는 함수. 이미 이름에 반환 타입이 포함되어 있으니, 반환 타입은 표기하지 않음.

```c++
// 상수 멤버 함수로 만드는 경우가 많음.
operator TYPE() const {
	return value;
}

// example
operator int() const {
	return value;
}
```

### 변환 연산자 vs 변환 생성자

- pn = un;
  - `un.operator int();`
  - **변환 연산자.** 객체(Int32) -> int 로 변환될 때
- un = pn;
  - `pn.operator Int32()`는 만들 수 없으므로
    - 대입 연산자, `un.operator=(int)` 를 만들거나
    - **변환 생성자,** Int32(pn) 을 만들면 된다.

```c++
#include <iostream>

class Int32 {
    int value;
public:
    Int32() : value(0) {}

    // default 변환
    Int32(int n) : value(n) {}

    // const (상수 멤버 함수로 만드는 경우가 많이 있음.)
    operator int() const { return value; }
};

int main() {
    int     pn; // primitive
    Int32 un; // user

    pn = un; // un.operator int()

    un = pn; // pn.opeartor Int32() 가 있으면 될 텐데, 못 만듦.
    // 컴파일러는 1,2 를 체크한다.
    // 1. un.operator = (pn) 대입 연산자가 있는지 확인함
    // 2. Int32(pn) 변환 생성자.
}
```

### 변환 생성자

`Int32 n2 = 3;` -> `Int32 n2 = Int32(3);` 결국 이렇게 변환된다.

- ~ C++14
  - 인자가 한 개인 생성자를 사용해서, Int32 임시 객체 생성
  - 생성된 임시 객체를 '복사 생성자' 또는 'move 생성자'를 사용해서 n2에 복사
- C++17 이후
  - 임시 객체 생성 안하고, 인자 한 개인 생성자 호출함.

```c++
#include <iostream>

class Int32 {
    int value;
public:
    Int32(int n) : value(n) {}
};

int main() {
    Int32 n1(3);
    Int32 n2 = 3; // -> Int32 n2 = Int32(3);
    Int32 n3{ 3 }; // direct initialition
    Int32 n4 = { 3 };

    // 변환의 용도
    // n1 = Int32(3); 을 뜻함.
    // 인자가 한 개인 생성자를 사용해서 Int32 임시객체 생성
    // 생성된 임시 객체를 디폴트 대입 연산자를 사용해서 n1에 대입
    // 디폴트 대입 연산자가 삭제된 경우, 컴파일 에러 발생
    // Int32& operator = (const Int32&) = delete
    n1 = 3;
}
```

### explicit 생성자

논리적으로 맞을 때, 맞지 않을 때를 골라서 사용해 주어야 한다. 생성자가 암시적 변환의 용도로 사용될 수 없도록 함. 직접 초기화만 가능하고, 복사 초기화가 불가능함.

`void f1(Int32 n) {} ` 일 때와, `void f2(Vector v) {} ` 일 때, f1(3)을 호출 한다면 전자는 `explicit`을 붙일 필요가 없을 거고, 후자는 붙이는게 맞을 것임.

```cpp
class Vector {
public:

    // 생성자가 암시적 변환의 용도로 사용될 수 없도록 함.
    // 직접 초기화만 가능 복사 초기화 사용 불가능
    explicit Vector(int size) {}
};

void foo(Vector v) {}

int main() {
    Vector v1(3);
    Vector v2 = 3; // error
    Vector v3{ 3 };
    Vector v4 = { 3 }; // error

    v1 = 3; // error

    foo(3); // error
}
```

opeartor bool 을 제공하면, 객체의 유효성을 if 문으로 조사가 가능하게 된다. 변환 연산자에 `explicit` 붙이는 것이 허용된다. 즉,

`explicit operator bool() { return state;} ` 와 같이 사용하는 것이 가능하다. bool 로의 암시적 변환은 허용되지 않아, safe bool 이라고 불린다.

```c++
#include <iostream>

class Machine {
    int data = 10;
    bool state = true;
public:

    // operator bool을 제공하면, 객체의 유효성 if 문으로 조사 가능.
    // 변환 연산자에 explicit 붙이는게 허용
    // bool 로의 암시적 변환은 허용되지 않음.
    // safe bool 이라고 부름.
    explicit operator bool() { return state; }
};

int main() {
    Machine m;

    bool b1 = m; // error
    bool b2 = static_cast<bool>(m); // ok 명시적 변환임.

    m << 10; // error

    // if문에서는 사용될 수 있다 .
    if (m) {

    }
}
```

c++20 부터는 다음과 같이 explicit 뒤에 조사식을 넣는 것이 가능하다. 상황에 따라, explicit 을 선택할 수 있도록 할 수 있다.

```c++
#include <iostream>
#include <type_traits>

template<class T>
class Number {
    T value;
public:

    // explicit (false) : explicit 이 아니다.
    // explicit( 조사식 ) 넣기 가능.
    // 정수일 때 , 아닐 때 true/ false 반환가능
    // explicit(!std::is_integral_v<T>)
    explicit(!std::is_integral_v<T>) Number(T v) : value(v) {}
    // explicit(false) Number(T v) : value(v) {}
};

int main() {
    Number n1 = 10;
    Number n2 = 3.4;
}
```

nullptr 구현. int* 와 char* 을 params로 받아야하는데 nullptr이 옴. 변환 생성자가 필요하고, template 화 시켜서 다음과 같이 선언 하면 됨.

```c++
void foo(int* p) {}
void goo(char* p) {}

struct nullptr_t {
    template<class T>
    constexpr operator T* const () { return 0; }
};

nullptr_t xnullptr;

int main() {
    foo(xnullptr); // xnullptr.operator int*()
    goo(xnullptr);
}

// nullptr 의 타입 std::nullptr_t
```

**return type resolver.**

좌변을 보고, 우변의 타입을 자동으로 결정하는 기술.

```c++
#include <iostream>

// template<class T>
// T* Alloc(std::size_t sz) {
//     return new T[sz];
// }


struct Alloc {
    std::size_t size;

    Alloc(std::size_t sz) : size(sz) {}

    // operator int* () { return new int[size]; }

    // template화 시키자
    template<class T>
    operator T* () { return new T[size]; }
};

int main() {

    // type 을 생략해보기
    // int* p1 = Alloc<int>(10);
    // double* p2 = Alloc<double>(10);

    int* p1 = Alloc(10); // 임시객체.operator int*()
    double* p2 = Alloc(10);
}

// return type resolver
// 좌변을 보고 우변의 반환 타입을 자동으로 결정하는 기술.

```

람다 함수에서의 변환 생성자

```c++
int main() {
    auto f1 = [](int a, int b) { return a + b;};

    // 임시 객체 (컴파일러가 만든 임시객체)
    // 임시객체.opeartor 함수포인터() (그안에 이런 함수포인터가 있음)
    int(*f2)(int, int) = [](int a, int b) { return a + b;};

}
```
