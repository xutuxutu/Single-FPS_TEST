// Fill out your copyright notice in the Description page of Project Settings
#pragma once
#include "Engine.h"
#include "Weapon/FPS_WeaponType.h"
#include "Weapon/FPS_WeaponProjectile_Launcher.h"
#include "FPS_WeaponImpactEffect.h"
/**
 * 
 */
class FPS_TEST_API FPS_WeaponEffectManager
{
	static FPS_WeaponEffectManager* Instance;
	UPROPERTY()
	UParticleSystem* ImpactFX_Rifle;
	UPROPERTY()
	USoundCue* ImpactSound_Rifle;
	FDecalData ImpactDecalMaterial_Rifle;

	UPROPERTY()
	UParticleSystem* ImpactFX_Launcher;
	UPROPERTY()
	USoundCue* ImpactSound_Launcher;
	FDecalData ImpactDecalMaterial_Launcher;

	AFPS_WeaponImpactEffect* ImpactEffect;
	AFPS_WeaponProjectile_Launcher* Projectile_Launcher[20];
private :
	FPS_WeaponEffectManager();
	~FPS_WeaponEffectManager();
	//Get Reference
	UParticleSystem* GetImpactEffect(EWeaponType weaponType);
	USoundCue* GetImpactSound(EWeaponType weaponType);
	FDecalData* GetImpactDecalMaterial(EWeaponType weaponType);
	//Spawn Actors
	void SpawnImpactEffectActor();
	void SetLauncherProjectile();
public:
	//Static Function
	static void CreateInstance();
	static FPS_WeaponEffectManager* GetInstance() { return Instance; }
	//Spawn Actors
	void SpawnEffectActors();
	//Create Effect
	void FireLauncherProjectile(FVector location, FRotator direction, float maxDistance);
	void CreateRifleImpactEffect(const FHitResult& hitResult);
	void CreateLauncherProjectileImpactEffect(const FHitResult& hitResult);
};
