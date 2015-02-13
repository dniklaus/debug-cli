/*
 * DbgCliTopic.h
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_CLI_DBGCLITOPIC_H_
#define PLAT_DEBUG_CLI_DBGCLITOPIC_H_

#include <DbgCliNode.h>

/**
 * This is the Composite part of the Composite Pattern.
 */
class DbgCli_Topic: public DbgCli_Node
{
public:
  DbgCli_Topic(const char* parentPath, const char* nodeName, const char* helpText);
  virtual ~DbgCli_Topic();

  static DbgCli_Topic* RootNode();

  /**
   * Add a new node to the tree.
   * @param node Pointer to the DbgCli_Node to be added.
   */
  virtual void addNode(DbgCli_Node* node);

  /**
   * Get the node at the particular path.
   * @param cmdPath Path string addressing the node.
   * @param cmdPathStrLen Length of the Path string
   * @return DbgCli_Node Pointer to the object found, null pointer otherwise
   */
  virtual DbgCli_Node* getNode(const char* cmdPath, unsigned int cmdPathStrLen);

  /**
   * Execute the debug command.
   * Finds its path according to the args array's tokens. Calls the execute method of the right child node if found, increments the index to the first parameter to handle accordingly.
   * @param argc
   * @param args
   * @param idxToFirstArgToHandle Index to the first argument in args array to be handled as parameter (this is the first parameter to be passed to the method that gets called by this command)
   */
  virtual void execute(unsigned int argc, char* args[], unsigned int idxToFirstArgToHandle);

private:
  void addChildNode(DbgCli_Node* node);
  DbgCli_Node* getChildNode(const char* childNodeName);

private:
  static DbgCli_Topic* s_rootNode;

  DbgCli_Node* m_child;
  DbgCli_Node* m_sibling;

private: // forbidden default functions
  DbgCli_Topic& operator= (const DbgCli_Topic& src);  // assignment operator
  DbgCli_Topic(const DbgCli_Topic& src);              // copy constructor
  DbgCli_Topic();                                     // default constructor
};

#endif /* PLAT_DEBUG_CLI_DBGCLITOPIC_H_ */
