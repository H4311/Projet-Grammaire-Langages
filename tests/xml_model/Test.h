#include <cstdio>
#include "Content.hpp"
#include "Data.hpp"
#include "EmptyElement.hpp"
#include "Comment.hpp"
#include "Element.hpp"

#include "mainTest1.hpp"
#include "mainTest2.hpp"
#include "mainTest3.hpp"
#include "mainTest4.hpp"

/**
@file Test.h
@author Jose GONZALEZ
*/

pair<string, string> name(string namespaceStr,string nomStr);

xml::Element *new_Element(string str);

xml::EmptyElement *new_EmptyElement(string str);

pair<string, string> Att(string AttName,string AttVal);
