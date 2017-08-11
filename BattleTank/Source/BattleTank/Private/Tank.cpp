// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/Actor.h"

float ATank::GetHealthPercent() const
{
	return(float)CurrentHealth / (float)StartingHealth;
}



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
//	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int32 DamagePoints = FMath::Clamp<int32>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);
	int32 prevHealth = CurrentHealth;
	CurrentHealth -= DamagePoints;

	if (CurrentHealth <= 0) 
	{
		OnDeath.Broadcast();
	}

	return DamagePoints;
}


