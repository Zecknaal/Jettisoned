// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "EscapePodEngines.h"


void UEscapePodEngines::turnOn() {
	on = true;
}

void UEscapePodEngines::setThrottle(float newThrottle){
	throttle = newThrottle < 0 ? 0 : newThrottle;
}

float UEscapePodEngines::getThrottle(){
	return throttle;
}

UEscapePodEngines::UEscapePodEngines(){
	fuel = 100;
	fuelConsumptionRate = 1;
	health = 100;
	throttle = 0;
	acceleration = 10;
	maxPropulsion = 10;
	on = false;
	power = 100;
	turnSpeed = 200;
	name = FString(TEXT("Engines"));
}

void UEscapePodEngines::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	/*
	fuel -= fuelConsumptionRate * DeltaTime;
	if (fuel <= 0){
		fuel = 0;
		turnOff();
	}
	*/
}

void UEscapePodEngines::throttleTickUp(){
	throttleDirection = 1;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::SanitizeFloat(throttle));
}

void UEscapePodEngines::throttleTickDown(){
	throttleDirection = -1;
}