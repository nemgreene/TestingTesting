#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Maths.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;
Vec2 PlayerPos(640,360);

struct GameState
{
	int score = 0;
};

GameState gameState;

enum GameObjectType
{
	TYPE_PLAYER,
	TYPE_ENEMY,
	TYPE_BULLET,
};

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();

	//Play::LoadBackground("Data\\Backgrounds\\background_01.png");

	Play::CreateGameObject(TYPE_PLAYER, { PlayerPos.GetX(),PlayerPos.GetY() }, 50, "phillip");
	Play::CreateGameObject(TYPE_BULLET, { PlayerPos.GetX(),PlayerPos.GetY() }, 50, "laser");
	//Play::CreateGameObject(TYPE_ENEMY, { 320, 360 }, 50, "bullet_sprite" );
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cOrange );
	Vec2 MousePos = Play::GetMousePos();
	Vec2 MouseDir = MousePos - PlayerPos;
	float MouseDirMag = MouseDir.mag(MouseDir);

	Vec2 MouseUnitVec{MouseDir.GetX()/MouseDirMag, MouseDir.GetY() / MouseDirMag };

	// Printing out the mouse direction
	std::string DirectionXString = std::to_string(MouseUnitVec.GetX());
	std::string DirectionYString = std::to_string(MouseUnitVec.GetY());
	std::string DirectionString = "x = " + DirectionXString + ", y =" + DirectionYString;
	const char* PS = DirectionString.c_str();
	Play::DrawDebugText({ 150,50 }, PS);
	// finished printing



	//Play::DrawBackground();
	GameObject& obj_player = Play::GetGameObjectByType(TYPE_PLAYER);
	GameObject& obj_bullet = Play::GetGameObjectByType(TYPE_BULLET);
	obj_bullet.rotation = MouseUnitVec.rad(MouseUnitVec);
	Play::SetSprite(obj_player, "phillip_idle_6", 0.16666f);
	Play::SetSprite(obj_bullet, "laser_2", 0.5);
	Play::UpdateGameObject(obj_player);
	Play::UpdateGameObject(obj_bullet);
	Play::DrawObjectRotated(obj_player);
	Play::DrawObjectRotated(obj_bullet);

	//Play::DrawObject(obj_player);

	/*GameObject& obj_enemy = Play::GetGameObjectByType(TYPE_ENEMY);
	Play::SetSprite(obj_enemy, "bullet_sprite", 0);
	Play::UpdateGameObject(obj_enemy);
	Play::DrawObject(obj_enemy);*/

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

