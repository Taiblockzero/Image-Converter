#pragma once
#include"P6Image.h"


class P6Monochrome : public P6Image
{
public:
	P6Monochrome(char* fileName, char* command, int maxValue);
	~P6Monochrome(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome(){}
	virtual void createHistogram();
	virtual void setCopyName();
};
