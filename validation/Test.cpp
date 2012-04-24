#include "Validateur.hpp"
#include "../dtd/Document.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"
#include <iostream>
#include <list>

int main(int argc, char** argv) {
	//Création du doc dtd
	dtd::Name *n = new dtd::Name("Test");
	dtd::Name *n2 = new dtd::Name("Test2");
	dtd::Name *n3 = new dtd::Name("Test3");
	dtd::Name *n4 = new dtd::Name("Test4");
	
	std::list<dtd::Children*> l;
	l.push_back(n);
	l.push_back(n2);
	dtd::Choice *c = new dtd::Choice(l);
	
	std::list<dtd::Children*> l2;
	l2.push_back(n3);
	l2.push_back(c);
	l2.push_back(n4);
	dtd::Seq *s = new dtd::Seq(l2);
	
	dtd::Element *e = new dtd::Element("ElemTest", s);
	
	std::list<std::string> att;
	att.push_back("att1");
	att.push_back("att2");
	dtd::Attribute *a = new dtd::Attribute("AttTest", att);
	
	std::list<dtd::Declaration*> decl;
	decl.push_back(e);
	decl.push_back(a);
	dtd::Document *d = new dtd::Document(decl);
	
	std::cout << d << std::endl;
	
	delete d;
	
	
	
	return 0;
}
