// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "TankAimingComponent.h"


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO Refactor
	// auto targetPosition = GetTargetFromCrossHair();
	// GetTargetingComponent()->Target(targetPosition, DeltaTime);

	AimTowardCrossHair();
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent != nullptr)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::AimTowardCrossHair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent != nullptr)) { return; }
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation)) 
	{
		AimingComponent->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& location) const
{
	FVector lookDirection;
	if (GetLookDirection(lookDirection)) {
		return GetLookVectorHitLocation(location, lookDirection);
	}
	return false;
}


bool ATankPlayerController::GetLookDirection(FVector & LookDirection) const
{
	int32 viewPortSizeX, viewPortSizeY;
	FVector worldLocation;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	auto screenLocation = FVector2D(viewPortSizeX * CrossHairXLocation, viewPortSizeY * CrossHairYLocation);
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FVector cameraLocation = PlayerCameraManager->GetCameraLocation();
	FHitResult hitResult;
	//FCollisionQueryParams params(FName(TEXT("")), false, GetOwner());
	FVector endPoint = cameraLocation + (LookDirection * LineTraceRange);
	//if (GetWorld()->LineTraceSingleByObjectType(hitResult, cameraLocation, endPoint, FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic), params))
	if (GetWorld()->LineTraceSingleByChannel( hitResult, cameraLocation, endPoint, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = hitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}


