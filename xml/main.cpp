# include <iostream>
using namespace std;

# include "Element.h"
# include "Data.h"
# include "Comment.h"
# include "SpecialElement.h"

int main(int argc, char**argv)
{
	Xml::Element* root = new Xml::Element("body");

	Xml::SpecialElement* se = new Xml::SpecialElement("xml");
	se->AddAttribute("version", "2.0");
	root->AddChild(se);

	Xml::Element* element = new Xml::Element("a");
	element->AddAttribute("alt", "Google.fr");
	element->AddAttribute("href", "http://www.google.fr/");
	Xml::Data* data = new Xml::Data("Mon petit lien");
	element->AddChild(data);

	Xml::Comment* comment = new Xml::Comment("Ceci est un commentaire.");
	element->AddChild(comment);

	root->AddChild(element);
	cout << root << endl;
	delete root;
}

