// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Engine.h"

UENUM()
enum class EWeaponType : uint8
{
	NONE,
	RIFLE,
	LAUNCHER,
};

struct FDecalData
{
	UMaterial* DecalMaterial;
	float DecalSize = 15;
	float LifeTime = 2.0f;
};
