/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : Quaternion.h
Description : Declarations for a SLERP calculator program
Author : Chris, Shikomisen (Ayoub)
Mail : christopher.houdt@mds.ac.nz, ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once
#include <iostream>
#include <iomanip>

class Quaternion
{
public:
	// Constructors
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

	// Variables
	double W, X, Y, Z;
	double Omega;
};

// Additional utility functions
std::ostream& operator<<(std::ostream& Os, const Quaternion& Quat);
