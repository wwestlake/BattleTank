// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackComponent.h"
#include "Engine/World.h"

UTrackComponent::UTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTrackComponent::BeginPlay() 
{
	OnComponentHit.AddDynamic(this, &UTrackComponent::OnHit);
}


void UTrackComponent::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2.0;
	TankRoot->AddForce(CorrectionForce);
}

void UTrackComponent::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
w	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}


void UTrackComponent::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}


void UTrackComponent::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation() + GetForwardVector() * 500;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

