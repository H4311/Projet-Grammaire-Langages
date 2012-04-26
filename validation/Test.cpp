#include "Validateur.hpp"
#include "../dtd/Document.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"
#include "../dtd/AttributeList.hpp"
#include "../dtd/Name.hpp"
#include "../dtd/Choice.hpp"
#include "../dtd/Seq.hpp"

#include "../xml/Content.hpp"
#include "../xml/Element.hpp"
#include "../xml/Data.hpp"
#include "../xml/Comment.hpp"
#include "../xml/ProcessingInstruction.hpp"
#include "../xml/Document.hpp"

#include <iostream>
#include <list>

int main(int argc, char** argv) {
	
	// doc xml
	xml::Document doc;
	AttList attributes;
	list<xml::Content*> childs;

	xml::ProcessingInstruction* se = new xml::ProcessingInstruction;
	se->SetName(ElementName("","xml"));
	attributes.push_back(Attribut("version", "2.0"));
	attributes.push_back(Attribut("encoding", "utf8"));
	se->SetAttList(attributes);
	doc.setXmlProlog(se);	

	xml::Element* root = new xml::Element;
	root->SetName(ElementName("", "html"));
	doc.setRoot(root);
	
	xml::Element* head = new xml::Element;
	head->SetName(ElementName("", "head"));
	list<xml::Content*> headChildren;
	xml::Element* title = new xml::Element;
	title->SetName(ElementName("", "title"));
	
	list<xml::Content*> titleChild;
	xml::Data* titleContent = new xml::Data("Bienvenue sur mon site oueb !");
	titleChild.push_back(titleContent);
	title->SetChildren(titleChild);
	
	headChildren.push_back(title);
	head->SetChildren(headChildren);
	childs.push_back(head);

	xml::Element* body = new xml::Element;
	body->SetName(ElementName("", "body"));
	childs.push_back(body);
	root->SetChildren(childs);

	xml::Element* element = new xml::Element;
	element->SetName(ElementName("", "a"));
	attributes.clear();
	attributes.push_back(Attribut("alt", "Google.fr"));
	attributes.push_back(Attribut("href", "http://www.google.fr"));	
	element->SetAttList(attributes);
	
	xml::EmptyElement* img = new xml::EmptyElement;
	img->SetName(ElementName("", "img"));
	attributes.clear();
	attributes.push_back(Attribut("src", "http://www.google.fr/img.jpg"));
	img->SetAttList(attributes);

	childs.clear();
	childs.push_back(img);

	xml::Data* data = new xml::Data("Mon petit lien");
	childs.push_back(data);

	xml::Comment* comment = new xml::Comment("<!-- Ceci est un commentaire. -->");
	childs.push_back(comment);
	element->SetChildren(childs);

	childs.clear();
	childs.push_back(element);
	body->SetChildren(childs);

	std::cout << doc << std::endl;



	// doc dtd
	dtd::Name *n = new dtd::Name("Test");
	n->SetCard('+');
	dtd::Name *n2 = new dtd::Name("Test2");
	dtd::Name *n3 = new dtd::Name("Test3");
	n3->SetCard('*');
	dtd::Name *n4 = new dtd::Name("Test4");
	
	std::list<dtd::Children*> l;
	l.push_back(n);
	l.push_back(n2);
	dtd::Choice *c = new dtd::Choice(l);
	c->SetCard('*');
	
	std::list<dtd::Children*> l2;
	l2.push_back(n3);
	l2.push_back(c);
	l2.push_back(n4);
	dtd::Seq *s = new dtd::Seq(l2);
	
	dtd::Element *e = new dtd::Element("ElemTest", s);
	
	dtd::Any *any = new dtd::Any();
	dtd::Element *e2 = new dtd::Element("ElemTest2", any);
	
	dtd::Empty *empty = new dtd::Empty();
	dtd::Element *e3 = new dtd::Element("br", empty);
	
	std::cout << e->getRegex() << std::endl << std::endl;
	
	std::list<std::string> type;
	type.push_back("CDATA");
	dtd::Attribute *a = new dtd::Attribute("att1", type, "#FIXED", "test");
	
	std::list<std::string> type2;
	type2.push_back("enum1");
	type2.push_back("enum2");
	type2.push_back("enum3");
	dtd::Attribute *a2 = new dtd::Attribute("att2", type2, "#IMPLIED");
	
	std::list<dtd::Attribute*> attList;
	attList.push_back(a);
	attList.push_back(a2);
	
	dtd::AttributeList *al = new dtd::AttributeList("list", attList);
	
	std::list<dtd::Declaration*>* decl = new std::list<dtd::Declaration*>();
	decl->push_back(e);
	decl->push_back(e2);
	decl->push_back(e3);
	decl->push_back(al);
	dtd::Document *d = new dtd::Document(decl);
	
	std::cout << d << std::endl;

	/*
	// Tests Validation Node
	cout << "==== Test validationChild ====" << endl;
	std::string dtdNode("(((((titre,))(p,)+)))");
	std::string xmlChildren("titre,p,p,");
	cout << "Regex : " << dtdNode << endl << "Test String :" << xmlChildren << endl << "Résultat : ";
	
	if (Validateur::validationChild(dtdNode, xmlChildren)) 
	{
		cout << "Noeud validé" << endl;
	}
	else
	{
		cout << "Noeud non validé" << endl;
	}
	* */
	
	cout << "==== Test validationDocument ====" << endl;
	
	
	if(Validateur::validationDocument(*d, doc)) {
		cout << "Document validé" << endl;
	} else {
		cout << "Document non validé" << endl;
	}
	delete d;
	
	
	return 0;
}
