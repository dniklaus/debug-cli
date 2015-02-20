/*
 * DbgCliNode.cpp
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#include <DbgCliTopic.h>
#include <DbgCliNode.h>
#include <string.h>

DbgCli_Node* DbgCli_Node::s_rootNode = 0;

void DbgCli_Node::AssignRootNode(DbgCli_Node* rootNode)
{
  s_rootNode = rootNode;
}

DbgCli_Node* DbgCli_Node::RootNode()
{
  return s_rootNode;
}

DbgCli_Node::DbgCli_Node(const char* parentPath, const char* nodeName, const char* helpText)
: m_parentPath(parentPath)
, m_nodeName(nodeName)
, m_helpText(helpText)
, m_sibling(0)
{
  DbgCli_Node* rootNode = DbgCli_Node::RootNode();
  if (0 != rootNode)
  {
    rootNode->addNode(this);
  }
}

DbgCli_Node::~DbgCli_Node()
{ }

const char* DbgCli_Node::getParentPath()
{
  return m_parentPath;
}

const char* DbgCli_Node::getNodeName()
{
  return m_nodeName;
}

const char* DbgCli_Node::getHelpText()
{
  return m_helpText;
}

DbgCli_Node* DbgCli_Node::getNextSibling()
{
  return m_sibling;
}

void DbgCli_Node::setNextSibling(DbgCli_Node* nextSibling)
{
  m_sibling = nextSibling;
}
