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

	//Texture Atlas
	UTexture2D* HitNotifyTexture;
	UTexture2D* HUDMainTexture;
	UTexture2D* HUDAssets02Texture;
	UTexture2D* LowHealthOverlayTexture;

	//Size Property
	float GeneralOffset;

	FVector2D CanvasSize;
	FVector2D CanvasCenter;
	float UI_SizeRatio;	
	float CurrentWeaponSpread;
	float UpdateWeaponSpread;

	FCanvasIcon Crosshair[5];

	UPROPERTY()
	UFont* BigFont;
	UPROPERTY()
	UFont* NormalFont;
private :

protected :
	virtual void BeginPlay() override;
	void SetSizeProperty();
	//CrossHair
	void DrawCrossHair();
	void DrawCrossHair_Rifle();
	void DrawCrossHair_Launcher();
	float CrosshairDamper();
	//Weapon
	void DrawWeaponAmmoInfo();
public :
	AFPS_CharacterHUD();

	virtual void DrawHUD() override;
};
