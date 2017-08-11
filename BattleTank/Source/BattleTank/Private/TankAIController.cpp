// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);

	}
}

void ATankAIController::OnPossessedTankDeath()
{
	auto pawn = GetPawn();
	if (!pawn) { return; }
	pawn->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank != nullptr && ControlledTank != nullptr)) { return; }
	// Move toward player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
	// Aim at the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}
}

