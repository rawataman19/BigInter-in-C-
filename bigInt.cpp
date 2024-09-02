#include <bits/stdc++.h>
#include "bigInt.h"

// Default constructor
BigInt::BigInt() : number("0"), isNegative(false) {}

// Constructor from string
BigInt::BigInt(const std::string& num) {
    if (num[0] == '-') {
        isNegative = true;
        number = num.substr(1);
    } else {
        isNegative = false;
        number = num;
    }
    removeLeadingZeros();
}

// Constructor from integer
BigInt::BigInt(long long num) {
    if (num < 0) {
        isNegative = true;
        num = -num;
    } else {
        isNegative = false;
    }
    number = std::to_string(num);
}

// Assignment operator from string
BigInt& BigInt::operator=(const std::string& num) {
    if (num[0] == '-') {
        isNegative = true;
        number = num.substr(1);
    } else {
        isNegative = false;
        number = num;
    }
    removeLeadingZeros();
    return *this;
}

// Assignment operator from integer
BigInt& BigInt::operator=(long long num) {
    if (num < 0) {
        isNegative = true;
        num = -num;
    } else {
        isNegative = false;
    }
    number = std::to_string(num);
    return *this;
}

// Overload the extraction operator (>>)
std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string str;
    in >> str;
    if (str[0] == '-') {
        num.isNegative = true;
        num.number = str.substr(1);
    } else {
        num.isNegative = false;
        num.number = str;
    }
    num.removeLeadingZeros();
    return in;
}

// Overload the insertion operator (<<)
std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.isNegative) {
        out << "-";
    }
    out << num.number;
    return out;
}

// Utility to remove leading zeros
void BigInt::removeLeadingZeros() {
    while (number.length() > 1 && number[0] == '0') {
        number.erase(0, 1);
    }
}

// Unary negation operator
BigInt BigInt::operator-() const {
    BigInt result = *this;
    result.isNegative = !result.isNegative;
    return result;
}

// Addition
BigInt BigInt::operator+(const BigInt& other) const {
    if (this->isNegative == other.isNegative) {
        BigInt result;
        result.number = "";
        result.isNegative = this->isNegative;

        const std::string& num1 = this->number;
        const std::string& num2 = other.number;
        int carry = 0, sum = 0;

        int len1 = num1.size(), len2 = num2.size();
        int maxLength = std::max(len1, len2);

        // Pad the shorter number with leading zeros
        std::string n1 = std::string(maxLength - len1, '0') + num1;
        std::string n2 = std::string(maxLength - len2, '0') + num2;

        for (int i = maxLength - 1; i >= 0; --i) {
            sum = (n1[i] - '0') + (n2[i] - '0') + carry;
            carry = sum / 10;
            result.number.push_back((sum % 10) + '0');
        }

        if (carry) {
            result.number.push_back(carry + '0');
        }

        std::reverse(result.number.begin(), result.number.end());
        result.removeLeadingZeros();
        return result;
    } else {
        // a + (-b) is the same as a - b
        return *this - (-other);
    }
}

// Subtraction
BigInt BigInt::operator-(const BigInt& other) const {
    if (this->isNegative != other.isNegative) {
        return *this + (-other);
    }

    bool resultNegative = false;
    BigInt a = *this;
    BigInt b = other;

    if (a < b) {
        std::swap(a, b);
        resultNegative = !this->isNegative;
    } else {
        resultNegative = this->isNegative;
    }

    std::string result;
    int carry = 0;

    int i = a.number.size() - 1;
    int j = b.number.size() - 1;

    while (i >= 0) {
        int digit1 = a.number[i] - '0';
        int digit2 = j >= 0 ? b.number[j] - '0' : 0;

        int current_sub = digit1 - digit2 - carry;
        if (current_sub < 0) {
            current_sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result.push_back(current_sub + '0');
        i--; j--;
    }

    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    std::reverse(result.begin(), result.end());

    BigInt res;
    res.number = result;
    res.isNegative = resultNegative;
    res.removeLeadingZeros();
    return res;
}

// Multiplication
BigInt BigInt::operator*(const BigInt& other) const {
    if (*this == BigInt(0) || other == BigInt(0)) {
        return BigInt(0);
    }

    BigInt result;
    result.number = std::string(this->number.size() + other.number.size(), '0');

    for (int i = this->number.size() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = other.number.size() - 1; j >= 0; j--) {
            int tmp = (result.number[i + j + 1] - '0') + (this->number[i] - '0') * (other.number[j] - '0') + carry;
            result.number[i + j + 1] = tmp % 10 + '0';
            carry = tmp / 10;
        }
        result.number[i] += carry;
    }

    result.isNegative = this->isNegative != other.isNegative;
    result.removeLeadingZeros();
    return result;
}

// Comparison operator: less than
bool BigInt::operator<(const BigInt& other) const {
    if (this->isNegative != other.isNegative) {
        return this->isNegative;
    }
    if (this->isNegative) {
        return compareAbs(*this, other);
    }
    return compareAbs(other, *this);
}

// Comparison operator: equality
bool BigInt::operator==(const BigInt& other) const {
    return this->isNegative == other.isNegative && this->number == other.number;
}

// Helper function to compare absolute values
bool BigInt::compareAbs(const BigInt& a, const BigInt& b) {
    if (a.number.size() != b.number.size()) {
        return a.number.size() < b.number.size();
    }
    return a.number < b.number;
}
