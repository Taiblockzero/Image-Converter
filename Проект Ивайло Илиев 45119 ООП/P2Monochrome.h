#pragma once
#include"P2Image.h"


class P2Monochrome : public P2Image
{
public:
	P2Monochrome(char* fileName, char* command, int maxValue);
	~P2Monochrome(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome(){}
	virtual void createHistogram();
	virtual void setCopyName();
};
