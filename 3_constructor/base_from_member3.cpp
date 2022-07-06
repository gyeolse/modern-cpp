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