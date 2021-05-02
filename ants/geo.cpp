#include "geo.h"

inline bool operator==(const geo& lhs, const geo& rhs) {
	return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

inline bool operator!=(const geo& lhs, const geo& rhs) {
	return !(lhs == rhs);
}