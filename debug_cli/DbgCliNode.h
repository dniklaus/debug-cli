/*
 * DbgCliNode.h
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_CLI_DBGCLINODE_H_
#define PLAT_DEBUG_CLI_DBGCLINODE_H_

/**
 * Composite Pattern: Abstract Node Class, acts as the Interface to the object tree.
 */
class DbgCli_Node
{
protected: // abstract class - constructor must not be accessible
  DbgCli_Node(const char* parentPath, const char* nodeName, const char* helpText);

public:
  virtual ~DbgCli_Node();

public:
  /**
   * print all child nodes to console output
   */
  virtual void printAllChildNodes() { }

protected:
  /**
   * Add a child node to this node.
   * @param childNode Pointer the node to be added as a child.
   */
  virtual void addChildNode(DbgCli_Node* childNode) { }

public:
  /**
   * Get a child node by name (no grandchildren).
   * Command nodes return always null, since these objects don't have any children.
   * @param nodeName Child node object name.
   * @return DbgCli_Node Pointer to the object found, null pointer otherwise.
   */
  virtual DbgCli_Node* getChildNode(const char* nodeName) { return 0; }

  /**
   * Get first child node.
   * @return DbgCli_Node Pointer to the firstchild object, null pointer if none is available.
   */
  virtual DbgCli_Node* getFirstChild() {return 0;}

public:
  /**
   * Execute the debug command.
   * Pure virtual method, to be implemented for leaf nodes (i.e. commands) by the application.
   * @param argc
   * @param args
   * @param idxToFirstArgToHandle Index to the first argument in args array to be handled as parameter (this is the first parameter to be passed to the method that gets called by this command)
   */
  virtual void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle) = 0;

  const char* getParentPath();
  const char* getNodeName();
  const char* getHelpText();

  /**
   * Get next sibling.
   * @return DbgCli_Node Pointer to the next sibling object, null pointer if none is available.
   */
  DbgCli_Node* getNextSibling();

  /**
   * Set specific node as next sibling.
   * @param nextSibling Pointer to the next sibling object to be assigned.
   */
  void setNextSibling(DbgCli_Node* nextSibling);

public:
  static void AssignRootNode(DbgCli_Node* rootNode);
  static DbgCli_Node* RootNode();
  /**
    * Get a pointer to a node
    * @param parentPath parentPath of the searched node
    * @param nodeName (optional) nodeName of the searched node
    * @return DbgCli_Node Pointer to searched node, to parent node if nodeName is empty or null if (parent)node not found.
    */
  static DbgCli_Node* getNode(const char* parentPath, const char* nodeName = "\0");

private:
  static DbgCli_Node* s_rootNode;

private:
  const char* m_parentPath;
  const char* m_nodeName;
  const char* m_helpText;

  DbgCli_Node* m_sibling;

private: // forbidden default functions
  DbgCli_Node& operator= (const DbgCli_Node& src);  // assignment operator
  DbgCli_Node(const DbgCli_Node& src);              // copy constructor
  DbgCli_Node();                                    // default constructor
};

#endif /* PLAT_DEBUG_CLI_DBGCLINODE_H_ */
