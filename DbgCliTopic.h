/*
 * DbgCliTopic.h
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_CLI_DBGCLITOPIC_H_
#define PLAT_DEBUG_CLI_DBGCLITOPIC_H_

#include "DbgCliNode.h"

/**
 * This is the Composite part of the Composite Pattern.
 */
class DbgCli_Topic: public DbgCli_Node
{
public:
  /**
   * ctor of a topic node
   * @param parentNode pointer to the parent node, to add the newly created topic. For creating the root node pass 0 (nullptr).
   * @param nodeName name of the node
   * @param helpText help text for this node
   */
  DbgCli_Topic(DbgCli_Node* parentNode, const char* nodeName, const char* helpText);

  virtual ~DbgCli_Topic();

  /**
   * print all child nodes of the topic to console output
   */
  virtual void printAllChildNodes();

public:
  /**
   * Add a new node as a child.
   * @param node Pointer to the DbgCli_Node to be added.
   */
  virtual void addChildNode(DbgCli_Node* node);

  /**
   * Remove a particular node from the children.
   * @param node Pointer to the DbgCli_Node to be removed.
   */
  virtual void removeChildNode(DbgCli_Node* node);

  /**
   * Get the child node by name (no grandchildren).
   * @param nodeName Child node object name.
   * @return DbgCli_Node Pointer to the object found, null pointer otherwise.
   */
  virtual DbgCli_Node* getChildNode(const char* nodeName);

  /**
   * Get child node.
   * @return DbgCli_Node Pointer to the firstchild object, null pointer if none is available.
   */
  virtual DbgCli_Node* getFirstChild();

  /**
   * Execute the debug command.
   * Finds its path according to the args array's tokens. Calls the execute method of the right child node if found, increments the index to the first parameter to handle accordingly.
   * @param argc number of elements in args
   * @param args all arguments stored in an array
   * @param idxToFirstArgToHandle Index to the first argument in args array to be handled as parameter (this is the first parameter to be passed to the method that gets called by this command)
   */
  virtual void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle);

private:
  DbgCli_Node* m_firstChild;

private: // forbidden default functions
  DbgCli_Topic& operator= (const DbgCli_Topic& src);  // assignment operator
  DbgCli_Topic(const DbgCli_Topic& src);              // copy constructor
  DbgCli_Topic();                                     // default constructor
};

#endif /* PLAT_DEBUG_CLI_DBGCLITOPIC_H_ */
