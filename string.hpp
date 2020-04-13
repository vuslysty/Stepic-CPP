
#ifndef STRING_HPP_
#define STRING_HPP_

#include <cstddef> // size_t
#include <stdexcept>

struct String {
	String(const char *str);
	String(size_t n, char c);
    String(const char *str, size_t i, size_t j);
	~String();

    String(const String &other);
    String &operator=(const String &other);

	void append(const String &other);

    operator const char*() const {
        return str;
    }

    class SubStr {
        const String *str;
        size_t i;

    public:
        SubStr(const String *str, size_t index) :
            str(str), i(index)   
        {}

        String operator[](size_t j) const {
            if (j >= this->i && j <= str->size) {
                return(String(str->str, this->i, j));
            } else {
                throw std::logic_error("Logic error");
            }
        }
    };

    SubStr operator[](size_t i) {

        if (i >= size)
            throw std::logic_error("Logic error");

        return SubStr(this, i);
    }

	size_t size;
	char *str;
};

#endif /* STRING_HPP_ */