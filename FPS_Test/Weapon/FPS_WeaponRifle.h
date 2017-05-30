// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_Weapon.h"
#include "FPS_WeaponImpactEffect_Rifle.h"
#include "FPS_WeaponRifle.generated.h"

UCLASS()
class FPS_TEST_API AFPS_WeaponRifle : public AFPS_Weapon
{
	GENERATED_BODY()
	
private:
	UParticleSystem* TrailFX;
	UParticleSystemComponent* TrailFX_Playing;

	FTimerHandle TimerHandle;
public:	
	// Sets default values for this actor's properties
	AFPS_WeaponRifle();
protected:
	void PrintTrailFX(const UCameraComponent* ViewCamera);
	void PrintBulletHitFX();
public:	
	virtual void StartFire(const UCameraComponent* ViewCamera) override;
	virtual void EndFire() override;
};
