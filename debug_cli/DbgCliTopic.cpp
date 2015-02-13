/*
 * DbgCliTopic.cpp
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#include <DbgCliTopic.h>

DbgCli_Topic* DbgCli_Topic::RootNode()
{
  if (0 == s_rootNode)
  {
    s_rootNode = new DbgCli_Topic("/", "", "Root Node");
  }
  return s_rootNode;
}


DbgCli_Topic::DbgCli_Topic(const char* parentPath, const char* nodeName, const char* helpText)
: DbgCli_Node(parentPath, nodeName, helpText)
, m_child(0)
, m_sibling(0)
{ }

DbgCli_Topic::~DbgCli_Topic()
{ }

void DbgCli_Topic::addNode(DbgCli_Node* node)
{
  // TODO: search the parent node according to the provided parentPath given by the node object.
  const char* parentPath = node->getParentPath();

}

DbgCli_Node* DbgCli_Topic::getNode(const char* cmdPath, unsigned int cmdPathStrLen)
{
  // TODO: search the node according to the provided cmdPath and return the pointer to the object if found.
  return 0;
}

void DbgCli_Topic::execute(unsigned int arg_cnt, char* args[], unsigned int idxToFirstArgToHandle)
{
  // TODO: Finds its path according to the args array's tokens.
  // TODO: Calls the execute method of the right child node if found, increments the index to the first parameter to handle accordingly.
}

void DbgCli_Topic::addChildNode(DbgCli_Node* node)
{
  DbgCli_Topic* tmpTopic = m_child;
  while (0 != tmpTopic)
  {
    tmpTopic = tmpTopic->m_sibling;
  }
  tmpTopic->addNode(node);
}

