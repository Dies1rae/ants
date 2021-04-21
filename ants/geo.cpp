#include "geo.h"

bool operator==(const geo& lhs, const geo& rhs) {
	return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

bool operator!=(const geo& lhs, const geo& rhs) {
	return !(lhs == rhs);
}
