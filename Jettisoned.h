// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

// This file is the private precompiled header for your game.
// You must include it first in each .cpp file.
//
// Place any includes here that are needed by the majority of your .cpp files

#include "Engine.h"
#include "JettisonedGameMode.h"

template <typename ASpawnBP>
FORCEINLINE ASpawnBP* SpawnBP(
	UWorld* TheWorld,
	UClass* TheBP,
	const FVector2D& Loc,
	const FRotator& Rot,
	const bool bNoCollisionFail = true,
	AActor* Owner = NULL,
	APawn* Instigator = NULL
	)
{
	if (!TheWorld) return NULL;
	if (!TheBP) return NULL;
	//~~~~~~~~~~~

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoCollisionFail = bNoCollisionFail;
	SpawnInfo.Owner = Owner;
	SpawnInfo.Instigator = Instigator;
	SpawnInfo.bDeferConstruction = false;
	FVector location = FVector(Loc.X, 0, Loc.Y);

	return TheWorld->SpawnActor<ASpawnBP>(TheBP, location, Rot, SpawnInfo);
}

FORCEINLINE UClass* readBP(TCHAR* path){
	UClass* bpClass;
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP(path);
	if (BP.Object)
		bpClass = (UClass*)BP.Object->GeneratedClass;
	return bpClass ? bpClass : nullptr;
}