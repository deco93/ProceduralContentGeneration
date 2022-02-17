// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerUI.h"
#include "PCGGameModeBase.h"

void USpawnerUI::NativeConstruct()
{
	Super::NativeConstruct();
	//TODO setup bindings
	GenerateWorldButton->OnClicked.AddDynamic(this, &USpawnerUI::OnGenerateWorldButtonClicked);
}

void USpawnerUI::OnGenerateWorldButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("OnGenerateWorldButtonClicked %f"), FCString::Atof(*GridWidth->GetText().ToString()));
	APCGGameModeBase* GM = Cast<APCGGameModeBase>(GetWorld()->GetAuthGameMode());
	float NewGridWidth = FCString::Atof(*GridWidth->GetText().ToString());
	float NewGridLength = FCString::Atof(*GridLength->GetText().ToString());
	float NewSandTileSpawnProbablity = FCString::Atof(*SandTileSpawnProbability->GetText().ToString());
	float NewFolliageTileTreeSpawnProbablity = FCString::Atof(*TreeSpawnProbability->GetText().ToString());
	float NewBushSpawnProbability = FCString::Atof(*BushSpawnProbability->GetText().ToString());
	float NewHumanPropSpawnProbability = FCString::Atof(*HumanPropSpawnProbability->GetText().ToString());
	if (NewGridWidth != GM->GridWidth || NewGridLength != GM->GridLength || NewSandTileSpawnProbablity != GM->SandTileSpawnProbablity
		|| NewFolliageTileTreeSpawnProbablity != GM->FolliageTileTreeSpawnProbablity 
		|| NewHumanPropSpawnProbability != GM->HumanPropSpawnProbability || NewBushSpawnProbability != GM->BushSpawnProbability)//allow change ONLY if entered values different from previous exposed terrain values
	{
		GM->GridWidth = NewGridWidth;
		GM->GridLength = NewGridLength;
		GM->SandTileSpawnProbablity = NewSandTileSpawnProbablity;
		GM->FolliageTileTreeSpawnProbablity = NewFolliageTileTreeSpawnProbablity;
		GM->HumanPropSpawnProbability = NewHumanPropSpawnProbability;
		GM->BushSpawnProbability = NewBushSpawnProbability;
		GM->ResetTerrainWorld();
	}
}