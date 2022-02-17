// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralTerrain.h"
#include "Kismet/GameplayStatics.h"
#include "PCGGameModeBase.h"
#include "Tree.h"

// Sets default values
AProceduralTerrain::AProceduralTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("__AProceduralTerrain Constructor called"));
	RootComp = CreateDefaultSubobject<USceneComponent>("TerrainRoot");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Terrain");
	SetRootComponent(RootComp);
	Mesh->SetupAttachment(RootComp);
	
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshForTerrain(TEXT("/Engine/MapTemplates/SM_Template_Map_Floor"));
	
}

// Called when the game starts or when spawned
void AProceduralTerrain::BeginPlay()
{
	Super::BeginPlay();
	int TileRand = FMath::RandRange(0, 100);
	APCGGameModeBase* GM =	Cast<APCGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	int SandTileCount = FMath::Floor( (GM->SandTileSpawnProbablity / 100.0f) * (GM->GridLength * GM->GridWidth) );
	int MaxSandPatchCount = GM->GetMaxSandPatchCount();
	int MaxTilesInAPatch = FMath::Floor(SandTileCount/MaxSandPatchCount);

	UE_LOG(LogTemp, Warning, TEXT(" SandTileCount %d MaxSandPatchCount %d MaxTilesInAPatch %d"), SandTileCount, MaxSandPatchCount, MaxTilesInAPatch);

	if (TileRand >= GM->SandTileSpawnProbablity && GM->CurrentSandPatchTileCount == 0)
	{
		if (GM->GrassMesh)
		{
			Mesh->SetStaticMesh(GM->GrassMesh);
			TerrainType = GRASS;
		}
	}
	else
	{
		GM->CurrentSandPatchTileCount++;
		if (GM->SandMesh && GM->CurrentSandPatchTileCount < MaxTilesInAPatch && GM->CurrentSandPatchCount< MaxSandPatchCount)
		{
			Mesh->SetStaticMesh(GM->SandMesh);
			TerrainType = SAND;
		}
		else
		{
			GM->CurrentSandPatchTileCount = 0;
			GM->CurrentSandPatchCount++;
			Mesh->SetStaticMesh(GM->GrassMesh);
			TerrainType = GRASS;
		}
	}
}

// Called every frame
void AProceduralTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}