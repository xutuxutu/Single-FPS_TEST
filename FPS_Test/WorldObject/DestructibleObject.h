// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/DestructibleActor.h"
#include "DestructibleObject.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API ADestructibleObject : public ADestructibleActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public :
	ADestructibleObject();
	void AddDamage(FVector impactPoint, float damage);
};
