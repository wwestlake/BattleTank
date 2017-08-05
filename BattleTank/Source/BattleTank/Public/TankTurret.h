// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward movement sppeed, +1 is max upward movement speed
	void Rotate(float relativeSpeed);


private:
	// Maximumnet movement speed in degrees per second
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 25;

	
	
};
