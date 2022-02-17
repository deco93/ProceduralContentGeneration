// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PCGGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class PCG_API APCGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APCGGameModeBase();
	void GenerateTerrain();//2-5 different types of ground generated intelligently not randomly
	void GenerateFolliage(float XCoordinate, float YCoordinate);//both folliage and objects should makeup 3 categories of objects and should have 2+ objects in each category in the world
	void GenerateObjects(float XCoordinate, float YCoordinate);
	void SpawnTile(float x, float y);
	void StartPlay() override;
	void ResetTerrainWorld();
	int GetMaxSandPatchCount();//more the SandTileSpawnProbablity more number of sand patches to be spawned

	float GetRandomGridCoordinate(float XOrYCoordinate, bool IsX = true);
	void RefillXAndYIndicesForTile();
	class AProceduralTerrain* TempTerrain;
	class ACharacter* Player;
	class APlayerController* PC;
	TArray<class AProceduralTerrain*> TerrainTiles;
	int GridLength = 10;//expose
	int GridWidth = 10;//expose
	float TileSize = 1000.0f;
	int CurrentSandPatchCount = 0;
	int CurrentSandPatchTileCount = 0;

	TArray<AActor*> ObjectList;//different trees/bushes/urban objects
	float SandTileSpawnProbablity = 10.0f;//expose
	float FolliageTileTreeSpawnProbablity = 10.0f;//expose
	float HumanPropSpawnProbability = 25.0f;//expose
	float BushSpawnProbability = 100.0f;//expose
	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* GrassMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* SandMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* BirchTreeMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* RuneRockMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* LogMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* BarrellMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* TentMesh;
	
private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* Tree1Mesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* Tree2Mesh;

	FActorSpawnParameters SpawnParams;

	TArray<int> XIndicesForATile;//should be repopulated once a tile has completely been populated
	TArray<int> YIndicesForATile;//should be repopulated once a tile has completely been populated
};
