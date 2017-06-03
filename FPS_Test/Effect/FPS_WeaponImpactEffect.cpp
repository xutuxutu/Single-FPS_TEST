// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponImpactEffect.h"


// Sets default values
AFPS_WeaponImpactEffect::AFPS_WeaponImpactEffect()
{
	bAutoDestroyWhenFinished = true;
}

void AFPS_WeaponImpactEffect::SetProperty(const FHitResult& hitResult, UParticleSystem* impactFX, USoundCue* impactSound, FDecalData* decalData)
{
	if (impactFX)
		UGameplayStatics::SpawnEmitterAtLocation(this, impactFX, hitResult.ImpactPoint, hitResult.ImpactNormal.Rotation());
	if (impactSound)
		UGameplayStatics::PlaySoundAtLocation(this, impactSound, hitResult.ImpactPoint);
	if (decalData->DecalMaterial)
	{
		FRotator RandomDecalRotation = hitResult.ImpactNormal.Rotation();
		RandomDecalRotation.Roll = FMath::FRandRange(-180.0f, 180.0f);

		UGameplayStatics::SpawnDecalAttached(decalData->DecalMaterial, FVector(1.0f, decalData->DecalSize, decalData->DecalSize),
			hitResult.Component.Get(), hitResult.BoneName,
			hitResult.ImpactPoint, RandomDecalRotation, EAttachLocation::KeepWorldPosition,
			decalData->LifeTime);
			
	}
}
