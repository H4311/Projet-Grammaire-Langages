# include "mainTest2.hpp"

/**
@file mainTest2.cpp
@author Jose GONZALEZ
*/

int mainTest2(){
	freopen("test2.xml","w",stdout);
//Declaration des listes des childrens
	list<xml::Content*> titreRapportChildren;
	list<xml::Content*> prenomChildren;
	list<xml::Content*> nomChildren;
	list<xml::Content*> auteurChildren;
	list<xml::Content*> resumeChildren;
	list<xml::Content*> pSection1Children;
	list<xml::Content*> titreSection1Children;
	list<xml::Content*> section1Children;
	list<xml::Content*> pSection2Children;
	list<xml::Content*> titreSection2Children;
	list<xml::Content*> section2Children;
	list<xml::Content*> titreChapitreChildren;
	list<xml::Content*> chapitreChildren;
	list<xml::Content*> rapportChildren;

	//Doctype doctype("rapport","rap1.dtd");
	xml::Element* rapport = new_Element("rapport");
	
//Elements de rapport
	xml::Element* titreRapport = new_Element("titre");
	xml::Element* auteur = new_Element("auteur");
	xml::Element* resume = new_Element("resume");
	xml::Element* chapitre = new_Element("chapitre");

//Elements de titre
	xml::Data* titreD = new xml::Data("Réaliser un compilateur");
	titreRapportChildren.push_back(titreD);
	
//Elements auteur
	xml::Element* prenom = new_Element("prenom");
	xml::Data* prenomD = new xml::Data("Nino");
	prenomChildren.push_back(prenomD);

	xml::Element* nom = new_Element("nom");
	xml::Data* nomD = new xml::Data("Silverio");
	nomChildren.push_back(nomD);

	auteurChildren.push_back(prenom);
	auteurChildren.push_back(nom);

//Elements resume
	xml::Data* resumeD = new xml::Data("Ceci est un extrait du livre \"Réaliser un compilateur: \nles outils Lex et Yacc\" de Nino Silverio");
	resumeChildren.push_back(resumeD);

//Elements chapitre
	xml::Element* section1 = new_Element("section");
	xml::Element* section2 = new_Element("section");
	xml::Element* pSection1 = new_Element("p");
	xml::Element* pSection2 = new_Element("p");
	xml::Data* pSection1D = new xml::Data(getStrP1());
	xml::Data* pSection2D = new xml::Data(getStrP2());
	
//Attributes
	pSection1Children.push_back(pSection1D);
	//section1->AddAttribute(Att("titre","Fonctions et structure d'un compilateur"));
	AttList attPSection1;
	attPSection1.push_back(Att("titre","Fonctions et structure d'un compilateur"));
	section1->SetAttList(&attPSection1);
	section1Children.push_back(pSection1);

	pSection2Children.push_back(pSection2D);
	//section2->AddAttribute(Att("titre","Réalisation d'un compilateur"));
	AttList attPSection2;
	attPSection2.push_back(Att("titre","Réalisation d'un compilateur"));
	section2->SetAttList(&attPSection2);
	section2Children.push_back(pSection2);

	//chapitre->AddAttribute(Att("titre","Introduction: concepts de base"));
	AttList attChapitre;
	attChapitre.push_back(Att("titre","Introduction: concepts de base"));
	chapitre->SetAttList(&attChapitre);
	chapitreChildren.push_back(section1);
	chapitreChildren.push_back(section2);
	
	//getChildren().push_back Rapport
	rapportChildren.push_back(titreRapport);
	rapportChildren.push_back(auteur);
	rapportChildren.push_back(resume);
	rapportChildren.push_back(chapitre);

	//SetChildrens
	titreRapport->SetChildren(&titreRapportChildren);
	prenom->SetChildren(&prenomChildren);
	nom->SetChildren(&nomChildren);
	auteur->SetChildren(&auteurChildren);
	resume->SetChildren(&resumeChildren);
	pSection1->SetChildren(&pSection1Children);
	section1->SetChildren(&section1Children);
	pSection2->SetChildren(&pSection2Children);
	section2->SetChildren(&section2Children);
	chapitre->SetChildren(&chapitreChildren);
	rapport->SetChildren(&rapportChildren);

	//xml::Document document(doctype);
	//xml::document.getChildren().push_back(rapport);
	cout<<rapport;
	fclose (stdout);

	delete rapport;
	return 0;
}