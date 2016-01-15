// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "AsteroidRegion.h"

TArray<UPaperSprite*> AAsteroidRegion::asteroids;

AAsteroidRegion::AAsteroidRegion(){
	if (asteroids.Num() == 0){
		//loadAsteroids();
	}
}

void AAsteroidRegion::loadAsteroids(){
	FString path;
	UPaperSprite* astclass;

	for (int32 spriteIndex = 0; spriteIndex <= ASTEROID_SPRITE_COUNT; spriteIndex++){
		path = FString(ASTEROID_SPRITE_PATH_PREFIX) + FString::FromInt(spriteIndex) + FString(ASTEROID_SPRITE_PATH_POSTFIX) + FString::FromInt(spriteIndex) + FString(TEXT("'"));
		astclass = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), NULL, *path));
		if (astclass){
			//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, astclass->GetName());
			asteroids.Emplace(astclass);
		}
	}
}
void AAsteroidRegion::BeginPlay(){
	Super::BeginPlay();
	if (asteroids.Num() == 0)
		loadAsteroids();
	spawnAllAsteroids();
}

void AAsteroidRegion::spawnAllAsteroids(){
	int32 x, y;
	regionRadius = 1000;
	for (int32 asteroidCount = 0; asteroidCount < 10; asteroidCount++){
		x = (rand() % (regionRadius * 2)) - regionRadius;
		y = (rand() % (regionRadius * 2)) - regionRadius;
		spawnAsteroid(FVector2D(GetActorLocation().X + x, GetActorLocation().Z + y));
	}
}

void AAsteroidRegion::spawnAsteroid(FVector2D location){
	APaperSpriteActor* asteroidActor;
	FRotator rotation = FRotator(rand() % 90, 0 , 0);
	int32 asteroidIndex = rand() % ASTEROID_SPRITE_COUNT;
	asteroidActor = SpawnBP<APaperSpriteActor>(GetWorld(), APaperSpriteActor::StaticClass(), location, rotation);
	asteroidActor->GetRenderComponent()->SetMobility(EComponentMobility::Movable);
	asteroidActor->GetRenderComponent()->SetSprite(asteroids[asteroidIndex]);
}