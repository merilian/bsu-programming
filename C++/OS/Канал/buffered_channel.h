#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

template<class T>
class BufferedChannel {
 public:
    explicit BufferedChannel(int size) {}

    void Send(T value) {
    }

    std::pair<T, bool> Recv() {
    }

    void Close() {
    }

 private:
};

#endif // BUFFERED_CHANNEL_H_