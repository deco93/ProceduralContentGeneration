// Represents a grid Tile

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralTerrain.generated.h"

enum TileType
{
	GRASS,
	SAND
};
UCLASS()
class PCG_API AProceduralTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralTerrain();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	TileType TerrainType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
