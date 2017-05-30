// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponProjectile.h"


// Sets default values
AFPS_WeaponProjectile::AFPS_WeaponProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bReplicateMovement = true;
	//Create Component
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	//Component Setup
	SphereCollider->InitSphereRadius(5.0f);
	SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollider->SetCollisionObjectType(COLLISION_PROJECTILE);
	SphereCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	RootComponent = SphereCollider;

	ProjectileParticle->bAutoActivate = false;
	ProjectileParticle->bAutoDestroy = false;
	ProjectileParticle->SetupAttachment(RootComponent);

	MovementComponent->UpdatedComponent = SphereCollider;
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->MaxSpeed = 2000.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void AFPS_WeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
}