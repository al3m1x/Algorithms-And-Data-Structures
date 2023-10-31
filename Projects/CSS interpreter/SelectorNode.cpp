#include "SelectorNode.h"

std::ostream& operator<<(std::ostream& out, const NodeSel& next) {
	return out << next.selector << " ";
}