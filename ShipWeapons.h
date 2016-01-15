// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShipComponent.h"
#include "ShipWeapons.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API UShipWeapons : public UShipComponent
{
	GENERATED_BODY()
public:
	virtual void fire(AActor* target){};
protected:
	FString weaponName;
	int32 ammo;
	int32 power;
};
