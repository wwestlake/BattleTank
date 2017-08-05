// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);
	auto azimuthChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newAzimuth = RelativeRotation.Yaw + azimuthChange;
	SetRelativeRotation(FRotator(0, newAzimuth, 0));

}
