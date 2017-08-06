// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TrackComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float ThrottleSetting);

	UFUNCTION(BlueprintCallable)
		void SetReverse(bool ReverseThrottleSetting);

	// Max force for this track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float TrackMaxDrivingForce = 400000;

private:
	float Throttle = 0.0f;
	float CurrentForce = 0.0f;
	bool ReverseThrottle = false;
};
