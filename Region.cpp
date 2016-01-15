// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "Region.h"


// Sets default values
ARegion::ARegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = NewObject<USceneComponent>(USceneComponent::StaticClass()); //PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
}

// Called when the game starts or when spawned
void ARegion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARegion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

