int main() {
    auto f1 = [](int a, int b) { return a + b;};

    // 임시 객체 (컴파일러가 만든 임시객체)
    // 임시객체.opeartor 함수포인터() (그안에 이런 함수포인터가 있음)
    int(*f2)(int, int) = [](int a, int b) { return a + b;};

}