#pragma once
#include"P5Image.h"


class P5Monochrome : public P5Image
{
public:
	P5Monochrome(char* fileName, char* command, int maxValue);
	~P5Monochrome(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome(){}
	virtual void createHistogram();
	virtual void setCopyName();
};
