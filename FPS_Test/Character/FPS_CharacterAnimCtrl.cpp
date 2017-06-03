// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_CharacterAnimCtrl.h"
#include "FPS_CharacterController.h"

UFPS_CharacterAnimCtrl::UFPS_CharacterAnimCtrl()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> rifleEquip(TEXT("AnimMontage'/Game/Blueprint/Character/BP_FPS_Character_RifleEquip_Montage.BP_FPS_Character_RifleEquip_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> rifleFire(TEXT("AnimMontage'/Game/Blueprint/Character/BP_FPS_CharacterRifleFire.BP_FPS_CharacterRifleFire'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> rifleAimingFire(TEXT("AnimMontage'/Game/Blueprint/Character/BP_FPS_CharacterRifleAimingFire.BP_FPS_CharacterRifleAimingFire'"));
	RifleEquipAnim = rifleEquip.Object;
	RifleFireAnim = rifleFire.Object;
	RifleAimingFireAnim = rifleAimingFire.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> launcherEquip(TEXT("AnimMontage'/Game/Blueprint/Character/BP_FPS_CharacterLauncherEquip_Montage.BP_FPS_CharacterLauncherEquip_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> launcherFire(TEXT("AnimMontage'/Game/Blueprint/Character/BP_FPS_CharacterLauncherFire.BP_FPS_CharacterLauncherFire'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> launcherAimingFire(TEXT("AnimMontage'/Game/Blueprint/Character/BP_FPS_CharacterLauncherAimingFire.BP_FPS_CharacterLauncherAimingFire'"));
	LauncherEquipAnim = launcherEquip.Object;
	LauncherFireAnim = launcherFire.Object;
	LauncherAimingFireAnim = launcherAimingFire.Object;

	WeaponSlotNum = 0;
	MovementState = ECharacterMovementState::IDLE;
	ActionState = ECharacterActionState::PEACE;

	PlayingStartJump = false;
	PlayingEndJump = false;
	IsLand = true;
	CurrentPlayMontage = NULL;
}
void UFPS_CharacterAnimCtrl::PlayMontageAnim(UAnimMontage* anim)
{
	StopCurrentPlayMontage();
	CurrentPlayMontage = anim;
	Montage_Play(anim);
}

void UFPS_CharacterAnimCtrl::PlayWeaponEquipAnim(EWeaponType& weaponType)
{
	switch (weaponType)
	{
	case EWeaponType::RIFLE :
		PlayMontageAnim(RifleEquipAnim);
		break;
	case EWeaponType::LAUNCHER :
		PlayMontageAnim(LauncherEquipAnim);
		break;
	}
}
void UFPS_CharacterAnimCtrl::PlayFireAnim(EWeaponType& weaponType)
{
	switch (weaponType)
	{
	case EWeaponType::RIFLE :
		PlayMontageAnim(RifleFireAnim);
		break;
	case EWeaponType::LAUNCHER :
		PlayMontageAnim(LauncherFireAnim);
		break;
	}
}

void UFPS_CharacterAnimCtrl::PlayAimingFireAnim(EWeaponType& weaponType)
{
	switch (weaponType)
	{
	case EWeaponType::RIFLE:
		PlayMontageAnim(RifleAimingFireAnim);
		break;
	case EWeaponType::LAUNCHER:
		PlayMontageAnim(LauncherAimingFireAnim);
		break;
	}
}

void UFPS_CharacterAnimCtrl::StopFireAnim(EWeaponType& weaponType)
{
	StopCurrentPlayMontage();
}

void UFPS_CharacterAnimCtrl::AnimNotify_ActionEnd(UAnimNotify* notify)
{
	switch (ActionState)
	{
	case ECharacterActionState::EQUIP :
		ActionState = ECharacterActionState::PEACE;
		break;
	}
}

void UFPS_CharacterAnimCtrl::AnimNotify_JumpEnd(UAnimNotify* notify)
{
	if (PlayingStartJump)
		PlayingStartJump = false;
	else if (PlayingEndJump)
	{
		PlayingEndJump = false;
		Cast<AFPS_CharacterController>(GetWorld()->GetFirstPlayerController())->EndJump();
	}
}
