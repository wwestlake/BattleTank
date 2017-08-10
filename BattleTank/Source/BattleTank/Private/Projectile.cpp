// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
	auto attachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);

	

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//auto root = CreateDefaultSubobject<USceneComponent>(FName("Scene Root"));
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(CollisionMesh, attachmentRules);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	MovementComponent->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(CollisionMesh, attachmentRules);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosive Force"));
	ExplosionForce->AttachToComponent(CollisionMesh, attachmentRules);
	ExplosionForce->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float Speed) 
{
	auto velocity = FVector::ForwardVector * Speed;
	MovementComponent->SetVelocityInLocalSpace(velocity);
	MovementComponent->Activate();
	auto Time = GetWorld()->GetTimeSeconds();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);

	FTimerHandle Timer;

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}


void AProjectile::OnTimerExpire()
{
	Destroy();
}
