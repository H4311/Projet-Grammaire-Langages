# include <iostream>
# include <list>
using namespace std;

# include "Content.hpp"
# include "Element.hpp"
# include "Data.hpp"
# include "Comment.hpp"
# include "ProcessingInstruction.hpp"
# include "Document.hpp"
using namespace xml;

# include "../tests/TestFramework.hpp"

static Document * singleton = NULL;

static Document & getDoc()
{
	if (singleton)
	{
		return *singleton;
	}

	singleton = new Document;
	Document & doc = *singleton;

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
	Data* titleContent = new Data("Bienvenue sur mon site oueb !");
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

struct TestContenu : public TestCase
{
	TestContenu() : TestCase("Vérifier que le contenu du document est bien celui créé.") {}
	bool operator()()
	{
		Document & doc = getDoc();
		Element* root = static_cast<Element*>(doc.getRoot());
		cout << "Vérifier que la racine est bien de type Element...";
		bool check = root != NULL;
		if (!check) return false;
		cout << "OK\nVérifier que le nom de l'élément racine est bien html...";
		check = root->getName() == "html";
		if (!check) return false;
		cout << "OK\nVérifier que html contient bien deux fils...";
		check = root->getChildren().size() == 2;
		if (!check) return false;
		cout << "OK" << endl;
		return true;
	}
};

int main(int argc, char** argv)
{
	TestSuite suite;
	
	suite.add(new TestAffichage);
	suite.add(new TestContenu);
	
	suite.launch();

	delete singleton;
}
