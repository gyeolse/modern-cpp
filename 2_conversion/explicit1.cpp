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