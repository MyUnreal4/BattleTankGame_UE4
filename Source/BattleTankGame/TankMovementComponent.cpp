// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
		if (Throw != 0.0) Accelerate.Broadcast();
	}
}

void UTankMovementComponent::IntendMoveLeft(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(-Throw);
		RightTrack->SetThrottle(Throw);
		if (Throw != 0.0) Accelerate.Broadcast();
	}
}

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (LeftTrackToSet && RightTrackToSet)
	{
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float MoveForwardVelocity = FVector::DotProduct(TankForwardVector, AIForwardIntention);
	IntendMoveForward(MoveForwardVelocity);

	float RightThrowVelocity = FVector::CrossProduct(AIForwardIntention, TankForwardVector).Z;
	IntendMoveLeft(RightThrowVelocity);
}
