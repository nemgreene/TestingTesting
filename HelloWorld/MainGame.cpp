#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;


struct GameState
{
	int score = 0;
};

GameState gameState;

enum GameObjectType
{
	TYPE_PLAYER,
	TYPE_ENEMY,
};

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();

	//Play::LoadBackground("Data\\Backgrounds\\background_01.png");

	Play::CreateGameObject(TYPE_PLAYER, { 640, 360 }, 50, "bullet_sprite" );
	Play::CreateGameObject(TYPE_ENEMY, { 320, 360 }, 50, "bullet_sprite" );
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cOrange );

	//Play::DrawBackground();
	GameObject& obj_player = Play::GetGameObjectByType(TYPE_PLAYER);
	Play::SetSprite(obj_player, "bullet_sprite", 0);	
	Play::UpdateGameObject(obj_player);
	Play::DrawObject(obj_player);

	GameObject& obj_enemy = Play::GetGameObjectByType(TYPE_ENEMY);
	Play::SetSprite(obj_enemy, "bullet_sprite", 0);
	Play::UpdateGameObject(obj_enemy);
	Play::DrawObject(obj_enemy);

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

