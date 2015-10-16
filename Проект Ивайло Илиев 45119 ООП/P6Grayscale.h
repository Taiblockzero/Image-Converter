#pragma once
#include"P6Image.h"


class P6Grayscale : public P6Image
{
public:
	P6Grayscale(char* fileName, char* command, int maxValue);
	~P6Grayscale(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome();
	virtual void createHistogram();
	virtual void setCopyName();
};
