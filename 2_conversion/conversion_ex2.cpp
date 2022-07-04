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
// 좌변을 보고 우변으ㅟ 반환 타입을 자동으로 결정하는 기술. 
