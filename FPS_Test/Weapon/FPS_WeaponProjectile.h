// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_WeaponProjectile.generated.h"

UCLASS()
class FPS_TEST_API AFPS_WeaponProjectile : public AActor
{
	GENERATED_BODY()
private:
	FTimerHandle CheckMoveDistTH;
	FVector FireStartLocation;
	float MaxDistance;
	const float FireSpeed = 2000;
	bool IsActive;
	UPROPERTY()
	USphereComponent* SphereCollider;
	UPROPERTY()
	UParticleSystem* ProjectileParticle;
	UPROPERTY()
	UParticleSystemComponent* ProjectileParticle_Playing;
	UPROPERTY()
	UProjectileMovementComponent* MovementComponent;
	UPROPERTY()
	UAudioComponent* ProjectileSound;
protected:
	virtual void PostInitializeComponents() override;
	void SetProjectileParticle(UParticleSystem* particle);
	void CheckMoveDistance();
public:	
	// Sets default values for this actor's properties
	AFPS_WeaponProjectile();
	void StartFire(FVector location, FRotator rotation, float maxDistance);
	void ActivateActor();
	void DeactivateActor();

	UFUNCTION()
	void OnImpact(const FHitResult& HitResult);

	bool GetIsActive() { return IsActive; }
};
