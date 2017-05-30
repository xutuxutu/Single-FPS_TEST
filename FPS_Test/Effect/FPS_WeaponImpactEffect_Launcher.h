// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_WeaponImpactEffect.h"
#include "FPS_WeaponImpactEffect_Launcher.generated.h"

UCLASS()
class FPS_TEST_API AFPS_WeaponImpactEffect_Launcher : public AFPS_WeaponImpactEffect
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPS_WeaponImpactEffect_Launcher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
