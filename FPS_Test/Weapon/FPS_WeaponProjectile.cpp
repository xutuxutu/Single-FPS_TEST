// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponProjectile.h"
#include "Effect/FPS_WeaponEffectManager.h"


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
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	ProjectileSound = CreateDefaultSubobject<UAudioComponent>(TEXT("FloatingSound"));
	//Component Setup
	SphereCollider->InitSphereRadius(5.0f);
	SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollider->SetCollisionObjectType(COLLISION_PROJECTILE);
	SphereCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	RootComponent = SphereCollider;
	
	MovementComponent->UpdatedComponent = SphereCollider;
	MovementComponent->InitialSpeed = FireSpeed;
	MovementComponent->MaxSpeed = FireSpeed;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->ProjectileGravityScale = 0;
	
	ProjectileSound->SetupAttachment(RootComponent);
	IsActive = true;
}

void AFPS_WeaponProjectile::SetProjectileParticle(UParticleSystem* particle)
{ 
	ProjectileParticle = particle;
}

// Called when the game starts or when spawned
void AFPS_WeaponProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereCollider->MoveIgnoreActors.Add(Instigator);
	MovementComponent->OnProjectileStop.AddDynamic(this, &AFPS_WeaponProjectile::OnImpact);
	DeactivateActor();
}

void AFPS_WeaponProjectile::StartFire(FVector location, FRotator rotation, float maxDistance)
{
	MaxDistance = maxDistance;
	FireStartLocation = location;
	SetActorLocation(location);
	SetActorRotation(rotation);
	ActivateActor();
	GetWorldTimerManager().SetTimer(CheckMoveDistTH, this, &AFPS_WeaponProjectile::CheckMoveDistance, GWorld->GetDeltaSeconds(), true);
}

void AFPS_WeaponProjectile::CheckMoveDistance()
{
	if (IsActive)
	{
		if ((GetActorLocation() - FireStartLocation).Size() > MaxDistance)
		{
			GetWorldTimerManager().ClearTimer(CheckMoveDistTH);
			DeactivateActor();
		}
	}
	else
	{
		if(GetWorldTimerManager().IsTimerActive(CheckMoveDistTH))
			GetWorldTimerManager().ClearTimer(CheckMoveDistTH);
	}
}

void AFPS_WeaponProjectile::OnImpact(const FHitResult& HitResult)
{
	FPS_WeaponEffectManager::GetInstance()->CreateLauncherProjectileImpactEffect(HitResult);
	GetWorldTimerManager().ClearTimer(CheckMoveDistTH);
	DeactivateActor();
}

void AFPS_WeaponProjectile::ActivateActor()
{
	IsActive = true;
	SetActorEnableCollision(true);
	ProjectileParticle_Playing = UGameplayStatics::SpawnEmitterAttached(ProjectileParticle, RootComponent);
	MovementComponent->SetUpdatedComponent(RootComponent);
	MovementComponent->Velocity = GetActorForwardVector() * FireSpeed;
}
void AFPS_WeaponProjectile::DeactivateActor()
{
	IsActive = false;
	SetActorEnableCollision(false);
	MovementComponent->StopMovementImmediately();
	if (ProjectileParticle_Playing)
		ProjectileParticle_Playing->Deactivate();
}