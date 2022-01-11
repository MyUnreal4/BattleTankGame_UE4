// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

class UTankAimingComponent;

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
	UE_LOG(LogTemp, Warning, TEXT("Aiming Comp"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())){ return; }
	FVector OutHitLocation; // Out parameter
	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

// Get world location of line trace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation;
	ScreenLocation.X = ViewportSizeX * CrossHairXLocation;
	ScreenLocation.Y = ViewportSizeY * CrossHairYLocation;
	FVector OutLookDirection;
	if(GetLookDirection(ScreenLocation, OutLookDirection))
	{// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
	}
	return false;
}

//Find our sight vector
bool ATankPlayerController::GetLookDirection(FVector2D &ScreenLocation, FVector &OutWorldDirection) const
{
	FVector OutCameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		OutCameraWorldLocation,
		OutWorldDirection);
}

//Find the actual point in the world where crosshair aims
bool ATankPlayerController::GetLookVectorHitLocation(FVector & LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitObject;
	FVector StartLineTrace = PlayerCameraManager->GetCameraLocation();
	FVector EndLineTrace = StartLineTrace + (LookDirection * LineTraceRange);
	FName TraceTag("TraceTag");
	FCollisionQueryParams Params(TraceTag);
	//GetWorld()->DebugDrawTraceTag = TraceTag; // TODO remove debug line
	Params.AddIgnoredActor(GetPawn());
	if (GetWorld()->LineTraceSingleByChannel(
		HitObject,
		StartLineTrace,
		EndLineTrace,
		ECollisionChannel::ECC_Visibility,
		Params
	))
	{
		OutHitLocation = HitObject.Location;
		return true;
	}
	OutHitLocation = FVector(0.0f);
	return false; // Line trace didn't succeed
}
