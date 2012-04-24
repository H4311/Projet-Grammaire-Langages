# include <iostream>
# include <list>
using namespace std;

# include "../../xml/Content.hpp"
# include "../../xml/Element.hpp"
# include "../../xml/Data.hpp"
# include "../../xml/Comment.hpp"
# include "../../xml/ProcessingInstruction.hpp"
# include "../../xml/Document.hpp"

int main(int argc, char**argv)
{
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
	root->SetChilds(&childs);

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
	element->SetChilds(&childs);

	childs.clear();
	childs.push_back(element);
	// body->AddChild(element);
	body->SetChilds(&childs);

	cout << doc << endl;
}

