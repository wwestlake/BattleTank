// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Public/Math/Rotator.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	void AimAt(FVector location, float LaunchSpeed);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void GetProjectileStart(FVector& Location, FRotator& Rotation);

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);

};
