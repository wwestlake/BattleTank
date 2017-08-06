// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// -1 is max downward movement sppeed, +1 is max upward movement speed
	void Elevate(float relativeSpeed);

private:
	// Maximumnet movement speed in degrees per second
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 10;

	// Maximum elevation angle in degrees
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxElevationDegrees = 45;

	// Minimum elevation angle in degrees
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinElevationDegrees = 0;



};
