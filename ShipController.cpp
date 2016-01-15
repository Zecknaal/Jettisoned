// Fill out your copyright notice in the Description page of Project Settings.

#include "Jettisoned.h"
#include "ShipController.h"

APawn* AShipController::controlledPawn = nullptr;

AShipController::AShipController(){
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void AShipController::BeginPlay(){
	FName cameraName = TEXT("Main Camera");
	FVector pos = FVector(0.f, 500.f, 0.f);
	FRotator rot = FRotator(0.f, -90.f, 0.f);
	mainCamera = (ACameraActor*)GetWorld()->SpawnActor(ACameraActor::StaticClass(), &pos, &rot); //CreateDefaultSubobject<ACameraActor>(cameraName);
	mainCamera->SetActorLabel(FString(TEXT("Main Camera")));
	//mainCamera->fov
	PlayerCameraManager->SetFOV(120.f);
	SetViewTarget(mainCamera);
	addUI();
}

void AShipController::Possess(APawn* InPawn){
	Super::Possess(InPawn);
	controlledPawn = InPawn;
}

void AShipController::SetupInputComponent(){
	Super::SetupInputComponent();
	bAutoManageActiveCameraTarget = false;
	//InputComponent->BindAction("CenterView", IE_Pressed, this, &AShipController::lockCameraToPawn);
	InputComponent->BindAction("ThrottleUp", IE_Pressed, this, &AShipController::throttleUp);
	InputComponent->BindAction("ThrottleDown", IE_Pressed, this, &AShipController::throttleDown);
	InputComponent->BindAction("ThrottleUp", IE_Released, this, &AShipController::stopThrottle);
	InputComponent->BindAction("ThrottleDown", IE_Released, this, &AShipController::stopThrottle);
	InputComponent->BindAction("TurnLeft", IE_Pressed, this, &AShipController::turnLeft);
	InputComponent->BindAction("TurnRight", IE_Pressed, this, &AShipController::turnRight);
	InputComponent->BindAction("TurnLeft", IE_Released, this, &AShipController::stopTurnLeft);
	InputComponent->BindAction("TurnRight", IE_Released, this, &AShipController::stopTurnRight);
	InputComponent->BindAction("Attack", IE_Released, this, &AShipController::attack);
}

void AShipController::attack(){
	auto pawn = Cast<AShip>(this->GetPawn());
	if (!pawn)
		return;

	pawn->attack();

}

//Eventually these should be scrapped, as the controller doesn't care *how* a ship moves to the target, just about
//making decisions *what* to do
void AShipController::throttleUp(){
	AShip* pawn = Cast<AShip>(this->GetPawn());
	if (!pawn)
		return;

	FVector2D target = FVector2D(1, 0);
	pawn->setMoveTarget(target);
}

void AShipController::throttleDown(){
	auto pawn = Cast<AShip>(this->GetPawn());
	if (!pawn)
		return;

	FVector2D target = FVector2D(-1, 0);
	pawn->setMoveTarget(target);
}

void AShipController::stopThrottle(){
	auto pawn = Cast<AShip>(this->GetPawn());
	if (!pawn)
		return;

	FVector2D target = FVector2D(0, 0);
	pawn->setMoveTarget(target);
}

void AShipController::setThrottle(float throttleDelta){
	/*
	auto pawn = Cast<AShip>(this->GetPawn());
	if (!GetPawn())
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("No pawn is possessed")));
	FVector vec = FVector(0.f, 0.f, 100.f);
	if (pawn){
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString(TEXT("Adding force....")));
		pawn->addForce(vec);
	}
	*/
}

// Called every frame
//void AShipController::begin_Implementation(){

//}

void AShipController::Tick_Implementation(float DeltaSeconds){
	lockCameraToPawn(DeltaSeconds);
	checkForScroll(mainCamera, DeltaSeconds);
}

void AShipController::lockCameraToPawn(float DeltaSeconds){
	if (!GetPawn())
		return;
	FVector pawnLocation = GetPawn()->GetActorLocation();
	FVector cameraLocation = mainCamera->GetActorLocation();
	FVector newCameraLocation = FVector(pawnLocation.X, cameraLocation.Y, pawnLocation.Z);

	if (!FMath::IsNearlyEqual(pawnLocation.X, cameraLocation.X)){
		newCameraLocation.X = FMath::FInterpTo(newCameraLocation.X, pawnLocation.X, DeltaSeconds, 100);
	}
	if (!FMath::IsNearlyEqual(pawnLocation.Z, cameraLocation.Z)){
		newCameraLocation.Z = FMath::FInterpTo(newCameraLocation.Z, pawnLocation.Z, DeltaSeconds, 100);
	}

	mainCamera->SetActorLocation(newCameraLocation);
}

void AShipController::checkForScroll(ACameraActor* camera, float delta){
	const float SCROLL_WIDTH = .15;
	float x, y;
	if (!GEngine || !GEngine->GameViewport || !GEngine->GameViewport->Viewport || !camera)
		return;
	FVector2D viewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
	
	FVector newCameraLocation = FVector(camera->GetActorLocation());

	GetMousePosition(x, y);

	if (x > 0 && x < viewportSize.X * SCROLL_WIDTH)
		newCameraLocation.X -= 10.f * delta * (viewportSize.X * SCROLL_WIDTH - x);
	else if (x > 0 && x > viewportSize.X * (1 - SCROLL_WIDTH))
		newCameraLocation.X += 10.f * delta * (x - viewportSize.X * (1 - SCROLL_WIDTH));

	if (y > 0 && y < viewportSize.Y *  SCROLL_WIDTH)
		newCameraLocation.Z += 10.f * delta * (viewportSize.Y * SCROLL_WIDTH - y);
	else if (y > 0 && y > viewportSize.Y * (1 - SCROLL_WIDTH))
		newCameraLocation.Z -= 10.f * delta * (y - viewportSize.Y * (1 - SCROLL_WIDTH));

	camera->SetActorLocation(newCameraLocation);
}

void AShipController::turnShip(float angle){
	AShip* pawn = Cast<AShip>(this->GetPawn());
	if (!pawn)
		return;
	pawn->setTurnDirection(angle);
}

void AShipController::turnLeft(){
	turnShip(1);
}

void AShipController::turnRight(){
	turnShip(-1);
}

void AShipController::stopTurnLeft(){
	turnShip(0);
}

void AShipController::stopTurnRight(){
	turnShip(0);
}