#include <iostream>
#include <cstddef>
#include <cstring>
#include <type_traits>

char *my_strdup(const char *s, size_t sz) {
    char *str;
    if (s) {
        str = new char[sz + 1];
        std::strcpy(str, s);
    } else {
        str = nullptr;
    }
    return str;
}

class String {
    size_t _size;
    char *_str;

    static bool log_output;

    void print_log(char * msg) {
        if (log_output)
            std::cout << msg << std::endl;
    }

public:
    String() : _size(0), _str(nullptr) { print_log("Default Constructor"); };
    String(char *s) : 
        _size(std::strlen(s)), _str(my_strdup(s, _size)) {
        print_log("1 element Constructor");
    }
    String(String const &src) : 
        _size(src._size), _str(my_strdup(src._str, _size)) {
        print_log("Copy Constructor");
    }
    String(String && src) : String() {
        print_log("Move Constructor");
        std::swap(_str, src._str);
        std::swap(_size, src._size);
    }

    // String(char * && s, size_t && sz) : String() {
    //     print_log("Move 2 elements Constructor");
    //     std::swap(_str, s);
    //     std::swap(_size, sz);
    // }

    String &operator=(String const &rhs) {
        print_log("Assing operator Copy");
        if (this != &rhs) {
            String copy(rhs);
            std::swap(_size, copy._size);
            std::swap(_str, copy._str);
        }
        return *this;
    }
    String &operator=(String && rhs) {
        print_log("Assing operator Move");
        std::swap(_size, rhs._size);
        std::swap(_str, rhs._str);
        return *this;
    }
    ~String() {
        print_log("Destructor");
        delete [] _str;
        _str = nullptr;
    }

    size_t size() const {
        return _size;
    }

    char *data() const {
        return _str;
    }

    static void turn_on_logs()  { log_output = true; }
    static void turn_off_logs() { log_output = false; }
    
};

bool String::log_output = false;

// String operator+(String const &str1, String const &str2) {
//     size_t new_size = str1.size() + str2.size();
//     char *new_str = my_strdup(str1.data(), new_size);
//     std::strcpy(new_str + str1.size(), str2.data());
//     return String(std::move(new_str), std::move(new_size));
// }

std::ostream &operator<<(std::ostream &o, String const &str)  {
    return o << str.data();
}

String getStr(String const &src) {
    String ret_val(src);
    return ret_val;
}

String && fun2(String & s)
{
    return std::move(s);
}

int main() {

    String::turn_on_logs();

    String a = "Hello";

    String b = fun2(a);

    std::cout << a << std::endl;



    return 0;
}