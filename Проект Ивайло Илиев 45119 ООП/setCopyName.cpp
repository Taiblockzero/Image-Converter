#include"setCopyName.h"

void setCopyName(char* fileName, char*& fileCopyName, char* command)
{
	delete[] fileCopyName;

	int fileNameLength = strlen(fileName);
	int extensionLength = 0;

	for (int i = 1;; i++)
	{
		if (fileName[fileNameLength - i] == '.')
		{
			extensionLength = i; //dot included
			break;
		}
	}

	char* extension = new char[extensionLength + 1];
	for (int i = 0; i < extensionLength; i++)
		extension[i] = fileName[fileNameLength - extensionLength + i];
	extension[extensionLength] = '\0';

	if (0 == strcmp(command, "--grayscale"))
	{
		fileCopyName = new char[strlen(fileName) + 10 + 1]; // 10 is strlen("_grayscale") 
		strcpy(fileCopyName, fileName);

		char suffix[] = "_grayscale";
		fileCopyName[fileNameLength - extensionLength] = '\0';
		strcat(fileCopyName, suffix);
		strcat(fileCopyName, extension);
	}
	else if (0 == strcmp(command, "--monochrome"))
	{
		fileCopyName = new char[strlen(fileName) + 11 + 1]; // 11 is strlen("_monochrome")
		strcpy(fileCopyName, fileName);

		char suffix[] = "_monochrome";
		fileCopyName[fileNameLength - extensionLength] = '\0';
		strcat(fileCopyName, suffix);
		strcat(fileCopyName, extension);
	}
	else
	{
		if (0 == strcmp(command, "--histogram=red"))
		{
			fileCopyName = new char[strlen(fileName) + 14 + 1]; // 14 is strlen("_histogram_red")
			strcpy(fileCopyName, fileName);

			char suffix[] = "_histogram_red";
			fileCopyName[fileNameLength - extensionLength] = '\0';
			strcat(fileCopyName, suffix);
			strcat(fileCopyName, ".ppm");
		}
		else if (0 == strcmp(command, "--histogram=green"))
		{
			fileCopyName = new char[strlen(fileName) + 16 + 1]; // 16 is strlen("_histogram_green")
			strcpy(fileCopyName, fileName);

			char suffix[] = "_histogram_green";
			fileCopyName[fileNameLength - extensionLength] = '\0';
			strcat(fileCopyName, suffix);
			strcat(fileCopyName, ".ppm");
		}
		else if (0 == strcmp(command, "--histogram=blue"))
		{
			fileCopyName = new char[strlen(fileName) + 15 + 1]; // 15 is strlen("_histogram_blue")
			strcpy(fileCopyName, fileName);

			char suffix[] = "_histogram_blue";
			fileCopyName[fileNameLength - extensionLength] = '\0';
			strcat(fileCopyName, suffix);
			strcat(fileCopyName, ".ppm");
		}
	}
	delete[] extension;
}