#define _USE_MATH_DEFINES
#define CATCH_CONFIG_MAIN 
#include "../catch/catch.hpp"
#include "../Complex/CComplex.h"
#include <cmath>
#include <sstream>

using namespace std;

TEST_CASE("Should return real part of complex number")
{
	CComplex A(5, 10);
	CHECK(A.Re() == 5);
}

TEST_CASE("Should return imaginary part of complex number")
{
	CComplex A(5, 10);
	CHECK(A.Im() == 10);
}

TEST_CASE("Must return the modulus of a complex number")
{
	CComplex A(5, 10);
	CHECK(A.GetMagnitude() - 11.1803 < 0.0001);
}

TEST_CASE("Must return an argument of a complex number")
{
	CComplex A(5, 10);
	CHECK(A.GetArgument() - 63.4349 < 0.0001);
}

TEST_CASE("Binary plus should sum two complex numbers")
{
	CComplex A(5, 10);
	CComplex B(2, 5);
	CComplex C = A + B;
	CHECK(C.Re() == 7);
	CHECK(C.Im() == 15);
}

TEST_CASE("Binary plus should sum complex and real number")
{
	CComplex A(5, 10);
	CComplex B(2, 5);
	CComplex C = 5.6 + A;
	CHECK(C.Re() == 10.6);
	CHECK(C.Im() == 10);

	C = B + 5.6;
	CHECK(C.Re() == 7.6);
	CHECK(C.Im() == 5);
}

TEST_CASE("Binary minus should subtracts a complex number from a complex number")
{
	CComplex A(5, 10);
	CComplex B(2, 5);
	CComplex C = A - B;
	CHECK(C.Re() == 3);
	CHECK(C.Im() == 5);
}

TEST_CASE("Binary minus should get the difference of a complex number and a real number")
{
	CComplex A(5, 10);
	CComplex B(2, 5);
	CComplex C = A - 5;
	CHECK(C.Re() == 0);
	CHECK(C.Im() == 10);

	C = 5 - B;
	CHECK(C.Re() == 3);
	CHECK(C.Im() == -5);
}

TEST_CASE("Should multiply complex numbers")
{
	CComplex A(5, 10);
	CComplex B(0, 5);
	CComplex C = A * B;
	CHECK(C.Re() == -50);
	CHECK(C.Im() == 25);
}

TEST_CASE("Should multiply a complex number and a real number")
{
	CComplex A(5, 10);
	CComplex B(2, 5);
	CComplex C = A * 3;
	CHECK(C.Re() == 15);
	CHECK(C.Im() == 30);

	C = 3 * B;
	CHECK(C.Re() == 6);
	CHECK(C.Im() == 15);
}

TEST_CASE("Should divide a complex number by a complex number")
{
	CComplex A(-1, 3);
	CComplex B(1, 2);
	CComplex C = A / B;
	CHECK(C.Re() == 1);
	CHECK(C.Im() == 1);
}

TEST_CASE("Should't divide a complex number by zero")
{
	CComplex A(5, 10);
	CComplex B(2, 5);
	CComplex C(0, 0);
	CHECK_THROWS(A / C);
	CHECK_THROWS(A / 0);
}

TEST_CASE("Division should get the quotient of a complex number and a real number")
{
	CComplex A(5, 10);
	CComplex B(2, -2);
	CComplex C = A / 5;
	CHECK(C.Re() == 1);
	CHECK(C.Im() == 2);

	C = 5 / B;
	CHECK(C.Re() == 1.25);
	CHECK(C.Im() == 1.25);
}

TEST_CASE("Unary plus should return a copy of a complex number")
{
	CComplex A(5, 10);
	CComplex C = +A;
	CHECK(C.Re() == 5);
	CHECK(C.Im() == 10);
}

TEST_CASE("Unary minus should return the opposite complex number")
{
	CComplex A(5, 10);
	CComplex C = -A;
	CHECK(C.Re() == -5);
	CHECK(C.Im() == -10);
}

TEST_CASE("+= must add to the complex number combining with the assignment")
{
	CComplex C(5, 10);
	CComplex B(5, 10);
	C += B;
	CHECK(C.Re() == 10);
	CHECK(C.Im() == 20);

	C += 4;
	CHECK(C.Re() == 14);
	CHECK(C.Im() == 20);
}

TEST_CASE("-= must subtract from a complex number combining with the assignment")
{
	CComplex C(5, 10);
	CComplex B(2, 4);
	C -= B;
	CHECK(C.Re() == 3);
	CHECK(C.Im() == 6);

	C -= 4;
	CHECK(C.Re() == -1);
	CHECK(C.Im() == 6);
}

TEST_CASE("*= must multiply a complex number combining with the assignment")
{
	CComplex B(2, 10);
	CComplex C(2, 4);
	C *= B;
	CHECK(C.Re() == -36);
	CHECK(C.Im() == 28);

	C *= 2;
	CHECK(C.Re() == -72);
	CHECK(C.Im() == 56);
}

TEST_CASE("/= must divide a complex number combining with the assignment")
{
	CComplex C(2, 10);
	CComplex B(2, 4);
	C /= B;
	CHECK(C.Re() == 2.2);
	CHECK(C.Im() == 0.6);

	C /= 2;
	CHECK(C.Re() == 1.1);
	CHECK(C.Im() == 0.3);
}

TEST_CASE("/= mustn't divide a complex number by zero combining with the assignment")
{
	CComplex A(5, 10);
	CComplex C(0, 0);
	CHECK_THROWS(A /= C);
	CHECK_THROWS(A /= 0);
}

TEST_CASE("== ñompares a complex numbers with a complex number")
{
	CComplex C(5, 10);
	CComplex A(5, 10);
	CComplex B(4, 10);
	CHECK(C == A);

	CHECK(!(A == B));
}

TEST_CASE("!= must check complex numbers for the inequality")
{
	CComplex A(4, 10);
	CComplex B(5, 10);
	CHECK(A != B);

	CComplex C(4, 10);
	CHECK(!(C != A));
}

TEST_CASE("Input operator should read a complex numbers")
{
	CComplex C;
	(std::stringstream)"-3.5-4.8i" >> C;
	CHECK(C.Re() == -3.5);
	CHECK(C.Im() == -4.8);

	(std::stringstream)"4+2i" >> C;
	CHECK(C.Re() == 4);
	CHECK(C.Im() == 2);
}

TEST_CASE("If complex number failed to read, stream has a failbit state")
{
	CComplex C;
	std::stringstream strm;
	strm << "4+2";
	strm >> C;
	CHECK(strm.fail());
}

TEST_CASE("Output operator should print a complex number")
{
	CComplex C(-3.5, -4.8);
	std::stringstream strmC;
	strmC << C;
	CHECK(strmC.str() == "-3.5-4.8i");

	CComplex D(4, 2);
	std::stringstream strmD;
	strmD << D;
	CHECK(strmD.str() == "4+2i");
}