#include "Program.h"

void Program::readQuaternionFromFile(std::ifstream& File, Quaternion& Quat) const
{
	std::string Line;
	std::getline(File, Line);

	// Format is "w +/- xi +/- yj +/- zk"
	std::istringstream Iss(Line);
	char Dummy; // to temporarily store '+'/'-' and 'i', 'j', 'k'

	// Read the real part
	if (!(Iss >> Quat.W))
	{
		Quat.W = 1; // If no real part specified, set to 1
		Iss.clear();
	}

	std::string Value;

	// Loop to read 'i', 'j', 'k' parts
	for (char Part : {'i', 'j', 'k'})
	{
		if (Iss >> Dummy)
		{
			double& CurrentPart = (Part == 'i') ? Quat.X : (Part == 'j') ? Quat.Y : Quat.Z;

			Iss >> Value;
			std::string PartValue(1, Part);

			if (Dummy == '+')
			{
				if (Value != PartValue)
				{
					CurrentPart = std::stod(Value);
				}
				else
				{
					CurrentPart = 1.0;
				}
			}
			else if (Dummy == '-')
			{
				if (Value != PartValue)
				{
					CurrentPart = -std::stod(Value);
				}
				else
				{
					CurrentPart = -1.0;
				}
			}
		}
	}
}

void Program::skipEmptyLine(std::ifstream& File) const
{
	std::string Line;
	std::getline(File, Line);
}

Program::Program() = default;

Program::~Program() = default;

void Program::run()
{
	loadQuaternionsAndInterpolation("Slerp.txt");
	displayQuaternions();
	performOperations();
}

void Program::loadQuaternionsAndInterpolation(const std::string& Filename)
{
	std::ifstream File(Filename);
	if (!File.is_open())
	{
		std::cerr << "Error opening file: " << Filename << std::endl;
		exit(EXIT_FAILURE);
	}

	// Read quaternion a (line 1)
	readQuaternionFromFile(File, QuaternionA);

	// Skip empty line (line 2)
	skipEmptyLine(File);

	// Read quaternion b (line 3)
	readQuaternionFromFile(File, QuaternionB);

	// Skip empty line (line 4)
	skipEmptyLine(File);

	// Read scalar value (line 5)
	File >> Interpolation;

	// Close the file
	File.close();
}

void Program::displayQuaternions() const
{
	std::cout << "Quaternion A: " << QuaternionA.W << " + " << QuaternionA.X << "i + " << QuaternionA.Y << "j + " <<
		QuaternionA.Z << "k" << std::endl;
	std::cout << "Quaternion B: " << QuaternionB.W << " + " << QuaternionB.X << "i + " << QuaternionB.Y << "j + " <<
		QuaternionB.Z << "k" << std::endl;
	std::cout << "Interpolation Parameter: " << Interpolation << std::endl;
}

void Program::performOperations() const
{
	std::cout << "\nInduced matrix for A:\n";
	QuaternionA.induceMatrix();
	std::cout << std::endl;

	std::cout << "Induced matrix for B:\n";
	QuaternionB.induceMatrix();
	std::cout << std::endl;

	Quaternion Result;
	
	Result = QuaternionA.slerp(QuaternionB, QuaternionA.omega(QuaternionB), Interpolation);
	std::cout << "Resultant Slerp: " << Result << std::endl;

	std::cout << "\nInduced matrix for Resultant Slerp:\n";
	Result.induceMatrix();
}
