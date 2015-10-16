#pragma once
#include"P3Image.h"


class P3Monochrome : public P3Image
{
public:
	P3Monochrome(char* fileName, char* command, int maxValue);
	~P3Monochrome(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome(){}
	virtual void createHistogram();
	virtual void setCopyName();
};
