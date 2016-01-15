// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Tickable.h"
#include "ShipEngines.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API UShipEngines : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UShipEngines() { };
	virtual void turnOn() { on = true; };
	virtual void turnOff() { on = false; throttle = 0; throttleDirection = 0; };
	virtual void setThrottle(float newThrottle) {};
	virtual void throttleTickUp(){};
	virtual void throttleTickDown(){};
	virtual void throttleTickOff(){ throttleDirection = 0; };
	UFUNCTION(BlueprintCallable,  Category = "Engines")
	virtual float getThrottle() { return throttle; };
	virtual float getTurnSpeed() { return turnSpeed; }
	virtual float getPower() { return power; }
	virtual void damage() {};
	virtual float getPropulsion() { return throttle * maxPropulsion; }
	virtual float getAcceleration(){ return acceleration; }
	virtual void Tick(float DeltaTime) override{
		updateThrottle(DeltaTime);
		updateFuel(DeltaTime);
	}
	virtual void updateThrottle(float delta){
		if (throttleDirection == 0)
			return;
		throttle += delta * throttleDirection * acceleration;
		if (throttle <= 0 && throttleDirection == -1)
			throttle = throttleDirection = 0;
		else if (throttle >= 100 && throttleDirection == 1){
			throttle = 100;
			throttleDirection = 0;
		}
	}
	virtual void updateFuel(float delta){
		if (!on)
			return;
		fuel -= fuelConsumptionRate * delta;
		if (fuel <= 0){
			fuel = 0;
			turnOff();
		}
	}
	virtual bool IsTickable() const override { return true; };
	virtual TStatId GetStatId() const override{ TStatId dummy;  return dummy; };
	virtual bool IsTickableWhenPaused() const{ return false; };
	virtual bool IsTickableInEditor() const{ return false; };

protected:
	float fuelConsumptionRate = 0;
	float fuel;
	float health = 0;
	float throttle = 0;
	float maxPropulsion = 0;
	float power = 0;
	float turnSpeed;
	float throttleDirection = 0;
	float acceleration = 0;
	FString name;
	bool on;
};
