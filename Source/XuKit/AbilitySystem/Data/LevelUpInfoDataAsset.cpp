// copyright xuzhipeng


#include "LevelUpInfoDataAsset.h"

int ULevelUpInfoDataAsset::FindLevelByXP(int xp)
{
	int playerLevel = 0;

	for (FAuraLevelUpInfo& info : LevelUpInfos)
	{
		if (info.RequiredExp <= xp)
		{
			playerLevel++;
		}
		else
		{
			break;
		}
	}
	return playerLevel;
}
