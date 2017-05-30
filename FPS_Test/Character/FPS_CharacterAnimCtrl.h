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
	bool PlayingStartJump;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Jump", Meta = (AllowPrivateAccess = "true"))
	bool PlayingEndJump;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Jump", Meta = (AllowPrivateAccess = "true"))
	bool IsLand;

	UAnimMontage* CurrentPlayMontage;
	//Montage_Rifle
	UAnimMontage* RifleEquipAnim;
	UAnimMontage* RifleFireAnim;
	//Montage_Launcher
	UAnimMontage* LauncherEquipAnim;
	UAnimMontage* LauncherFireAnim;
private :
	void StopCurrentPlayMontage() { if (CurrentPlayMontage != NULL) Montage_Stop(0.1f, CurrentPlayMontage); }
	void PlayMontageAnim(UAnimMontage* anim);
public :
	UFPS_CharacterAnimCtrl();
	//Montage
	void PlayWeaponEquipAnim(EWeaponType& weaponType);
	void PlayFireAnim(EWeaponType& weaponType);
	void StopFireAnim(EWeaponType& weaponType);
	//AnimNotify
	UFUNCTION()
	void AnimNotify_ActionEnd(UAnimNotify* notify);
	UFUNCTION()
	void AnimNotify_JumpEnd(UAnimNotify* notify);
	//Setter
	void SetJumpStart(bool jumpStart) { PlayingStartJump = jumpStart; }
	void SetJumpEnd(bool jumpEnd) { PlayingEndJump = jumpEnd; }
	void SetIsLand(bool isLand) { IsLand = isLand; }
	void SetWeaponSlotNum(int slotNum) { WeaponSlotNum = slotNum; }
	void SetCharacterMovementState(ECharacterMovementState state) { MovementState = state; }
	void SetCharacterActionState(ECharacterActionState state) { ActionState = state; }
	//Getter
	const ECharacterMovementState& GetCharacterMovementState() { return MovementState; }
	const ECharacterActionState& GetCharacterActionState() { return ActionState; }
};
