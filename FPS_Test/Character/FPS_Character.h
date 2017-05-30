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
	UStaticMeshComponent* RotPibot;
	USpringArmComponent* SpringArm;
	UCameraComponent* Camera;
	//Member Class
	class AFPS_Weapon* CurrentEquipWeapon;
	EWeaponType CurrentEquipWeaponType;
	class UFPS_CharacterAnimCtrl* AnimCtrl;
	//SocketName
	FName WeaponAttachPoint;
	//Animation
	void SetEquipAnim();
	//Property
	int ReserveAmmo;
	float MOVE_SPEED;
	float CameraRotSpeed;
public:
	// Sets default values for this character's properties
	AFPS_Character();
	void InitProperty();
	void EquipWeapon(class AFPS_Weapon* weapon);
	void SetPitchInput(float pitch);

	//Animation
	void SetIdleAnim() { AnimCtrl->SetCharacterMovementState(ECharacterMovementState::IDLE); }
	void SetMoveAnim() { AnimCtrl->SetCharacterMovementState(ECharacterMovementState::MOVE); }
	void SetJumpAnim();
	void SetLandAnim();
	void StartFire();
	void EndFire();

	void Debug();

	//Getter
	const float& GetMoveSpeed() { return MOVE_SPEED; }
	const float& GetCameraRotSpeed() { return CameraRotSpeed; }
	const USpringArmComponent* GetSpringArmCompnent() { return SpringArm; }
	const UCameraComponent* GetCameraCompnent() { return Camera; }
	const EWeaponType& GetCurrentEquipWeaponType() { return CurrentEquipWeaponType; }
	const ECharacterActionState& GetCharacterActionState() { return AnimCtrl->GetCharacterActionState(); }
	const ECharacterMovementState& GetCharacterMovementState() { return AnimCtrl->GetCharacterMovementState(); }
};
