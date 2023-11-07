/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : Program.h
Description : Declarations for a SLERP calculator program
Author : Chris, Shikomisen (Ayoub)
Mail : christopher.houdt@mds.ac.nz, ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once
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
	// Constructor
	Program();
	// Deconstructor
	~Program();

	// Program operations
	void run();
	void loadQuaternionsAndInterpolation(const std::string& Filename);
	void displayQuaternions() const;
	void performOperations() const;
};
