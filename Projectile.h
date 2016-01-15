// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Projectile.generated.h"

UCLASS()
class JETTISONED_API AProjectile : public APawn
{
	GENERATED_BODY()

public:
	//The sprite for the projectile, obviously!
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* projectileSprite;

	// Sets default values for this pawn's properties
	AProjectile();

	AProjectile(FRotator direction, float force);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//On hit
	virtual void hit();

	virtual void OnHit(AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult* hit);
	
};
