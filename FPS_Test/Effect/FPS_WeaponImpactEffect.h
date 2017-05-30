// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_WeaponImpactEffect.generated.h"

struct FDecalData
{
	UMaterial* DecalMaterial;
	float DecalSize = 256.0f;
	float LifeTime = 10.0f;
};

UCLASS()
class FPS_TEST_API AFPS_WeaponImpactEffect : public AActor
{
	GENERATED_BODY()

private :
	UParticleSystem* ImpactFX;
	USoundCue* ImpactSound;
	FDecalData ImpactDecal;
protected:
	void SetImpactFX(UParticleSystem* impactFX) { ImpactFX = impactFX; }
	void SetImpactSoundCue(USoundCue* impactSound) { ImpactSound = impactSound; }
	void SetImpactDecalMetarial(UMaterial* impactDecal) { ImpactDecal.DecalMaterial = impactDecal; }
public:	
	AFPS_WeaponImpactEffect();
};
