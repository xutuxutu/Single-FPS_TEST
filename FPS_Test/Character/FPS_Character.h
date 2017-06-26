// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPS_CharacterAnimCtrl.h"
#include "FPS_Character.generated.h"

UCLASS()
class FPS_TEST_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()
private:
	//Component
	UPROPERTY()
	UStaticMeshComponent* RotPibot;
	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCameraComponent* Camera;
	//Member Class
	UPROPERTY()
	class AFPS_Weapon* CurrentEquipWeapon;
	EWeaponType CurrentEquipWeaponType;
	bool IsWeaponFire;
	UPROPERTY()
	class UFPS_CharacterAnimCtrl* AnimCtrl;
	//SocketName
	FName WeaponAttachPoint;
	//Property
	float MOVE_SPEED_DEFAULT;
	float MOVE_SPEED_AIMING;
	float MOVE_SPEED_RUN;
	float CameraRotSpeed;
	FTransform CAMERA_DEFAULT_TRANSFORM;
private :
	//Animation
	void SetEquipAnim();
public:
	// Sets default values for this character's properties
	AFPS_Character();
	void InitProperty();
	void EquipWeapon(class AFPS_Weapon* weapon);
	void ReloadAmmo();
	void CameraShake();

	//Animation
	void SetIdleAnim() { AnimCtrl->SetCharacterMovementState(ECharacterMovementState::IDLE); }
	void SetMoveAnim() { AnimCtrl->SetCharacterMovementState(ECharacterMovementState::MOVE); }
	void SetJumpAnim();
	void SetLandAnim();
	bool StartFire();
	void EndFire();
	void SetAiming_ZoomIn();
	void SetAiming_ZoomOut();
	void SetRunAnim() { AnimCtrl->SetCharacterMovementState(ECharacterMovementState::RUN); }

	//Getter - CharacterProperty
	const float& GetMoveSpeed();
	const float& GetCameraRotSpeed() { return CameraRotSpeed; }
	const USpringArmComponent* GetSpringArmCompnent() { return SpringArm; }
	//Getter - WeaponProperty
	const EWeaponType& GetCurrentEquipWeaponType() { return CurrentEquipWeaponType; }
	const bool& GetIsAiming() { return AnimCtrl->GetIsAiming(); }
	const float GetCurrentWeaponSpread();
	AFPS_Weapon* GetCurrentEquipWeapon() { return CurrentEquipWeapon; }
	const bool& GetIsWeaponFire() { return IsWeaponFire; }
	//Getter - AnimationProperty
	const ECharacterActionState& GetCharacterActionState() { return AnimCtrl->GetCharacterActionState(); }
	const ECharacterMovementState& GetCharacterMovementState() { return AnimCtrl->GetCharacterMovementState(); }

	//Setter
	void SetPitchInput(float pitch);
	void SetCameraFOV(float FOV) { Camera->FieldOfView = FOV; }
	void SetOnceFireWeaponFireEnd() { IsWeaponFire = false; }
	//Debug
	void Debug();
};
