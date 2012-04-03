#ifndef __XML_COMMENT_H__
#define __XML_COMMENT_H__

# include "Content.h"
# include <string>
using namespace std;

namespace Xml {
	class Comment : public Content {
	private:
		string comment;

	public:
		Comment(string _c) : comment(_c) { /* empty */ }
		
		virtual ostream& toString(ostream& stream);
	};
}
#endif
