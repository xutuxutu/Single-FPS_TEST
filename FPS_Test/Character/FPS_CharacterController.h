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
private :
	AFPS_Character* Character;
	class FFPS_WeaponList* WeaponList;
	TSubclassOf<UCameraShake> CamShake_RifleFire;
	TSubclassOf<UCameraShake> CamShake_LauncherFire;
	UForceFeedbackEffect* FireForceFeedback;

	FTimerHandle JumpTH;
	FVector CapsuleHalfHeight;
	FVector MoveVector;
	FVector2D MouseXY;

	const float GRAVITY = 10;
	const float JUMP_FORCE = 100;

	float CurrentJumpForce;
	bool IsLand;

	bool PossibleJump;
	bool PossibleMove;
public :
	AFPS_CharacterController();
protected :
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
private :
	void InitWeaponList();
	//BindFuction
	void MouseMove_X(float x);
	void MouveMove_Y(float y);
	void ForwardMoveKeyDown(float forward);
	void RightMoveKeyDown(float right);
	void JumpKeyDown();
	void FireButtonPress();
	void FireButtonRelease();

	//Action
	void CharacterRotate();
	void CharacterMovement();
	void EquipWeapon_Rifle();
	void EquipWeapon_Launcher();
	void CheckGround();

	//Possible Action & Movement
	bool IsPossibleMove();
	bool IsPossibleJump();
	bool IsPossibleEquipWeapon(EWeaponType type);

public :
	//Notify
	void EndJump();
	void PlayCameraShakeWeaponFire(EWeaponType weaponType);
};
