// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//
#include "ShipEngines.h"
#include "EscapePodEngines.generated.h"
//
//
UCLASS()
class JETTISONED_API UEscapePodEngines : public UShipEngines
{
	GENERATED_BODY()
public:
	virtual void turnOn() override;
	virtual void setThrottle(float newThrottle) override;
	virtual float getThrottle() override;
	virtual void throttleTickUp() override;
	virtual void throttleTickDown() override;
	virtual void Tick(float DeltaTime) override;
	UEscapePodEngines();
};
