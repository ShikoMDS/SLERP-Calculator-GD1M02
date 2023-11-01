﻿#include "Quaternion.h"

// Constructors
Quaternion::Quaternion() : W(0), X(0), Y(0), Z(0)
{
	Omega = 0.0;
}

Quaternion::Quaternion(const double W, const double X, const double Y, const double Z) : W(W), X(X), Y(Y), Z(Z)
{
	Omega = 0.0;
}

// Destructor
Quaternion::~Quaternion() = default;

Quaternion Quaternion::operator+(const Quaternion& Rhs) const
{
    return { W + Rhs.W, X + Rhs.X, Y + Rhs.Y, Z + Rhs.Z };
}

double Quaternion::magnitude() const
{
	return sqrt((this->W * this->W) + (this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z));
}

double Quaternion::omega(const Quaternion& Rhs) const
{
	return acos(((this->W * Rhs.W) + (this->X * Rhs.X) + (this->Y * Rhs.Y) + (this->Z * Rhs.Z))
		/ (this->magnitude() * Rhs.magnitude()));
}

Quaternion Quaternion::slerp(const Quaternion& Rhs, double OmegaValue, double Interpolation) const
{
	Quaternion SlerpQuaternion;

	if (Interpolation < 0.00 || Interpolation > 1.00)
	{
		SlerpQuaternion.W = this->W;
		SlerpQuaternion.X = this->X;
		SlerpQuaternion.Y = this->Y;
		SlerpQuaternion.Z = this->Z;
		std::cout << "t < 0 || t > 1\n";
	}

	SlerpQuaternion = this->operator*(sin((1 - Interpolation) * OmegaValue) / sin(OmegaValue))
		+ Rhs.operator*(sin(Interpolation * OmegaValue) / sin(OmegaValue));

	return SlerpQuaternion;
}

void Quaternion::induceMatrix() const
{
	double Matrix[4][4]{};

	Matrix[0][0] = (2 * ((this->W) * (this->W))) - 1 + (2 * ((this->X) * (this->X)));
	Matrix[0][1] = (2 * (this->X * this->Y)) + (2 * (this->W * this->Z));
	Matrix[0][2] = (2 * (this->X * this->Z)) - (2 * (this->W * this->Y));
	Matrix[1][0] = (2 * (this->X * this->Y)) - (2 * (this->W * this->Z));
	Matrix[1][1] = (2 * ((this->W) * (this->W))) - 1 + (2 * ((this->Y) * (this->Y)));
	Matrix[1][2] = (2 * (this->Y * this->Z)) + (2 * (this->W * this->X));
	Matrix[2][0] = (2 * (this->X * this->Z)) + (2 * (this->W * this->Y));
	Matrix[2][1] = (2 * (this->Y * this->Z)) - (2 * (this->W * this->X));
	Matrix[2][2] = (2 * ((this->W) * (this->W))) - 1 + (2 * ((this->Z) * (this->Z)));

	for (int I = 0; I < 3; I++)
	{
		for (int J = 0; J < 3; J++)
		{
			if (Matrix[I][J] < 0.0001 && Matrix[I][J] > -0.0001)
			{
				if (Matrix[I][J] < 0.0000)
				{
					Matrix[I][J] = -0.0;
				}
				else
				{
					Matrix[I][J] = 0.0;
				}
			}
		}
	}

	std::cout << std::setprecision(3);
	std::cout << Matrix[0][0] << "		" << Matrix[0][1] << "		" << Matrix[0][2] << "		" << Matrix[0][3] << std::endl;
	std::cout << Matrix[1][0] << "		" << Matrix[1][1] << "		" << Matrix[1][2] << "		" << Matrix[1][3] << std::endl;
	std::cout << Matrix[2][0] << "		" << Matrix[2][1] << "		" << Matrix[2][2] << "		" << Matrix[2][3] << std::endl;
	std::cout << Matrix[3][0] << "		" << Matrix[3][1] << "		" << Matrix[3][2] << "		" << Matrix[3][3] << std::endl;
}

Quaternion Quaternion::operator*(double Scalar) const
{
	return { this->W * Scalar, this->X * Scalar, this->Y * Scalar, this->Z * Scalar };
}

std::ostream& operator<<(std::ostream& Os, const Quaternion& Quat)
{
	Os << Quat.W << " + " << Quat.X << "i + " << Quat.Y << "j + " << Quat.Z << "k";
	return Os;
}