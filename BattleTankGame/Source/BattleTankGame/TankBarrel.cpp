// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	UE_LOG(LogTemp, Error, TEXT("Frames per milliseconds: %f"), GetWorld()->DeltaTimeSeconds)
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChange, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(RawElevation, 0.0f, 0.0f));
}