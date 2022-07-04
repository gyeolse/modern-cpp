#include <iostream>

class Counter {
    int count{ 0 };
public:
    Counter& increment() {
        // Counter increment() {
        ++count;
        return *this; // 자기 자신 return 근데, 값으로 return. 
        // 복사본을 만들겠지. 그거에 대해서 복사본이 2가 되고, 
        // 다시 return 하면 복사본이 3 이됨. 
        // 결국 복사본은 파괴됨.
    }
    int get() const { return count; }
};

int main() {
    Counter c;
    c.increment().increment().increment();

    // 결론적으로 Counter 로 반환하면 값은 1일 것임. 
    // 3이 나오게 하려면 참조변환으로 바꿔야함. 
    std::cout << c.get() << std::endl;

}