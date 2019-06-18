#include "Exit.h"

//void Exit::Update()
//{
//}

void Exit::SetLocked(bool locked) {
	this->locked = locked;
}

bool Exit::IsLocked()
{
	return locked;
}
