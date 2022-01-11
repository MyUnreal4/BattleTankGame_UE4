// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FAimingState);

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
	UTankAimingComponent();
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative UClass* is NOT safe
	void AimAt(FVector WorldSpaceAim) const;// Called every frame
	void Fire();
	UPROPERTY(BlueprintAssignable)
	FAimingState Firing;
	UPROPERTY(BlueprintAssignable)
	FAimingState Reloading;

protected:
	UTankBarrel* Barrel = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Aiming;
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
private:
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection) const;
	double LastFireTime = 0.0;
};
