
#include<list>
#include<string>
#include<iostream>

#include "Document.hpp"
#include "Element.hpp"
#include "Seq.hpp"
#include "Choice.hpp"
#include "Name.hpp"
#include "AttributeList.hpp"
#include "Attribute.hpp"

using namespace dtd;

int main() {
	
	Name *n = new Name("Test", '+');
	Name *n2 = new Name("Test2");
	Name *n3 = new Name("Test3", '*');
	Name *n4 = new Name("Test4");
	
	std::list<Children*> l;
	l.push_back(n);
	l.push_back(n2);
	Choice *c = new Choice(l, '*');
	
	std::list<Children*> l2;
	l2.push_back(n3);
	l2.push_back(c);
	l2.push_back(n4);
	Seq *s = new Seq(l2);
	
	Element *e = new Element("ElemTest", s);
	
	Any *any = new Any();
	Element *e2 = new Element("ElemTest2", any);
	
	Empty *empty = new Empty();
	Element *e3 = new Element("br", empty);
	
	std::cout << e->getRegex() << std::endl << std::endl;
	
	std::list<std::string> type;
	type.push_back("CDATA");
	Attribute *a = new Attribute("att1", type, "#FIXED", "test");
	
	std::list<std::string> type2;
	type2.push_back("enum1");
	type2.push_back("enum2");
	type2.push_back("enum3");
	Attribute *a2 = new Attribute("att2", type2, "#IMPLIED");
	
	std::list<Attribute*> attList;
	attList.push_back(a);
	attList.push_back(a2);
	
	AttributeList *al = new AttributeList("list", attList);
	
	std::list<Declaration*> decl;
	decl.push_back(e);
	decl.push_back(e2);
	decl.push_back(e3);
	decl.push_back(al);
	Document *d = new Document(decl);
	
	std::cout << d << std::endl;
	
	delete d;
	
	return 0;
	
}
