// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// TODO Fix Firing
void ATank::Fire()
{
//	auto TankAimingComponent = FindComponentByClass<UTankAimingComponent>
//	if (ensure(TankAimingComponent != nullptr)) {
//		bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
//
//		FVector ProjectileStartLocation;
//		FRotator ProjectileStartRotation;
//
//		TankAimingComponent->GetProjectileStart(ProjectileStartLocation, ProjectileStartRotation);
//
//		if (isReloaded && EnableFiringMode) {
//			auto newProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, ProjectileStartLocation, ProjectileStartRotation);
//			newProjectile->LaunchProjectile(LaunchSpeed);
//			LastFireTime = FPlatformTime::Seconds();
//		}
//	}
}


