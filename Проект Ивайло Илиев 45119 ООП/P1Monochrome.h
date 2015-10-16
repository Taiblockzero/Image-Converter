#pragma once
#include"P1Image.h"


class P1Monochrome : public P1Image
{
public:
	P1Monochrome(char* fileName, char* command, int maxValue);
	~P1Monochrome(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome(){}
	virtual void createHistogram();
	virtual void setCopyName();
};
