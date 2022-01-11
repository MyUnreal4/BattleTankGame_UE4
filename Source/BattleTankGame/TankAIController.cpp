// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ensure(PlayerTank && ControlledTank)) { return; }

	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	//Aim towards the player
	AimTowardsCrosshair();
	//Fire if ready
	ControlledTank->Fire();
}

void ATankAIController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) { return; }

	Cast<ATank>(GetPawn())->AimAt(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
}
