// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TrackComponent.h"


void UTankMovementComponent::Initialize(UTrackComponent* LeftTrackToSet, UTrackComponent* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::LeftThrottle(float throttle)
{
	if (LeftTrack == nullptr || RightTrack == nullptr) return;
	LeftTrack->SetThrottle(throttle);
}

void UTankMovementComponent::RightThrottle(float throttle)
{
	if (LeftTrack == nullptr || RightTrack == nullptr) return;
	RightTrack->SetThrottle(throttle);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack == nullptr || RightTrack == nullptr) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendMoveTurn(float Throw)
{
	if (LeftTrack == nullptr || RightTrack == nullptr) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardAmount = FVector::DotProduct(TankForward, AIForwardIntention);
	auto TurnAmount = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendMoveForward(ForwardAmount);

	IntendMoveTurn(TurnAmount);


}