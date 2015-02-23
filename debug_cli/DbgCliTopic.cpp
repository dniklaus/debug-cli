/*
 * DbgCliTopic.cpp
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#include <DbgCliTopic.h>
#include <string.h>
#include <stdlib.h>

#ifdef ARDUINO
#include "Arduino.h"
#else
#include <stdio.h>
#endif

DbgCli_Topic::DbgCli_Topic(const char* parentPath, const char* nodeName, const char* helpText)
: DbgCli_Node(parentPath, nodeName, helpText)
, m_firstChild(0)
{ }

DbgCli_Topic::~DbgCli_Topic()
{ }

void DbgCli_Topic::addNode(DbgCli_Node* node)
{
  if (0 != node)
  {
    const char* nodeParentPath = node->getParentPath();
    unsigned int strLen = 50;
    char str[strLen];
    strncpy(str, nodeParentPath, strLen);

    unsigned int nbrOfTokens = 0;
    char nodeParentPathTokens[10][50];

    char* token;
    token = strtok(str, " /.-");
    while (0 != token)
    {
      strncpy(nodeParentPathTokens[nbrOfTokens], token, 50);
      nbrOfTokens++;
      token = strtok(0, " /.-");
    }

    // find name of this in parent path of node to add
    bool found = false;
    const char* thisNodeName  = this->getNodeName();
    unsigned int tokenIterator = 0;  // range: 0..nbrOfTokens-1
    while ((tokenIterator < nbrOfTokens) && !found)
    {
      char* nodePathToken = nodeParentPathTokens[tokenIterator];
      found = (strcmp(nodePathToken, thisNodeName) == 0);
      tokenIterator++;
    }

    if (found)
    {
      if ((tokenIterator) == nbrOfTokens)
      {
        // node shall be a child of this
        this->addChildNode(node);
      }
      else
      {
        char* childNodeName = nodeParentPathTokens[tokenIterator];
        // node shall be a grand-child (or deeper) of this
        // find continued path in own family
        DbgCli_Node* childNode = this->getNode(childNodeName);
        if (0 != childNode)
        {
          childNode->addNode(node);
        }
        else
        {
          // not yet existing intermediate node, create it
          unsigned int strLen = 50;
          const char* thisParentPath = this->getParentPath();
          char parentPathForChild[strLen];
          strncpy(parentPathForChild, thisParentPath, strLen);
          if (strlen(thisParentPath) > 0)
          {
            strcat(parentPathForChild, " ");
          }
          strcat(parentPathForChild, thisNodeName);

          DbgCli_Node* childNode = new DbgCli_Topic(parentPathForChild, childNodeName, "");
          this->addChildNode(childNode);
          childNode->addNode(node);
        }
      }
    }
    else
    {

    }
  }
}

void DbgCli_Topic::addChildNode(DbgCli_Node* node)
{
  if (0 == m_firstChild)
  {
    m_firstChild = node;
  }
  else
  {
    DbgCli_Node* next = m_firstChild;

    while (0 != next->getNextSibling())
    {
      next = next->getNextSibling();
    }
    next->setNextSibling(node);
  }
}

DbgCli_Node* DbgCli_Topic::getNode(const char* nodeName)
{
  bool found = false;
  DbgCli_Node* tmpNode = m_firstChild;
  while ((0 != tmpNode) && !found)
  {
    found = (strcmp(tmpNode->getNodeName(), nodeName) == 0);
    if (!found)
    {
      tmpNode = tmpNode->getNextSibling();
    }
  }
  return tmpNode;
}

void DbgCli_Topic::execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
{
  const char* nodeName = args[idxToFirstArgToHandle];
#ifdef ARDUINO
  Serial.print("DbgCli_Topic::execute, curNodeName: ");
  Serial.print(this->getNodeName());
  Serial.print(", nodeName: ");
  Serial.println(nodeName);
#endif

  DbgCli_Node* tmpNode = getNode(nodeName);
  if (0 != tmpNode)
  {
    idxToFirstArgToHandle++;
    tmpNode->execute(argc, args, idxToFirstArgToHandle);
  }
  else
  {
    // not found
#ifdef ARDUINO
    if ('\0' == nodeName)
    {
      Serial.println(getHelpText());
    }
    else
    {
      Serial.print("Node or cmd \"");
      Serial.print(nodeName);
      Serial.println("\" not found!");
    }
#else
    if ('\0' == nodeName)
    {
      printf("%s\n", getHelpText());
    }
    else
    {
      printf("Node or cmd \"%s\" not found!\n", nodeName);
    }
#endif
  }
}
