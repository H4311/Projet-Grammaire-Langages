
#include<list>
#include<string>
#include<iostream>

#include "Document.hpp"
#include "Element.hpp"
#include "Attribute.hpp"

using namespace dtd;

int main() {
	
	Name *n = new Name("Test");
	Name *n2 = new Name("Test2");
	Name *n3 = new Name("Test3");
	Name *n4 = new Name("Test4");
	
	std::list<Children*> l;
	l.push_back(n);
	l.push_back(n2);
	Choice *c = new Choice(l);
	
	std::list<Children*> l2;
	l2.push_back(n3);
	l2.push_back(c);
	l2.push_back(n4);
	Seq *s = new Seq(l2);
	
	Element *e = new Element("ElemTest", s);
	
	std::list<std::string> att;
	att.push_back("att1");
	att.push_back("att2");
	Attribute *a = new Attribute("AttTest", att);
	
	std::list<Declaration*> decl;
	decl.push_back(e);
	decl.push_back(a);
	Document *d = new Document(decl);
	
	std::cout << d << std::endl;
	
	//delete e;
	//delete a;
	//delete d;
	
	return 0;
	
}
