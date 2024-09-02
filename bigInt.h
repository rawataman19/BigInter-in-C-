// bigInt.h

#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <iostream>

class BigInt {
private:
    std::string number;
    bool isNegative;

    // Helper function to remove leading zeros
    void removeLeadingZeros();

    // Helper function to compare absolute values
    static bool compareAbs(const BigInt& a, const BigInt& b);

public:
    // Default constructor
    BigInt();

    // Constructor from string
    BigInt(const std::string& num);

    // Constructor from integer
    BigInt(long long num);

    // Assignment operator from string
    BigInt& operator=(const std::string& num);

    // Assignment operator from integer
    BigInt& operator=(long long num);

    // Overload the extraction operator (>>)
    friend std::istream& operator>>(std::istream& in, BigInt& num);

    // Overload the insertion operator (<<)
    friend std::ostream& operator<<(std::ostream& out, const BigInt& num);

    // Unary negation operator
    BigInt operator-() const;

    // Addition operator
    BigInt operator+(const BigInt& other) const;

    // Subtraction operator
    BigInt operator-(const BigInt& other) const;

    // Multiplication operator
    BigInt operator*(const BigInt& other) const;

    // Comparison operator: less than
    bool operator<(const BigInt& other) const;

    // Comparison operator: equality
    bool operator==(const BigInt& other) const;
};

#endif // BIGINT_H
