// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enumerations

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward declaration
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	// Called every frame
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed) const;
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UTankBarrel* Barrel = nullptr;
private:
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection) const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Locked;
};
