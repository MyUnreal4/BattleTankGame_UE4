// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FiringEvent();
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void ReloadingEvent();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UTankBarrel* Barrel = nullptr;// local reference for spawning projectile
	UPROPERTY(EditDefaultsOnly, Category = Firing)//TODO Two copies of this parameter
	float LaunchSpeed = 4000.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative UClass* is NOT safe
	double ReloadTimeInSeconds = 3.0;
	double LastFireTime = 0.0;
};
