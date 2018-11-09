// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed) const
{
	if (!Barrel || !Turret)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank's barrel or turret is not found"));
		return;
	}

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim found"), Time);

		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No Solution Found"), Time);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (BarrelToSet)
	{
		Barrel = BarrelToSet;
		Cast<ATank>(GetOwner())->SetAimingComponent(this);
	}
	if (TurretToSet)
	{
		Turret = TurretToSet;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const
{
	if (!Barrel || !Turret) { return; }
	//find barral current position
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("Aim as rotator: %s"), *AimAsRotator.ToString());
	//move barrel & turret to have the same vector as AimDirection
	Barrel->Elevate(DeltaRotator.Pitch);
	//always yaw the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}
