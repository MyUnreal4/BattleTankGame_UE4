// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO move towards the player
	//Aim towards the player
	if (GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		AimTowardsCrosshair();
	}
	//Fire if ready

}

void ATankAIController::AimTowardsCrosshair()
{
	if (GetPawn())
	{
		Cast<ATank>(GetPawn())->AimAt(
			GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	}
}
