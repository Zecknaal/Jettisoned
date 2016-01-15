// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Biome.h"
#include "DeepSpace.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API UDeepSpace : public UBiome
{
	GENERATED_BODY()

		UDeepSpace();
		void spawnBackground(FVector2D position) override;
};
