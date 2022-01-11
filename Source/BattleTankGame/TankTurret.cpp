// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RotationSpeed)
{
	RotationSpeed = FMath::Clamp<float>(RotationSpeed, -1.0, 1.0);
	float RotationChange = RotationSpeed * MaxRotationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawRotation = GetRelativeRotation().Yaw + RotationChange;
	SetRelativeRotation(FRotator(0.0f, RawRotation, 0.0f));
}


