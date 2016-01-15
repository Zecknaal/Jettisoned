// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "WeaponMissile.h"

UClass* UWeaponMissile::missileClass = nullptr;

UWeaponMissile::UWeaponMissile(){
	weaponName = "Missile Launcher";
	ammo = 10;
	power = 20;
	if (!missileClass)
		loadMissileBP();
}

void UWeaponMissile::fire(AActor* target){
	auto loc = FVector2D(target->GetActorLocation().X + 100, target->GetActorLocation().Z + 100);
	auto rot = FRotator(target->GetActorRotation());
	missile = SpawnBP<ASmallMissile>(target->GetWorld(), missileClass, loc, rot);
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, missile->GetName());
}

void UWeaponMissile::loadMissileBP(){
	static ConstructorHelpers::FObjectFinder<UBlueprint> missileBP(TEXT("Blueprint'/Game/2dSideScroller/Blueprints/Projectiles/Weapons/BP_Small_Missile.BP_Small_Missile'"));
	if (missileBP.Object)
		missileClass = (UClass*)missileBP.Object->GeneratedClass;
}