#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "MapObject.h"
#include "MapCell.h"
#include "NPC.h"
#include "Item.h"
#include "Static.h"
#include "Character.h"
#include "Quest.h"
#include "Skill.h"
#include "Game.h"
#include "GameResources.h"

template<class T>
T** GameResources::FilterByTag(T** mapObjects, int mapObjectsCounter, char** tags, int numberOfTags)
{
	int i, j, k;
	T** result;
	int resultSize = 0;
	bool flag = true;

	for (i = 0; i < mapObjectsCounter; i++)
	{
		for (k = 0; k < numberOfTags; k++)	
		{
			flag = false;
			for (j = 0; j < mapObjects[i]->tagsCount; j++)
			{
				if (strcmp(tags[k], mapObjects[i]->tags[j]) != 0)
				{
					flag = true;
					break;
				}
			}

			if (!flag) break;
		}

		if (flag)
		{
			result = (T**)realloc(mapobjects, (++resultSize) * sizeof(T));
			result[resultSize - 1] = mapObjects[i];
		}
	}

	return result;
}

GameResources::GameResources(void)
{
	MapObjectsInit<MapCell>(mapCells, mapCellsCount, "MapCell");
	MapObjectsInit<NPC>(npcs, npcsCount, "NPC");
	MapObjectsInit<Item>(items, itemsCount, "Item");
	MapObjectsInit<Static>(statics, staticsCount, "`Static`");
	MapObjectsInit<Character>(characters, charactersCount, "Character");
	MapObjectsInit<Quest>(quests, questsCount, "Quest");
	MapObjectsInit<Skill>(skills, skillsCount, "Skill");
}

GameResources::~GameResources(void)
{
	int i;

	for (i = 0; i < mapCellsCount; i++)
		delete mapCells[i];
	delete mapCells;
	for (i = 0; i < npcsCount; i++)
		delete npcs[i];
	delete npcs;
	for (i = 0; i < itemsCount; i++)
		delete items[i];
	delete items;
	for (i = 0; i < staticsCount; i++)
		delete statics[i];
	delete statics;
	for (i = 0; i < charactersCount; i++)
		delete characters[i];
	delete characters;
	for (i = 0; i < questsCount; i++)
		delete quests[i];
	delete quests;
	for (i = 0; i < skillsCount; i++)
		delete skills[i];
	delete skills;
}

template<class T> //T inherits MapObject
void GameResources::MapObjectsInit(T** &mapObjects, int &mapObjectsCount, char* tableName)
{
	char query[64];
	std::vector<SqliteResult> sqliteResults;
	
	sprintf(query, "SELECT * FROM %s;", tableName); //TODO: Get class T name
	sqliteResults = SqliteGetRows(Game::instance->db, query);
	
	mapObjectsCount = 0;
	mapObjects = NULL;
	
	int rowsCount = sqliteResults.size();
	while (mapObjectsCount < rowsCount)
	{
		mapObjectsCount++;
		mapObjects = (T**)realloc(mapObjects, mapObjectsCount * sizeof(T*));
		mapObjects[mapObjectsCount - 1] = new T(sqliteResults[mapObjectsCount - 1]);
	}
}

int GameResources::GetMapObjectsTags(MapObject** mapObjects, int mapObjectsCount, char** &tags)
{
	int tagsCount;
	int i, j;

	tagsCount = 0;
	tags = NULL;
	for (i = 0; i < mapObjectsCount; i++)
	{
		for (j = 0; j < mapObjects[i]->tagsCount; j++)
		{
			if (std::find(tags, tags + tagsCount, mapObjects[i]->tags[j]) == (tags + tagsCount))
			{
				tagsCount++;
				tags = (char**)realloc(tags, tagsCount * sizeof(char*));
				tags[tagsCount - 1] = mapObjects[i]->tags[j];
			}
		}
	}
	return tagsCount;
}

MapCell* GameResources::GetMapCell(int id)
{
	return GetMapObject<MapCell>(mapCells, mapCellsCount, id);
}

NPC* GameResources::GetNPC(int id)
{
	return GetMapObject<NPC>(npcs, npcsCount, id);
}

Static* GameResources::GetStatic(int id)
{
	return GetMapObject<Static>(statics, staticsCount, id);
}

Item* GameResources::GetItem(int id)
{
	return GetMapObject<Item>(items, itemsCount, id);
}

Character* GameResources::GetCharacter(int id)
{
	return GetMapObject<Character>(characters, charactersCount, id);
}
