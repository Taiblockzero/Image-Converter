#include"ImageType.h"




ImageType::ImageType()
{
	fileName = NULL;
	command = NULL;
	fileCopyName = NULL;
}
ImageType::~ImageType()
{
	delete[] fileName;
	delete[] command;
	delete[] fileCopyName;
}
void ImageType::setWidthAndHeight()
{
	ifstream image(fileName);
	char line[COMMENT_LENGTH];
	char c;
	image.getline(line, COMMENT_LENGTH);

	image.get(c);
	while (c == '#') //preskacham komentarite
	{
		image.getline(line, COMMENT_LENGTH);
		image.get(c);
	}
	image.unget();

	int skippedNumber;
	image >> width; //preskacham width
	image >> height; //preskacham height
	image >> skippedNumber; //preskacham maxValue
	image.close();
}
void ImageType::copyHeaderInBinary(ofstream& imageDestination, ifstream& imageSource)
{
	imageDestination.seekp(0);
	imageSource.seekg(0);
	unsigned char line[COMMENT_LENGTH];

	imageSource.read((char*)line, 3);
	imageDestination.write((char*)line, 3);
	if (width < 10)
	{
		imageSource.read((char*)line, 1);
		imageDestination.write((char*)line, 1);
	}
	else if (width < 100)
	{
		imageSource.read((char*)line, 2);
		imageDestination.write((char*)line, 2);
	}
	else
	{
		imageSource.read((char*)line, 3);
		imageDestination.write((char*)line, 3);
	}
	imageSource.read((char*)line, 1);
	imageDestination.write((char*)line, 1);
	if (height < 10)
	{
		imageSource.read((char*)line, 1);
		imageDestination.write((char*)line, 1);
	}
	else if (height < 100)
	{
		imageSource.read((char*)line, 2);
		imageDestination.write((char*)line, 2);
	}
	else
	{
		imageSource.read((char*)line, 3);
		imageDestination.write((char*)line, 3);
	}
	imageSource.read((char*)line, 1);
	imageDestination.write((char*)line, 1);
	if (maxValue < 10)
	{
		imageSource.read((char*)line, 1);
		imageDestination.write((char*)line, 1);
	}
	else if (maxValue < 100)
	{
		imageSource.read((char*)line, 2);
		imageDestination.write((char*)line, 2);
	}
	else
	{
		imageSource.read((char*)line, 3);
		imageDestination.write((char*)line, 3);
	}
	imageSource.read((char*)line, 1);
	imageDestination.write((char*)line, 1);

}
void ImageType::copyHeader(ofstream& imageDestination, ifstream& imageSource)
{
	char line[COMMENT_LENGTH];
	imageSource.getline(line, COMMENT_LENGTH);

	imageDestination << line << '\n';

	char c;
	imageSource.get(c);
	while (c == '#')
	{
		imageSource.unget();
		imageSource.getline(line, COMMENT_LENGTH);
		imageDestination << line << '\n';
		imageSource.get(c);
	}
	imageSource.unget();

	int width;
	int height;
	int maxvalue;

	imageSource >> width >> height >> maxvalue;
	imageDestination << width << ' ' << height << '\n';
	imageDestination << maxvalue << '\n';
}
void ImageType::skipHeaderInBinary(fstream& image)
{

	unsigned char c[10];
	image.read((char*)c, 2); //skip header
	image.read((char*)c, 1); //newline
	if (width < 10) //width
		image.read((char*)c, 1); 
	else if (width < 100)
		image.read((char*)c, 2);
	else
		image.read((char*)c, 3);
	image.read((char*)c, 1); //space
	if (height < 10) //height
		image.read((char*)c, 1);
	else if (height < 100)
		image.read((char*)c, 2);
	else
		image.read((char*)c, 3);
	image.read((char*)c, 1); //newline
	if (maxValue < 10) //maxvalue
		image.read((char*)c, 1);
	else if (maxValue < 100)
		image.read((char*)c, 2);
	else
		image.read((char*)c, 3);
	image.read((char*)c, 1); //newline
	
}
void ImageType::skipHeader(fstream& image)
{
	char line[COMMENT_LENGTH];
	char c;
	image.getline(line, COMMENT_LENGTH);
	
	image.get(c);
	while(c == '#') //preskacham komentarite
	{
		image.getline(line, COMMENT_LENGTH);
		image.get(c);
	}
	image.unget();

	int skippedNumber;
	image >> skippedNumber; //preskacham width
	image >> skippedNumber; //preskacham heigth
	image >> skippedNumber; //preskacham maxValue
}

void ImageType::skipHeaderInPBM(fstream& image)
{
	char line[COMMENT_LENGTH];
	char c;
	image.getline(line, COMMENT_LENGTH);

	image.get(c);
	while (c == '#') //preskacham komentarite
	{
		image.getline(line, COMMENT_LENGTH);
		image.get(c);
	}
	image.unget();

	int skippedNumber;
	image >> skippedNumber; //preskacham width
	image >> skippedNumber; //preskacham heigth
	//pri pixelBitmap nqma maxValue
}

int ImageType::getPositionAfterHeader(fstream& image)
{
	image.clear();
	image.seekg(0);

	char line[COMMENT_LENGTH];
	char c;
	
	image.getline(line, COMMENT_LENGTH);

	image.get(c);
	while (c == '#') //preskacham komentarite
	{
		image.getline(line, COMMENT_LENGTH);
		image.get(c);
	}
	image.unget();

	int skippedNumber;
	image >> skippedNumber; //preskacham width
	image >> skippedNumber; //preskacham heigth
	image >> skippedNumber; //preskacham maxValue
	
	image.getline(line, COMMENT_LENGTH);
	return image.tellg();
}

int* ImageType::readPixelsIntoArray(char* header) 
{
	this->setWidthAndHeight();

	//izpolzvam tezi za da ne pravi proverkata kakuv e headera sus strcmp() mnogo puti
	bool headerIsP3 = false, headerIsP2 = false, headerIsP1 = false, headerIsP6 = false, headerIsP5 = false, headerIsP4 = false;
	if (0 == strcmp(header, "P3"))
		headerIsP3 = true;
	else if (0 == strcmp(header, "P2"))
		headerIsP2 = true;
	else if (0 == strcmp(header, "P1"))
		headerIsP1 = true;
	else if (0 == strcmp(header, "P6"))
		headerIsP6 = true;
	else if (0 == strcmp(header, "P5"))
		headerIsP5 = true;
	else if (0 == strcmp(header, "P4"))
		headerIsP4 = true;

	bool histogramRed = false, histogramGreen = false, histogramBlue = false;
	if (0 == strcmp(command, "--histogram=red"))
		histogramRed = true;
	else if (0 == strcmp(command, "--histogram=green"))
		histogramGreen = true;
	else if (0 == strcmp(command, "--histogram=blue"))
		histogramBlue = true;


	int* arr = new int[256]();

	if (headerIsP1) //ASCII
	{
		fstream image(fileName, ios::in);
		//cycle will loop 2 times - once for arr cell 0(black) and once for array cell 255(white)
		for (int i = 0, count = 0, colorPercent; i < 256; i += 255)
		{
			count = 0;
			skipHeaderInPBM(image);
			for (int num; image;)
			{
				image >> num;
				if (0 == i)
				{
					if (1 == num)
						count++;
				}
				else if (255 == i)
				{
					if (0 == num)
						count++;
				}
			}
			colorPercent = (count * 100) / (width * height);
			if (101 == colorPercent)
				colorPercent = 100; //vremenno reshenie na problema sus 101-te procenta
			arr[i] = colorPercent;
			image.clear();
			image.seekg(0);
		}
		image.close();
	}

	else if (headerIsP3 || headerIsP2) //ASCII
	{
		fstream image(fileName, ios::in);
		for (int i = 0, count = 0, colorPercent; i <= maxValue; i++) //count e broqt ot konkretniq cvqt ravni na 0(1,2,...,maxvalue)
		{
			count = 0; //resetvam count
			skipHeader(image);
			for (int num; image;)
			{
				image >> num;
				if (histogramRed || headerIsP2) //tova e purviq cvqt pri P3 ili purviq pixel pri P2
				{
					if (i == num)
						count++;
				}
				if (headerIsP3)
				{
					image >> num;
					if (histogramGreen)
					{
						if (i == num)
							count++;
					}
					image >> num;
					if (histogramBlue)
					{
						if (i == num)
							count++;
					}
				}
			}
			//ne moga da razbera zashto mi gi izkarva 101 procenta
			colorPercent = (count * 100) / (width * height);
			if (101 == colorPercent)
				colorPercent = 100; //vremenno reshenie na problema sus 101-te procenta
			int cell = i * coefficient; //arr cells that will be filled with color percents
			arr[cell] = colorPercent;
			image.clear();
			image.seekg(0);
		}
		image.close();
	}

	else if (headerIsP1) //Binary
	{
		fstream image(fileName, ios::in);
		//cycle will loop 2 times - once for arr cell 0(black) and once for array cell 255(white)
		for (int i = 0, count = 0, colorPercent; i < 256; i += 255)
		{
			count = 0;
			skipHeaderInPBM(image);
			for (unsigned char num[1]; image;)
			{
				image.read((char*)num, 1);
				if (0 == i)
				{
					if (1 == num[0])
						count++;
				}
				else if (255 == i)
				{
					if (0 == num[0])
						count++;
				}
			}
			colorPercent = (count * 100) / (width * height);
			if (101 == colorPercent)
				colorPercent = 100; //vremenno reshenie na problema sus 101-te procenta
			arr[i] = colorPercent;
			image.clear();
			image.seekg(0);
		}
		image.close();
	}

	else if (headerIsP6 || headerIsP5) //Binary
	{
		fstream image(fileName, ios::in | ios::binary);
		for (int i = 0, count = 0, colorPercent; i <= maxValue; ++i) 
		{
			count = 0; //resetvam count
			skipHeader(image);
			for (unsigned char num[1]; image;)
			{
				image.read((char*)num, 1);
				if (histogramRed || headerIsP5) //tova e purviq cvqt pri P6 ili purviq pixel pri P5, napravi i za P4
				{
					if (i == num[0])
						count++;
				}
				if (headerIsP6)
				{
					image.read((char*)num, 1);
					if (histogramGreen)
					{
						if (i == num[0])
							count++;
					}
					image.read((char*)num, 1);
					if (histogramBlue)
					{
						if (i == num[0])
							count++;
					}
				}
			}
			colorPercent = (count * 100) / (width * height);
			if (101 == colorPercent)
				colorPercent = 100; //vremenno reshenie na problema sus 101-te procenta
			int cell = i * coefficient; //arr cells that will be filled with color percents
			arr[cell] = colorPercent;
			image.clear();
			image.seekg(0);
		}
		image.close();
	}
	return arr;
}

void ImageType::drawHistogram(int* arr, char* header)
{

	//izpolzvam tezi za da ne pravi proverkata kakuv e headera sus strcmp() mnogo puti
	bool headerIsP3 = false, headerIsP2 = false, headerIsP1 = false, headerIsP6 = false, headerIsP5 = false, headerIsP4 = false;
	if (0 == strcmp(header, "P3"))
		headerIsP3 = true;
	else if (0 == strcmp(header, "P2"))
		headerIsP2 = true;
	else if (0 == strcmp(header, "P1"))
		headerIsP1 = true;
	else if (0 == strcmp(header, "P6"))
		headerIsP6 = true;
	else if (0 == strcmp(header, "P5"))
		headerIsP5 = true;
	else if (0 == strcmp(header, "P4"))
		headerIsP4 = true;

	bool imageIsASCII = false, imageIsBinary = false;

	if (headerIsP3 || headerIsP2 || headerIsP1)
		imageIsASCII = true;

	else if (headerIsP6 || headerIsP5 || headerIsP4)
		imageIsBinary = true;


	if (imageIsASCII)
	{
		fstream image(fileCopyName, ios::out);
		drawHeader(image);
		drawPixmap(image, arr);
		image.close();
		delete[] arr;
	}
	else if (imageIsBinary)
	{
		fstream image(fileCopyName, ios::out | ios::binary);
		drawHeaderBinary(image);
		drawPixmapBinary(image, arr);
		image.close();
		delete[] arr;
	}
}

void ImageType::drawHeader(fstream& image)
{
	image << "P3" << endl; //All histograms of ASCII images will be P3 and .ppm
	image << 256 << ' ' << 101 << endl;
	image << 255 << endl;
}

void ImageType::drawHeaderBinary(fstream& image)
{
	image << "P6" << endl; //All histograms of Binary images will be P6 and .ppm
	image << 256 << ' ' << 101 << endl;
	image << 255 << endl;
}

void ImageType::drawPixmap(fstream& image, int* arr)
{
	//izpolzvam tezi za da ne pravi proverka sus strcmp() vseki put kato proverqva dali e --histogram=red, =green ili =blue
	bool histogramRed = false, histogramGreen = false, histogramBlue = false; 
	if (0 == strcmp(command, "--histogram=red"))
		histogramRed = true;
	else if (0 == strcmp(command, "--histogram=green"))
		histogramGreen = true;
	else if (0 == strcmp(command, "--histogram=blue"))
		histogramBlue = true;


	for (int i = 100; i > 0; --i) //100 is height for 100 to 1 percent
	{
		for (int cnt = 0; cnt < 256; ++cnt) //255 is histogram width
		{
			if (arr[cnt] >= i)
			{
				if (histogramRed)
					image << 255 << ' ' << 0 << ' ' << 0 << ' ';
				else if (histogramGreen)
					image << 0 << ' ' << 255 << ' ' << 0 << ' ';
				else if (histogramBlue)
					image << 0 << ' ' << 0 << ' ' << 255 << ' ';
			}
			else
				image << 255 << ' ' << 255 << ' ' << 255 << ' ';
		}
		image << endl;
	}
	
	for (int i = 0; i < 256; ++i) //nai-dolniqt red na histogramata e prosto liniq
	{
		if (histogramRed)
			image << 255 << ' ' << 0 << ' ' << 0 << ' ';
		else if (histogramGreen)
			image << 0 << ' ' << 255 << ' ' << 0 << ' ';
		else if (histogramBlue)
			image << 0 << ' ' << 0 << ' ' << 255 << ' ';
	}
}

void ImageType::drawPixmapBinary(fstream& image, int* arr) //razlikata mejdu ascii i binary na tazi funkciq e samo kak se zapisvat cvetovete
{
	bool histogramRed = false, histogramGreen = false, histogramBlue = false;
	if (0 == strcmp(command, "--histogram=red"))
		histogramRed = true;
	else if (0 == strcmp(command, "--histogram=green"))
		histogramGreen = true;
	else if (0 == strcmp(command, "--histogram=blue"))
		histogramBlue = true;


	unsigned char max[1] = { 255 }; // za "image.write()"-ovete
	unsigned char zero[1] = { 0 };
	for (int i = 100; i > 0; --i) //100 is height for 100 to 1 percent
	{
		
		for (int cnt = 0; cnt < 256; ++cnt) //255 is histogram width
		{
			if (arr[cnt] >= i)
			{
				if (histogramRed)
				{
					image.write((char*)max, 1);
					image.write((char*)zero, 1);
					image.write((char*)zero, 1);
				}
				else if (histogramGreen)
				{
					image.write((char*)zero, 1);
					image.write((char*)max, 1);
					image.write((char*)zero, 1);
				}
				else if (histogramBlue)
				{
					image.write((char*)zero, 1);
					image.write((char*)zero, 1);
					image.write((char*)max, 1);
				}
			}
			else
			{
				image.write((char*)max, 1);
				image.write((char*)max, 1);
				image.write((char*)max, 1);
			}
		}
	}
	for (int i = 0; i < 256; ++i) //nai-dolniqt red na histogramata e prosto liniq
	{
		if (histogramRed)
		{
			image.write((char*)max, 1);
			image.write((char*)zero, 1);
			image.write((char*)zero, 1);
		}
		else if (histogramGreen)
		{
			image.write((char*)zero, 1);
			image.write((char*)max, 1);
			image.write((char*)zero, 1);
		}
		else if (histogramBlue)
		{
			image.write((char*)zero, 1);
			image.write((char*)zero, 1);
			image.write((char*)max, 1);
		}
	}
}