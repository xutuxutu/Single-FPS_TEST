// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Test.h"
#include "FPS_WeaponList.h"

FFPS_WeaponList::FFPS_WeaponList()
{
}

FFPS_WeaponList::~FFPS_WeaponList()
{
}

void FFPS_WeaponList::AddWeapon(AFPS_Weapon* weapon)
{
	WeaponList.push_back(weapon);
}

AFPS_Weapon* FFPS_WeaponList::GetWeapon(EWeaponType weaponType)
{
	for (int i = 0; i < WeaponList.size(); ++i)
	{
		if (WeaponList[i]->GetWeaponType() == weaponType)
			return WeaponList[i];
	}
	return nullptr;
}