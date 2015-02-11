/*
 * DbgCliCommand.cpp
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#include <DbgCliCommand.h>

DbgCli_Command::DbgCli_Command(const char* parentPath, const char* nodeName, const char* helpText)
: DbgCli_Node(parentPath, nodeName, helpText)
{ }

DbgCli_Command::~DbgCli_Command()
{ }
