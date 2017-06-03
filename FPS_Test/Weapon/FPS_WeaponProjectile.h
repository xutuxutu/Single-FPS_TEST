// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_WeaponProjectile.generated.h"

UCLASS()
class FPS_TEST_API AFPS_WeaponProjectile : public AActor
{
	GENERATED_BODY()
private:
	float FireSpeed;
	UPROPERTY()
	USphereComponent* SphereCollider;
	UPROPERTY()
	UParticleSystemComponent* ProjectileParticle;
	UPROPERTY()
	UProjectileMovementComponent* MovementComponent;
public:	
	// Sets default values for this actor's properties
	AFPS_WeaponProjectile();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
};
