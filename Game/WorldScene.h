#pragma once
#include <vector>
#include "Game.h"
#include "Entity.h"
#include "Textures.h"
#include "Scene.h"
#include "Tilemap.h"
#include "HUD.h"

#include "WorldMapMario.h"
#include "Cactus.h"
#include "HammerBrother.h"
#include "SpeechBubble.h"
#include "define.h"


//#define SCENE_SECTION_UNKNOWN -1
//#define SCENE_SECTION_TEXTURES 2
//#define SCENE_SECTION_SPRITES 3
//#define SCENE_SECTION_ANIMATIONS 4
//#define SCENE_SECTION_ANIMATION_SETS	5
//#define SCENE_SECTION_OBJECTS	6
//#define SCENE_SECTION_TILEMAP	7
//#define SCENE_SECTION_GRID		8

#define OBJECT_TYPE_MARIO					0
#define OBJECT_TYPE_CACTUS					1
#define OBJECT_TYPE_HAMMER_BROTHER			2
#define OBJECT_TYPE_SPEECH_BUBBLE			3


#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

#define TILEMAP_X_OFFSET 0
#define TILEMAP_Y_OFFSET -20

#define GRID_TOTAL_ROWS			9
#define GRID_TOTAL_COLUMNS		11


class WorldScene : public Scene
{
protected:
	TileMap* tilemap;
	HUD* hud;
	WorldMapMario* player;			// A play scene has to have player, right? 

	vector<vector<int>> mapGrid;
	//{	
	//	{1,	1,	3,	0,	2,	0,	2,	0,	2,	0,	2},
	//	{1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	0},
	//	{2,	0,	2,	1,	1,	1,	2,	0,	2,	0,	2},
	//	{1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1},
	//	{1,	1,	2,	0,	2,	0,	2,	1,	1,	1,	1},
	//	{1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1},
	//	{1,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0},
	//	{1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1},
	//	{1,	1,	2,	0,	2,	0,	2,	1,	1,	1,	1} 
	//};

	int grid_rows, grid_columns;

	int curNodeX;
	int curNodeY;

	bool hasLoadGrid = false;


	int startSceneTime;

	vector<LPGAMEENTITY> objects;
	vector<LPCWSTR> listSceneFilePath;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);
	void _ParseSection_GRID(string line);

public:
	WorldScene();
	int idStage;

	void LoadSceneObjects();
	void Update(DWORD dt);
	void Render();
	void Unload();
	void LoadBaseObjects();
	void LoadBaseTextures();
	void ChooseMap(int whatStage);

	void KeyState(BYTE* states) {}
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);


	void LoadGrid(wstring filePath);
	bool CheckIfCanMove(D3DXVECTOR2);
};
//class PlayScenceKeyHandler : public ScenceKeyHandler
//{
//public:
//	virtual void KeyState(BYTE* states);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//	PlayScenceKeyHandler(Scene* s) :ScenceKeyHandler(s) {};
//};

enum MapNode
{
	EMPTY,
	BLOCK,
	STOP,
	INTERACTABLE,
	START
};

