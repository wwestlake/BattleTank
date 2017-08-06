// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
	void SetTurretReference(UTankTurret* TurretToSet);


	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0f;

	// Maximum firing rate in seconds
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float MaxFiringRate = 3.0f;

	// Maximum firing rate in seconds
	UPROPERTY(EditAnyWhere, Category = Firing)
		bool EnableFiringMode = true;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UTankAimingComponent* TankAimingComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector location);

	UFUNCTION(BlueprintCallable)
	void Fire();


private:


	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	// local pointer to Barrel for spawning projectile
	UTankBarrel* Barrel = nullptr;

	float ReloadTimeSeconds = 3.0f;
	double LastFireTime = 0.0f;
};
