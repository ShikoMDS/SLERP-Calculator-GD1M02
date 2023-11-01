#pragma once
//#include "SLERP.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Quaternion.h"

class Program
{
private:
	double Interpolation{};
	Quaternion QuaternionA;
	Quaternion QuaternionB;

	void readQuaternionFromFile(std::ifstream& File, Quaternion& Quat) const;
	void skipEmptyLine(std::ifstream& File) const;

public:
	Program();
	~Program();

	void run();
	void loadQuaternionsAndInterpolation(const std::string& Filename);
	void displayQuaternions() const;
	void performOperations() const;
};
