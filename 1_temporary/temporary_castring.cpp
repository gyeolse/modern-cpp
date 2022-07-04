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
