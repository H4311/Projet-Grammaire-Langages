#ifndef DTD_DOCUMENT_H
#define DTD_DOCUMENT_H

#include<string>
#include<list>
#include<iostream>

namespace dtd {

	class Declaration;
	
	class Document {
		public:
			Document(std::list<Declaration*> _declarations = NULL);
			virtual ~Document();
			std::ostream& put(std::ostream& out);
		
		protected:
			std::list<Declaration*> declarations;
	};
	
	class Declaration {
		public:
			virtual ~Declaration();
			virtual std::ostream& put(std::ostream& out) = 0;
	};
}

std::ostream& operator<<(std::ostream& out, dtd::Document* d);

std::ostream& operator<<(std::ostream& out, dtd::Declaration* d);

#endif
