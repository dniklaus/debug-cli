/*
 * DbgCliTopic.cpp
 *
 *  Created on: 11.02.2015
 *      Author: niklausd
 */

#include "DbgCliTopic.h"
#include <string.h>
#include <stdlib.h>

#ifdef ARDUINO
#include "Arduino.h"
#else
#include <stdio.h>
#endif

DbgCli_Topic::DbgCli_Topic(DbgCli_Node* parentNode, const char* nodeName, const char* helpText)
: DbgCli_Node(parentNode, nodeName, helpText)
, m_firstChild(0)
{ }

DbgCli_Topic::~DbgCli_Topic()
{ 
  DbgCli_Node* next = m_firstChild;
  while (0 != next)
  {
    DbgCli_Node* toBeDeleted = next;
    next = next->getNextSibling();
    delete toBeDeleted;
    toBeDeleted = 0;
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

void DbgCli_Topic::removeChildNode(DbgCli_Node* node)
{
  if (m_firstChild == node)
  {
    m_firstChild = node->getNextSibling();
  }
  else
  {
    DbgCli_Node* next = m_firstChild;
    while ((next != 0) && (next->getNextSibling() != node))
    {
      next = next->getNextSibling();
    }
    if (next != 0)
    {
      next->setNextSibling(node->getNextSibling());
    }
  }
}

void DbgCli_Topic::printAllChildNodes()
{
#ifdef ARDUINO
  Serial.print("Node ");
  Serial.print(this->getNodeName());
  Serial.print(": ");
  Serial.println(this->getHelpText());
  DbgCli_Node* tmpNode = this->getFirstChild();
  if (0 != tmpNode)
  {
    Serial.print("Contains: ");
    Serial.print(tmpNode->getNodeName());
    tmpNode = tmpNode->getNextSibling();
    while (0 != tmpNode)
    {
      Serial.print(", ");
      Serial.print(tmpNode->getNodeName());
      tmpNode = tmpNode->getNextSibling();
    }
    Serial.println(" ");
  }
#else
  printf("Node %s: %s\n", this->getNodeName(), this->getHelpText());
  DbgCli_Node* tmpNode = this->getFirstChild();
  if (0 != tmpNode)
  {
    printf("Contains: %s", tmpNode->getNodeName());
    tmpNode = tmpNode->getNextSibling();
    while (0 != tmpNode)
    {
      printf(", %s", tmpNode->getNodeName());
      tmpNode = tmpNode->getNextSibling();
    }
    printf("\n");
  }
#endif
}

DbgCli_Node* DbgCli_Topic::getChildNode(const char* nodeName)
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

DbgCli_Node* DbgCli_Topic::getFirstChild()
{
  return m_firstChild;
}

void DbgCli_Topic::execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
{
  if (idxToFirstArgToHandle < argc)
  {
    const char* nodeName = args[idxToFirstArgToHandle];
//  #ifdef ARDUINO
//    Serial.print("DbgCli_Topic::execute, curNodeName: ");
//    Serial.print(this->getNodeName());
//    Serial.print(", nodeName: ");
//    Serial.println(nodeName);
//  #else
//    printf("DbgCli_Topic::execute, curNodeName: %s", this->getNodeName());
//    printf(", nodeName: %s\n",nodeName);
//  #endif

    DbgCli_Node* tmpNode = this->getChildNode(nodeName); //get child or sibling with this nodeName
    if (0 != tmpNode)
    {
      idxToFirstArgToHandle++;
      tmpNode->execute(argc, args, idxToFirstArgToHandle);
    }
    else if (0==strcmp(DbgCli_Topic::RootNode()->getNodeName(),nodeName))
    {
      // root node was executed
      this->printAllChildNodes();
    }
    else
    {
      // at least one node not found
  #ifdef ARDUINO
      Serial.print("Node or cmd \"");
      Serial.print(nodeName);
      Serial.println("\" not found!");
  #else
      printf("Node or cmd \"%s\" not found!\n", nodeName);
  #endif
    }
  }
  else
  { // at last node and its a topic
    this->printAllChildNodes();
  }
}
