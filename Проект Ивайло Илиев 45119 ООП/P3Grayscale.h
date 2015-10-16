#pragma once
#include"P3Image.h"


class P3Grayscale : public P3Image
{
public:
	P3Grayscale(char* fileName, char* command, int maxValue);
	~P3Grayscale(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome();
	virtual void createHistogram();
	virtual void setCopyName();
};
