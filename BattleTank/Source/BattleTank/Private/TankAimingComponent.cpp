// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::GetProjectileStart(FVector& Location, FRotator& Rotation)
{
	if (ensure(Barrel != nullptr)) {
		Location = Barrel->GetSocketLocation(FName("Projectile"));
		Rotation = Barrel->GetSocketRotation(FName("Projectile"));
	}
}


void UTankAimingComponent::AimAt(FVector location) 
{
	if (ensure(Barrel != nullptr &&  Turret != nullptr))
	{
		auto OurTank = Cast<ATank>(GetOwner());
		auto OurTankName = OurTank->GetName();
		auto barrelLocation = Barrel->GetSocketLocation(FName("Projectile"));

		FVector tossVelocity;
		FVector aimDirection;

		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, tossVelocity, barrelLocation, location, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
		if (bHaveAimSolution)
		{
			aimDirection = tossVelocity.GetSafeNormal();
			MoveBarrelTowards(aimDirection);
		}
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) 
{

	// find difference between current barrel rotation and aim direction

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = aimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	if (ensure(Barrel != nullptr && Turret != nullptr)) 
	{
		Barrel->Elevate(DeltaRotator.Pitch);
		Turret->Rotate(DeltaRotator.Yaw);
	}
}
