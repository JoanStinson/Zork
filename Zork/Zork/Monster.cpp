#include "Monster.h"

Direction Monster::GetDirection() const {
	return position;
}

void Monster::UpdateMonsterPosition() {
	int pos = rand() % 4;
	switch (pos) {
	case 0:
		position = Direction::NORTH;
		break;
	case 1:
		position = Direction::EAST;
		break;
	case 2:
		position = Direction::SOUTH;
		break;
	case 3:
		position = Direction::WEST;
		break;
	}
}

void Monster::Attack(Direction* dir) {

	if (dir != nullptr) {
		if (position == *dir) {
			life--;
			cout << "You hit the " << GetName() << "! " << "It has " << life << " lives left." << endl;
			UpdateMonsterPosition();
		}
		else
			cout << "You missed to attack the " << GetName() << "..." << endl;
	}
}

bool Monster::IsDead() const {
	return life == 0;
}
