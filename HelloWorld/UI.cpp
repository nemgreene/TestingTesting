#define PLAY_USING_GAMEOBJECT_MANAGER
#include "UI.h"
#include "Play.h"


void handleUI(int _playerHealth, int _playerMaxHealth, int DISPLAY_WIDTH, int DISPLAY_HEIGHT)
{
	//load all the sprites
	//load in player health
	//if statement about the amount of health
	float HealthD = (_playerHealth - 0.75*_playerMaxHealth) / (0.25*_playerMaxHealth);
	if (HealthD < 0)
		HealthD = 0;
	if (HealthD > 1)
		HealthD = 1;
	float HealthC = (_playerHealth - 0.5 * _playerMaxHealth) / (0.25 * _playerMaxHealth);
	if (HealthC < 0)
		HealthC = 0;
	if (HealthC > 1)
		HealthC = 1;
	float HealthB = (_playerHealth - 0.25 * _playerMaxHealth) / (0.25 * _playerMaxHealth);
	if (HealthB < 0)
		HealthB = 0;
	if (HealthB > 1)
		HealthB = 1;
	float HealthA = (_playerHealth - 0.f ) / (0.25 * _playerMaxHealth);
	if (HealthA < 0)
		HealthA = 0;
	if (HealthA > 1)
		HealthA = 1;
	// Calculating Dash transparency
	GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);
	float DashTimer = player.Timer;
	float DashUI = (DashTimer - 0.5) / 3.5;
	if (player.Timer == 0)
	{
		DashUI = 1.f;
	}


	//make visible portions of health bar based on health percentage and dash regen
	//draw all sprites
	Play::DrawSprite("UI_background", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 },1);
	Play::DrawSpriteTransparent("UI_dashbar", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50}, 1, DashUI);
	Play::DrawSpriteTransparent("UI_healthA", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 }, 1, HealthA);
	Play::DrawSpriteTransparent("UI_healthB", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 }, 1, HealthB);
	Play::DrawSpriteTransparent("UI_healthC", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 }, 1, HealthC);
	Play::DrawSpriteTransparent("UI_healthD", { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 50 }, 1, HealthD);
	




}
