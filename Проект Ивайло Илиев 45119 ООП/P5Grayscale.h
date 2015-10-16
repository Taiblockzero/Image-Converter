#pragma once
#include"P5Image.h"


class P5Grayscale : public P5Image
{
public:
	P5Grayscale(char* fileName, char* command, int maxValue);
	~P5Grayscale(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome();
	virtual void createHistogram();
	virtual void setCopyName();
};
