// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Tickable.h"
#include "ShipComponent.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API UShipComponent : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UShipComponent() { };
	virtual void Tick(float DeltaTime) override{};
	virtual bool IsTickable() const override { return true; };
	virtual TStatId GetStatId() const override{ TStatId dummy;  return dummy; };
	virtual bool IsTickableWhenPaused() const{ return false; };
	virtual bool IsTickableInEditor() const{ return false; };
	
	
};
