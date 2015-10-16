#pragma once
#include"P6Image.h"


class P6Colorful : public P6Image
{
public:
	P6Colorful(char* fileName, char* command, int maxValue);
	~P6Colorful();
public:
	virtual void convertToGrayscale();
	virtual void convertToMonochrome();
	virtual void createHistogram();
	virtual void setCopyName();
	//void copyHeader(ofstream& imageDestination, ifstream& imageSource);
};
