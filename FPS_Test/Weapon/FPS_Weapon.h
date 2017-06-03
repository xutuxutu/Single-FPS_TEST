// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_WeaponType.h"
#include "FPS_Weapon.generated.h"

UCLASS()
class FPS_TEST_API AFPS_Weapon : public AActor
{
	GENERATED_BODY()
private :
	UPROPERTY()
	USkeletalMeshComponent* Mesh;
	UPROPERTY()
	UParticleSystem* MuzzleFX;
	UPROPERTY()
	UParticleSystemComponent* MuzzleFX_Playing;
	UPROPERTY()
	USoundCue* FireSound;
	UPROPERTY()
	USoundCue* FireEndSound;
	UPROPERTY()
	UAudioComponent* FireSound_Playing;

	FHitResult HitResult;
	FName MuzzleFlashPosition;
	EWeaponType WeaponType;
	bool IsFire;
	bool IsAiming;
	float AttackDistance;
	int ChargedAmmo;
	int MaxChargeAmmo;
public:	
	// Sets default values for this actor's properties
	AFPS_Weapon();
protected:
	USkeletalMeshComponent* GetMesh() { return Mesh; }
	const FName& GetMuzzleFlashSocketName() { return MuzzleFlashPosition; }
	const float& GetAttackDistance() { return AttackDistance; }
	const bool& GetIsFire() { return IsFire; }
	const FHitResult& GetHitResult() { return HitResult; }

	void SetFireSound(USoundCue* fireSound, USoundCue* fireEndSound) { FireSound = fireSound; FireEndSound = fireEndSound; }
	void SetIsFire(bool isFire) { IsFire = isFire; }
	void SetWeaponType(EWeaponType weaponType) { WeaponType = weaponType; }
	void SetMuzzleFX(UParticleSystem* muzzleFX) { MuzzleFX = muzzleFX; }
	void SetWeaponFireHitResult(FVector Start, FVector End);

	void ActivateMuzzleFX();
	void DeactivateMuzzleFX();

	UAudioComponent* PlayWeaponSound(USoundCue* sound);
	void PlayFireSound() { FireSound_Playing = PlayWeaponSound(FireSound); }
	void StopFireSound();
public:		
	void InitProperty(float attackDistance, int maxChargeAmmo, int chargedAmmo);
	void IncreaseAmmoQuantity(int ammo) { ChargedAmmo += ammo; }
	virtual void StartFire(const UCameraComponent* ViewCamera) { }
	virtual bool EndFire() { return false; }
	//Setter
	void SetActive(bool isActive);
	virtual void SetAiming(bool isAiming) { IsAiming = isAiming; }
	//Getter
	const EWeaponType& GetWeaponType() { return WeaponType; }
	int GetChargedAmmoQuantity() { return ChargedAmmo; }
	bool GetIsAiming() { return IsAiming; }
};
