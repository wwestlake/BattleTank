// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	PrimaryActorTick.bCanEverTick = false;
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference( BarrelToSet );
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent->SetTurretReference(TurretToSet);
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

void ATank::AimAt(FVector location)
{
	auto OurTankName = GetName();
	TankAimingComponent->AimAt(location, LaunchSpeed);
}

void ATank::Fire()
{

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;

	if (Barrel && isReloaded && EnableFiringMode) {
		auto newProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		newProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

}


