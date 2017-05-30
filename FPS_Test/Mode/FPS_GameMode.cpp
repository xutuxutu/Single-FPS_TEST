// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_GameMode.h"
#include "Character/FPS_CharacterController.h"
#include "Character/FPS_Character.h"
#include "UI/FPS_CharacterHUD.h"

AFPS_GameMode::AFPS_GameMode()
{
	PlayerControllerClass = AFPS_CharacterController::StaticClass();
	DefaultPawnClass = AFPS_Character::StaticClass();
	HUDClass = AFPS_CharacterHUD::StaticClass();
}