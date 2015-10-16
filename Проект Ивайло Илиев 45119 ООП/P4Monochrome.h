#pragma once
#include"P4Image.h"

class P4Monochrome : public P4Image
{
public:
	P4Monochrome(char* fileName, char* command, int maxValue);
	~P4Monochrome(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome(){}
	virtual void createHistogram();
	virtual void setCopyName();
};
