// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto tank = GetControlledTank();
	if (tank == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No AI Controlled Tank Found"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found AI Controlled Tank: %s"), *tank->GetName());
	}

	auto playerTank = GetPlayerTank();
	if (playerTank == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to locate Player Tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found Player Tank: %s"), *playerTank->GetName());
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerController = GetWorld()->GetFirstPlayerController();
	if (playerController != nullptr) {
		auto tankPlayerController = Cast<ATankPlayerController>(playerController);
		return tankPlayerController->GetControlledTank();
	}
	return nullptr;
}


