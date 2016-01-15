// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "GalaxySector.h"


// Sets default values
AGalaxySector::AGalaxySector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGalaxySector::buildSector(UWorld* world, FVector2D position){
	biome = NewObject<UDeepSpace>(UDeepSpace::StaticClass());
	biome->setWorld(world);
	biome->spawnBackground(position);
}

FVector2D AGalaxySector::getIndex(){
	return position;
}

void AGalaxySector::BeginPlay(){
	Super::BeginPlay();
	spawnRegions();
}

void AGalaxySector::setIndex(FVector2D index){
	sectorInfo.x = index.X;
	sectorInfo.y = index.Y;
}

void AGalaxySector::spawnRegions(){
	for (int32 regionCount = 0; regionCount < MAX_NUMBER_OF_REGIONS; regionCount++)
		regions.Emplace(makeRegion());
}

ARegion* AGalaxySector::makeRegion(){
	int32 x, y;
	FVector location;
	FRotator rotation;

	x = (rand() % SECTOR_SIZE) - (SECTOR_SIZE / 2);
	y = (rand() % SECTOR_SIZE) - (SECTOR_SIZE / 2);

	location = FVector(GetActorLocation().X + x, 0, GetActorLocation().Z + y);
	rotation = FRotator(0, 0, 0);

	return SpawnBP<ARegion>(GetWorld(), AAsteroidRegion::StaticClass(), FVector2D(location.X, location.Z), rotation);
}

float AGalaxySector::getLength(){
	FVector origin;
	FVector box;

	GetActorBounds(false, origin, box);
	return origin.Y;
}

void AGalaxySector::crossNorthBound(){
	crossBound(NORTH);
}
void AGalaxySector::crossEastBound(){
	crossBound(EAST);
}
void AGalaxySector::crossSouthBound(){
	crossBound(SOUTH);
}
void AGalaxySector::crossWestBound(){
	crossBound(WEST);
}

void AGalaxySector::crossBound(Bound direction){
	if (direction == EAST){
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x + 1, sectorInfo.y));
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x + 1, sectorInfo.y + 1));
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x + 1, sectorInfo.y - 1));
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("East")));
	}
	else if (direction == WEST){
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x - 1, sectorInfo.y));
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x - 1, sectorInfo.y + 1));
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x - 1, sectorInfo.y - 1));
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("West")));
	}
	else if (direction == NORTH){
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x, sectorInfo.y + 1));
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x - 1, sectorInfo.y + 1));
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x + 1, sectorInfo.y + 1));
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("North")));
	}
	else if (direction == SOUTH){
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x, sectorInfo.y - 1));
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x - 1, sectorInfo.y - 1));
		((AJettisonedGameMode*)GetWorld()->GetAuthGameMode())->createSector(GetWorld(), FVector2D(sectorInfo.x + 1, sectorInfo.y - 1));
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("South")));
	}
}