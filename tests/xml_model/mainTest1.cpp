# include "mainTest1.hpp"

/**
@file mainTest1.cpp
@author Jose GONZALEZ
*/

xml::Element* rapport = new_Element("rapport");
int mainTest1(){
	freopen("test1.xml","w",stdout);
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
	xml::Element* titreChapitre = new_Element("titre");
	xml::Data* titreChapitreD = new xml::Data("Introduction : concepts de base");
	xml::Element* section1 = new_Element("section");
	xml::Element* section2 = new_Element("section");
	xml::Element* titreSection1 = new_Element("titre");
	xml::Data* titreSection1D = new xml::Data("Fonctions et structure d'un compilateur");
	xml::Element* titreSection2 = new_Element("titre");
	xml::Data* titreSection2D = new xml::Data("Réalisation d'un compilateur");
	xml::Element* pSection1 = new_Element("p");
	xml::Element* pSection2 = new_Element("p");
	xml::Data* pSection1D = new xml::Data(getStrP1());
	xml::Data* pSection2D = new xml::Data(getStrP2());

//Association des childrens
	pSection1Children.push_back(pSection1D);
	titreSection1Children.push_back(titreSection1D);	
	section1Children.push_back(titreSection1);
	section1Children.push_back(pSection1);
	pSection2Children.push_back(pSection2D);
	titreSection2Children.push_back(titreSection2D);
	section2Children.push_back(titreSection2);
	section2Children.push_back(pSection2);
	titreChapitreChildren.push_back(titreChapitreD);
	chapitreChildren.push_back(titreChapitre);
	chapitreChildren.push_back(section1);
	chapitreChildren.push_back(section2);
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
	titreSection1->SetChildren(&titreSection1Children);
	section1->SetChildren(&section1Children);
	pSection2->SetChildren(&pSection2Children);
	titreSection2->SetChildren(&titreSection2Children);
	section2->SetChildren(&section2Children);
	titreChapitre->SetChildren(&titreChapitreChildren);
	chapitre->SetChildren(&chapitreChildren);
	rapport->SetChildren(&rapportChildren);

	//Document document();
	//document.getChildren().push_back(rapport);*/

	cout<<rapport;
	fclose (stdout);
	
	delete rapport;
	return 0;
}

string getStrP1(){
	return "Tout programme rédigé dans un langage de programmation de haut niveau tel que Pascal ou C ne peut être exécuté par un ordinateur que s'il est traduit en instructions exécutables par l'ordinateur, généralement des instruction en langage machine. L'ordinateur qui doit exécuter le programme ainsi traduit est appelé machine cible.";
}

string getStrP2(){
	return "Comme l'écriture d'un compilateur est une tâche fort complexe, le programmateur a tout intérêt à travailler en utilisant un langage de programmation de haut niveau.";
}