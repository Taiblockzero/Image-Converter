#pragma once
#include"P2Image.h"


class P2Grayscale : public P2Image
{
public:
	P2Grayscale(char* fileName, char* command, int maxValue);
	~P2Grayscale(){}
public:
	virtual void convertToGrayscale(){}
	virtual void convertToMonochrome();
	virtual void createHistogram();
	virtual void setCopyName();
};
