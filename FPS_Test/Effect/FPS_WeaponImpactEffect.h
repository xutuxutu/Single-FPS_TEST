// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon/FPS_WeaponType.h"
#include "FPS_WeaponImpactEffect.generated.h"


UCLASS()
class FPS_TEST_API AFPS_WeaponImpactEffect : public AActor
{
	GENERATED_BODY()

public:	
	AFPS_WeaponImpactEffect();
	void SetProperty(const FHitResult& hitResult, UParticleSystem* impactFX, USoundCue* impactSound, FDecalData* decalData);
};
