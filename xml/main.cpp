# include <iostream>
using namespace std;

# include "Element.h"
# include "Data.h"
# include "Comment.h"

int main(int argc, char**argv)
{
	Xml::Element* element = new Xml::Element("a");
	element->AddAttribute("alt", "Google.fr");
	element->AddAttribute("href", "http://www.google.fr/");

	Xml::Data* data = new Xml::Data("Mon petit lien");
	element->AddChild(data);

	Xml::Comment* comment = new Xml::Comment("Ceci est un commentaire.");
	element->AddChild(comment);
	cout << element << endl;
	delete element;
}
