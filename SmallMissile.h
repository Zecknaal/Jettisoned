// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "SmallMissile.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API ASmallMissile : public AProjectile
{
	GENERATED_BODY()

	virtual void Tick(float deltaSeconds) override;
	ASmallMissile();
	
	float speed;
	float lifetime;
};
