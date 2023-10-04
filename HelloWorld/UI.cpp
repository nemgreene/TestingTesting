#define PLAY_USING_GAMEOBJECT_MANAGER
#include "UI.h"
#include "Play.h"


void handleUI(int _playerHealth, int DISPLAY_WIDTH, int DISPLAY_HEIGHT)
{
	//load all the sprites
	//load in player health
	//if statement about the ammount of health
	float HealthD = (_playerHealth - 75.f) / 25.f;
	if (HealthD < 0)
		HealthD = 0;
	if (HealthD > 1)
		HealthD = 1;
	float HealthC = (_playerHealth - 50.f) / 25.f;
	if (HealthC < 0)
		HealthC = 0;
	if (HealthC > 1)
		HealthC = 1;
	float HealthB = (_playerHealth - 25.f) / 25.f;
	if (HealthB < 0)
		HealthB = 0;
	if (HealthB > 1)
		HealthB = 1;
	float HealthA = (_playerHealth - 0.f ) / 25.f;
	if (HealthA < 0)
		HealthA = 0;
	if (HealthA > 1)
		HealthA = 1;
	//make visible portions of health bar based on health percentage
	//draw all sprites
	Play::DrawSprite("UI_background", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 },1);
	Play::DrawSpriteTransparent("UI_dashbar", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50}, 1, 1.0f);
	Play::DrawSpriteTransparent("UI_healthA", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 }, 1, HealthA);
	Play::DrawSpriteTransparent("UI_healthB", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 }, 1, HealthB);
	Play::DrawSpriteTransparent("UI_healthC", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 }, 1, HealthC);
	Play::DrawSpriteTransparent("UI_healthD", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 }, 1, HealthD);
	std::cout << "test";
}
