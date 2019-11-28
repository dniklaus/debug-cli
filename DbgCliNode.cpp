/*
 * DbgCliNode.cpp
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#include "DbgCliTopic.h"
#include "DbgCliNode.h"
#include <string.h>

#define MAX_TREE_HEIGHT        7
#define MAX_PATH_LEGTH        50
#define MAX_NODE_NAME_LENGTH  15
#define PATH_DELIMITERS   " /.-"

DbgCli_Node* DbgCli_Node::s_rootNode = 0;

void DbgCli_Node::AssignRootNode(DbgCli_Node* rootNode)
{
  s_rootNode = rootNode;
}

DbgCli_Node* DbgCli_Node::RootNode()
{
  return s_rootNode;
}

DbgCli_Node* DbgCli_Node::getNode(const char* parentPath, const char* nodeName)
{
  char str[MAX_PATH_LEGTH];
  char parentPathTokens[MAX_TREE_HEIGHT][MAX_NODE_NAME_LENGTH];
  char* token;
  unsigned int nbrOfTokens = 0;

  // split parent path to its nodes
  strncpy(str, parentPath, MAX_PATH_LEGTH);
  token = strtok(str, PATH_DELIMITERS);
  while (0 != token)
  {
    strncpy(parentPathTokens[nbrOfTokens], token, MAX_NODE_NAME_LENGTH);
    nbrOfTokens++;
    token = strtok(0, PATH_DELIMITERS);
  }

  if (0 != strncmp(nodeName,"\0",MAX_NODE_NAME_LENGTH))
  {
    // add nodeName to tokens, if parameter is used
    strncpy(parentPathTokens[nbrOfTokens], nodeName, MAX_NODE_NAME_LENGTH);
    nbrOfTokens++;
  }

  unsigned int tokenIterator = 0;  // range: 0..nbrOfTokens-1
  DbgCli_Node* tmpNode = DbgCli_Node::RootNode();

  if ((0 != tmpNode) && (0 != strncmp(tmpNode->getNodeName(), parentPathTokens[tokenIterator], MAX_NODE_NAME_LENGTH)))
  {
    // Root node not found, brake!
    return 0;
  }
  else
  {
    tokenIterator++;
    DbgCli_Node* nextNode;
    while (tokenIterator < nbrOfTokens)
    {
      // get next node
      nextNode = tmpNode->getChildNode(parentPathTokens[tokenIterator]);
      if (0 != nextNode)
      {
        tmpNode = nextNode;
        tokenIterator++;
      }
      else
      {
        return 0;
      }
    }
    return tmpNode;
  }
}

DbgCli_Node::DbgCli_Node(DbgCli_Node* parentNode, const char* nodeName, const char* helpText)
: m_parentNode(parentNode)
, m_nodeName(nodeName)
, m_helpText(helpText)
, m_sibling(0)
{
  DbgCli_Node* rootNode = DbgCli_Node::RootNode();
  if (0 != rootNode) // not possible to add nodes, without root node
  {
    if (0 != m_parentNode)
    {
      DbgCli_Topic* parentTopic = static_cast<DbgCli_Topic*>(m_parentNode);
      parentTopic->addChildNode(this);
    }
  }
}

DbgCli_Node::~DbgCli_Node()
{ }

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
