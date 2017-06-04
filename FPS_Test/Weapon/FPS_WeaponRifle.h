// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_Weapon.h"
#include "FPS_WeaponRifle.generated.h"

UCLASS()
class FPS_TEST_API AFPS_WeaponRifle : public AFPS_Weapon
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UParticleSystem* TrailFX;
	UParticleSystemComponent* TrailFX_Playing;

	FTimerHandle TimerHandle;
	const float SPREAD_DEFAULT = 5.0f;
	const float SPREAD_AIMING = 1.0f;
	const float SPREAD_MAX = 10.0f;
	const float SPREAD_INCREMENT = 2.0f;

	float CurrentSpread;
public:	
	// Sets default values for this actor's properties
	AFPS_WeaponRifle();
protected:
	void PrintTrailFX(const UCameraComponent* ViewCamera);
	void PrintBulletHitFX();
public:	
	virtual void StartFire(const UCameraComponent* ViewCamera) override;
	virtual void EndFire() override;
	virtual void SetAiming(bool isAiming) override;
	void InitCurrentSpread() { GetIsAiming() ? CurrentSpread = SPREAD_AIMING : CurrentSpread = SPREAD_DEFAULT; }

	const float& GetCurrentSpread() { return CurrentSpread; }
};
