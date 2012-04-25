        list<xml::Content*> childrenTitreRapport;
	childrenTitreRapport.push_back(titreD);
	titreRapport->SetChildren(&childrenTitreRapport
	list<xml::Content*> prenomChildren;
	prenomChildren.push_back(prenomD);
	prenom->SetChildren(&prenomChildren);

	xml::Element* nom = new_Element("nom");
	xml::Data* nomD = new xml::Data("Silverio");
	list<xml::Content*> nomChildren;
	nomChildren.push_back(nomD);
	nom->SetChildren(&nomChildren);

	list<xml::Content*> auteurChildren;
	auteurChildren.push_back(prenom);
	auteurChildren.push_back(nom);
	auteur->SetChildren(&auteurChildren);

	list<xml::Content*> resumeChildren;
	resumeChildren.push_back(resumeD);
	resume->SetChildren(&resumeChildren//Childrens du paragraph de la section 1: p1Data
	list<xml::Content*> pSection1Children;
	pSection1Children.push_back(pSection1D);
	pSection1->SetChildren(&pSection1Children);

//Childrens du titre de la premiere section: titreSection1Data
	list<xml::Content*> titreSection1Children;
	titreSection1Children.push_back(titreSection1D);
	titreSection1->SetChildren(&titreSection1Children);

//Childrens de la section 1: titre et paragraph
	list<xml::Content*> section1Children;
	section1Children.push_back(titreSection1);
	section1Children.push_back(pSection1);
	section1->SetChildren(&section1Children);

//Childrens du paragraph de la section 2: p2Data
	list<xml::Content*> pSection2Children;
	pSection2Children.push_back(pSection2D);
	pSection2->SetChildren(&pSection2Children);

//Childrens du titre de la section 2: titreSection2Data
	list<xml::Content*> titreSection2Children;
	titreSection2Children.push_back(titreSection2D);
	titreSection2->SetChildren(&titreSection2Children);

//Childrens de la section 2: titre et paragraph
	list<xml::Content*> section2Children;
	section2Children.push_back(titreSection2);
	section2Children.push_back(pSection2);
	section2->SetChildren(&section2Children);

//Childrens du titre du chapitre: titreChapitreData
	list<xml::Content*> titreChapitreChildren;
	titreChapitreChildren.push_back(titreChapitreD);
	titreChapitre->SetChildren(&titreChapitreChildren);

	list<xml::Content*> chapitreChildren;
	chapitreChildren.push_back(titreChapitre);
	chapitreChildren.push_back(section1);
	chapitreChildren.push_back(section2);
	chapitre->SetChildren(&chapitreChildren);	

	//getChildren().push_back Rapport
	list<xml::Content*> rapportChildren;
	rapportChildren.push_back(titreRapport);
	rapportChildren.push_back(auteur);
	rapportChildren.push_back(resume);
	rapportChildren.push_back(chapitre);
	rapport->SetChildren(&rapportChildren);

	//Document document();
	//document.getChildren().push_back(rapport);*/