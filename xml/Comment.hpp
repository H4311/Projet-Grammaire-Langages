#ifndef __XML_COMMENT_H__
#define __XML_COMMENT_H__

# include "Content.hpp"
# include <string>
using namespace std;

namespace xml {
	class Comment : public Content {
	private:
		string comment;

	public:
		Comment(string _c) : comment(_c) { /* empty */ }
		
		virtual ostream& toString(ostream& stream, int depth);
	};
}
#endif
