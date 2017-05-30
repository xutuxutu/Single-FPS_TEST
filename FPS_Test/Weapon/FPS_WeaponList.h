// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "FPS_WeaponRifle.h"
#include "FPS_WeaponLauncher.h"
#include <vector>
/**
 * 
 */
class FPS_TEST_API FFPS_WeaponList
{
private :
	std::vector<AFPS_Weapon*> WeaponList;
public:
	FFPS_WeaponList();
	~FFPS_WeaponList();

	void AddWeapon(AFPS_Weapon* weapon);
	AFPS_Weapon* GetWeapon(EWeaponType weaponType);
	const std::vector<AFPS_Weapon*>& GetWeaponList() { return WeaponList; }
};
