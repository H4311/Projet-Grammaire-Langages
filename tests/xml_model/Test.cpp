#include "Test.h"

/**
@file Test.hpp
@author Jose GONZALEZ
*/

pair<string, string> name(string namespaceStr,string nomStr){
	return make_pair(namespaceStr,nomStr);
}

xml::Element* new_Element(string str){
	xml::Element * e = new xml::Element();
	e->setName(name("",str));
	return e;
}

xml::EmptyElement* new_EmptyElement(string str){
	xml::EmptyElement * ee = new xml::EmptyElement();
	ee->setName(name("",str));
	return ee;
}

pair<string, string> Att(string AttName,string AttVal){
	 return make_pair(AttName,AttVal);
}

int Test(){
	mainTest1();
	mainTest2();
	mainTest3();
	mainTest4();
	return 0;
}
