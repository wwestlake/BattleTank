// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/Actor.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	auto damage = FMath::Clamp<float>(DamageAmount, 0.0f, Health);

	UE_LOG(LogTemp, Warning, TEXT("Hit: %f - %f"), Health, damage)

	Health -= damage;

	return Health;
}


