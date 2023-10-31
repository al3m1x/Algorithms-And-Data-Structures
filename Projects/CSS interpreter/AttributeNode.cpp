#include "AttributeNode.h"

std::ostream& operator<<(std::ostream& out, const NodeAtt& next) {
	return out << next.attribute.property << " " << next.attribute.value;
}