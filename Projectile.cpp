// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sprite defaults
	FName name = TEXT("SpriteComponent0");
	FName massName = TEXT("Mass");
	projectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(name);
	projectileSprite->SetSimulatePhysics(true);
	projectileSprite->WakeRigidBody();
	projectileSprite->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	projectileSprite->AttachTo(RootComponent);
	projectileSprite->SetCollisionProfileName(TEXT("BlockAll"));
	projectileSprite->SetEnableGravity(false);
	projectileSprite->SetConstraintMode(EDOFMode::XZPlane);
	projectileSprite->bGenerateOverlapEvents = true;
	projectileSprite->SetCollisionObjectType(ECC_Pawn);
}

AProjectile::AProjectile(FRotator direction, float force){
	PrimaryActorTick.bCanEverTick = true;

	FTransform transform = GetTransform();
	transform.ConcatenateRotation(direction.Quaternion());
	transform.NormalizeRotation();
	SetActorTransform(transform);
}

void AProjectile::hit(){
	//This could be overridden if necessary but most projectiles will be blown up / consumed when they hit a target
	Destroy();
}

void AProjectile::OnHit(AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult* hit){
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("Hit!")));
}
// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AProjectile::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

