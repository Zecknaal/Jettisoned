// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "DeepSpace.h"




void UDeepSpace::spawnBackground(FVector2D position){
	FRotator rotation = FRotator(0, 0, 0);
	FVector location = FVector(position.X, 0, position.Y);
	if (!world)
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("No world yet")));
	//backgroundActor = SpawnBP<AActor>(world, getBackgroundBP(), position, rotation);
	backgroundActor = world->SpawnActor<AActor>(getBackgroundBP(), FVector(position.X, -1000, position.Y), rotation);
	//backgroundActor->Destroy();
	backgroundActor = nullptr;
}

UDeepSpace::UDeepSpace(){
	//static ConstructorHelpers::FObjectFinder<UBlueprint> BP(TEXT("Blueprint'/Game/2dSideScroller/Blueprints/BP_Backgorund_DeepSpace.BP_Backgorund_DeepSpace'"));
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP(TEXT("Blueprint'/Game/2dSideScroller/Blueprints/BP_DeepSpace_Sector.BP_DeepSpace_Sector'"));
	if (BP.Object){
		backgroundBP = (UClass*)BP.Object->GeneratedClass;
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("Didn't make background BP")));

	//backgroundBP = readBP(TEXT("Blueprint'/Game/2dSideScroller/Blueprints/BP_Backgorund_DeepSpace.BP_Backgorund_DeepSpace'"));
}