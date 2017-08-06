// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime) override;

	float fireRateCoolDown = 0.0f;

};
