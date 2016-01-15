// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "InputcoreTypes.h"
#include "Ship.h"
#include "Engine.h"
#include "ShipController.generated.h"

/**
 * 
 */
UCLASS()
class JETTISONED_API AShipController : public APlayerController
{
	GENERATED_BODY()
private:
	bool cameraLock;
public:
	ACameraActor* mainCamera;
	AShipController();
	virtual void SetupInputComponent() override;
	void setThrottle(float throttleDelta);
	void throttleUp();
	void throttleDown();
	// Called every frame
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
		void addUI();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void Tick(float DeltaSeconds) override;
	virtual void Tick_Implementation(float DeltaSeconds);
	//UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	virtual void BeginPlay() override;
	void lockCameraToPawn(float DeltaSeconds);
	void checkForScroll(ACameraActor* camera, float delta);
	void turnShip(float angle);
	void turnLeft();
	void turnRight();
	void stopTurnLeft();
	void stopTurnRight();
	void stopThrottle();
	void attack();
	virtual void Possess(APawn* InPawn) override;
	static APawn* controlledPawn;
};
