// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float Speed);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UProjectileMovementComponent * MovementComponent;


private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "Componenst")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Componenst")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Componenst")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Componenst")
	URadialForceComponent* ExplosionForce;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10.f;

	void OnTimerExpire();


};
