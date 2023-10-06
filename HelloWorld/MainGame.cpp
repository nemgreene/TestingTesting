#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "UI.h"
#include "Map.h"
#include "Gun.h"
#include "Play.h"
#include "Maths.h"
#include "Utilities.h"
#include "ChickenGun.h"
#include "HandleInputs.h"
#include "SpriteManager.h"
#include "PlayerMovement.h"
#include "EnemyController.h"

int DISPLAY_WIDTH = 1254;//38 tiles across
int DISPLAY_HEIGHT = 693;//21 tiles across
int DISPLAY_SCALE = 1;

Vec2 vPlayerPos(DISPLAY_WIDTH/2, DISPLAY_HEIGHT / 2);

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
EnemyController enemyController = EnemyController(&spriteManager, &gameState);

ChickenGun primaryGun = ChickenGun::ChickenGun(TYPE_BULLET_PRIMARY, "Chicken_Bullets_4", &spriteManager);
Gun secondaryGun = Gun::Gun(TYPE_BULLET_SECONDARY, "laser_2", &spriteManager);

void PlayMusic();



// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground("Data\\Backgrounds\\testing_background.png");

	int iPlayer = Play::CreateGameObject(TYPE_PLAYER, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 20, "fry");
	int iGunPrimary = Play::CreateGameObject(TYPE_GUN_PRIMARY, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 5, "Chicken_Gun");

	int iGunSecondary = Play::CreateGameObject(TYPE_GUN_SECONDARY, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 5, "shotgun");

	Point2D secondaryOrigin = Play::GetSpriteOrigin(iGunSecondary);

	Play::MoveSpriteOrigin("shotgun", Play::GetSpriteWidth(Play::GetSpriteId("shotgun"))/-4, 0);
	Play::UpdateGameObject(Play::GetGameObject(iGunSecondary));


	std::vector<std::map<int, std::string>> vInitializeSpriteMap = {
		{},		                             //Background    0
		{},									 //Bullets       1
		{},									 //Enemies       2
		{},                                  //enemies guns  3
		{{iPlayer, "fry_ruinning_down_6"} }, //Char          4
		{{iGunSecondary, "shotgun"}},       //Guns          5
		{}									 //foreground    6
	};

	spriteManager.initializeSprites(vInitializeSpriteMap);


	enemyController.spawnEnemy(TYPE_ENEMY, { 350, 350 }, 5, "robit");
	enemyController.spawnEnemy(TYPE_ENEMY, { 150, 350 }, 5, "robit");
	enemyController.spawnEnemy(TYPE_ENEMY, { 250, 350 }, 5, "robit");  
	enemyController.spawnEnemy(TYPE_ENEMY, { 750, 150 }, 5, "robit");  
	enemyController.spawnEnemy(TYPE_ENEMY, { 750, 450 }, 5, "robit");
	enemyController.spawnEnemy(TYPE_ENEMY, { 850, 450 }, 5, "robit");
	/*
	enemyController.spawnEnemy(TYPE_ENEMY, { 350, 350 }, 5, "robit");*/


	enemyController.playerId = iPlayer;
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);

	if (gameState.currentGameState == STATE_MENU)
	{
		// draws background
		Play::DrawBackground();
		// draws title
		Play::DrawFontText("132px", "TESTING",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 - 140 }, Play::CENTRE);
		Play::DrawFontText("64px", "2",
			{ DISPLAY_WIDTH / 2 + 105, DISPLAY_HEIGHT / 2 - 180 }, Play::CENTRE);
		// draws controls
		Play::DrawFontText("64px", "WASD TO MOVE, MOUSE TO AIM, MOUSE CLICK TO SHOOT!",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT * 0.75f }, Play::CENTRE);
		Play::DrawFontText("64px", "PRESS SPACE TO START",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT * 0.75f + 40 }, Play::CENTRE);

		//idle fry
		Play::SetSprite(player, "phillip_idle_2q_4", 0.2f);
		Play::UpdateGameObject(player);
		Play::DrawObject(player);
		Play::PresentDrawingBuffer();
		if (Play::KeyPressed(VK_SPACE) == true)
		{
			gameState.currentGameState = STATE_PLAY;
			PlayMusic();
		}
		return Play::KeyDown(VK_ESCAPE);
	}




	Play::DrawBackground();


	GameObject& secondaryGunObj = Play::GetGameObjectByType(TYPE_GUN_SECONDARY);

	//get mouse position
	Vec2 vMousePos = Play::GetMousePos();
	//calculate aim vector
	Vec2 vAimVec = utilHandleCursorDirection({ player.pos.x,player.pos.y }, vMousePos);

	handleInputs({ player.pos.x,player.pos.y }, vAimVec, &primaryGun, &secondaryGun);
	HandlePlayerMovement(elapsedTime);


	//tick all bullets
	primaryGun.moveBullets();
	secondaryGun.moveBullets();

	//Ui sprite render
	handleUI(gameState.PlayerCurrentHealth, gameState.MaxPlayerHealth, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	//after all destroyed eleements are removed
	utilJanitor();

	//
	enemyController.checkPlayerCollisions();
	enemyController.moveEnemies();

	spriteManager.tickSprites(vMousePos, vAimVec.rad(), elapsedTime);

	//display
	//dismount
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

void PlayMusic()
{
	int randomRoll = (std::rand() % 3) + 1;

	if (randomRoll == 1)
	{
		Play::StartAudioLoop("science_action_01_loop");
	}
	else if (randomRoll == 2)
	{
		Play::StartAudioLoop("science_action_02_loop");
	}
	else if (randomRoll == 3)
	{
		Play::StartAudioLoop("science_action_04_loop");
	}
}



void UpdateGameState()

// STATEMENU
//std::string print

//if(state_menu)
//{
//	pritn = "Menu"
//}


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