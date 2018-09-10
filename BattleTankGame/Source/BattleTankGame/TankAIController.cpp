// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetControlledTank()) {
		FString PossessedTank = GetControlledTank()->GetName();
		UE_LOG(LogTemp, Warning,
			TEXT("Hello from TankAIController. Possessed tank: %s"), *PossessedTank);
	}
	else
	{
		UE_LOG(LogTemp, Warning,
			TEXT("TankAIController not possessing a tank."));
	}
	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Player tank detected. ID: %s"), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("Cannot find player tank"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO move towards the player
	//Aim towards the player
	if (GetPlayerTank())
	{
		AimTowardsCrosshair();
	}
	//Fire if ready
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		AActor* PlayerTank = PlayerController->GetPawn();
		if (PlayerTank != nullptr)
		{
			return Cast<ATank>(PlayerTank);
		}
	}
	return nullptr;
}

void ATankAIController::AimTowardsCrosshair()
{
	if (GetControlledTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}
