// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "FPS_Character.h"
#include "FPS_CharacterController.generated.h"
/**
 * 
 */
UCLASS()
class FPS_TEST_API AFPS_CharacterController : public APlayerController
{
	GENERATED_BODY()
private:
	AFPS_Character* Character;
	class FFPS_WeaponList* WeaponList;
	TSubclassOf<UCameraShake> CamShake_RifleFire;
	TSubclassOf<UCameraShake> CamShake_LauncherFire;
	UForceFeedbackEffect* FireForceFeedback;

	FTimerHandle JumpTH;
	FTimerHandle AimingTH;
	FVector CapsuleHalfHeight;
	FVector MoveVector;
	FVector2D MouseXY;

	const float GRAVITY = 10.f;
	const float JUMP_FORCE = 100.f;
	const float CAMERA_DEFAULT_FOV = 90.f;
	const float CAMERA_AIMING_FOV = 60.f;

	float CurrentJumpForce;
	float CurrentCameraFOV;
	float WeaponEquipTime;
	bool IsLand;

	bool PossibleJump;
	bool PossibleMove;
public:
	AFPS_CharacterController();
protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
private:
	void InitWeaponList();
	//BindFuction
	void MouseMove_X(float x);
	void MouveMove_Y(float y);
	void ForwardMoveKeyDown(float forward);
	void RightMoveKeyDown(float right);
	void JumpKeyDown();
	void FireButtonPress();
	void FireButtonRelease();
	void AimingButtonPress();
	void AimingButtonRelease();

	//Action
	void CharacterRotate();
	void CharacterMovement();
	void EquipWeapon_Rifle();
	void EquipWeapon_Launcher();
	void CheckGround();
	void SetCameraFOV(float targetFOV);

	//Possible Action & Movement
	bool IsPossibleMove();
	bool IsPossibleJump();
	bool IsPossibleEquipWeapon(EWeaponType type);
	bool IsPossibleFire();

public:
	//Notify
	void EndJump();
	void PlayCameraShakeWeaponFire(EWeaponType weaponType);
	//Getter
	float GetCurrentEquipWeaponSpread() { return Character->GetCurrentWeaponSpread(); }
	float GetWeaponEquipTime() { return WeaponEquipTime; }
};
