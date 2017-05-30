// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPS_Weapon.generated.h"

UENUM()
enum class EWeaponType : uint8
{
	NONE,
	RIFLE,
	LAUNCHER,
};

UCLASS()
class FPS_TEST_API AFPS_Weapon : public AActor
{
	GENERATED_BODY()
private :
	USkeletalMeshComponent* Mesh;
	UParticleSystem* MuzzleFX;
	UParticleSystemComponent* MuzzleFX_Playing;
	USoundCue* FireSound;
	USoundCue* FireEndSound;
	UAudioComponent* FireSound_Playing;

	FName MuzzleFlashPosition;
	EWeaponType WeaponType;
	bool IsFire;
	float AttackDistance;
	FHitResult HitResult;
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
	void SetWeaponFireHitResult(const UCameraComponent* ViewCamera);

	void ActivateMuzzleFX();
	void DeactivateMuzzleFX();

	UAudioComponent* PlayWeaponSound(USoundCue* sound);
	void PlayFireSound() { FireSound_Playing = PlayWeaponSound(FireSound); }
	void StopFireSound();
public:		
	void InitProperty(float attackDistance, int maxChargeAmmo, int chargedAmmo);
	void IncreaseAmmoQuantity(int ammo) { ChargedAmmo += ammo; }

	void SetActive(bool isActive);
	virtual void StartFire(const UCameraComponent* ViewCamera) { }
	virtual void EndFire() { }
	const EWeaponType& GetWeaponType() { return WeaponType; }
	int GetChargedAmmoQuantity() { return ChargedAmmo; }
};
