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