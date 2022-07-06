# Modern C++

## Constructor

- 사용자가 생성자 호출 순서를 변경할 수 없다.
- 컴파일러가 생성한 코드는 항상 디폴트 생성자를 호출한다.

  - 기반 클래스나 멤버 데이터에 "디폴트 생성자가 없는 경우" 반드시 사용자가 디폴트가 아닌 "다른 생성자를 호출하는 코드를 작성" 해야 함.

- 멤버 데이터 생성자보다 기반 클래스의 생성자가 먼저불린다. 따라서 다음과 같은 경우에 초기화 시키지 않은 변수를 `Stream` class에 넣게 되는 문제가 발생할 수 있다.

```cpp
#include <iostream>

class Buffer {
public:
    Buffer(std::size_t sz) {
        std::cout << " init buffeer" << std::endl;
    }
    void use() {
        std::cout << "use buffer" << std::endl;
    }
};

// ------------초기화 되지 않는 범퍼를 쓰게됨
class StreamWithBuffer : public Stream {
    Buffer buf{ 1024 };
public:
    StreamWithBuffer() : Stream(buf) {}
};

class Stream {
public:
    Stream(Buffer& buf) { buf.use(); }
};

int main() {
    // Buffer buf(1024);
    // Stream s(buf);
    StreamWithBuffer swb;
}
```

해결책

- Buffer 를 멤버로 가진 별도의 기반 클래스를 설계한 후, 다중 상속을 실시한다.

```cpp
#include <iostream>

class Buffer {
public:
    Buffer(std::size_t sz) {
        std::cout << " init buffeer" << std::endl;
    }
    void use() {
        std::cout << "use buffer" << std::endl;
    }
};

class StreamWithBuffer : public StreamBuffer, public Stream {
public:
    StreamWithBuffer() : Stream(buf) {}
};

class Stream {
public:
    Stream(Buffer& buf) { buf.use(); }
};

// -------------------------
class StreamBuffer {
protected:
    Buffer buf{ 1024 };

};
int main() {
    // Buffer buf(1024);
    // Stream s(buf);
    StreamWithBuffer swb;
}
```

이 기술을 "Base From Member"라고 부른다.

- 생성자는 가상함수가 동작하지 않는다. Base 생성자에서 'vFunc' 호출 시 항상 Base의 vfunc() 함수가 호출된다.
  - Base() 함수에서 가상함수를 호출할 때, "초기화 되지 않은 data"를 사용하게 될 수 있으므로
