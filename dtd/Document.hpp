#ifndef DTD_DOCUMENT_H
#define DTD_DOCUMENT_H

#include<list>
#include<iostream>

#include "Declaration.hpp"

namespace dtd {	
	class Document {
		public:
			Document(std::list<Declaration*> _declarations = NULL);
			virtual ~Document();
			std::ostream& put(std::ostream& out);
			std::list<Declaration*> getDeclarations();
		
		protected:
			std::list<Declaration*> declarations;
	};
}

std::ostream& operator<<(std::ostream& out, dtd::Document* d);

#endif
