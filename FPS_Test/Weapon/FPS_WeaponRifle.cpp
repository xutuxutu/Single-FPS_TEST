// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponRifle.h"
#include "Effect/FPS_WeaponImpactEffect.h"
#include "Effect/FPS_WeaponEffectManager.h"


// Sets default values
AFPS_WeaponRifle::AFPS_WeaponRifle() : AFPS_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> rifle(TEXT("SkeletalMesh'/Game/Weapons/Rifle.Rifle'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> muzzleFX(TEXT("ParticleSystem'/Game/Effects/ParticleSystems/Weapons/AssaultRifle/Muzzle/P_AssaultRifle_MF.P_AssaultRifle_MF'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> trailFX(TEXT("ParticleSystem'/Game/Effects/ParticleSystems/Weapons/AssaultRifle/Muzzle/P_AssaultRifle_Trail.P_AssaultRifle_Trail'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> fireSound(TEXT("SoundCue'/Game/Sounds/Weapon_AssaultRifle/Mono/AssaultRifle_ShotLoop_Cue.AssaultRifle_ShotLoop_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> fireEndSound(TEXT("SoundCue'/Game/Sounds/Weapon_AssaultRifle/Mono/AssaultRifle_ShotEnd_Cue.AssaultRifle_ShotEnd_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ammoEmpty(TEXT("SoundCue'/Game/Sounds/Weapon_AssaultRifle/Mono/AssaultRifle_Empty_Cue.AssaultRifle_Empty_Cue'"));

	GetMesh()->SetSkeletalMesh(rifle.Object);
	SetMuzzleFX(muzzleFX.Object);
	SetFireSound(fireSound.Object, fireEndSound.Object);
	SetAmmoEmptySound(ammoEmpty.Object);
	TrailFX = trailFX.Object;
	TrailFX_Playing = NULL;

	SetWeaponType(EWeaponType::RIFLE);
	SetLoopFireWeapon(true);
	CurrentSpread = SPREAD_DEFAULT;
}

void AFPS_WeaponRifle::SetAiming(bool isAiming)
{
	Super::SetAiming(isAiming);
	InitCurrentSpread();
}

void AFPS_WeaponRifle::StartFire(const UCameraComponent* ViewCamera)
{
	ActivateMuzzleFX();
	PlayFireSound();
	InitCurrentSpread();
	if (TrailFX != NULL)
	{
		FTimerDelegate Del = FTimerDelegate::CreateUObject(this, &AFPS_WeaponRifle::PrintTrailFX, ViewCamera);
		GetWorldTimerManager().SetTimer(TimerHandle, Del, 0.1f, true, 0.0f);
	}
}

void AFPS_WeaponRifle::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	DeactivateMuzzleFX();
	StopFireSound();
	InitCurrentSpread();
}

void AFPS_WeaponRifle::PrintTrailFX(const UCameraComponent* ViewCamera)
{
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float ConeHalfAngle = FMath::DegreesToRadians(CurrentSpread * 0.5f);

	FVector Start = ViewCamera->GetComponentLocation();
	FVector Direcion = WeaponRandomStream.VRandCone(ViewCamera->GetComponentRotation().Vector(), ConeHalfAngle, ConeHalfAngle);
	FVector End = Start + Direcion * GetAttackDistance();
	SetWeaponFireHitResult(Start, End);

	if (!GetIsAiming())
	{
		if (CurrentSpread < SPREAD_MAX)
			CurrentSpread += SPREAD_INCREMENT;
	}

	TrailFX_Playing = UGameplayStatics::SpawnEmitterAtLocation(this, TrailFX, GetMesh()->GetSocketLocation(GetMuzzleFlashSocketName()));
	TrailFX_Playing->SetVectorParameter(TEXT("ShockBeamEnd"), GetHitResult().ImpactPoint);

	PrintBulletHitFX();
	DecreaseChargedAmmo();
}

void AFPS_WeaponRifle::PrintBulletHitFX()
{
	if (GetHitResult().Actor != nullptr)
	{
		FTransform const SpawnTransform(GetHitResult().ImpactNormal.Rotation(), GetHitResult().ImpactPoint);
		FPS_WeaponEffectManager* EffectList = FPS_WeaponEffectManager::GetInstance();
		EffectList->CreateRifleImpactEffect(GetHitResult());
	}
}
