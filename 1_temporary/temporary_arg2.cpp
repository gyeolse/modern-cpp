#include <string>
#include <string_view>

void foo(const std::string& s) {}

// C++17 이상
void goo(std::string_view s) {}

int main() {

    // foo 를 호출 할 때, string temporary 임시 객체를 컴파일러가 생성한 후,
    // foo 에 전달해준다. 문자열의 복사본도 힙에 생성한다. 
    foo("Practice make perfect");

    // 문자열 주소, 문자열 길이만 받음. 복사본 생성 안하고, 가리키기만 함. 
    goo("Practive make perfect");
}