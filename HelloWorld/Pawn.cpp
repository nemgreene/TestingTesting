#include "Pawn.h"
Pawn::Pawn() {};
Pawn::Pawn(GameObject* player) {
	_player = player;
}
void Pawn::_ApplyMovement() {

	_tempVelocity = _tempVelocity * _moveSpeed;

	float tempX = abs(_tempVelocity.x);
	float tempY = abs(_tempVelocity.y);

	//if x > 6, set it to 6, if x < -6, set it -6, else leave it alone
	//Limits vector to 6 or -6

	_tempVelocity.x = (tempX < 6) ? tempX : (6 > _tempVelocity.x) ? -6 : 6;
	_tempVelocity.y = (tempY < 6) ? tempY : (6 > _tempVelocity.y) ? -6 : 6;
	/*_tempvelocity.x = (tempX < 6 ) ? _tempvelocity.x : 6;
	_tempvelocity.y = (abs(_tempvelocity.y) < 6 ) ? _tempvelocity.y : 6;*/

	if (_tempVelocity.x != 0 && _tempVelocity.y != 0)
	{
		_tempVelocity.x /= 1.414;
		_tempVelocity.y /= 1.414;
	}

	_player->velocity = _tempVelocity;
	
	
	GameObject& player = *_player;
	if (Play::IsLeavingDisplayArea(player))
		_player->pos = _player->oldPos;
}