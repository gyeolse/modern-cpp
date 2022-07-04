#include <iostream> 

class Int32 {
    int value;
public:
    Int32() : value(0) {}
    Int32(int n) : value(n) {}

    // const 붙여주기
    operator int() const { return value; }
};

int main() {
    int     pn;
    Int32 un;

    pn = un; // un.operator int() 

    un = pn; // pn.opeartor Int32() 가 있으면 될 텐데, 못 만듦.
    // 컴파일러는 1,2 를 체크한다. 
    // 1. un.operator = (pn) 대입 연산자가 있는지 확인함
    // 2. Int32(pn) default 대입 연산자로 
}