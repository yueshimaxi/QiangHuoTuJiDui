#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBaseInterface.h"
#include "UIEnemyHealthBar.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class XUKIT_API UUIEnemyHealthBar : public UUserWidget
{
public:


private:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void InitEnemyData(AEnemyCharacter* Enemy);
	
	
	
	

protected:

};
