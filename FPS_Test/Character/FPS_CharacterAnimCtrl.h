// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "Weapon/FPS_Weapon.h"
#include "FPS_CharacterAnimCtrl.generated.h"
/**
 * 
 */
UENUM()
enum class ECharacterMovementState : uint8
{
	IDLE,
	MOVE,
	JUMP,
	RUN,
};

UENUM()
enum class ECharacterActionState : uint8
{
	PEACE,
	EQUIP,
	RELOAD,
	FIRE,
};

UCLASS()
class FPS_TEST_API UFPS_CharacterAnimCtrl : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	int WeaponSlotNum;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CharacterState", Meta = (AllowPrivateAccess = "true"))
	ECharacterMovementState MovementState;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CharacterState", Meta = (AllowPrivateAccess = "true"))
	ECharacterActionState ActionState;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Jump", Meta = (AllowPrivateAccess = "true"))
	bool IsLand;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CharacterState", Meta = (AllowPrivateAccess = "true"))
	bool IsAiming;

	UAnimMontage* CurrentPlayMontage;
	//Montage_Rifle
	UPROPERTY()
	UAnimMontage* RifleEquipAnim;
	UPROPERTY()
	UAnimMontage* RifleReloadAnim;
	UPROPERTY()
	UAnimMontage* RifleFireAnim;
	UPROPERTY()
	UAnimMontage* RifleAimingFireAnim;
	//Montage_Launcher
	UPROPERTY()
	UAnimMontage* LauncherEquipAnim;
	UPROPERTY()
	UAnimMontage* LauncherReloadAnim;
	UPROPERTY()
	UAnimMontage* LauncherFireAnim;
	UPROPERTY()
	UAnimMontage* LauncherAimingFireAnim;

	//Notify Target
	class AFPS_CharacterController* CharacterController;
private :
	void StopCurrentPlayMontage() { if (CurrentPlayMontage != NULL) Montage_Stop(0.1f, CurrentPlayMontage); }
	void PlayMontageAnim(UAnimMontage* anim);
public :
	UFPS_CharacterAnimCtrl();
	void InitNotifyTarget(); 
	//Montage
	void PlayWeaponEquipAnim(EWeaponType& weaponType);
	void PlayWeaponReloadAnim(EWeaponType& weaponType);
	void PlayFireAnim(EWeaponType& weaponType);
	void PlayAimingFireAnim(EWeaponType& weaponType);
	void StopFireAnim(EWeaponType& weaponType);
	//AnimNotify
	UFUNCTION()
	void AnimNotify_ActionEnd(UAnimNotify* notify);
	UFUNCTION()
	void AnimNotify_FireEnd(UAnimNotify* notify);
	//Setter
	void SetIsLand(bool isLand) { IsLand = isLand; }
	void SetAiming(bool isAiming) { IsAiming = isAiming; }
	void SetWeaponSlotNum(int slotNum) { WeaponSlotNum = slotNum; }
	void SetCharacterMovementState(ECharacterMovementState state) { MovementState = state; }
	void SetCharacterActionState(ECharacterActionState state) { ActionState = state; }
	//Getter
	const bool& GetIsAiming() { return IsAiming; }
	const ECharacterMovementState& GetCharacterMovementState() { return MovementState; }
	const ECharacterActionState& GetCharacterActionState() { return ActionState; }
};
