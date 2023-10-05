#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Maths.h"
#include "SpriteManager.h"
#include "Utilities.h"
#include "HandleInputs.h"
#include "PlayerMovement.h"
#include "Gun.h"
#include "UI.h"
#include "Map.h"

int DISPLAY_WIDTH = 1254;//38 tiles across
int DISPLAY_HEIGHT = 693;//21 tiles across
int DISPLAY_SCALE = 1;

Vec2 vPlayerPos(DISPLAY_WIDTH/2, DISPLAY_HEIGHT / 2);

enum GameStateType 
{
	STATE_MENU,
	STATE_PLAY,
	STATE_GAMEOVER,
};

struct GameState {
	int score = 0;
	GameStateType currentGameState = STATE_MENU;
};

GameState gameState;

#pragma region NeedsWork

//Detect map collisions one way or another to make sure nobody walks/flies through walls
void utilBuildMap();

//Handle user commands
void HandleInputs() {
	//Once the sprite has been drawn 
	//Is user moving
	//Is the user shooting, do they have ammo
	//Is user dodging, can they dodge, where are they dodging
	//reload, handle perfect reload
};

void HandleEnemyMovement();
// random movement pattern
// VV
//a* pathfinding, raytracing
#pragma endregion

SpriteManager spriteManager = SpriteManager();

Gun primaryGun = Gun::Gun(TYPE_BULLET_PRIMARY, "laser_2", &spriteManager);

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground("Data\\Backgrounds\\testing_background.png");

	int iPlayer = Play::CreateGameObject(TYPE_PLAYER, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 50, "fry");
	int iGunPrimary = Play::CreateGameObject(TYPE_GUN_PRIMARY, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 50, "lava_gun");
	int iRobit = Play::CreateGameObject(TYPE_ENEMY, { 350, 350 }, 50, "robit");

	std::vector<std::map<int, std::string>> vInitializeSpriteMap = {
		{},		//Background    0
		{},												  //Bullets       1
		{{iRobit, "robit_running_down_6"}} , //Enemies       2
		{},                                  //enemies guns  3
		{{iPlayer, "fry_ruinning_down_6"} }, //Char          4
		{{iGunPrimary, "lava_gun_1"}},       //Guns          5
		{}									 //foreground    6
	};

	spriteManager.initializeSprites(vInitializeSpriteMap);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);
	//Play::ClearDrawingBuffer( Play::cOrange );
	Play::DrawBackground();
	//get mouse position
	Vec2 vMousePos = Play::GetMousePos();
	//calculate aim vector
	Vec2 vAimVec = utilHandleCursorDirection({ player.pos.x,player.pos.y }, vMousePos);


	utilDebugString("The mouse is colliding: " + std::to_string(MaxsCollisionChecker({player.pos.x,player.pos.y}, simpleCollisionMap)), 400, 400);
	//catch user inputs

	handleInputs({ player.pos.x,player.pos.y }, vAimVec, &primaryGun);

	HandlePlayerMovement();
	//tick all sprites
	spriteManager.tickSprites(vMousePos, vAimVec.rad());

	//tick all bullets
	primaryGun.moveBullets();

	//Ui sprite render
	handleUI(60, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	utilJanitor();
	//display
	Play::PresentDrawingBuffer();
	//dismount
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

void UpdateGameState()
{
	switch (gameState.currentGameState)
	{
		case STATE_MENU:
			// display title
			// display controls
			// "PRESS SPACE TO START"
		break;

		case STATE_PLAY:
			// current build
		break;

		case STATE_GAMEOVER:
			// display "GAME OVER"
			// display score
			// "PRESS SPACE TO RESTART"
		break;
	}
}