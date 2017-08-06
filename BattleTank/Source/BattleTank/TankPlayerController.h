// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	ATank* GetControlledTank() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float LineTraceRange = 1000000.0f;


private:
	void AimTowardCrossHair();
	bool GetSightRayHitLocation(FVector& location) const;
	bool GetLookDirection(FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const;

};
