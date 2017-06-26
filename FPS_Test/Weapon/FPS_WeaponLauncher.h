// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_Weapon.h"
#include "FPS_WeaponLauncher.generated.h"

UCLASS()
class FPS_TEST_API AFPS_WeaponLauncher : public AFPS_Weapon
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AFPS_WeaponLauncher();
protected:
public:	
	virtual void StartFire(const UCameraComponent* ViewCamera) override;
};
