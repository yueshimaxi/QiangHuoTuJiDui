#pragma once

#include "CoreMinimal.h"
#include "UIMgr.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIMgr : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	void Init();

	bool isInit=false;
	
	UPROPERTY()
	TArray<UUserWidget*> uiActiveList;
	UPROPERTY()
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> uiActiveDic;
	UPROPERTY()
	TArray<UUserWidget*> UIStackList;
	UPROPERTY()
	TMap<UClass*,FString>UIPathMap;


	UFUNCTION(Category = "UUIManager", BlueprintCallable,meta=(DeterminesOutputType="uiType"))
	UUserWidget* ShowUIBP(TSubclassOf<UUserWidget> uiType,bool bHideLast=true,bool ForceShow=false);

	UFUNCTION(Category = "UUIManager", BlueprintCallable,meta=(DeterminesOutputType="uiType"))
	UUserWidget* GetUIBP(TSubclassOf<UUserWidget> uiType);
	
	UFUNCTION(Category = "UUIManager", BlueprintCallable)
	void HideUIBP(TSubclassOf<UUserWidget> uiType);
	
	UFUNCTION(BlueprintCallable)
	void PopUI();


	int GetStackUINum();
	FString GetUIPath( FString uiName,FString dir=TEXT(""));
	


	template <class T>
	T* ShowUI(bool bHideLast=true,bool ForceShow=false)
	{
		UClass* U_TClassType= T::StaticClass();
		UUserWidget* uiBase=ShowUIBP(U_TClassType,bHideLast,ForceShow);
		T* t = Cast<T>(uiBase);
		return t;
	}

	template <class T>
	T* GetUI()
	{
		UClass* U_TClassType= T::StaticClass();
		UUserWidget* uiBase=GetUIBP(U_TClassType);
		T* t = Cast<T>(uiBase);
		return t;
	}
	
	template <class T>
	void HideUI()
	{
		UClass* U_TClassType= T::StaticClass();
		HideUIBP(U_TClassType);
	}

	
};


