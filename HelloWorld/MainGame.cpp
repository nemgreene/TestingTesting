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
void PlayMusic();
#pragma region NeedsWork

//Make sure that penultimate robot scream is triggered on both guns ( all robit destrucitons noised)
//Make sure robit can swear agian one day
// fix state managerment (onload shouldnt say level completes)
// Put in display score
// put in gun imgs in UI
// Put in tennis gun
//


#pragma endregion

SpriteManager spriteManager = SpriteManager();
EnemyController enemyController = EnemyController(&spriteManager, &gameState);

ChickenGun primaryGun = ChickenGun::ChickenGun(TYPE_BULLET_PRIMARY, "Chicken_Bullets_4", &spriteManager);
Gun secondaryGun = Gun::Gun(TYPE_BULLET_SECONDARY, "acid_bullets_4", &spriteManager);




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



	/*
	enemyController.spawnEnemy(TYPE_ENEMY, { 350, 350 }, 5, "robit");*/


	enemyController.playerId = iPlayer;
}
bool launched = false;
bool dying = false;
bool spawned = false;
// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);
	//gameState.currentGameState = STATE_PLAY;
	 
	if (gameState.currentGameState != STATE_MENU && launched && enemyController._enemyIds.size() < 1) {
		gameState.currentGameState = STATE_LEVEL_CLEARED;
	}
	if (gameState.PlayerCurrentHealth < 1)
	{
		gameState.currentGameState = STATE_GAMEOVER;
	}
	if (gameState.currentGameState == STATE_GAMEOVER)
	{
		// draws background
		//again
		Play::DrawBackground();
		// draws title
		Play::DrawFontText("132px", "GAME OVER!",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 - 140 }, Play::CENTRE);
		// draws controls

		Play::DrawFontText("64px", "PRESS ESC TO EXIT",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT * 0.75f + 40 }, Play::CENTRE);

		Play::DrawFontText("64px", "PRESS SPACE TO TRY AGAIN",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT * 0.75f + 100 }, Play::CENTRE);

		player.velocity = { 0,0 };
		Play::DestroyGameObjectsByType(TYPE_BULLET_ENEMY);


		//idle 
		if (dying) {
			Play::SetSprite(player, "fry_idle_death_10", 0.2f);

			if (player.frame == 9) dying = false;
		}
		if (!dying)
		{
			Play::SetSprite(player, "fry_death_static", 0.2f);

		}

		Play::UpdateGameObject(player);
		Play::DrawObject(player);
		Play::PresentDrawingBuffer();
		if (Play::KeyPressed(VK_SPACE))
		{
			gameState.currentGameState = STATE_PLAY;
			gameState.PlayerCurrentHealth = 100;
			Play::DestroyGameObjectsByType(TYPE_ENEMY);
			Play::DestroyGameObjectsByType(TYPE_BULLET_ENEMY);
			Play::DestroyGameObjectsByType(TYPE_BULLET_PRIMARY);
			Play::DestroyGameObjectsByType(TYPE_BULLET_SECONDARY);
			dying = true;
			spawned = false;

		}
		return Play::KeyDown(VK_ESCAPE);
	}

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
		Play::SetSprite(player, "fry_idle_2q_4", 0.2f);
		Play::UpdateGameObject(player);
		Play::DrawObject(player);
		Play::PresentDrawingBuffer();
		if (Play::KeyPressed(VK_SPACE) == true)
		{
			gameState.currentGameState = STATE_PLAY;
			PlayMusic();
			launched = true;
		}
		return Play::KeyDown(VK_ESCAPE);
	}

	if (gameState.currentGameState == STATE_LEVEL_CLEARED)
	{
		// draws background
		Play::DrawBackground();
		// draws title
		Play::DrawFontText("132px", "LEVEL CLEARED!",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 - 140 }, Play::CENTRE);
		// draws controls

		Play::DrawFontText("64px", "PRESS ESC TO EXIT",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT * 0.75f + 40 }, Play::CENTRE);
		
		Play::DrawFontText("64px", "PRESS SPACE TO START THE NEXT LEVEL",
			{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT * 0.75f + 100 }, Play::CENTRE);
		
		player.velocity = { 0,0 };
		Play::DestroyGameObjectsByType(TYPE_BULLET_ENEMY);


		//idle fry
		Play::SetSprite(player, "fry_idle_2q_4", 0.2f);
		Play::UpdateGameObject(player);
		Play::DrawObject(player);
		Play::PresentDrawingBuffer();
		if (Play::KeyPressed(VK_SPACE))
		{
			gameState.currentGameState = STATE_PLAY;
			enemyController.spawnEnemy(TYPE_ENEMY, { 350, 350 }, 5, "robit");
			enemyController.spawnEnemy(TYPE_ENEMY, { 150, 350 }, 5, "robit");
			enemyController.spawnEnemy(TYPE_ENEMY, { 250, 350 }, 5, "robit");
			enemyController.spawnEnemy(TYPE_ENEMY, { 750, 150 }, 5, "robit");
			enemyController.spawnEnemy(TYPE_ENEMY, { 750, 450 }, 5, "robit");
			enemyController.spawnEnemy(TYPE_ENEMY, { 850, 450 }, 5, "robit");
			spawned = true;
		}
		return Play::KeyDown(VK_ESCAPE);
	}

	if (gameState.currentGameState == STATE_PLAY && !spawned)
	{
		enemyController.spawnEnemy(TYPE_ENEMY, { 350, 350 }, 5, "robit");
		enemyController.spawnEnemy(TYPE_ENEMY, { 150, 350 }, 5, "robit");
		enemyController.spawnEnemy(TYPE_ENEMY, { 250, 350 }, 5, "robit");
		enemyController.spawnEnemy(TYPE_ENEMY, { 750, 150 }, 5, "robit");
		enemyController.spawnEnemy(TYPE_ENEMY, { 750, 450 }, 5, "robit");
		enemyController.spawnEnemy(TYPE_ENEMY, { 850, 450 }, 5, "robit");
		spawned = true;
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
	primaryGun.moveBullets(elapsedTime);
	secondaryGun.moveBullets(elapsedTime);

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