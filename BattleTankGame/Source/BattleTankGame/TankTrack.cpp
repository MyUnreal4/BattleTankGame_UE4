// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FString TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s trottle: %f "), *TrackName, Throttle);
	//Clamp actual throttle value to avoid player's overdrive
	FVector ForceApplied = GetForwardVector()*
							FMath::Clamp<float>(Throttle, -1.0f, 1.0f)*
							TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

