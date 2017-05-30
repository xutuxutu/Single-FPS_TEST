// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponRifle.h"


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

	GetMesh()->SetSkeletalMesh(rifle.Object);
	SetMuzzleFX(muzzleFX.Object);
	SetFireSound(fireSound.Object, fireEndSound.Object);
	TrailFX = trailFX.Object;
	TrailFX_Playing = NULL;
	SetWeaponType(EWeaponType::RIFLE);
}

void AFPS_WeaponRifle::StartFire(const UCameraComponent* ViewCamera)
{
	if (!GetIsFire())
	{
		SetIsFire(true);
		ActivateMuzzleFX();
		PlayFireSound();
		if (TrailFX != NULL)
		{
			FTimerDelegate Del = FTimerDelegate::CreateUObject(this, &AFPS_WeaponRifle::PrintTrailFX, ViewCamera);
			GetWorldTimerManager().SetTimer(TimerHandle, Del, 0.2f, true);
		}
	}
}

void AFPS_WeaponRifle::EndFire()
{
	if (GetIsFire())
	{
		SetIsFire(false);
		DeactivateMuzzleFX();
		StopFireSound();
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AFPS_WeaponRifle::PrintTrailFX(const UCameraComponent* ViewCamera)
{
	FVector MuzzleLoc = GetMesh()->GetSocketLocation(GetMuzzleFlashSocketName());
	SetWeaponFireHitResult(ViewCamera);

	TrailFX_Playing = UGameplayStatics::SpawnEmitterAtLocation(this, TrailFX, MuzzleLoc);
	TrailFX_Playing->SetVectorParameter(TEXT("ShockBeamEnd"), GetHitResult().ImpactPoint);

	PrintBulletHitFX();
}

void AFPS_WeaponRifle::PrintBulletHitFX()
{
	const FHitResult& hitResult = GetHitResult();

	if (hitResult.Actor != nullptr)
	{

	}
}
