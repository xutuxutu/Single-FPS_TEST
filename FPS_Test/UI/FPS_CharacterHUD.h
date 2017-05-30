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
	UTexture2D* CharacterMainHUD;

	//Size Property
	FVector2D CanvasCenter;
	float UI_SizeRatio;			//1080 YSize Based Ratio
	/** Crosshair icons (left, top, right, bottom and center). */
	UPROPERTY()
	FCanvasIcon Crosshair[5];
protected :
	void SetSizeProperty();
	void DrawCrossHair();
	float CrosshairDamper() { return 30 * UI_SizeRatio; }
public :
	AFPS_CharacterHUD();

	virtual void DrawHUD() override;
};
