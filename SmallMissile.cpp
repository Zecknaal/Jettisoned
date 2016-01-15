// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "SmallMissile.h"

ASmallMissile::ASmallMissile(){
	speed = 50000;
	lifetime = 5;
}

void ASmallMissile::Tick(float deltaSeconds){
	auto direction = GetActorForwardVector();
	GetRootPrimitiveComponent()->AddForce(FVector(direction.X * speed * deltaSeconds, 0.f, direction.Z * speed * deltaSeconds));
	lifetime -= deltaSeconds;

	if (lifetime <= 0)
		Destroy();
}

