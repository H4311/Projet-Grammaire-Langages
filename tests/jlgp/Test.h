#include<cstdio>
#include "Content.cpp"
#include "Data.cpp"
#include "EmptyElement.cpp"
#include "Comment.cpp"
#include "Element.cpp"

#define name(namespace,nom) make_pair(namespace,nom)
#define new_Element(str) new xml::Element(name("",str))
#define new_EmptyElement(str) new xml::EmptyElement(name("",str))
#define Att(AttName,AttVal) make_pair(AttName,AttVal)
