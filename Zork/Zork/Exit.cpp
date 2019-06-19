#include "Exit.h"

Direction Exit::GetDirection() {
	return direction;
}

void Exit::SetLocked(bool locked) {
	this->locked = locked;
}

bool Exit::IsLocked() {
	return locked;
}
