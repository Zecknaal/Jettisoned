// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "EscapePod.h"


// Sets default values
AEscapePod::AEscapePod()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//sprite->SetCollisionObjectType(ECC_Pawn);
	//engines = ConstructObject<UEscapePodEngines>(UEscapePodEngines::StaticClass());
}

// Called when the game starts or when spawned
void AEscapePod::BeginPlay()
{
	Super::BeginPlay();
	engines = NewObject<UEscapePodEngines>(UEscapePodEngines::StaticClass());
	auto weapons = NewObject<UWeaponMissile>(UWeaponMissile::StaticClass());
	shipComponents.Emplace(weapons);
}

// Called every frame
void AEscapePod::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AEscapePod::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}