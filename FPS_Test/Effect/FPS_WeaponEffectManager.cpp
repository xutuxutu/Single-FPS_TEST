// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponEffectManager.h"

FPS_WeaponEffectManager* FPS_WeaponEffectManager::Instance;

FPS_WeaponEffectManager::FPS_WeaponEffectManager()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> impactFX_Rifle(TEXT("ParticleSystem'/Game/Effects/ParticleSystems/Weapons/AssaultRifle/Impacts/P_AssaultRifle_IH.P_AssaultRifle_IH'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> impactFX_Launcher(TEXT("ParticleSystem'/Game/Effects/ParticleSystems/Weapons/RocketLauncher/Impact/P_Launcher_IH.P_Launcher_IH'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> impactSound_Rifle(TEXT("SoundCue'/Game/Sounds/Weapon_AssaultRifle/Mono/AssaultRifle_ImpactConcrete_Cue.AssaultRifle_ImpactConcrete_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> impactSound_Launcher(TEXT("SoundCue'/Game/Sounds/Weapon_GrenadeLauncher/Mono/GrenadeLauncher_Explosion_Cue.GrenadeLauncher_Explosion_Cue'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> impactDecalMat_Rifle(TEXT("Material'/Game/Effects/Materials/Weapon/M_Impact_Decal.M_Impact_Decal'"));

	ImpactFX_Rifle = impactFX_Rifle.Object;
	ImpactFX_Launcher = impactFX_Launcher.Object;
	ImpactSound_Rifle = impactSound_Rifle.Object;
	ImpactSound_Launcher = impactSound_Launcher.Object;
	ImpactDecalMaterial_Rifle.DecalMaterial = impactDecalMat_Rifle.Object;
}

FPS_WeaponEffectManager::~FPS_WeaponEffectManager()
{
}

void FPS_WeaponEffectManager::CreateRifleImpactEffect(const FHitResult& hitResult)
{
	ImpactEffect->SetProperty(hitResult, GetImpactEffect(EWeaponType::RIFLE), GetImpactSound(EWeaponType::RIFLE), GetImpactDecalMaterial(EWeaponType::RIFLE));
}

void FPS_WeaponEffectManager::CreateInstance()
{
	if (Instance == NULL)
		Instance = new FPS_WeaponEffectManager();
}

UParticleSystem* FPS_WeaponEffectManager::GetImpactEffect(EWeaponType weaponType)
{
	switch (weaponType)
	{
		case EWeaponType::RIFLE :		return ImpactFX_Rifle;
		case EWeaponType::LAUNCHER :	return ImpactFX_Launcher;
	}
	return nullptr;
}

USoundCue* FPS_WeaponEffectManager::GetImpactSound(EWeaponType weaponType)
{
	switch (weaponType)
	{
		case EWeaponType::RIFLE :		return ImpactSound_Rifle;
		case EWeaponType::LAUNCHER :	return ImpactSound_Launcher;
	}
	return nullptr;
}

FDecalData* FPS_WeaponEffectManager::GetImpactDecalMaterial(EWeaponType weaponType)
{
	switch (weaponType)
	{
		case EWeaponType::RIFLE :		return &ImpactDecalMaterial_Rifle;
	}
	return nullptr;
}
