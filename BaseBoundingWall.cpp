// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "BaseBoundingWall.h"


// Sets default values
ABaseBoundingWall::ABaseBoundingWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBoundingWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBoundingWall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

