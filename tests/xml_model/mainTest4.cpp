# include "mainTest4.hpp"

/**
@file mainTest4.cpp
@author Jose GONZALEZ
*/

int mainTest4(){
	freopen("test4.xml","w",stdout);
	//Doctype doctype("rapport","rap1.dtd");
	xml::Element* rapport = new_Element("rapport");
	
//Elements de rapport
	xml::Element* titreRapport = new_Element("titre");
	xml::Element* auteur = new_Element("auteur");
	xml::Element* resume = new_Element("resume");
	xml::Element* chapitre = new_Element("chapitre");

//Elements de titre
	xml::Data* titreD = new xml::Data("Réaliser un compilateur");
	titreRapport->getChildren().push_back(titreD);
	
//Elements auteur
	xml::Element* prenom = new_Element("prenom");
	xml::Data* prenomD = new xml::Data("Nino");
	prenom->getChildren().push_back(prenomD);

	xml::Element* nom = new_Element("nom");
	xml::Data* nomD = new xml::Data("Silverio");
	nom->getChildren().push_back(nomD);

	auteur->getChildren().push_back(prenom);
	auteur->getChildren().push_back(nom);

//Elements resume
	xml::Data* resumeD = new xml::Data("Ceci est un extrait du livre \"Réaliser un compilateur: \nles outils Lex et Yacc\" de Nino Silverio");
	resume->getChildren().push_back(resumeD);

//Elements chapitre
	xml::Element* section1 = new_Element("section");
	xml::Element* section2 = new_Element("section");
	xml::Element* pSection1 = new_Element("p");
	xml::Element* pSection2 = new_Element("p");
	xml::Data* pSection1D1 = new xml::Data(getStrP1_1());
	xml::EmptyElement* img = new_EmptyElement("img");
	xml::Data* pSection1D2 = new xml::Data(getStrP1_2());
	xml::Data* pSection2D = new xml::Data(getStrP2());

	//Attributes img
	AttList attImg;
	attImg.push_back(Att("src","ordinateur.png"));
	attImg.push_back(Att("title","Image"));
	img->SetAttList(&attImg);
	
	pSection1->getChildren().push_back(pSection1D1);
	section1->getChildren().push_back(pSection1);
	pSection1->getChildren().push_back(img);
	pSection1->getChildren().push_back(pSection1D2);
	//section1->AddAttribute(Att("titre","Fonctions et structure d'un compilateur"));
	AttList attPSection1;
	attPSection1.push_back(Att("titre","Fonctions et structure d'un compilateur"));
	section1->SetAttList(&attPSection1);
	section1->getChildren().push_back(pSection1);

	pSection2->getChildren().push_back(pSection2D);
	//section2->AddAttribute(Att("titre","Réalisation d'un compilateur"));
	AttList attPSection2;
	attPSection2.push_back(Att("titre","Réalisation d'un compilateur"));
	section2->SetAttList(&attPSection2);
	section2->getChildren().push_back(pSection2);

	//chapitre->AddAttribute(Att("titre","Introduction: concepts de base"));
	AttList attChapitre;
	attChapitre.push_back(Att("titre","Introduction: concepts de base"));
	chapitre->SetAttList(&attChapitre);
	chapitre->getChildren().push_back(section1);
	chapitre->getChildren().push_back(section2);
	
	//getChildren().push_back Rapport
	rapport->getChildren().push_back(titreRapport);
	rapport->getChildren().push_back(auteur);
	rapport->getChildren().push_back(resume);
	rapport->getChildren().push_back(chapitre);

	//xml::Document document(doctype);
	//xml::document.getChildren().push_back(rapport);
	cout<<rapport;
	fclose (stdout);

	delete rapport;
	return 0;
}

string getStrP1_1(int n){
	return "Tout programme rédigé dans un langage de programmation de haut niveau tel que Pascal ou C ne peut être exécuté par un ordinateur que s'il est traduit en instructions exécutables par l'ordinateur, généralement des instruction en langage machine. L'ordinateur qui doit exécuter le programme ainsi traduit est appelé machine cible. Un ordinateur est représenté sur l'image ci dessous : ";
}

string getStrP1_2(int n){
	return "Voilà.";
}
