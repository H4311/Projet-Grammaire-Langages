#include "Validateur.hpp"
#include "../dtd/Document.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"
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
	
	//Création du doc xml
	
	xml::Document doc;

	xml::ProcessingInstruction* se = new xml::ProcessingInstruction(ElementName("","xml"));
	AttList attributes;
	attributes.push_back(Attribut("version", "2.0"));
	// se->AddAttribute(Attribut("version", "2.0"));
	se->SetAttList(&attributes);
	doc.setXmlProlog(se);	

	xml::Element* root = new xml::Element(ElementName("", "html"));
	doc.setRoot(root);

	xml::Element* body = new xml::Element(ElementName("", "body"));
	// root->AddChild(body);
	list<xml::Content*> childs;
	childs.push_back(body);
	root->SetChildren(&childs);

	xml::Element* element = new xml::Element(ElementName("", "a"));
	attributes.push_back(Attribut("alt", "Google.fr"));
	attributes.push_back(Attribut("href", "http://www.google.fr"));	
	element->SetAttList(&attributes);
	// element->AddAttribute(Attribut("alt", "Google.fr"));
	// element->AddAttribute(Attribut("href", "http://www.google.fr/"));
	xml::Data* data = new xml::Data("Mon petit lien");
	// element->AddChild(data);
	childs.clear();
	childs.push_back(data);

	xml::Comment* comment = new xml::Comment("Ceci est un commentaire.");
	// element->AddChild(comment);
	childs.push_back(comment);
	element->SetChildren(&childs);

	childs.clear();
	childs.push_back(element);
	// body->AddChild(element);
	body->SetChildren(&childs);

	std::cout << doc << std::endl;
	
	
	// Tests Validation Node
	cout << "==== Test validationNode ====" << endl;
	std::string dtdNode("(titre,)(p,)+");
	std::string xmlChildren("titre,p,p,");
	cout << "Regex : " << dtdNode << endl << "Test String :" << xmlChildren << endl << "Résultat : ";
	
	if (Validateur::validationNode(dtdNode, xmlChildren)) 
	{
		cout << "Noeud validé" << endl;
	}
	else
	{
		cout << "Noeud non validé" << endl;
	}
	
	
	delete d;
	
	return 0;
}
