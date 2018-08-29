// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FString PossessedTank = GetControlledTank()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *PossessedTank);
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
