// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_Character.h"

// Sets default values
AFPS_Character::AFPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Set SocketName
	WeaponAttachPoint = TEXT("WeaponPoint");
	//Create SubObject
	RotPibot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RotPibot"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Road Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("SkeletalMesh'/Game/Characters/HeroFPP/HeroFPP.HeroFPP'"));
	GetMesh()->SetSkeletalMesh(mesh.Object);
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> animBP(TEXT("AnimBlueprint'/Game/Blueprint/Character/BP_FPS_CharacterAnimCtrl.BP_FPS_CharacterAnimCtrl'"));
	GetMesh()->SetAnimInstanceClass(animBP.Object->GetAnimBlueprintGeneratedClass());
	//Setup Component Hierarchy
	RotPibot->SetupAttachment(RootComponent);
	GetMesh()->SetupAttachment(RotPibot);
	SpringArm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(SpringArm);
	//Setup Compnent Property
	GetCapsuleComponent()->SetEnableGravity(false);
	GetCapsuleComponent()->SetCapsuleHalfHeight(86);
	GetCapsuleComponent()->SetCapsuleRadius(65);
	RotPibot->SetRelativeLocation(FVector(0, 0, 40));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -126), FRotator(0, -90, 0));
	GetMesh()->SetEnableGravity(false);
	SpringArm->TargetArmLength = -7;
	SpringArm->SetRelativeLocationAndRotation(FVector(0, 0, 147), FRotator(0, 90, 0));
	//Setup MemberProperty
	ReserveAmmo = 50;
	MOVE_SPEED = 100;
	CameraRotSpeed = 100;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bFindCameraComponentWhenViewTarget = true;
}

// Called when the game starts or when spawned
void AFPS_Character::InitProperty()
{
	AnimCtrl = Cast<UFPS_CharacterAnimCtrl>(GetMesh()->GetAnimInstance());
	CurrentEquipWeapon = nullptr;
	CurrentEquipWeaponType = EWeaponType::NONE;
}

void AFPS_Character::EquipWeapon(class AFPS_Weapon* weapon)
{
	if (CurrentEquipWeapon != nullptr)
		CurrentEquipWeapon->SetActorHiddenInGame(true);

	CurrentEquipWeapon = weapon;
	CurrentEquipWeaponType = CurrentEquipWeapon->GetWeaponType();
	CurrentEquipWeapon->SetActive(true);
	CurrentEquipWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponAttachPoint);
	SetEquipAnim();
}

void AFPS_Character::SetPitchInput(float pitch)
{
	FRotator pibotRot = RotPibot->GetComponentRotation();
	pibotRot.Pitch += pitch;

	if (pibotRot.Pitch < -85)
		pibotRot.Pitch = -85;
	if (pibotRot.Pitch > 85)
		pibotRot.Pitch = 85;

	RotPibot->SetWorldRotation(pibotRot);
}

void AFPS_Character::SetEquipAnim()
{
	AnimCtrl->SetCharacterActionState(ECharacterActionState::EQUIP);
	AnimCtrl->SetWeaponSlotNum(static_cast<int>(CurrentEquipWeaponType));
	AnimCtrl->PlayWeaponEquipAnim(CurrentEquipWeaponType);
}

void AFPS_Character::SetJumpAnim()
{
	AnimCtrl->SetJumpStart(true);
	AnimCtrl->SetIsLand(false);
	AnimCtrl->SetCharacterMovementState(ECharacterMovementState::JUMP);
}

void AFPS_Character::SetLandAnim()
{
	AnimCtrl->SetJumpEnd(true);
	AnimCtrl->SetIsLand(true);
}

void AFPS_Character::StartFire()
{
	if (CurrentEquipWeapon != NULL)
	{
		AnimCtrl->SetCharacterActionState(ECharacterActionState::FIRE);
		AnimCtrl->PlayFireAnim(CurrentEquipWeaponType);
		CurrentEquipWeapon->StartFire(Camera);
	}
}

void AFPS_Character::EndFire()
{
	if (CurrentEquipWeapon != NULL)
	{
		AnimCtrl->SetCharacterActionState(ECharacterActionState::PEACE);
		AnimCtrl->StopFireAnim(CurrentEquipWeaponType);
		CurrentEquipWeapon->EndFire();
	}
}

void AFPS_Character::Debug()
{
	/*
	FVector AimVector = Camera->GetComponentRotation().Vector();
	FVector CamLoc = Camera->GetComponentLocation();
	DrawDebugLine(GetWorld(), CamLoc, CamLoc + AimVector * 20000, FColor::Red);*/
}