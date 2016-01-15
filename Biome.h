// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Biome.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API UBiome : public UObject
{
	GENERATED_BODY()
public:
	virtual void spawnBackground(FVector2D position){};
	virtual UClass* getBackgroundBP(){ return backgroundBP; };
	virtual void setWorld(UWorld* newWorld){ world = newWorld; }
	virtual FVector2D getPosition(){ return position; }
	~UBiome(){}
protected:
	UPROPERTY()
		UWorld* world;
	UPROPERTY()
		FString name;
	UPROPERTY()
		UClass* backgroundBP;
	UPROPERTY()
		AActor* backgroundActor;
	UPROPERTY()
		FVector2D position;
};
