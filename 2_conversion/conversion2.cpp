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