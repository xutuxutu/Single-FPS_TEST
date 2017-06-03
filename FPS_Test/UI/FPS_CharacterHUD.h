// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "FPS_CharacterHUD.generated.h"

namespace ECrosshairDirection
{
	enum Type
	{
		Left = 0,
		Right = 1,
		Top = 2,
		Bottom = 3,
		Center = 4
	};
};

UCLASS()
class FPS_TEST_API AFPS_CharacterHUD : public AHUD
{
	GENERATED_BODY()
private :
	class AFPS_CharacterController* CharacterController;
	class AFPS_Character* Character;
	UTexture2D* CharacterMainHUD;

	//Size Property
	FVector2D CanvasCenter;
	float UI_SizeRatio;	
	float CurrentWeaponSpread;
	float UpdateWeaponSpread;
	/** Crosshair icons (left, top, right, bottom and center). */
	UPROPERTY()
	FCanvasIcon Crosshair[5];
protected :
	virtual void BeginPlay() override;

	void SetSizeProperty();
	void DrawCrossHair();
	void DrawCrossHair_Rifle();
	void DrawCrossHair_Launcher();
	float CrosshairDamper();
public :
	AFPS_CharacterHUD();

	virtual void DrawHUD() override;
};
