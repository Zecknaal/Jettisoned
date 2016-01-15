// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Region.generated.h"

UCLASS()
class JETTISONED_API ARegion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARegion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Region")
		int32 regionRadius;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Region")
		FString regionName;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Region")
		bool active;
	
};
