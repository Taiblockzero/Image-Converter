
#pragma once
#include"Distributor.h"


class CommandLineInterpreter
{
	char** argv;
	int argc;
	char* fileName;
	int fileNameNextIndexToCheckInArgv;
	char* command;
	int commandNextIndexToCheckInArgv;
public:
	CommandLineInterpreter(int argc, char** argv);
	~CommandLineInterpreter();
public:
	void setFileNameToNextFileInArgv();
	void setCommandToNextCommandInArgv();
public:
	void doAllCommandsForFile();
	void doAllCommandsForAllFiles();
};