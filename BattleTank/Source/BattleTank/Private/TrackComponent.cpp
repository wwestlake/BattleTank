// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackComponent.h"



void UTrackComponent::SetThrottle(float ThrottleSetting)
{

	if (ReverseThrottle) {
		Throttle = FMath::Clamp<float>(-ThrottleSetting, -1, 1);
	}
	else {
		Throttle = FMath::Clamp<float>(ThrottleSetting, -1, 1);
	}

	Throttle = FMath::Clamp<float>(Throttle, -1, 1);

	CurrentForce = TrackMaxDrivingForce * Throttle;

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation() + GetForwardVector() * 500;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);


}

void UTrackComponent::SetReverse(bool ReverseThrottleSetting)
{
	ReverseThrottle = ReverseThrottleSetting;
}


