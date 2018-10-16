// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	FString TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s trottle: %f "), *TrackName, Throttle);

	//TODO Clamp actual throttle value to avoid player's overdrive 
}

