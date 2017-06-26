// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include "FPS_WeaponProjectile.generated.h"

using std::vector;

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
	USphereComponent* SphereTrigger;
	UPROPERTY()
	UParticleSystem* ProjectileParticle;
	UPROPERTY()
	UParticleSystemComponent* ProjectileParticle_Playing;
	UPROPERTY()
	UProjectileMovementComponent* MovementComponent;
	UPROPERTY()
	UAudioComponent* ProjectileSound;

	vector<AActor*> OnTriggerActor;
protected:
	virtual void PostInitializeComponents() override;
	void SetProjectileParticle(UParticleSystem* particle);
	void CheckMoveDistance();
public:	
	// Sets default values for this actor's properties
	AFPS_WeaponProjectile();
	void StartFire(FVector location, FRotator rotation, float maxDistance);
	void DamageToActors(FVector hitPoint);
	void ActivateActor();
	void DeactivateActor();

	//Delegate Bind Function
	UFUNCTION()
	void OnImpact(const FHitResult& HitResult);
	UFUNCTION()
	void OnBeginOverlapSphereTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlapSphereTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//Getter
	bool GetIsActive() { return IsActive; }
};
