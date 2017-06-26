// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "FPS_Character.h"
#include "FPS_CharacterController.generated.h"
/**
 * 
 */
UCLASS(config=Game)
class FPS_TEST_API AFPS_CharacterController : public APlayerController
{
	GENERATED_BODY()
private:
	AFPS_Character* Character;
	class FFPS_WeaponList* WeaponList;

	UPROPERTY()
	TSubclassOf<UCameraShake> CamShake_RifleFire;

	UPROPERTY(config)
	FStringClassReference CamShakeRifleClass;


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
	bool AimingWeapon;
	bool IsRun;

	bool PossibleFire;
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
	void RunButtonPress();
	void RunButtonRelease();

	//Action
	void CharacterRotate();
	void CharacterMovement();
	void EquipWeapon_Rifle();
	void EquipWeapon_Launcher();
	void CheckGround();
	void SetCameraFOV(float targetFOV);
	void ReloadAmmo();
	void AutoReloadAmmo();

	//Possible Action & Movement
	bool IsPossibleMove();
	bool IsPossibleJump();
	bool IsPossibleEquipWeapon(EWeaponType type);
	bool IsPossibleReload();
	bool IsPossibleFire();
	bool IsPossibleAiming();
	bool IsPossibleRun();

public:
	//Notify
	void EndJump();
	void SetOnceFireEnd();
	void PlayCameraShakeWeaponFire(EWeaponType weaponType);
	//Getter
	float GetCurrentEquipWeaponSpread() { return Character->GetCurrentWeaponSpread(); }
	float GetWeaponEquipTime() { return WeaponEquipTime; }
};
