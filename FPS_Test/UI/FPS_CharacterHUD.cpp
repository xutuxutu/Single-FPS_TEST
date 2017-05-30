// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_CharacterHUD.h"


AFPS_CharacterHUD::AFPS_CharacterHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/UI/HUD/HUDMain"));

	CharacterMainHUD = HUDMainTextureOb.Object;

	Crosshair[ECrosshairDirection::Left] = UCanvas::MakeIcon(CharacterMainHUD, 43, 402, 25, 9); // left
	Crosshair[ECrosshairDirection::Right] = UCanvas::MakeIcon(CharacterMainHUD, 88, 402, 25, 9); // right
	Crosshair[ECrosshairDirection::Top] = UCanvas::MakeIcon(CharacterMainHUD, 74, 371, 9, 25); // top
	Crosshair[ECrosshairDirection::Bottom] = UCanvas::MakeIcon(CharacterMainHUD, 74, 415, 9, 25); // bottom
	Crosshair[ECrosshairDirection::Center] = UCanvas::MakeIcon(CharacterMainHUD, 75, 403, 7, 7); // center

	AB_LOG(Warning, TEXT("%f"), Crosshair[ECrosshairDirection::Center].U);
	AB_LOG(Warning, TEXT("%f"), Crosshair[ECrosshairDirection::Center].V);
	AB_LOG(Warning, TEXT("%f"), Crosshair[ECrosshairDirection::Center].UL);
	AB_LOG(Warning, TEXT("%f"), Crosshair[ECrosshairDirection::Center].VL);
}

void AFPS_CharacterHUD::DrawHUD()
{
	Super::DrawHUD();

	SetSizeProperty();
	DrawCrossHair();
}

void AFPS_CharacterHUD::SetSizeProperty()
{
	CanvasCenter.X = Canvas->ClipX / 2;
	CanvasCenter.Y = Canvas->ClipY / 2;
	UI_SizeRatio = (Canvas->ClipX + Canvas->ClipY) / (1080.f + 2160.f);
}

void AFPS_CharacterHUD::DrawCrossHair()
{
	Canvas->DrawIcon(Crosshair[ECrosshairDirection::Center],
		CanvasCenter.X - Crosshair[ECrosshairDirection::Center].UL * UI_SizeRatio / 2,
		CanvasCenter.Y - Crosshair[ECrosshairDirection::Center].VL * UI_SizeRatio / 2, UI_SizeRatio);
	
	Canvas->DrawIcon(Crosshair[ECrosshairDirection::Left],
		CanvasCenter.X - Crosshair[ECrosshairDirection::Left].UL * UI_SizeRatio / 2 - CrosshairDamper(),
		CanvasCenter.Y - Crosshair[ECrosshairDirection::Left].VL * UI_SizeRatio / 2, UI_SizeRatio);

	Canvas->DrawIcon(Crosshair[ECrosshairDirection::Right],
		CanvasCenter.X - Crosshair[ECrosshairDirection::Right].UL * UI_SizeRatio / 2 + CrosshairDamper(),
		CanvasCenter.Y - Crosshair[ECrosshairDirection::Right].VL * UI_SizeRatio / 2, UI_SizeRatio);

	Canvas->DrawIcon(Crosshair[ECrosshairDirection::Top],
		CanvasCenter.X - Crosshair[ECrosshairDirection::Top].UL * UI_SizeRatio / 2,
		CanvasCenter.Y - Crosshair[ECrosshairDirection::Top].VL * UI_SizeRatio / 2 - CrosshairDamper(), UI_SizeRatio);

	Canvas->DrawIcon(Crosshair[ECrosshairDirection::Bottom],
		CanvasCenter.X - Crosshair[ECrosshairDirection::Bottom].UL * UI_SizeRatio / 2,
		CanvasCenter.Y - Crosshair[ECrosshairDirection::Bottom].VL * UI_SizeRatio / 2 + CrosshairDamper(), UI_SizeRatio);
		
}