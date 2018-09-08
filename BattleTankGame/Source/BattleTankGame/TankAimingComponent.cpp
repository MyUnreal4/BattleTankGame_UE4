// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed) const
{
	if (!Barrel)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Tank's barrel is not found"));
		return; 
	}
	FString CurrentTankName = GetOwner()->GetName();
	FVector BarrelLocation = Barrel->GetComponentLocation();
	/*UE_LOG(LogTemp, Warning, TEXT("%s Aim at : %s from: %s"),
			*CurrentTankName, 
			*WorldSpaceAim.ToString(),
			*BarrelLocation.ToString()
			);
	UE_LOG(LogTemp, Warning, TEXT("Launch speed %f cm/s"), LaunchSpeed);*/

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	))
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aim Direction: %s"), *AimDirection.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find AIM DIRECTION"));
	}
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	if (BarrelToSet)
	{
		Barrel = BarrelToSet;
	}
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

