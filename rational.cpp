#include <iostream>

struct Rational {
    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) {
        trace(__FUNCTION__);
    };

    void add(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void sub(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void mul(Rational rational) {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
    }

    void div(Rational rational) {
        numerator_ *= rational.denominator_;
        denominator_ *= rational.numerator_;
    }

    void neg() {
        numerator_ = -numerator_;
    }

    void inv() {}

    double to_double() const {
        return numerator_ / (double) denominator_;
    }

    int get_numerator() const { return numerator_; }
    int get_denominator() const { return denominator_; }

    Rational(Rational const &src) {
        trace(__FUNCTION__);
        *this = src;
    }

    Rational &operator=(Rational const &rhs) {
        trace(__FUNCTION__);
        if (this != &rhs) {
            this->numerator_ = rhs.numerator_;
            this->denominator_ = rhs.denominator_;
        }
        return *this;
    }

    Rational &operator+=(Rational rational) {
        trace(__FUNCTION__);
        add(rational);
        return *this;
    }
    
    Rational &operator-=(Rational rational) {
        trace(__FUNCTION__);
        sub(rational);
        return *this;
    }

    Rational &operator*=(Rational rational) {
        trace(__FUNCTION__);
        mul(rational);
        return *this;
    }

    Rational &operator/=(Rational rational) {
        trace(__FUNCTION__);
        div(rational);
        return *this;
    }

    Rational operator+() const {
        trace(__FUNCTION__);
        return *this;
    }

    Rational operator-() const {
        trace(__FUNCTION__);
        Rational r = *this;
        r.neg();
        return r;
    }

    operator double() const {
        return to_double();
    }

    ~Rational() {trace(__FUNCTION__);}

private:
    int numerator_;
    int denominator_;

public:
    static void trace(char const *str) {  }
};

Rational operator+(Rational lhs, Rational const &rhs) {
    return lhs += rhs;
}

Rational operator-(Rational lhs, Rational const &rhs) {
    return lhs -= rhs;
}

Rational operator*(Rational lhs, Rational const &rhs) {
    return lhs *= rhs;
}

Rational operator/(Rational lhs, Rational const &rhs) {
    return lhs /= rhs;
}

bool operator==(Rational const &lhs, Rational const &rhs) {
    return  lhs.get_numerator() * rhs.get_denominator() == 
            rhs.get_numerator() * lhs.get_denominator();
}

bool operator!=(Rational const &lhs, Rational const &rhs) {
    return !(lhs == rhs); 
}

bool operator<(Rational const &lhs, Rational const &rhs) {
    int lhs_num = lhs.get_numerator() * rhs.get_denominator();
    int rhs_num = rhs.get_numerator() * lhs.get_denominator();

    if (lhs.get_denominator() * rhs.get_denominator() < 0) {
        lhs_num = -lhs_num;
        rhs_num = -rhs_num;
    }

    return lhs_num < rhs_num;
}

bool operator>(Rational const &lhs, Rational const &rhs) {
    return rhs < lhs;
}

bool operator<=(Rational const &lhs, Rational const &rhs) {
    return !(lhs > rhs);
}

bool operator>=(Rational const &lhs, Rational const &rhs) {
    return !(lhs < rhs);
}


int main() {
    Rational r1(13, 3);
    Rational r2(6, 3);
    // Rational r3 = 5;


    std::cout << r1 << std::endl;
    // std::cout << -r1.to_double() << std::endl;
    // std::cout << +r1.to_double() << std::endl;


}