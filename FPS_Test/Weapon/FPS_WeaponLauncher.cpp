// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponLauncher.h"


// Sets default values
AFPS_WeaponLauncher::AFPS_WeaponLauncher() : AFPS_Weapon()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> launcher(TEXT("SkeletalMesh'/Game/Weapons/Launcher.Launcher'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> muzzleFX(TEXT("ParticleSystem'/Game/Effects/ParticleSystems/Weapons/RocketLauncher/Muzzle/P_Launcher_MF.P_Launcher_MF'"));

	GetMesh()->SetSkeletalMesh(launcher.Object);
	SetMuzzleFX(muzzleFX.Object);
	SetWeaponType(EWeaponType::LAUNCHER);
}

