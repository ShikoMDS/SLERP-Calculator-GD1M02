#pragma once
#include <iostream>
#include <iomanip>

class Quaternion
{
public:
	Quaternion();
	Quaternion(double W, double X, double Y, double Z);

	// Destructor
	~Quaternion();

	// Quaternion operations
	Quaternion operator+(const Quaternion& Rhs) const;
	[[nodiscard]] double magnitude() const;
	[[nodiscard]] double omega(const Quaternion& Rhs) const;
	[[nodiscard]] Quaternion slerp(const Quaternion& Rhs, double OmegaValue, double Interpolation) const;
	void induceMatrix() const;

	Quaternion operator*(double Scalar) const;

	double W, X, Y, Z;
	double Omega;
};

// Additional utility functions
std::ostream& operator<<(std::ostream& Os, const Quaternion& Quat);
