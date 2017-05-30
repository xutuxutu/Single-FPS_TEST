// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponImpactEffect_Rifle.h"


// Sets default values
AFPS_WeaponImpactEffect_Rifle::AFPS_WeaponImpactEffect_Rifle() : AFPS_WeaponImpactEffect()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> impactFX(TEXT("ParticleSystem'/Game/Effects/ParticleSystems/Weapons/AssaultRifle/Impacts/P_AssaultRifle_IH.P_AssaultRifle_IH'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> impactSound(TEXT("SoundCue'/Game/Sounds/Weapon_AssaultRifle/Mono/AssaultRifle_ImpactConcrete_Cue.AssaultRifle_ImpactConcrete_Cue'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> impactDecalM(TEXT("Material'/Game/Effects/Materials/Weapon/M_Impact_Decal.M_Impact_Decal'"));

	SetImpactFX(impactFX.Object);
	SetImpactSoundCue(impactSound.Object);
	SetImpactDecalMetarial(impactDecalM.Object);
}

// Called when the game starts or when spawned
void AFPS_WeaponImpactEffect_Rifle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPS_WeaponImpactEffect_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

