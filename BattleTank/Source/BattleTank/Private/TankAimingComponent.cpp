// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	// so that first fire is after reload
	LastFireTime = FPlatformTime::Seconds();
	AmmoRemaining = AmmoInnitialLoad;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (AmmoRemaining <= 0) {
		FiringStatus = EFiringState::OutOfAmmo;
	} else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds) {
		FiringStatus = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringState::Aiming;
	}
	else {
		FiringStatus = EFiringState::Locked;
	}
}


EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int32 UTankAimingComponent::GetRemainingAmmo() const
{
	return AmmoRemaining;
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
	if (ensure(Barrel != nullptr  && Turret != nullptr)) {
		auto barrelLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FVector tossVelocity;
		FVector aimDirection;
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, tossVelocity, barrelLocation, location, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
		if (bHaveAimSolution) {
			aimDirection = tossVelocity.GetSafeNormal();
			MoveBarrelTowards(aimDirection);
		}
	}
}



void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	currentAimDirection = aimDirection;
	// find difference between current barrel rotation and aim direction

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = aimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	if (ensure(Barrel != nullptr && Turret != nullptr)) 
	{
		Barrel->Elevate(DeltaRotator.Pitch);
		if (FMath::Abs(DeltaRotator.Yaw) < 180) {
			Turret->Rotate(DeltaRotator.Yaw);
		}
		else // avoid going the long way around
		{
			Turret->Rotate(-DeltaRotator.Yaw);
		}
	}
}

bool UTankAimingComponent::IsBarrelMoving() 
{
	auto barrelVector = Barrel->GetForwardVector();
	return (! barrelVector.Equals(currentAimDirection, 0.1f));
}

void UTankAimingComponent::Fire()
{
	FVector ProjectileStartLocation;
	FRotator ProjectileStartRotation;
	
	GetProjectileStart(ProjectileStartLocation, ProjectileStartRotation);
	
	if (FiringStatus == EFiringState::Locked || FiringStatus == EFiringState::Aiming) {
		auto newProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, ProjectileStartLocation, ProjectileStartRotation);
		newProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoRemaining--;
	}
}
