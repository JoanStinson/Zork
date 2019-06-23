#include "Exit.h"

Direction Exit::GetDirection() const {
	return direction;
}

Room* Exit::GetSource() const {
	return source;
}

Room* Exit::GetDestination() const {
	return destination;
}

void Exit::SetLocked(bool locked) {
	this->locked = locked;
}

bool Exit::IsLocked() const {
	return locked;
}
