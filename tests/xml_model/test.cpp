# include <iostream>
# include <list>
using namespace std;

# include "Content.hpp"
# include "Element.hpp"
# include "Data.hpp"
# include "Comment.hpp"
# include "ProcessingInstruction.hpp"
# include "Document.hpp"

int main(int argc, char**argv)
{
	xml::Document doc;
	AttList attributes;
	list<xml::Content*> childs;

	xml::ProcessingInstruction* se = new xml::ProcessingInstruction;
	ElementName * seName = new ElementName("", "xml");
	se->SetName(*seName);
	delete seName;

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

	cout << doc << endl;
}
