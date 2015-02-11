/*
 * DbgCliNode.h
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_CLI_DBGCLINODE_H_
#define PLAT_DEBUG_CLI_DBGCLINODE_H_

class DbgCli_Node
{
protected: // abstract class - constructor must not be accessible
  DbgCli_Node(const char* parentPath, const char* nodeName, const char* helpText);

public:
  virtual ~DbgCli_Node();

  /**
   * Add a new node to the tree.
   * @param node Pointer to the DbgCli_Node to be added.
   */
  virtual void addNode(DbgCli_Node* node) { }

  /**
   * Get the node at the particular path.
   * @param cmdPath Path string addressing the node.
   * @param cmdPathStrLen Length of the Path string
   * @return DbgCli_Node Pointer to the object found, null pointer otherwise
   */
  virtual DbgCli_Node* getNode(const char* cmdPath, unsigned int cmdPathStrLen) = 0;

  /**
   * Execute the debug command.
   * Pure virtual method, to be implemented for leaf nodes (i.e. commands) by the application.
   * @param argc
   * @param args
   * @param idxToFirstArgToHandle Index to the first argument in args array to be handled as parameter (this is the first parameter to be passed to the method that gets called by this command)
   */
  virtual void execute(unsigned int argc, char* args[], unsigned int idxToFirstArgToHandle) = 0;

  const char* getParentPath();
  const char* getNodeName();
  const char* getHelpText();

private:
  const char* m_parentPath;
  const char* m_nodeName;
  const char* m_helpText;

private: // forbidden default functions
  DbgCli_Node& operator= (const DbgCli_Node& src);  // assignment operator
  DbgCli_Node(const DbgCli_Node& src);              // copy constructor
  DbgCli_Node();                                    // default constructor
};

#endif /* PLAT_DEBUG_CLI_DBGCLINODE_H_ */
