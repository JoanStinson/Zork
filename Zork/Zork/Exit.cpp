#include "Exit.h"

Direction Exit::GetDirection() {
	return direction;
}

Room * Exit::GetSource() {
	return source;
}

Room * Exit::GetDestination() {
	return destination;
}

void Exit::SetLocked(bool locked) {
	this->locked = locked;
}

bool Exit::IsLocked() {
	return locked;
}
