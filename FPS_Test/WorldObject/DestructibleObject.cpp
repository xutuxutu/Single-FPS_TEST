// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "Engine/DestructibleMesh.h"
#include "DestructibleObject.h"

ADestructibleObject::ADestructibleObject()
{
	static ConstructorHelpers::FObjectFinder<UDestructibleMesh> destructibleMesh(TEXT("DestructibleMesh'/Game/Object/DM_Box.DM_Box'"));
	GetDestructibleComponent()->SetDestructibleMesh(destructibleMesh.Object);
}

void ADestructibleObject::BeginPlay()
{
	GetDestructibleComponent()->SetSimulatePhysics(true);
}

void ADestructibleObject::AddDamage(FVector impactPoint, float damage)
{
	GetDestructibleComponent()->ApplyRadiusDamage(damage, impactPoint, 800, 5000, true);
}

