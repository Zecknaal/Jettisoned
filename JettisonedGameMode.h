// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/GameMode.h"
#include "GalaxySector.h"
#include "ShipController.h"
#include "Ship.h"
#include "JettisonedGameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of JettisonedCharacter

UCLASS(minimalapi)
class AJettisonedGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ACameraActor* mainCamera;
	
	AJettisonedGameMode();
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable, Category = "Sector")
	virtual void createSector(UWorld* world, FVector2D index);
	virtual void BeginPlay() override;
	~AJettisonedGameMode();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship Component")
	AGalaxySector* sector;
	UClass* boundBP;
	UClass* deepSpaceBP;
	TActorIterator<AGalaxySector> findSector(int32 x, int32 y);

	TCHAR* BOUNDING_WALL_PATH = TEXT("Blueprint'/Game/2dSideScroller/Blueprints/BP_Bounding_Wall.BP_Bounding_Wall'");
	TCHAR* SHIP_CONTROLLER_PATH = TEXT("Blueprint'/Game/2dSideScroller/Blueprints/BP_ShipController.BP_ShipController'");
	TCHAR* DEEP_SPACE_SECTOR_PATH = TEXT("Blueprint'/Game/2dSideScroller/Blueprints/BP_DeepSpace_Sector.BP_DeepSpace_Sector'");
};
