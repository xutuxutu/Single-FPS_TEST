// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponProjectile.h"
#include "Effect/FPS_WeaponEffectManager.h"
#include "WorldObject/DestructibleObject.h"


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
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	ProjectileSound = CreateDefaultSubobject<UAudioComponent>(TEXT("FloatingSound"));
	//Component Setup
	SphereCollider->InitSphereRadius(1.0f);
	SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollider->SetCollisionObjectType(COLLISION_PROJECTILE);
	SphereCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);
	RootComponent = SphereCollider;

	SphereTrigger->InitSphereRadius(150.0f);
	SphereTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereTrigger->SetCollisionObjectType(TRIGGER_PROJECTILE);
	SphereTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereTrigger->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	//SphereTrigger->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereTrigger->SetCollisionResponseToChannel(ECC_Destructible, ECR_Overlap);
	SphereTrigger->SetupAttachment(RootComponent);
	
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
	SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFPS_WeaponProjectile::OnBeginOverlapSphereTrigger);
	SphereTrigger->OnComponentEndOverlap.AddDynamic(this, &AFPS_WeaponProjectile::OnEndOverlapSphereTrigger);
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
	DamageToActors(HitResult.ImpactPoint);
	DeactivateActor();
}

void AFPS_WeaponProjectile::OnBeginOverlapSphereTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive)
	{
		for (auto actor : OnTriggerActor)
		{
			if (actor == OtherActor)
				return;
		}
		OnTriggerActor.push_back(OtherActor);
	}
}

void AFPS_WeaponProjectile::OnEndOverlapSphereTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsActive)
	{
		for (vector<AActor*>::iterator iter = OnTriggerActor.begin(); iter < OnTriggerActor.end(); ++iter)
		{
			if ((*iter) == OtherActor)
			{
				OnTriggerActor.erase(iter);
				return;
			}
		}
	}
}

void AFPS_WeaponProjectile::DamageToActors(FVector hitPoint)
{
	FName actorCollisionPreset;
	FName ImpactObjectType = TEXT("Destructible");

	for (auto actor : OnTriggerActor)
	{
		actorCollisionPreset = Cast<UPrimitiveComponent>(actor->GetRootComponent())->GetCollisionProfileName();

		if (actorCollisionPreset == ImpactObjectType)
		{
			ADestructibleObject* hitObject = Cast<ADestructibleObject>(actor);
			if (hitObject)
			{
				AB_LOG(Warning, TEXT("%s"), *hitObject->GetName());
				float distance = FVector::Dist(hitObject->GetActorLocation(), hitPoint);
				if (distance <= 1)
					distance = 1;

				hitObject->AddDamage(hitPoint, 1000 / distance);
			}
		}
	}
}

void AFPS_WeaponProjectile::ActivateActor()
{
	IsActive = true;
	SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileParticle_Playing = UGameplayStatics::SpawnEmitterAttached(ProjectileParticle, RootComponent);
	MovementComponent->SetUpdatedComponent(RootComponent);
	MovementComponent->Velocity = GetActorForwardVector() * FireSpeed;
}
void AFPS_WeaponProjectile::DeactivateActor()
{
	IsActive = false;
	SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MovementComponent->StopMovementImmediately();
	if (ProjectileParticle_Playing)
		ProjectileParticle_Playing->Deactivate();
	OnTriggerActor.clear();
}