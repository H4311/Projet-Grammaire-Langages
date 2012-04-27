
/**
 * @file Test.hpp
 * @brief Tests - XPATH
 * 
 * Contains the test functions for the XPATH finder.
 * 
 * @author Thibaut Patel & Arnaud Lahache & un peu Benjamin Bouvier
 */

# include <iostream>
# include <list>
using namespace std;

# include "../xml/Content.hpp"
# include "../xml/Element.hpp"
# include "../xml/Data.hpp"
# include "../xml/Comment.hpp"
# include "../xml/EmptyElement.hpp"
# include "../xml/Document.hpp"
# include "XPath.hpp"
using namespace xml;
using namespace xpath;

# include "../tests/TestFramework.hpp"

static Document *singleton = NULL;

static Document & getDoc()
{
	if(singleton)
	{
		return *singleton;
	}

	singleton = new Document;
	Document & doc = *singleton;
	doc.setDoctype(Doctype("html.dtd", "html"));

	AttList attributes;
	list<Content*> childs;

	ProcessingInstruction* se = new ProcessingInstruction;
	ElementName * seName = new ElementName("", "xml");
	se->setName(*seName);
	delete seName;

	attributes.push_back(Attribut("version", "2.0"));
	attributes.push_back(Attribut("encoding", "utf8"));
	se->setAttList(attributes);
	doc.setXmlProlog(se);	

	Element* root = new Element;
	root->setName(ElementName("", "html"));
	doc.setRoot(root);
	
	Element* head = new Element;
	head->setName(ElementName("", "head"));
	list<Content*> headChildren;
	Element* title = new Element;
	title->setName(ElementName("", "title"));
	
	list<Content*> titleChild;
	Data* titleContent = new Data("Bienvenue");
	titleChild.push_back(titleContent);
	title->setChildren(titleChild);
	
	headChildren.push_back(title);
	head->setChildren(headChildren);
	childs.push_back(head);

	Element* body = new Element;
	body->setName(ElementName("", "body"));
	childs.push_back(body);
	root->setChildren(childs);

	Element* element = new Element;
	element->setName(ElementName("", "a"));
	attributes.clear();
	attributes.push_back(Attribut("alt", "Google.fr"));
	attributes.push_back(Attribut("href", "http://www.google.fr"));	
	element->setAttList(attributes);
	
	EmptyElement* img = new EmptyElement;
	img->setName(ElementName("", "img"));
	attributes.clear();
	attributes.push_back(Attribut("src", "http://www.google.fr/img.jpg"));
	img->setAttList(attributes);

	childs.clear();
	childs.push_back(img);

	Data* data = new Data("Mon petit lien");
	childs.push_back(data);

	Comment* comment = new Comment("<!-- Ceci est un commentaire. -->");
	childs.push_back(comment);
	element->setChildren(childs);

	childs.clear();
	childs.push_back(element);
	body->setChildren(childs);

	return doc;
}

struct TestAffichage : public TestCase
{
	TestAffichage() : TestCase("Affichage du document (validation humaine)") {}
	bool operator()()
	{
		Document & doc = getDoc();
		cout << doc << endl;
		return true;
	}
};

struct TestTitle : public TestCase
{
	TestTitle() : TestCase("Affichage du contenu de la balise <title> : Bienvenue)") {}
	bool operator()()
	{
		Document & doc = getDoc();
		Element* e = dynamic_cast<Element*>(doc.getRoot());
		if(e == NULL) return false;
		
		string res = xpath::find(e, "./head/title");
		cout << res << endl;
		
		if(res == "Bienvenue") return true;
		else return false;
	}
};

struct TestAttribute : public TestCase
{
	TestAttribute() : TestCase("Affichage du contenu de l'attribut alt de la balise <a> : Google.fr)") {}
	bool operator()()
	{
		Document & doc = getDoc();
		Element* e = dynamic_cast<Element*>(doc.getRoot());
		if(e == NULL) return false;
		
		string res = xpath::find(e, "./body/a/@alt");
		cout << res << endl;
		
		if(res == "Google.fr") return true;
		else return false;
	}
};

int main(int argc, char** argv)
{
	TestSuite suite;
	
	suite.add(new TestAffichage);
	suite.add(new TestTitle);
	suite.add(new TestAttribute);
	
	suite.launch();

	delete singleton;
}
