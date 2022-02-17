// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComp = CreateDefaultSubobject<USceneComponent>("TerrainRoot");
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Terrain");
	SetRootComponent(RootComp);
	MeshComp->SetupAttachment(RootComp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshForTree1(TEXT("/Game/DreamscapeSeries/DreamscapeMeadows/Meshes/Foliage/SM_Bushes_New_01"));
	if (MeshForTree1.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshForTree1.Object);
	}
}


// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}