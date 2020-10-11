#include "CComplex.h"

CComplex::CComplex(double real, double image)
	: m_real(real), m_image(image)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(pow(Re(), 2) + pow(Im(), 2));
}

double CComplex::GetArgument() const
{
	return atan(Im() / Re());
}

CComplex const operator+(const CComplex& first, const CComplex& second)
{
	return CComplex(first.Re() + second.Re(), first.Im() + second.Im());
}

CComplex const operator-(const CComplex& first, const CComplex& second)
{
	return CComplex(first.Re() - second.Re(), first.Im() - second.Im());
}

CComplex const operator*(const CComplex& first, const CComplex& second)
{
	double real = first.Re() * second.Re() - first.Im() * second.Im();
	double image = first.Re() * second.Im() + first.Im() * second.Re();
	return CComplex(real, image);
}

CComplex const operator/(const CComplex& first, const CComplex& second)
{
	if (second.Re() == 0 && second.Im() == 0)
	{
		throw std::invalid_argument("Division by 0");
	}

	double real = (first.Re() * second.Re() + first.Im() * second.Im()) / (pow(second.Re(), 2) + pow(second.Im(), 2));
	double image = (second.Re() * first.Im() - first.Re() * second.Im()) / (pow(second.Re(), 2) + pow(second.Im(), 2));
	return CComplex(real, image);
}

CComplex const CComplex::operator +() const
{
	return *this;
}

CComplex const CComplex::operator -() const
{
	return CComplex(-m_real, -m_image);
}

CComplex& CComplex::operator+=(const CComplex& first)
{
	*this = *this + first;
	return *this;
}

CComplex& CComplex::operator-=(const CComplex& first)
{
	*this = *this - first;
	return *this;
}

CComplex& CComplex::operator*=(const CComplex& first)
{
	*this = *this * first;
	return *this;
}

CComplex& CComplex::operator/=(const CComplex& first)
{
	*this = *this / first;
	return *this;
}

bool CComplex::operator==(const CComplex& first) const
{
	return ((fabs(Re() - first.Re()) < DBL_MIN) && (fabs(Im() - first.Im()) < DBL_MIN));
}

bool CComplex::operator!=(const CComplex& first) const
{
	return !(*this == first);
}

std::ostream& operator<<(std::ostream& os, const CComplex& complex)
{
	os << complex.Re();
	if (complex.Im() >= 0)
	{
		os << "+";
	}
	os << complex.Im() << "i";

	return os;
}

std::istream& operator>>(std::istream& is, CComplex& complex)
{
	double real, image;

	if ((is >> real) && (is >> image) && (is.get() == 'i'))
	{
		complex = CComplex(real, image);
	}
	else
	{
		is.setstate(std::ios_base::failbit);
	}

	return is;
}