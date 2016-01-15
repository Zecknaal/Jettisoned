// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Biome.h"
#include "DeepSpace.h"
#include "Region.h"
#include "AsteroidRegion.h"
#include "GalaxySector.generated.h"

UCLASS()
class JETTISONED_API AGalaxySector : public AActor
{
	GENERATED_BODY()
	
	public:	
		enum Bound{NORTH, SOUTH, EAST, WEST};

		struct sectorData{
			int32 x;
			int32 y;
		};

		sectorData sectorInfo;
		const int32 SECTOR_SIZE = 30000;
		AGalaxySector();
		void buildSector(UWorld* world, FVector2D position);
		FVector2D getIndex();
		void setIndex(FVector2D index);
		float getLength();
		void crossBound(Bound direction);
		void spawnRegions();
		virtual ARegion* makeRegion();
		virtual void BeginPlay() override;
		UFUNCTION(BlueprintCallable, Category = "Sector")
			void crossNorthBound();
		UFUNCTION(BlueprintCallable, Category = "Sector")
			void crossEastBound();
		UFUNCTION(BlueprintCallable, Category = "Sector")
			void crossSouthBound();
		UFUNCTION(BlueprintCallable, Category = "Sector")
			void crossWestBound();
	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sector Component")
			UBiome* biome;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sector Component")
			AGalaxySector* north;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sector Component")
			AGalaxySector* east;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sector Component")
			AGalaxySector* west;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sector Component")
			AGalaxySector* south;
		FVector2D position;
		TArray<ARegion*> regions;
		const int32 MAX_NUMBER_OF_REGIONS = 20;
};
