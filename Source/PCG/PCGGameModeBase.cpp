// Copyright Epic Games, Inc. All Rights Reserved.


#include "PCGGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tree.h"
#include "ProceduralTerrain.h"


APCGGameModeBase::APCGGameModeBase()
{
	UE_LOG(LogTemp, Warning, TEXT("APCGGameModeBase constructor called"));
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//Init the meshes for grass tile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshForTree1(TEXT("/Game/DreamscapeSeries/DreamscapeMeadows/Meshes/Foliage/SM_Bushes_New_01"));
	if (MeshForTree1.Succeeded())
	{
		Tree1Mesh = MeshForTree1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshForTree2(TEXT("/Game/DreamscapeSeries/DreamscapeMeadows/Meshes/Foliage/SM_Bushes_New_04_Flowers"));
	if (MeshForTree2.Succeeded())
	{
		Tree2Mesh = MeshForTree2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GrassMeshForTerrain(TEXT("/Game/MyCutomMeshes/SM_Template_Map_Floor_Grass"));
	if (GrassMeshForTerrain.Succeeded())
	{
		GrassMesh = GrassMeshForTerrain.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SandMeshForTerrain(TEXT("/Game/MyCutomMeshes/SM_Template_Map_Floor_Sand"));
	if (SandMeshForTerrain.Succeeded())
	{
		SandMesh = SandMeshForTerrain.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BirchTreeMeshForTerrain(TEXT("/Game/DreamscapeSeries/DreamscapeMeadows/Meshes/Trees/SM_TreeBirch_05"));
	if (BirchTreeMeshForTerrain.Succeeded())
	{
		BirchTreeMesh = BirchTreeMeshForTerrain.Object;
	}

	//Init the meshes for sand tile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshForRuneRock(TEXT("/Game/DreamscapeSeries/DreamscapeMeadows/Meshes/Rocks/SM_RuneRock_01"));
	if (MeshForRuneRock.Succeeded())
	{
		RuneRockMesh = MeshForRuneRock.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshForLog(TEXT("/Game/DreamscapeSeries/DreamscapeMeadows/Meshes/Props/SM_Tree_Fallen_01"));
	if (MeshForLog.Succeeded())
	{
		LogMesh = MeshForLog.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshForTent(TEXT("/Game/DreamscapeSeries/DreamscapeMeadows/Meshes/Props/SM_Tent_03"));
	if (MeshForTent.Succeeded())
	{
		TentMesh = MeshForTent.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshForBarrell(TEXT("/Game/DreamscapeSeries/DreamscapeMeadows/Meshes/Props/SM_Barrell_01"));
	if (MeshForBarrell.Succeeded())
	{
		BarrellMesh = MeshForBarrell.Object;
	}
	CurrentSandPatchTileCount = 0;
	CurrentSandPatchCount = 0;
	RefillXAndYIndicesForTile();
}

void APCGGameModeBase::StartPlay()
{
	Super::StartPlay();
	UE_LOG(LogTemp, Warning, TEXT("Spawning Terrain in GM"));
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	GenerateTerrain();
	
}

void APCGGameModeBase::ResetTerrainWorld()
{
	int TerrainTilesSize = TerrainTiles.Num();
	for (int x = TerrainTilesSize - 1; x >= 0; x--)
	{
		TerrainTiles[x]->Destroy();
	}
	int ObjectListSize = ObjectList.Num();
	for (int x = ObjectListSize - 1; x >= 0; x--)
	{
		ObjectList[x]->Destroy();
	}
	TerrainTiles.Empty();
	ObjectList.Empty();
	CurrentSandPatchTileCount = 0;
	CurrentSandPatchCount = 0;
	RefillXAndYIndicesForTile();
	UE_LOG(LogTemp, Warning, TEXT(">>>TerrainTiles size: %d ObjectsList size: %d"), TerrainTiles.Num(),ObjectList.Num() );
	GenerateTerrain();
	UE_LOG(LogTemp, Warning, TEXT(">>>After Generate Terrain success"));
}


void APCGGameModeBase::GenerateTerrain()
{
	float XCoordinate = -((TileSize * GridWidth) / 2) + (TileSize / 2);//start X Coordinate
	float YCoordinate = ((TileSize * GridLength) / 2) - (TileSize / 2);
	for (int y = 0; y < GridLength; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			SpawnTile(XCoordinate, YCoordinate);
			if (TerrainTiles[TerrainTiles.Num() - 1]->TerrainType == GRASS)
				GenerateFolliage(XCoordinate, YCoordinate);
			else if (TerrainTiles[TerrainTiles.Num() - 1]->TerrainType == SAND)
				GenerateObjects(XCoordinate, YCoordinate);
			XCoordinate += TileSize;
		}
		XCoordinate = -((TileSize * GridWidth) / 2) + (TileSize / 2);
		YCoordinate -= TileSize;
	}
	UE_LOG(LogTemp, Warning, TEXT("TilesSpawned= %d"), TerrainTiles.Num());
}

void APCGGameModeBase::GenerateFolliage(float XCoordinate, float YCoordinate)
{	
	
	//ATree* Tree1 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(XCoordinate - 450, YCoordinate, 0), FRotator(), SpawnParams);
	int BushSpawnRand = FMath::RandRange(0, 100);
	if (BushSpawnRand < BushSpawnProbability)
	{
		ATree* Tree1 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(GetRandomGridCoordinate(XCoordinate), GetRandomGridCoordinate(YCoordinate, false), 25), FRotator(0, 90, 0), SpawnParams);

		Tree1->MeshComp->SetStaticMesh(Tree1Mesh);
		ObjectList.Add(Tree1);


		//ATree* Tree2 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(XCoordinate + 450, YCoordinate, 0), FRotator(), SpawnParams);
		ATree* Tree2 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(GetRandomGridCoordinate(XCoordinate) + FMath::RandRange(-5, 5), GetRandomGridCoordinate(YCoordinate, false) + FMath::RandRange(-5, 5), 135), FRotator(0, 90, 0), SpawnParams);

		Tree2->MeshComp->SetStaticMesh(Tree2Mesh);

		ObjectList.Add(Tree2);
	}

	int BirchTreeSpawnRand = FMath::RandRange(0,100);
	if (BirchTreeSpawnRand < FolliageTileTreeSpawnProbablity)
	{
		
		ATree* Tree3 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(GetRandomGridCoordinate(XCoordinate) + FMath::RandRange(-5, 5), GetRandomGridCoordinate(YCoordinate, false) + FMath::RandRange(-5, 5), 0), FRotator(), SpawnParams);
		
		Tree3->MeshComp->SetStaticMesh(BirchTreeMesh);
		ObjectList.Add(Tree3);
	}
	RefillXAndYIndicesForTile();
}

void APCGGameModeBase::GenerateObjects(float XCoordinate, float YCoordinate)
{
	int CurrentHumanPropSpawnProbability = FMath::RandRange(0,100);
	if (CurrentHumanPropSpawnProbability < HumanPropSpawnProbability)
	{
		ATree* Prop1 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(GetRandomGridCoordinate(XCoordinate), GetRandomGridCoordinate(YCoordinate,false), 20), FRotator(0,90,0), SpawnParams);
		Prop1->MeshComp->SetStaticMesh(BarrellMesh);
		ObjectList.Add(Prop1);
	}

	ATree* Prop2 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(GetRandomGridCoordinate(XCoordinate) + FMath::RandRange(-5, 5), GetRandomGridCoordinate(YCoordinate,false) + FMath::RandRange(-5, 5), 25), FRotator(0,90, 0), SpawnParams);
	Prop2->MeshComp->SetStaticMesh(LogMesh);
	Prop2->SetActorScale3D(FVector(0.5f,1,1));
	ObjectList.Add(Prop2);
	
	CurrentHumanPropSpawnProbability = FMath::RandRange(0, 100);
	if (CurrentHumanPropSpawnProbability < HumanPropSpawnProbability)
	{
		ATree* Prop3 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(GetRandomGridCoordinate(XCoordinate) + FMath::RandRange(6, 10), GetRandomGridCoordinate(YCoordinate,false) + FMath::RandRange(6, 10), 15), FRotator(0, 90, 0), SpawnParams);
		Prop3->MeshComp->SetStaticMesh(TentMesh);
		ObjectList.Add(Prop3);
	}

	ATree* Prop4 = GetWorld()->SpawnActor<ATree>(ATree::StaticClass(), FVector(GetRandomGridCoordinate(XCoordinate) + FMath::RandRange(-11, -6), GetRandomGridCoordinate(YCoordinate,false) + FMath::RandRange(-11, -6), 25), FRotator(0,90,0), SpawnParams);
	Prop4->MeshComp->SetStaticMesh(RuneRockMesh);
	ObjectList.Add(Prop4);
	RefillXAndYIndicesForTile();
}

void APCGGameModeBase::SpawnTile(float x, float y)
{	
	TempTerrain = GetWorld()->SpawnActor<AProceduralTerrain>(AProceduralTerrain::StaticClass(), FVector(x, y, 0), FRotator(0, 0, 0), FActorSpawnParameters());
	TerrainTiles.Add(TempTerrain);
}

int APCGGameModeBase::GetMaxSandPatchCount()
{
	if (SandTileSpawnProbablity < 25.0f)
		return 3;
	else if (SandTileSpawnProbablity >= 25.0f && SandTileSpawnProbablity < 50.0f)
		return 4;
	else if (SandTileSpawnProbablity >= 50.0f && SandTileSpawnProbablity < 75.0f)
		return 5;
	else
		return 6;
}

float APCGGameModeBase::GetRandomGridCoordinate(float XOrYCoordinate, bool IsX)
{
	int RandGrid = -1;
	int RandomIndexFromIndicesArray = -1;
	if (IsX && XIndicesForATile.Num()>0)
	{
		RandomIndexFromIndicesArray = FMath::RandRange(0, XIndicesForATile.Num() - 1);
		RandGrid = XIndicesForATile[RandomIndexFromIndicesArray];
		if (XIndicesForATile.IsValidIndex(RandomIndexFromIndicesArray))
			XIndicesForATile.RemoveAt(RandomIndexFromIndicesArray);
		UE_LOG(LogTemp, Warning, TEXT("==XGridIndex: %d"), RandGrid);
	}
	else if(YIndicesForATile.Num()>0)
	{
		RandomIndexFromIndicesArray = FMath::RandRange(0, YIndicesForATile.Num() - 1);
		RandGrid = YIndicesForATile[RandomIndexFromIndicesArray];
		if (YIndicesForATile.IsValidIndex(RandomIndexFromIndicesArray))
			YIndicesForATile.RemoveAt(RandomIndexFromIndicesArray);
		UE_LOG(LogTemp, Warning, TEXT("==YGridIndex: %d"), RandGrid);
	}

	float GridSize = (TileSize / 4);
	float RandomXorYGridCoordinate = XOrYCoordinate;
	switch (RandGrid)
	{
		case 0:
			RandomXorYGridCoordinate = XOrYCoordinate - ((GridSize / 2) + GridSize);
			break;
		case 1:
			RandomXorYGridCoordinate = XOrYCoordinate - (GridSize / 2);
			break;
		case 2:
			RandomXorYGridCoordinate = XOrYCoordinate + (GridSize / 2);
			break;
		default:
			RandomXorYGridCoordinate = XOrYCoordinate + ((GridSize / 2) + GridSize);
	}
	//RGData.XOrYCoordinate = RandomXorYGridCoordinate;
	return RandomXorYGridCoordinate;
	//return FMath::RandRange(RandomXorYGridCoordinate-(GridSize/2)+10, RandomXorYGridCoordinate + (GridSize / 2)-10);
}

void APCGGameModeBase::RefillXAndYIndicesForTile()
{
	XIndicesForATile.Empty();
	YIndicesForATile.Empty();

	XIndicesForATile.Add(0);
	XIndicesForATile.Add(1);
	XIndicesForATile.Add(2);
	XIndicesForATile.Add(3);
	YIndicesForATile.Add(0);
	YIndicesForATile.Add(1);
	YIndicesForATile.Add(2);
	YIndicesForATile.Add(3);
}
