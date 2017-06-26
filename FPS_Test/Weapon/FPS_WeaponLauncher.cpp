// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponLauncher.h"
#include "Effect/FPS_WeaponEffectManager.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFPS_WeaponLauncher::AFPS_WeaponLauncher() : AFPS_Weapon()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> launcher(TEXT("SkeletalMesh'/Game/Weapons/Launcher.Launcher'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> muzzleFX(TEXT("ParticleSystem'/Game/Effects/ParticleSystems/Weapons/RocketLauncher/Muzzle/P_Launcher_MF.P_Launcher_MF'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> fireSound(TEXT("SoundCue'/Game/Sounds/Weapon_GrenadeLauncher/Mono/GrenadeLauncher_Shot_Cue.GrenadeLauncher_Shot_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ammoEmpty(TEXT("SoundCue'/Game/Sounds/Weapon_AssaultRifle/Mono/AssaultRifle_Empty_Cue.AssaultRifle_Empty_Cue'"));

	GetMesh()->SetSkeletalMesh(launcher.Object);
	SetMuzzleFX(muzzleFX.Object);
	SetFireSound(fireSound.Object, NULL);
	SetAmmoEmptySound(ammoEmpty.Object);
	SetWeaponType(EWeaponType::LAUNCHER);
	SetLoopFireWeapon(false);
}

void AFPS_WeaponLauncher::StartFire(const UCameraComponent* ViewCamera)
{
	ActivateMuzzleFX();
	PlayFireSound();
	DecreaseChargedAmmo();

	FVector Start = ViewCamera->GetComponentLocation();
	FVector Dir = ViewCamera->GetComponentRotation().Vector();
	FVector End = Start + Dir * GetAttackDistance();
	SetWeaponFireHitResult(Start, End);

	FVector FirePoint = GetMesh()->GetSocketLocation(GetMuzzleFlashSocketName());
	FVector FireDir = GetHitResult().ImpactPoint - FirePoint;
	FireDir.Normalize();

	FPS_WeaponEffectManager::GetInstance()->FireLauncherProjectile(FirePoint, FireDir.Rotation(), GetAttackDistance());
}

