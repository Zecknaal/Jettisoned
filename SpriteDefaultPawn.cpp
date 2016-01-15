// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "SpriteDefaultPawn.h"


#include "Engine.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerInput.h"

FName ASpriteDefaultPawn::MovementComponentName(TEXT("MovementComponent0"));
FName ASpriteDefaultPawn::CollisionComponentName(TEXT("CollisionComponent0"));
//FName ASpriteDefaultPawn::MeshComponentName(TEXT("MeshComponent0"));


ASpriteDefaultPawn::ASpriteDefaultPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCanBeDamaged = true;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	NetPriority = 3.0f;

	BaseEyeHeight = 0.0f;
	bCollideWhenPlacing = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(ASpriteDefaultPawn::CollisionComponentName);
	CollisionComponent->InitSphereRadius(35.0f);

	static FName CollisionProfileName(TEXT("Pawn"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName);

	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->bShouldUpdatePhysicsVolume = true;
	CollisionComponent->bCanEverAffectNavigation = false;
	CollisionComponent->bDynamicObstacle = true;

	RootComponent = CollisionComponent;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(ASpriteDefaultPawn::MovementComponentName);
	MovementComponent->UpdatedComponent = CollisionComponent;

	//// Structure to hold one-time initialization
	//struct FConstructorStatics
	//{
	//	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh;
	//	FConstructorStatics()
	//		: SphereMesh(TEXT("/Engine/EngineMeshes/Sphere")) {}
	//};

	//static FConstructorStatics ConstructorStatics;

	//MeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(ASpriteDefaultPawn::MeshComponentName);
	//if (MeshComponent)
	//{
	//	MeshComponent->SetStaticMesh(ConstructorStatics.SphereMesh.Object);
	//	MeshComponent->AlwaysLoadOnClient = true;
	//	MeshComponent->AlwaysLoadOnServer = true;
	//	MeshComponent->bOwnerNoSee = true;
	//	MeshComponent->bCastDynamicShadow = true;
	//	MeshComponent->bAffectDynamicIndirectLighting = false;
	//	MeshComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	//	MeshComponent->AttachParent = RootComponent;
	//	MeshComponent->SetCollisionProfileName(CollisionProfileName);
	//	const float Scale = CollisionComponent->GetUnscaledSphereRadius() / 160.f; // @TODO: hardcoding known size of EngineMeshes.Sphere. Should use a unit sphere instead.
	//	MeshComponent->SetRelativeScale3D(FVector(Scale));
	//	MeshComponent->bGenerateOverlapEvents = false;
	//	MeshComponent->bCanEverAffectNavigation = false;
	//}

	// This is the default pawn class, we want to have it be able to move out of the box.
	bAddDefaultMovementBindings = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void InitializeDefaultPawnInputBindings()
{
	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Up, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Down, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::Gamepad_LeftY, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::Gamepad_LeftX, 1.f));

		// HACK: Android controller bindings in ini files seem to not work
		//  Direct overrides here some to work
#if !PLATFORM_ANDROID
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_LeftThumbstick, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_RightThumbstick, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_FaceButton_Bottom, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::LeftControl, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::SpaceBar, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::C, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::E, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Q, -1.f));
#else
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_LeftTriggerAxis, -0.5f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Gamepad_RightTriggerAxis, 0.5f));
#endif

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_TurnRate", EKeys::Gamepad_RightX, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_TurnRate", EKeys::Left, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_TurnRate", EKeys::Right, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_Turn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_LookUpRate", EKeys::Gamepad_RightY, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_LookUp", EKeys::MouseY, -1.f));
	}
}

void ASpriteDefaultPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	check(InputComponent);

	if (bAddDefaultMovementBindings)
	{
		InitializeDefaultPawnInputBindings();

		InputComponent->BindAxis("DefaultPawn_MoveForward", this, &ASpriteDefaultPawn::MoveForward);
		InputComponent->BindAxis("DefaultPawn_MoveRight", this, &ASpriteDefaultPawn::MoveRight);
		InputComponent->BindAxis("DefaultPawn_MoveUp", this, &ASpriteDefaultPawn::MoveUp_World);
		InputComponent->BindAxis("DefaultPawn_Turn", this, &ASpriteDefaultPawn::AddControllerYawInput);
		InputComponent->BindAxis("DefaultPawn_TurnRate", this, &ASpriteDefaultPawn::TurnAtRate);
		InputComponent->BindAxis("DefaultPawn_LookUp", this, &ASpriteDefaultPawn::AddControllerPitchInput);
		InputComponent->BindAxis("DefaultPawn_LookUpRate", this, &ASpriteDefaultPawn::LookUpAtRate);
	}
}

void ASpriteDefaultPawn::UpdateNavigationRelevance()
{
	if (CollisionComponent)
	{
		CollisionComponent->SetCanEverAffectNavigation(bCanAffectNavigationGeneration);
	}
}

void ASpriteDefaultPawn::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
		}
	}
}

void ASpriteDefaultPawn::MoveForward(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
		}
	}
}

void ASpriteDefaultPawn::MoveUp_World(float Val)
{
	if (Val != 0.f)
	{
		AddMovementInput(FVector::UpVector, Val);
	}
}

void ASpriteDefaultPawn::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void ASpriteDefaultPawn::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

// @TODO: DEPRECATED, remove.
void ASpriteDefaultPawn::LookUp(float Val)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->AddPitchInput(Val);
	}
}

// @TODO: DEPRECATED, remove.
void ASpriteDefaultPawn::Turn(float Val)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->AddYawInput(Val);
	}
}

UPawnMovementComponent* ASpriteDefaultPawn::GetMovementComponent() const
{
	return MovementComponent;
}

/** Returns CollisionComponent subobject **/
USphereComponent* ASpriteDefaultPawn::GetCollisionComponent() const { return CollisionComponent; }
/** Returns MeshComponent subobject **/
//UStaticMeshComponent* ASpriteDefaultPawn::GetMeshComponent() const { return MeshComponent; }


