#pragma once
#include <cmath>
#include "math.h"
#include "float.h"
#include <fstream>

class CComplex
{
public:
    CComplex(double real = 0, double image = 0);
    double Re() const;
    double Im() const;
    double GetMagnitude() const;
    double GetArgument() const;

    CComplex const operator +()const;
    CComplex const operator -()const;

    CComplex& operator+=(const CComplex& first);
    CComplex& operator-=(const CComplex& first);
    CComplex& operator*=(const CComplex& first);
    CComplex& operator/=(const CComplex& first);

    bool operator==(const CComplex& first) const;
    bool operator!=(const CComplex& first) const;
private:
    double m_real;
    double m_image;
};

CComplex const operator+(const CComplex& first, const CComplex& second);
CComplex const operator-(const CComplex& first, const CComplex& second);
CComplex const operator*(const CComplex& first, const CComplex& second);
CComplex const operator/(const CComplex& first, const CComplex& second);

std::ostream& operator<<(std::ostream& os, const CComplex& complex);
std::istream& operator>>(std::istream& is, CComplex& complex);