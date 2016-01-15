// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "Ship.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FName name = TEXT("SpriteComponent0");
	FName massName = TEXT("Mass");
	
	//Sprite defaults
	sprite = CreateDefaultSubobject<UPaperSpriteComponent>(name);
	sprite->SetSimulatePhysics(true);
	sprite->WakeRigidBody();
	sprite->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	sprite->AttachTo(RootComponent);
	sprite->SetCollisionProfileName(TEXT("BlockAll"));
	sprite->SetEnableGravity(false);
	sprite->SetConstraintMode(EDOFMode::XZPlane);
	sprite->bGenerateOverlapEvents = true;
	sprite->SetCollisionObjectType(ECC_Pawn);

	health = 100;
	//sprite->GetBodyInstance()->bOverrideMass = true;
	//sprite->GetBodyInstance()->MassInKg = 5.f;
	//sprite->GetBodyInstance()->UpdateMassProperties();
	//sprite->SetMassOverrideInKg(NAME_None, 5.f, true);
	
	//Super(FObjectInitializer->SetDefaultSubobjectClass<UMovementComponent>(TEXT("Movement")));
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	calculateMovement();
	turnShip(DeltaTime);
	//GetWorld()->GetAuthGameMode()->check
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AShip::setMoveTarget(FVector2D target){
	//At some point navigation procedures will need to be done. For now, we're doing a simple direct control that
	//can easily be mapped over to AI control when necessary
	if (target.X < 0)
		engines->throttleTickDown();
	else if (target.X > 0)
		engines->throttleTickUp();
	else if (target.X == 0)
		engines->throttleTickOff();
}

void AShip::attack(){
	//For now, just loop over the components and shoot any weapons.
	//In the future, this would ideally be controlled by either manual selection from the player,
	//or better, AI chooses how to fight.

	//For purposes of getworld, temporary going to allow this assignment
	attackTarget = this;
	for (auto component : shipComponents){
		auto weapon = dynamic_cast<UShipWeapons*>(component);
		weapon->fire(attackTarget);
	}
}

void AShip::addForce(FVector force){
	GetRootPrimitiveComponent()->AddForce(FVector(0.f, 0.f, 1000000.f));
}

void AShip::calculateMovement(){
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(engines));
	FVector direction = GetActorForwardVector();
	if (engines && engines->getThrottle() > 0){
		direction.X *= engines->getThrottle() * engines->getPower();
		direction.Z *= engines->getThrottle() * engines->getPower();
		direction.Y += 0.f;
		GetRootPrimitiveComponent()->AddForce(direction);
	}
}

void AShip::turnShip(float delta){
	if (turnDirection == 0)
		return;

	FRotator rot = FRotator(turnDirection * engines->getTurnSpeed() * delta, 0.f, 0.f);
	FTransform transform = GetTransform();
	transform.ConcatenateRotation(rot.Quaternion());
	transform.NormalizeRotation();
	SetActorTransform(transform);

}

void AShip::setTurnDirection(float direction){
	turnDirection = direction;
}