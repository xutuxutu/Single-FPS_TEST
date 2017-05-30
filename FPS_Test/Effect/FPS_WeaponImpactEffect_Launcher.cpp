// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponImpactEffect_Launcher.h"


// Sets default values
AFPS_WeaponImpactEffect_Launcher::AFPS_WeaponImpactEffect_Launcher() : AFPS_WeaponImpactEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPS_WeaponImpactEffect_Launcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPS_WeaponImpactEffect_Launcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

