/********************************************************************************/
/*																				*/
/*  This file is part of source codes of program Graph.							*/
/*  Program was developed as an course work of subject "Graph theory".			*/
/*																				*/
/*	Contacts:																	*/
/*		E-mail:	arsen.gharagyozyn.96@gmail.com									*/
/*		Phone:	+374 77 006 861													*/
/*																				*/
/*  Copyright Arsen Gharagyozyan © 2018 Armenia, Yerevan						*/
/*																				*/
/********************************************************************************/

#include "ccommand.h"
#include "cgraph.h"
#include "itype.h"
#include <iostream>
#include <string>
#include <Windows.h>

static const std::string INTRO =
" Type help for command list.\n";

std::istream& inputStream = std::cin;
std::ostream& outputStream = std::cout;
Flags eFlags;

std::string& toHigher(std::string& string)
{
	for (unsigned i = 0; i < string.length(); ++i)
	{
		if (string[i] >= 'a' && string[i] <= 'z')
			string[i] += 'A' - 'a';
	}

	return string;
}

std::string& toLower(std::string& string)
{
	for (unsigned i = 0; i < string.length(); ++i)
	{
		if (string[i] >= 'A' && string[i] <= 'Z')
			string[i] += 'a' - 'A';
	}

	return string;
}

int main(int argc, char **argv)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, 15);
	ICommand *CMD = new ICommand();
	CResult result;
	CGraph *graph = nullptr;


	SetConsoleTextAttribute(Console, 7);
	std::cout << INTRO << std::endl;

	while ((eFlags & Exit) == 0)
	{
		std::cout << "Command: ";
		// error exception handler
		
		result = CMD->Parse();

		if(!result.Failure())
			result = CMD->Execute((IType *&)graph);
		
		Arglist *args = CMD->GetArgumentList();

		if (args == nullptr)
			continue;

		while (!args->empty())
			args->pop();
	}

	return 0;
	system("pause");
}