#include<iostream>
#include<fstream>
#include"CommandLineInterpreter.h"

CommandLineInterpreter::CommandLineInterpreter(int argc, char** argv)
{
	fileName = NULL;
	fileNameNextIndexToCheckInArgv = 1;
	this->argv = argv;
	this->argc = argc;
	command = NULL;
	commandNextIndexToCheckInArgv = 1; 
}
CommandLineInterpreter::~CommandLineInterpreter()
{
	delete[] fileName;
	delete[] command;
}
void CommandLineInterpreter::setFileNameToNextFileInArgv()
{
	if (NULL == argv)
	{
		cout << "Please set this->argv with setArgv function first!" << endl;
		return;
	}
	for (int i = fileNameNextIndexToCheckInArgv; i < argc; i++)
	{
		if (i >= argc)

		{
			delete[] fileName;
			return;
		}
		if (0 == strcmp(argv[i], "--grayscale"))
			continue;
		if (0 == strcmp(argv[i], "--monochrome"))
			continue;
		if (0 == strcmp(argv[i], "--histogram=red"))
			continue;
		if (0 == strcmp(argv[i], "--histogram=green"))
			continue;
		if (0 == strcmp(argv[i], "--histogram=blue"))
			continue;

		delete[] fileName;
		fileName = new char[strlen(argv[i]) + 1];
		strcpy(fileName, argv[i]);
		fileNameNextIndexToCheckInArgv = i + 1;
	}
}
void CommandLineInterpreter::setCommandToNextCommandInArgv()
{
	if (NULL == argv)
	{
		cout << "Please set this->argv with setArgv function first!" << endl;
		return;
	}
	for (int i = commandNextIndexToCheckInArgv; i < argc; i++)
	{
		if (0 == strcmp(argv[i], "--grayscale"))
		{
			delete[] command;
			command = new char[strlen("--grayscale") + 1];
			strcpy(command, "--grayscale");
			commandNextIndexToCheckInArgv = i + 1;
			return;
		}
		if (0 == strcmp(argv[i], "--monochrome"))
		{
			delete[] command;
			command = new char[strlen("--monochrome") + 1];
			strcpy(command, "--monochrome");
			commandNextIndexToCheckInArgv = i + 1;
			return;
		}
		if (0 == strcmp(argv[i], "--histogram=red"))
		{
			delete[] command;
			command = new char[strlen("--histogram=red") + 1];
			strcpy(command, "--histogram=red");
			commandNextIndexToCheckInArgv = i + 1;
			return;
		}
		if (0 == strcmp(argv[i], "--histogram=green"))
		{
			delete[] command;
			command = new char[strlen("--histogram=green") + 1];
			strcpy(command, "--histogram=green");
			commandNextIndexToCheckInArgv = i + 1;
			return;
		}
		if (0 == strcmp(argv[i], "--histogram=blue"))
		{
			delete[] command;
			command = new char[strlen("--histogram=blue") + 1];
			strcpy(command, "--histogram=blue");
			commandNextIndexToCheckInArgv = i + 1;
			return;
		}
	}
	commandNextIndexToCheckInArgv = argc;
}
void CommandLineInterpreter::doAllCommandsForFile()
{
	setFileNameToNextFileInArgv();
	while (commandNextIndexToCheckInArgv <= argc)
	{
		setCommandToNextCommandInArgv();
		Distributor image(fileName, command);
		image.passFileNameAndCommandToProperClass();
	}
	commandNextIndexToCheckInArgv = 1;
}
void CommandLineInterpreter::doAllCommandsForAllFiles()
{
	while (fileNameNextIndexToCheckInArgv < argc)
	{
		setFileNameToNextFileInArgv();
		while (commandNextIndexToCheckInArgv < argc)
		{
			setCommandToNextCommandInArgv();
			if (argc == commandNextIndexToCheckInArgv)
				break;

			Distributor image(fileName, command);
			image.passFileNameAndCommandToProperClass();
		}
		commandNextIndexToCheckInArgv = 1;
	}
}