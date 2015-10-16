#include<iostream>
#include<fstream>
using namespace std;
const int COMMENT_LENGTH = 71;

#include"CommandLineInterpreter.h"

int main(int argc, char** argv)
{
	CommandLineInterpreter cmd(argc, argv);
	cmd.doAllCommandsForAllFiles();
}

