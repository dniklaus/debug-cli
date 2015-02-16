/*
 * DbgCliCommand.h
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_CLI_DBGCLICOMMAND_H_
#define PLAT_DEBUG_CLI_DBGCLICOMMAND_H_

#include <DbgCliNode.h>

/**
 * Composite Pattern: Abstract Command Class, acts as the leaf node of the tree, has to be implemented by the client.
 */
class DbgCli_Command: public DbgCli_Node
{
public: // abstract class - constructor must not be accessible
  /**
   * Constructor for a leaf node in the Command tree.
   * @param parentPath Parent path string, each token is space separated.
   * @param nodeName Name of this node (this becomes a part of the command path / tree).
   * @param helpText Help and usage string.
   */
  DbgCli_Command(const char* parentPath, const char* nodeName, const char* helpText);

public:
  /**
   * Destructor.
   */
  virtual ~DbgCli_Command();

  /**
   * Execute the debug command.
   * Pure virtual method, to be implemented by the client application.
   * @param argc
   * @param args
   * @param idxToFirstArgToHandle Index to the first argument in args array to be handled as parameter (this is the first parameter to be passed to the method that gets called by this command)
   */
  virtual void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle);

private: // forbidden default functions
  DbgCli_Command& operator= (const DbgCli_Command& src);  // assignment operator
  DbgCli_Command(const DbgCli_Command& src);              // copy constructor
  DbgCli_Command();                                       // default constructor
};

#endif /* PLAT_DEBUG_CLI_DBGCLICOMMAND_H_ */
