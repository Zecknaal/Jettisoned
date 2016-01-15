// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ShipEngines.h"
#include "ShipWeapons.h"
#include "PaperSprite.h"
#include "PaperSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "ShipComponent.h"
#include "Ship.generated.h"

UCLASS()
class JETTISONED_API AShip : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship Component")
	UShipEngines* engines;
	// Sets default values for this pawn's properties
	AShip();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	//Attacks an enemy! Of course.
	virtual void attack();

	//Adds propulsion - usually for engine, could conceivably be for outside impacts as well
	virtual void addForce(FVector force);

	//Figures out your new position every tick
	virtual void calculateMovement();

	//Set our destination - details of the actual movement can be taken care of in Ticks
	virtual void setMoveTarget(FVector2D target);

	//Whether you're turning left, right, or not at all!
	virtual void setTurnDirection(float direction);

	//Turns you round baby right round
	virtual void turnShip(float delta);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship Stats")
	float health;
protected:
	TArray<UShipComponent*> shipComponents;
	AActor* attackTarget;
	float turnDirection;
	float throttleDirection;
};
