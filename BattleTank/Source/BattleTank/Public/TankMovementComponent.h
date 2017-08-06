// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTrackComponent;

/**
 * Provides tank like movement including drive by wire for AI controllers
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable)
	void IntendMoveTurn(float Throw);

	UFUNCTION(BlueprintCallable)
	void LeftThrottle(float throttle);

	UFUNCTION(BlueprintCallable)
	void RightThrottle(float throttle);


	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTrackComponent* LeftTrackToSet, UTrackComponent* RightTrackToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


private:
	UTrackComponent* LeftTrack = nullptr;
	UTrackComponent* RightTrack = nullptr;

};
