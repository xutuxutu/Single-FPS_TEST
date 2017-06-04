// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponProjectile_Launcher.h"

AFPS_WeaponProjectile_Launcher::AFPS_WeaponProjectile_Launcher()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> projectileParticle(TEXT("ParticleSystem'/Game/Effects/ParticleSystems/Weapons/RocketLauncher/Muzzle/P_Launcher_proj.P_Launcher_proj'"));

	SetProjectileParticle(projectileParticle.Object);
}
