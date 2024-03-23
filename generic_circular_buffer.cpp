#include <vector>
#include <iostream>
#include <optional>
#include <iomanip>

/**
    definition: generic circular buffer
    TODOs:
    it is not thread-safe now
    print_data function prints only printable data, type which has insertion operator overload.
    godbolt link: https://godbolt.org/z/TPqdn5fn7
*/

template<typename T>
struct circular_buffer{

    private:
    int head_position = 0;
    int tail_position = 0;
    int capacity = 0;
    std::vector<T> buffer;

    public:
    circular_buffer(int capacity){
        buffer.reserve(capacity+1);
        this->capacity = capacity;
    }

    bool is_full(){
        if(tail_position == capacity){
            return head_position == 0; 
        }
        return tail_position+1 == head_position;
    }

    bool is_empty(){
        int diff = tail_position - head_position;
        return diff == 0; 
    }

    bool push(T data){
        if(!is_full()){
            buffer[tail_position%capacity] = data;
            tail_position = tail_position == capacity ? 0 : tail_position+1;
            return true;
        }
        return false;
    }

    std::optional<T> pop(){
        std::optional<T> data;
        if(!is_empty()){
            data = buffer[head_position%capacity];
            ++head_position;
            if(is_empty()) {
                head_position = tail_position = 0;
            }
        }
        return data;
    }

    void print_data(){
        std::cout << "\n*********** print data *********** \n";
        std::cout << "head: " << head_position << "\n";
        std::cout << "tail: " << tail_position << "\n";
        std::cout << "size: " << buffer.size() << "\n";
        std::cout << "capacity: " << capacity << "\n";
        for(auto index = 0; index < capacity; ++index){
            std::cout <<  buffer[index] << " ";
        }
        std::cout << "\n*********** print data *********** \n";
    }
};

int main() {
    circular_buffer<int> buffer{2};
    std::cout << "is empty: " << std::boolalpha << buffer.is_empty() << "\n\n";

    ///////////////////////////////////////////////////////////////////////////////////////
    std::cout << "push  " << std::boolalpha << buffer.push(100) << "\n";
    std::cout << "push  " << std::boolalpha << buffer.push(200) << "\n";
    std::cout << "push  " << std::boolalpha << buffer.push(300) << "\n";

    std::cout << "pop   " << std::boolalpha << buffer.pop().value_or(-1) << "\n";
    std::cout << "pop   " << std::boolalpha << buffer.pop().value_or(-1) << "\n";

    std::cout << "push  " << std::boolalpha << buffer.push(300) << "\n";
    std::cout << "push  " << std::boolalpha << buffer.push(400) << "\n";

    std::cout << "is full: " << std::boolalpha << buffer.is_full() << "\n";
    std::cout << "is empty: " << std::boolalpha << buffer.is_empty() << "\n\n";
    ///////////////////////////////////////////////////////////////////////////////////////

    buffer.print_data();

    return 0;
}