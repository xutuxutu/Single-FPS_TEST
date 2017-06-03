// Fill out your copyright notice in the Description page of Project Settings
#pragma once
#include "Engine.h"
#include "Weapon/FPS_WeaponType.h"
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
	UParticleSystem* ImpactFX_Launcher;
	UPROPERTY()
	USoundCue* ImpactSound_Rifle;
	UPROPERTY()
	USoundCue* ImpactSound_Launcher;

	FDecalData ImpactDecalMaterial_Rifle;

	AFPS_WeaponImpactEffect* ImpactEffect;
private :
	FPS_WeaponEffectManager();
	~FPS_WeaponEffectManager();

	UParticleSystem* GetImpactEffect(EWeaponType weaponType);
	USoundCue* GetImpactSound(EWeaponType weaponType);
	FDecalData* GetImpactDecalMaterial(EWeaponType weaponType);
public:
	static void CreateInstance();
	static FPS_WeaponEffectManager* GetInstance() { return Instance; }
	void SetImpactEffect(AFPS_WeaponImpactEffect* impactEffect) { ImpactEffect = impactEffect; }

	void CreateRifleImpactEffect(const FHitResult& hitResult);
};
