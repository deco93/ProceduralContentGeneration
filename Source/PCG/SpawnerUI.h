// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "SpawnerUI.generated.h"

/**
 * 
 */
UCLASS()
class PCG_API USpawnerUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* GridWidth;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* GridLength;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* SandTileSpawnProbability;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* TreeSpawnProbability;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* BushSpawnProbability;
	
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* HumanPropSpawnProbability;

	UPROPERTY(meta = (BindWidget))
	class UButton* GenerateWorldButton;

	UFUNCTION()
	void OnGenerateWorldButtonClicked();

	void NativeConstruct() override;
};
