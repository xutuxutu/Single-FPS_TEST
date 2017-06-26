// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_CharacterController.h"
#include "FPS_CharacterCameraManager.h"
#include "Weapon/FPS_WeaponList.h"
#include "Effect/FPS_WeaponEffectManager.h"

AFPS_CharacterController::AFPS_CharacterController()
{
	ConstructorHelpers::FClassFinder<UCameraShake> camShack_Rifle(TEXT("/Game/Blueprint/Weapons/BP_CamShack_RifleFire.BP_CamShack_RifleFire_C"));
	CamShake_RifleFire = camShack_Rifle.Class;

	ConstructorHelpers::FObjectFinder<UBlueprint> camShack_Launcher(TEXT("Blueprint'/Game/Blueprint/Weapons/BP_CamShack_LauncherFire.BP_CamShack_LauncherFire'"));
	CamShake_LauncherFire = camShack_Launcher.Object->StaticClass();
	ConstructorHelpers::FObjectFinder<UForceFeedbackEffect> fireForceFeedBack(TEXT("ForceFeedbackEffect'/Game/Effects/ForceFeedback/FFE_Fire.FFE_Fire'"));
	FireForceFeedback = fireForceFeedBack.Object;

	WeaponList = new FFPS_WeaponList;
	PossibleFire = true;
	PossibleJump = true;
	PossibleMove = true;
	CurrentJumpForce = 0;
	CurrentCameraFOV = CAMERA_DEFAULT_FOV;
	IsLand = true;
	AimingWeapon = false;
	IsRun = false;
	//PlayerCameraManagerClass = AFPS_CharacterCameraManager::StaticClass();
	FPS_WeaponEffectManager::CreateInstance();
}

void AFPS_CharacterController::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AFPS_Character>(GetPawn());
	Character->InitProperty();
	InitWeaponList();
	EquipWeapon_Rifle();

	CapsuleHalfHeight = FVector(0, 0, Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	FPS_WeaponEffectManager::GetInstance()->SpawnEffectActors();
}

void AFPS_CharacterController::InitWeaponList()
{
	AFPS_Weapon* Rifle = GetWorld()->SpawnActor<AFPS_WeaponRifle>(AFPS_WeaponRifle::StaticClass());
	AFPS_Weapon* Launcher = GetWorld()->SpawnActor<AFPS_WeaponLauncher>(AFPS_WeaponLauncher::StaticClass());
	Rifle->InitProperty(2000, 50, 0, 100);
	Launcher->InitProperty(5000, 6, 0, 100);

	WeaponList->AddWeapon(Rifle);
	WeaponList->AddWeapon(Launcher);

	const std::vector<AFPS_Weapon*> weaponList = WeaponList->GetWeaponList();
	for (int i = 0; i < weaponList.size(); ++i)
		weaponList[i]->SetActive(false);
}

void AFPS_CharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CharacterRotate();
	CharacterMovement();
	AutoReloadAmmo();
	Character->Debug();
}

void AFPS_CharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MouseX", this, &AFPS_CharacterController::MouseMove_X);
	InputComponent->BindAxis("MouseY", this, &AFPS_CharacterController::MouveMove_Y);
	InputComponent->BindAxis("MoveForward", this, &AFPS_CharacterController::ForwardMoveKeyDown);
	InputComponent->BindAxis("MoveRight", this, &AFPS_CharacterController::RightMoveKeyDown);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPS_CharacterController::FireButtonPress);
	InputComponent->BindAction("Fire", IE_Released, this, &AFPS_CharacterController::FireButtonRelease);
	InputComponent->BindAction("WeaponSlot_Rifle", IE_Pressed, this, &AFPS_CharacterController::EquipWeapon_Rifle);
	InputComponent->BindAction("WeaponSlot_Launcher", IE_Pressed, this, &AFPS_CharacterController::EquipWeapon_Launcher);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPS_CharacterController::JumpKeyDown);
	InputComponent->BindAction("Aiming", IE_Pressed, this, &AFPS_CharacterController::AimingButtonPress);
	InputComponent->BindAction("Aiming", IE_Released, this, &AFPS_CharacterController::AimingButtonRelease);
	InputComponent->BindAction("Reload", IE_Pressed, this, &AFPS_CharacterController::ReloadAmmo);
	InputComponent->BindAction("Run", IE_Pressed, this, &AFPS_CharacterController::RunButtonPress);
	InputComponent->BindAction("Run", IE_Released, this, &AFPS_CharacterController::RunButtonRelease);
}
void AFPS_CharacterController::MouseMove_X(float x) { MouseXY.X = x; }
void AFPS_CharacterController::MouveMove_Y(float y) { MouseXY.Y = y; }
void AFPS_CharacterController::ForwardMoveKeyDown(float forward) { MoveVector.X = forward; }
void AFPS_CharacterController::RightMoveKeyDown(float right) { MoveVector.Y = right; }
void AFPS_CharacterController::ReloadAmmo() 
{ 
	if (IsPossibleReload())
	{
		if (Character->GetIsWeaponFire())
			Character->EndFire();

		Character->ReloadAmmo();
		if (AimingWeapon)
			AimingButtonRelease();
	}
}
void AFPS_CharacterController::FireButtonPress() 
{
	if (IsPossibleFire())
	{
		if (Character->GetCurrentEquipWeapon()->GetChargedAmmoQuantity() > 0)
		{
			PossibleFire = Character->StartFire();
			PlayCameraShakeWeaponFire(EWeaponType::RIFLE);
			if (IsRun)
				RunButtonRelease();
		}
		else
			Character->GetCurrentEquipWeapon()->PlayAmmoEmptySound();
	}
}
void AFPS_CharacterController::FireButtonRelease() { Character->EndFire();  }
void AFPS_CharacterController::AimingButtonPress() 
{
	if (IsPossibleAiming())
	{
		if (IsRun)
			RunButtonRelease();
		AimingWeapon = true;
		Character->SetAiming_ZoomIn();
		FTimerDelegate del = FTimerDelegate::CreateUObject(this, &AFPS_CharacterController::SetCameraFOV, CAMERA_AIMING_FOV);
		GetWorldTimerManager().SetTimer(AimingTH, del, GWorld->GetDeltaSeconds(), true); 
	}
}
void AFPS_CharacterController::AimingButtonRelease() 
{
	if (AimingWeapon)
	{
		AimingWeapon = false;
		Character->SetAiming_ZoomOut();
		FTimerDelegate del = FTimerDelegate::CreateUObject(this, &AFPS_CharacterController::SetCameraFOV, CAMERA_DEFAULT_FOV);
		GetWorldTimerManager().SetTimer(AimingTH, del, GWorld->GetDeltaSeconds(), true);
	}
}
void AFPS_CharacterController::JumpKeyDown()
{
	if (IsPossibleJump())
	{
		Character->bPressedJump = true;
		PossibleMove = false;
		PossibleJump = false;
		IsLand = false;
		Character->SetJumpAnim();
		GetWorldTimerManager().SetTimer(JumpTH, this, &AFPS_CharacterController::CheckGround, GWorld->GetDeltaSeconds(), true, 0.5f);
	}
}
void AFPS_CharacterController::RunButtonPress()
{
	if (IsPossibleRun())
	{
		IsRun = true;
		if (AimingWeapon)
			AimingButtonRelease();
		if (Character->GetCharacterActionState() == ECharacterActionState::FIRE)
		{
			if (Character->GetCurrentEquipWeapon()->GetIsLoopFire())
				FireButtonRelease();
		}

	}
}
void AFPS_CharacterController::RunButtonRelease()
{
	if (IsRun)
	{
		IsRun = false;
	}
}

void AFPS_CharacterController::CharacterMovement()
{
	MoveVector.Normalize();
	if (IsPossibleMove())
	{
		if (MoveVector.Size() > 0)
		{
			if (MoveVector.X < 0)
				RunButtonRelease();

			if (IsRun)
				Character->SetRunAnim();
			else
				Character->SetMoveAnim();

			MoveVector = GetPawn()->GetActorTransform().TransformVector(MoveVector);
			GetPawn()->AddMovementInput(MoveVector * Character->GetMoveSpeed() * GWorld->GetDeltaSeconds());
		}
		else
			Character->SetIdleAnim();
	}
}

void AFPS_CharacterController::CharacterRotate()
{
	MouseXY = MouseXY * Character->GetCameraRotSpeed() * GWorld->GetDeltaSeconds();

	FRotator actorRot = GetControlRotation();
	actorRot.Yaw += MouseXY.X;

	SetControlRotation(actorRot);
	Character->SetPitchInput(MouseXY.Y);
}

void AFPS_CharacterController::CheckGround()
{
	FHitResult hitResult;
	FVector StartPos = GetPawn()->GetActorLocation() - CapsuleHalfHeight;

	if (!IsLand && GetWorld()->LineTraceSingleByObjectType(hitResult, StartPos, StartPos - FVector(0, 0, 3), ECollisionChannel::ECC_WorldStatic))
	{
		GetWorldTimerManager().ClearTimer(JumpTH);
		PossibleMove = true;
		IsLand = true;
		Character->SetLandAnim();
		GetWorldTimerManager().SetTimer(JumpTH, this, &AFPS_CharacterController::EndJump, 0.5f, false);
	}
}

void AFPS_CharacterController::AutoReloadAmmo()
{
	if (Character->GetCurrentEquipWeapon()->GetChargedAmmoQuantity() <= 0)
	{
		if (Character->GetIsWeaponFire())
			Character->EndFire();

		if (IsPossibleReload())
		{
			if (AimingWeapon)
				AimingButtonRelease();

			Character->ReloadAmmo();
		}
	}
}

void AFPS_CharacterController::SetCameraFOV(float targetFOV)
{
	CurrentCameraFOV = FMath::Lerp(CurrentCameraFOV, targetFOV, GWorld->GetDeltaSeconds() * 10);
	if (FMath::Abs(targetFOV - CurrentCameraFOV) < 0.5f)
		CurrentCameraFOV = targetFOV;
	Character->SetCameraFOV(CurrentCameraFOV);
}

void AFPS_CharacterController::EndJump()
{
	PossibleJump = true;
	Character->SetIdleAnim();
}

void AFPS_CharacterController::EquipWeapon_Rifle()
{
	if (IsPossibleEquipWeapon(EWeaponType::RIFLE))
	{
		AFPS_Weapon* Rifle = WeaponList->GetWeapon(EWeaponType::RIFLE);
		Character->EquipWeapon(Rifle);
		WeaponEquipTime = GWorld->GetTimeSeconds();
	}
}

void AFPS_CharacterController::EquipWeapon_Launcher()
{
	if (IsPossibleEquipWeapon(EWeaponType::LAUNCHER))
	{
		AFPS_Weapon* Launcher = WeaponList->GetWeapon(EWeaponType::LAUNCHER);
		Character->EquipWeapon(Launcher);
		WeaponEquipTime = GWorld->GetTimeSeconds();
	}
}

bool AFPS_CharacterController::IsPossibleEquipWeapon(EWeaponType type)
{
	if (Character->GetIsAiming())
		return false;
	if (Character->GetCharacterActionState() == ECharacterActionState::FIRE || Character->GetCharacterActionState() == ECharacterActionState::EQUIP)
		return false;
	if (Character->GetCurrentEquipWeaponType() == type)
		return false;

	return true;
}

bool AFPS_CharacterController::IsPossibleMove()
{
	if (!PossibleMove)
		return false;

	return true;
}

bool AFPS_CharacterController::IsPossibleJump()
{
	if (Character->GetCharacterMovementState() == ECharacterMovementState::JUMP)
		return false;
	if (!PossibleJump || !IsLand)
		return false;
	return true;
}

bool AFPS_CharacterController::IsPossibleReload()
{
	if (Character->GetCurrentEquipWeapon()->GetReserveAmmoQuantity() <= 0 || 
		Character->GetCurrentEquipWeapon()->GetChargedAmmoQuantity() >= Character->GetCurrentEquipWeapon()->GetMaxChargeAmmoQuantity())
		return false;

	if (Character->GetCharacterActionState() == ECharacterActionState::EQUIP || Character->GetCharacterActionState() == ECharacterActionState::RELOAD)
		return false;
	if (!PossibleFire)
		return false;

	return true;
}

bool AFPS_CharacterController::IsPossibleFire()
{
	if (!PossibleFire)
		return false;
	if (Character->GetCharacterActionState() != ECharacterActionState::PEACE)
		return false;
	return true;
}

bool AFPS_CharacterController::IsPossibleAiming()
{
	if (!PossibleFire)
		return false;

	if (AimingWeapon || Character->GetCharacterActionState() != ECharacterActionState::PEACE)
		return false;

	return true;
}

bool AFPS_CharacterController::IsPossibleRun()
{
	if (Character->GetCharacterMovementState() == ECharacterMovementState::JUMP)
		return false;

	return true;
}

void AFPS_CharacterController::SetOnceFireEnd()
{ 
	PossibleFire = true; 
	Character->SetOnceFireWeaponFireEnd();
}

void AFPS_CharacterController::PlayCameraShakeWeaponFire(EWeaponType weaponType)
{
	/*
	switch (weaponType)
	{
	case EWeaponType::RIFLE :
		ClientPlayCameraShake(CamShake_RifleFire, 1);
		break;
	case EWeaponType::LAUNCHER :
		ClientPlayCameraShake(CamShake_LauncherFire, 1);
		break;
	}*/

	AB_LOG(Warning, TEXT("Shake"));
	/*
	UClass* ShakeClass = CamShakeRifleClass.TryLoadClass<UCameraShake>();
	ClientPlayCameraShake(ShakeClass, 1);
	ClientPlayForceFeedback(FireForceFeedback, false, "Weapon");
	*/
}