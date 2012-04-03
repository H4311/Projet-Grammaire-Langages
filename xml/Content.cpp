# include "Content.h"

ostream& operator<<(ostream& stream, Xml::Content* content) {
	return content->toString(stream);
}
