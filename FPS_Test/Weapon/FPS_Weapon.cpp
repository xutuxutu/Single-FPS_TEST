// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_Weapon.h"


// Sets defaut values
AFPS_Weapon::AFPS_Weapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	Mesh->SetRelativeRotation(FRotator(0, 0, -90));
	SetRootComponent(Mesh);

	MuzzleFlashPosition = TEXT("MuzzleFlashSocket");
}

void AFPS_Weapon::InitProperty(float attackDistance, int maxChargeAmmo, int chargedAmmo)
{
	AttackDistance = attackDistance;
	MaxChargeAmmo = maxChargeAmmo;
	ChargedAmmo = chargedAmmo;
}

void AFPS_Weapon::SetActive(bool isActive)
{
	SetActorHiddenInGame(!isActive);
}

void AFPS_Weapon::SetWeaponFireHitResult(const UCameraComponent* ViewCamera)
{
	FVector Start = ViewCamera->GetComponentLocation();
	FVector End = Start + ViewCamera->GetComponentRotation().Vector() * AttackDistance;

	if (!GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ECollisionChannel::ECC_WorldStatic))
	{
		HitResult.ImpactPoint = End;
		HitResult.Actor = nullptr;
	}
}

void AFPS_Weapon::ActivateMuzzleFX()
{
	if (MuzzleFX)
		MuzzleFX_Playing = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, Mesh, MuzzleFlashPosition);
}

void AFPS_Weapon::DeactivateMuzzleFX()
{
	if (MuzzleFX_Playing != NULL)
	{
		MuzzleFX_Playing->Deactivate();
		MuzzleFX_Playing = NULL;
	}
}

UAudioComponent* AFPS_Weapon::PlayWeaponSound(USoundCue* sound)
{
	UAudioComponent* AC = NULL;
	if (sound)
		AC = UGameplayStatics::SpawnSoundAttached(sound, GetMesh());

	return AC;
}

void AFPS_Weapon::StopFireSound()
{ 
	FireSound_Playing->Deactivate();
	FireSound_Playing = NULL; 
	PlayWeaponSound(FireEndSound);
}