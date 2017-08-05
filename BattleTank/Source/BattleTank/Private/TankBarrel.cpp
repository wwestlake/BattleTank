// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	// move barrel the correct amount this frame given a max elevation speed and the frame time

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);
	auto elevationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto newElevation = FMath::Clamp<float>(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(newElevation, 0, 0));

}


