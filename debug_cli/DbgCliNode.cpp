/*
 * DbgCliNode.cpp
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#include <DbgCliNode.h>

DbgCli_Node::DbgCli_Node(const char* parentPath, const char* nodeName, const char* helpText)
: m_parentPath(parentPath)
, m_nodeName(nodeName)
, m_helpText(helpText)
{ }

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
