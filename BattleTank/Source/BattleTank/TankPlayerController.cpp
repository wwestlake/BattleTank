// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto tank = GetControlledTank();
	if (tank == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No Controlled Tank Found"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found Controlled Tank: %s"), *tank->GetName());
	}
}
