// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "FPS_CharacterCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API AFPS_CharacterCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	virtual void UpdateCamera(float deltaTime) override;
};
