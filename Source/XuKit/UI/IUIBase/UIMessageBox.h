// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XuKit/UI/UIBase.h"
#include "UIMessageBox.generated.h"

class USizeBox;
class UButton;
class UTextBlock;
DECLARE_DELEGATE(FMyDelegate);
/**
 * 
 */
UCLASS()
class XUKIT_API UUIMessageBox : public UUIBase
{
public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;

private:
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* title;
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* content;
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* leftBtnText;
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* rightBtnText;
	
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UButton* leftBtn;
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	USizeBox* leftSizeBox;
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UButton* rightBtn;
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	USizeBox* rightSizeBox;

	FMyDelegate left_btn_delegate;

	FMyDelegate right_btn_delegate;
	
	void InitOne(FString titleStr,FString contentStr,FString leftBtnStr,FMyDelegate leftBtnFunc);
	
	void InitTwo(FString titleStr,FString contentStr,FString leftBtnStr,FMyDelegate leftBtnFunc,FString rightBtnStr ,FMyDelegate rightBtnFunc);

	
	UFUNCTION()
	void OnClickLeftBtn();

	UFUNCTION()
	void OnClickRightBtn();

protected:

	virtual void NativeOnInitialized() override;
};
