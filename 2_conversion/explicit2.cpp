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

    m << 10; // 오류가 안남. error

    // if문에서는 사용될 수 있다 .
    if (m) {

    }
}