#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "XuKit/AbilitySystem/AuraAbilityLibrary.h"
#include "XuKit/Event/EventMgr.h"
#include "XuKit/UI/UIBaseInterface.h"
#include "UIPlayerHUD.generated.h"

class UEventData;
class UQHAttributeSet;
class UAbilitySystemComponent;
struct FWeaponInfo;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWidgetControllerSetDelegate);


UCLASS()
class XUKIT_API UUIPlayerHUD : public UUserWidget,public  IUIBaseInterface
{
public:
	virtual EUILayer GetUILayer_Implementation() const override;
	virtual EUIType GetUIType_Implementation() const override;
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void OnUpdateServerTimeEvent(UEventData* event_data);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	GENERATED_BODY()

public:

//HP、Shield、Rush
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* shield_progress_bar;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* Health_progress_bar;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* Rush_progress_bar;
	
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ClipAmmoNum_Text;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* AllAmmoNum_Text;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* WeaponIcon_Image;
	
	
//XP、Coin
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* XP_progress_bar;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* XP_Text;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Coin_Text;

	
//Task
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TaskTitle_Text;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TaskContent_Text;


	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TimeCountDown;
	

	void SetHUDAmmo(int ClipAmmoNum, int AllAmmoNum,FWeaponInfo local_weapon_info);

	UPROPERTY(BlueprintReadWrite)
	float curMaxHealth;

	UPROPERTY(BlueprintReadWrite)
	float curHealth;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewValue);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float NewValue);

	void SetHealthProgress();


	UPROPERTY(BlueprintReadWrite)
	FWidgetControllerParams widget_controller_params= FWidgetControllerParams();

	UPROPERTY()
	FXuEventDelegate fresh_hud_delegate;
	int freshhud_EventID;
	UFUNCTION()
	void OnFreshHUDEvent(UEventData* event_data);


	UPROPERTY(BlueprintAssignable)
	FWidgetControllerSetDelegate widget_controller_set_delegate;

	bool bInit=false;

	int UpdateServerTimeEventID;
	
};


