// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_CharacterHUD.h"
#include "Character/FPS_CharacterController.h"
#include "Weapon/FPS_WeaponType.h"


AFPS_CharacterHUD::AFPS_CharacterHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> HitTextureOb(TEXT("/Game/UI/HUD/HitIndicator"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/UI/HUD/HUDMain"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDAssets02TextureOb(TEXT("/Game/UI/HUD/HUDAssets02"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LowHealthOverlayTextureOb(TEXT("/Game/UI/HUD/LowHealthOverlay"));

	static ConstructorHelpers::FObjectFinder<UFont> BigFontOb(TEXT("/Game/UI/HUD/Roboto51"));
	static ConstructorHelpers::FObjectFinder<UFont> NormalFontOb(TEXT("/Game/UI/HUD/Roboto18"));

	HitNotifyTexture = HitTextureOb.Object;
	HUDMainTexture = HUDMainTextureOb.Object;
	HUDAssets02Texture = HUDAssets02TextureOb.Object;
	LowHealthOverlayTexture = LowHealthOverlayTextureOb.Object;

	BigFont = BigFontOb.Object;
	NormalFont = NormalFontOb.Object;

	Crosshair[ECrosshairDirection::Left] = UCanvas::MakeIcon(HUDMainTexture, 43, 402, 25, 9); // left
	Crosshair[ECrosshairDirection::Right] = UCanvas::MakeIcon(HUDMainTexture, 88, 402, 25, 9); // right
	Crosshair[ECrosshairDirection::Top] = UCanvas::MakeIcon(HUDMainTexture, 74, 371, 9, 25); // top
	Crosshair[ECrosshairDirection::Bottom] = UCanvas::MakeIcon(HUDMainTexture, 74, 415, 9, 25); // bottom
	Crosshair[ECrosshairDirection::Center] = UCanvas::MakeIcon(HUDMainTexture, 75, 403, 7, 7); // center

	GeneralOffset = 20.0f;
}


void AFPS_CharacterHUD::BeginPlay()
{
	CharacterController = Cast<AFPS_CharacterController>(PlayerOwner);
	Character = Cast<AFPS_Character>(PlayerOwner->GetPawn());
}

void AFPS_CharacterHUD::DrawHUD()
{
	Super::DrawHUD();

	SetSizeProperty();
	DrawCrossHair();
	DrawWeaponAmmoInfo();
}

void AFPS_CharacterHUD::SetSizeProperty()
{
	CanvasSize.X = Canvas->ClipX - Canvas->OrgX;
	CanvasSize.Y = Canvas->ClipY - Canvas->OrgY;

	CanvasCenter.X = Canvas->ClipX / 2;
	CanvasCenter.Y = Canvas->ClipY / 2;
	UI_SizeRatio = (Canvas->ClipX + Canvas->ClipY) / (2048.f + 1080.f);
}

void AFPS_CharacterHUD::DrawCrossHair()
{
	if (CharacterController)
		UpdateWeaponSpread = CharacterController->GetCurrentEquipWeaponSpread();

	switch (Character->GetCurrentEquipWeaponType())
	{
		case EWeaponType::RIFLE :		DrawCrossHair_Rifle(); break;
		case EWeaponType::LAUNCHER :	DrawCrossHair_Launcher(); break;
	}
}

void AFPS_CharacterHUD::DrawCrossHair_Rifle()
{
	if (Character->GetIsAiming())
	{
		Canvas->SetDrawColor(255, 0, 0, 192);
		Canvas->DrawIcon(Crosshair[ECrosshairDirection::Center],
			CanvasCenter.X - Crosshair[ECrosshairDirection::Center].UL * UI_SizeRatio / 2,
			CanvasCenter.Y - Crosshair[ECrosshairDirection::Center].VL * UI_SizeRatio / 2, UI_SizeRatio * 2);
	}
	else
	{
		Canvas->SetDrawColor(255, 255, 255, 192);
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
}

void AFPS_CharacterHUD::DrawCrossHair_Launcher()
{
	Canvas->SetDrawColor(255, 255, 255, 192);
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

float AFPS_CharacterHUD::CrosshairDamper()
{
	float CurrentTime = GWorld->GetTimeSeconds();
	float WeaponEquipTime = CharacterController->GetWeaponEquipTime();

	//시간을 이용하여 움직이게
	float AnimOffset = 500 * (0.4f - FMath::Min(0.4f, CurrentTime - WeaponEquipTime));
	CurrentWeaponSpread = 2 + AnimOffset;
	//탄젠트 곡선을 이용
	CurrentWeaponSpread += 300 * FMath::Tan(FMath::DegreesToRadians(UpdateWeaponSpread));

	return CurrentWeaponSpread;
}


void AFPS_CharacterHUD::DrawWeaponAmmoInfo()
{
	FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), BigFont, FColor::White);
	TextItem.EnableShadow(FLinearColor::Black);
	TextItem.Scale = FVector2D(0.73f * UI_SizeRatio, 0.73f * UI_SizeRatio);

	//ChargedAmmo
	FString AmmoInfo = FString::FromInt(Character->GetCurrentEquipWeapon()->GetChargedAmmoQuantity());
	const float ChargedAmmo_PosX = Canvas->ClipX - (200 * UI_SizeRatio);
	const float ChargedAmmo_PosY = Canvas->ClipY - (80 * UI_SizeRatio);

	TextItem.Text = FText::FromString(AmmoInfo);
	Canvas->DrawItem(TextItem, ChargedAmmo_PosX, ChargedAmmo_PosY);

	//Seperate Word
	AmmoInfo = FString("/");
	const float Seperate_PosX = (Canvas->ClipX - (200 * UI_SizeRatio)) + (50 * UI_SizeRatio);
	const float Seperate_PosY = Canvas->ClipY - (80 * UI_SizeRatio);

	TextItem.Text = FText::FromString(AmmoInfo);
	Canvas->DrawItem(TextItem, Seperate_PosX, Seperate_PosY);

	//ReserveAmmo
	AmmoInfo = FString::FromInt(Character->GetCurrentEquipWeapon()->GetReserveAmmoQuantity());
	const float ReserveAmmo_PosX = (Canvas->ClipX - (200 * UI_SizeRatio)) + (80 * UI_SizeRatio);
	const float ReserveAmmo_PosY = Canvas->ClipY - (80 * UI_SizeRatio);

	TextItem.Text = FText::FromString(AmmoInfo);
	Canvas->DrawItem(TextItem, ReserveAmmo_PosX, ReserveAmmo_PosY);
}