// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Region.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "AsteroidRegion.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API AAsteroidRegion : public ARegion
{
	GENERATED_BODY()
		AAsteroidRegion();
	virtual void BeginPlay() override;
	void loadAsteroids();
	UFUNCTION(BlueprintCallable, Category = "AsteroidRegion")
	void spawnAsteroid(FVector2D location);
	void spawnAllAsteroids();
	
	const int ASTEROID_SPRITE_COUNT = 63;
	TCHAR* ASTEROID_SPRITE_PATH_PREFIX = TEXT("PaperSprite'/Game/2dSideScroller/Sprites/AsteroidSprites/asteroid_strip64_Sprite_Asteroid_");
	TCHAR* ASTEROID_SPRITE_PATH_POSTFIX = TEXT(".asteroid_strip64_Sprite_Asteroid_");
	static TArray<UPaperSprite*> asteroids;
};
