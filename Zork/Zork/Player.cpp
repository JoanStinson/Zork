#include "Player.h"

void Player::GrabItem(Item * item) {
	Insert(item);
}

void Player::DropItem(Item * item) {
	Remove(item);
}
