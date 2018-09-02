// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetControlledTank()) {
		FString PossessedTank = GetControlledTank()->GetName();
		UE_LOG(LogTemp, Warning, 
			TEXT("Hello from TankPlayerController. Possessed tank: %s"), *PossessedTank);
	}
	else
	{
		UE_LOG(LogTemp, Warning,
			TEXT("TankPlayerController not possessing a tank."));
	}
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
