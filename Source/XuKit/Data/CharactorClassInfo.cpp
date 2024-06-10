// copyright xuzhipeng


#include "CharactorClassInfo.h"

FCharactorInfo UCharactorClassInfo::GetCharactorInfo(ECharactorClass CharactorClass)
{
	return CharactorClassInfoMap.FindChecked(CharactorClass);
}
