// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Jettisoned.h"
#include "JettisonedGameMode.h"
#include "ShipController.h"

AJettisonedGameMode::AJettisonedGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = 0;
	PlayerControllerClass = readBP(SHIP_CONTROLLER_PATH);
	boundBP = readBP(BOUNDING_WALL_PATH);

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP(BOUNDING_WALL_PATH);//(TEXT("Blueprint'/Game/2dSideScroller/Blueprints/BP_Bounding_Wall.BP_Bounding_Wall'"));
	if (BP.Object)
		boundBP = (UClass*)BP.Object->GeneratedClass;
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP2(DEEP_SPACE_SECTOR_PATH);//(TEXT("Blueprint'/Game/2dSideScroller/Blueprints/BP_Bounding_Wall.BP_Bounding_Wall'"));
	if (BP2.Object)
		deepSpaceBP = (UClass*)BP2.Object->GeneratedClass;
	//deepSpaceBP = readBP(DEEP_SPACE_SECTOR_PATH);
}

void AJettisonedGameMode::createSector(UWorld* world, FVector2D index){
	FRotator rotation = FRotator(0,0,0);
	FVector2D location = FVector2D(index.X * 30000, index.Y * 30000);
	TActorIterator<AGalaxySector> existingSector = findSector(index.X, index.Y);
	AGalaxySector* sector;
	//findSector(index.X, index.Y, sector);
	if (existingSector){
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("Found a sectorX: ")) + FString::SanitizeFloat(index.X) + FString(TEXT(" Y: ")) + FString::SanitizeFloat(index.Y));
	}
	if (GetWorld() && !existingSector){
		sector = SpawnBP<AGalaxySector>(world, deepSpaceBP, location, rotation);
		if (!sector){
			GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("Sector creation failed! X: ")) + FString::SanitizeFloat(index.X) + FString(TEXT(" Y: ")) + FString::SanitizeFloat(index.Y));
			return;
		}
		else{
			GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("Sector creation successful!! X: ")) + FString::SanitizeFloat(index.X) + FString(TEXT(" Y: ")) + FString::SanitizeFloat(index.Y));
		}

		sector->setIndex(index);
	}
}

void AJettisonedGameMode::BeginPlay(){
	if (!sector)
		createSector(GetWorld(), FVector2D(0, 0));
}

void AJettisonedGameMode::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
}

TActorIterator<AGalaxySector> AJettisonedGameMode::findSector(int32 x, int32 y){
	TActorIterator<AGalaxySector> actorItr(GetWorld());
	for (; actorItr; ++actorItr){
		if (actorItr->getIndex().X == x && actorItr->getIndex().Y == y)
			return actorItr;
	}
	return actorItr;
}

AJettisonedGameMode::~AJettisonedGameMode(){
	if (GetWorld())
	GetWorld()->ForceGarbageCollection(true);
}