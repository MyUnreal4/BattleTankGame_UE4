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
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetAimingComponent(UTankAimingComponent* AimingComponentToSet)
{
	if (AimingComponentToSet)
	{
		TankAimingComponent = AimingComponentToSet;
		Barrel = AimingComponentToSet->Barrel;
	}
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReload = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReload)
	{
		// Spawning projectile at the socet location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		FiringEvent();
		LastFireTime = FPlatformTime::Seconds();
	}
	else
	{
		ReloadingEvent();
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

