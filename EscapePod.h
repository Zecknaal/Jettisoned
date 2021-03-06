// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ship.h"
#include "EscapePodEngines.h"
#include "WeaponMissile.h"
#include "EscapePod.generated.h"

UCLASS()
class JETTISONED_API AEscapePod : public AShip
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEscapePod();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};