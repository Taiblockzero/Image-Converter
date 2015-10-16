#pragma once
#include<fstream>
using namespace std;
const int HEADER_STRING_LENGTH = 3;
class Distributor
{
	char* fileName;
	char* command;
	char header[HEADER_STRING_LENGTH];
	char* imageType;
	int maxValue;
public:
	Distributor(char* fileName, char* command);
	~Distributor();
public:
	void setHeader();
	void setImageType();
	void setMaxValue();
public:
	bool isP3ImageMonochrome();
	bool isP3ImageGrayscale();
	bool isP2ImageMonochrome();
	bool isP6ImageMonochrome();
	bool isP6ImageGrayscale();
	bool isP5ImageMonochrome();
public:
	void skipHeader(ifstream& image);
public:
	void passFileNameAndCommandToProperClass();
};