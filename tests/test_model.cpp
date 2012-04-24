# include <iostream>
using namespace std;

# include "Element.hpp"
# include "Data.hpp"
# include "Comment.hpp"
# include "ProcessingInstruction.hpp"
# include "Document.hpp"

int main(int argc, char**argv)
{
	xml::Document doc;

	xml::ProcessingInstruction* se = new xml::ProcessingInstruction(ElementName("","xml"));
	se->AddAttribute(Attribut("version", "2.0"));
	doc.setXmlProlog(se);	

	xml::Element* root = new xml::Element(ElementName("", "html"));
	doc.setRoot(root);

	xml::Element* body = new xml::Element(ElementName("", "body"));
	root->AddChild(body);

	xml::Element* element = new xml::Element(ElementName("", "a"));
	element->AddAttribute(Attribut("alt", "Google.fr"));
	element->AddAttribute(Attribut("href", "http://www.google.fr/"));
	xml::Data* data = new xml::Data("Mon petit lien");
	element->AddChild(data);

	xml::Comment* comment = new xml::Comment("Ceci est un commentaire.");
	element->AddChild(comment);

	body->AddChild(element);

	cout << doc << endl;
}

