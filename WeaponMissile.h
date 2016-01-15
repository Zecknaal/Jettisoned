// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShipWeapons.h"
#include "SmallMissile.h"
#include "WeaponMissile.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API UWeaponMissile : public UShipWeapons
{
	GENERATED_BODY()

	UWeaponMissile();
	
	//Load the blueprint to spawn - only need to do this once
	void loadMissileBP();
	static UClass* missileClass;
	virtual void fire(AActor* target) override;

	ASmallMissile* missile;
	
};
