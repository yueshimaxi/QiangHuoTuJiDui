


#include "AppConfigDatabase.h"

#include "JsonObjectConverter.h"

DataBaseType UAppConfigDatabase::DataBaseType()
{
	return DataBaseType::AppConfigData;
}

FString UAppConfigDatabase::DataPath()
{
	return FPaths::Combine(FPaths::ProjectContentDir(), FString("XuAsset/DataAsset/AppConfig.json"));

}

void UAppConfigDatabase::OnParse()
{
	Super::OnParse();
	
	FString jsonString;
	FFileHelper::LoadFileToString(jsonString, *DataPath());
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(jsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		FJsonObjectConverter::JsonObjectToUStruct<FAppConfigData>(JsonObject.ToSharedRef(),&appConfigData);
	}
}


void UAppConfigDatabase::OnSave()
{
	Super::OnSave();

	FAppConfigData local_appConfigData;
	local_appConfigData.ip=TEXT("1111");
	FString jsonString;
	FJsonObjectConverter::UStructToJsonObjectString(local_appConfigData,jsonString);
	FFileHelper::SaveStringToFile(jsonString, *DataPath());
}

void UAppConfigDatabase::ClearData()
{
	Super::ClearData();
}
