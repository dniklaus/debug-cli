/*
 * DbgCliCommand.cpp
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#include <DbgCliCommand.h>

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>
#endif

DbgCli_Command::DbgCli_Command(const char* parentPath, const char* nodeName, const char* helpText)
: DbgCli_Node(parentPath, nodeName, helpText)
{ }

DbgCli_Command::~DbgCli_Command()
{ }

void DbgCli_Command::execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
{
#ifdef ARDUINO
  Serial.println(getHelpText());
#else
  printf("%s\n", getHelpText());
#endif
}
