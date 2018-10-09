// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

class UTankTurret;

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (TankAimingComponent && BarrelToSet)
	{
		TankAimingComponent->SetBarrelReference(BarrelToSet);
		Barrel = BarrelToSet;
	}
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	if (TankAimingComponent && TurretToSet)
	{
		TankAimingComponent->SetTurretReference(TurretToSet);
	}
}

void ATank::Fire()
{
	if (Barrel)
	{
		// Spawning projectile at the socet location on the barrel
		FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			SpawnLocation, 
			SpawnRotation
			);
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

