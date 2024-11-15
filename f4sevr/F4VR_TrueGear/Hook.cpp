#include "Hook.h"
//#include "f4se/NiRTTI.h"
//#include "f4se/NiExtraData.h"
#include <F4VR_TrueGear/Utility.hpp>
#include <rpcndr.h>

namespace F4VR_TrueGear
{

	int rainSleepDuration = 100;
	int heartbeatfastsleepduration = 400;
	int heartbeatsleepduration = 600;
	int swimmingsleepduration = 1000;
	int vatssleepduration = 1000;
	int jetpacksleepduration = 500;
	int powerarmorsprintingsleepduration = 300;
	int powerarmorwalkingsleepduration = 500;

	bool isPowerArmorLeftRunning = false;
	bool isPowerArmorLeftWalking = false;

	RelocAddr<_IsInAir> IsInAir(0x00DC3230);


	////////////////////////////////////

	Sky2** g_SkyPtr = nullptr;

	std::atomic<bool> raining(false);

	//Rain variables:
	std::atomic<float> rainIntensity = 1.0f;
	std::atomic<float> rainDensity = 10;
	std::atomic<bool> inPowerArmorFrame = false;
	std::atomic<bool> powerArmorValueKnown = false;

	////////////////////////////////////////////////////////////////////////

	float lowhealthpercentage = 0.2f;
	float verylowhealthpercentage = 0.1f;

	ActorValueInfo* HealthAVI;

	ActorValueInfo* HungerAVI;


	ActorValueInfo* PoisonResistAVI;
	ActorValueInfo* FireResistAVI;
	ActorValueInfo* ElectricResistAVI;
	ActorValueInfo* FrostResistAVI;
	ActorValueInfo* MagicResistAVI;
	ActorValueInfo* RadResistIngestionAVI;
	ActorValueInfo* RadResistExposureAVI;
	ActorValueInfo* EnergyResistAVI;

	UInt32 KeywordActorTypeNPCFormId = 0x13794;
	UInt32 KeywordActorTypeHumanFormId = 0x2CB72;
	UInt32 KeywordActorTypeSuperMutantFormId = 0x6D7B6;
	UInt32 KeywordActorTypeSuperMutantBehemothFormId = 0x14F6A5;

	UInt32 KeywordActorTypeDog = 0x021AD0;
	UInt32 KeywordActorTypeFeralDog = 0x02CB97;
	UInt32 KeywordActorTypeMolerat = 0x02CB70;
	UInt32 KeywordActorTypeDeathclaw = 0x0317AA;
	UInt32 KeywordActorTypeMirelurk = 0x02CB71;
	UInt32 KeywordActorTypeMirelurkQueen = 0x0108178;
	UInt32 KeywordActorTypeMirelurkKing = 0x0E58C7;
	UInt32 KeywordActorTypeRadScorpion = 0x0636DE;
	UInt32 KeywordActorTypeGhoul = 0x0EAFB7;
	UInt32 KeywordActorTypeFeralGhoul = 0x06B4F2;
	UInt32 KeywordActorTypeRadStag = 0x090E55;
	UInt32 KeywordActorTypeRobot = 0x02CB73;
	UInt32 KeywordActorTypeSynth = 0x010C3CE;

	UInt32 KeywordActorTypeAnimalFormId = 0x13798;
	UInt32 KeywordActorTypeCreatureFormId = 0x13795;
	UInt32 KeywordActorTypeBugFormId = 0x2866C;


	UInt32 KeywordWeaponTypeAlienBlasterFormId = 0x16968B;
	UInt32 KeywordWeaponTypeAutomaticFormId = 0x04A0A2;
	UInt32 KeywordWeaponTypeBallisticFormId = 0x092A86;
	UInt32 KeywordWeaponTypeExplosiveFormId = 0x04C922;
	UInt32 KeywordWeaponTypeHeavyGunFormId = 0x04A0A3;
	UInt32 KeywordWeaponTypeThrownFormId = 0x04A0A6;
	UInt32 KeywordWeaponTypeLaserFormId = 0x092A84;


	UInt32 KeywordWeaponTypeRifleFormId = 0x04A0A1;
	UInt32 KeywordWeaponTypeAssaultRifleFormId = 0x226455;
	UInt32 KeywordWeaponTypeGaussRifleFormId = 0x226456;

	UInt32 KeywordWeaponTypePistolFormId = 0x04A0A0;
	UInt32 KeywordWeaponTypeGrenadeFormId = 0x10C415;
	UInt32 KeywordWeaponTypeMineFormId = 0x10C414;
	UInt32 KeywordWeaponTypePlasmaFormId = 0x092A85;
	UInt32 KeywordWeaponTypeShotgunFormId = 0x226454;
	UInt32 KeywordEnergyGunFormId = 0x03E208;
	UInt32 KeywordWeaponTypeHandToHandFormId = 0x226453;
	UInt32 KeywordWeaponTypeUnarmedFormId = 0x05240E;
	UInt32 KeywordWeaponTypeAnimsUnarmedFormId = 0x02405E;
	UInt32 KeywordWeaponTypeMelee1HFormId = 0x04A0A4;
	UInt32 KeywordWeaponTypeMelee2HFormId = 0x04A0A5;
	UInt32 KeywordWeaponTypeRipperFormId = 0x225767;
	UInt32 KeywordWeaponTypeShishkebabFormId = 0x225768;

	UInt32 KeywordWeaponTypeAnims1HMShortFormId = 0xD20A6;
	UInt32 KeywordWeaponTypeAnims1HMFormId = 0x23465;
	UInt32 KeywordWeaponTypeAnims2HMFormId = 0xA7C45;
	UInt32 KeywordWeaponTypeAnims2HMWideFormId = 0xEB4A2;
	UInt32 KeywordWeaponTypeAnims44FormId = 0xCE97E;
	UInt32 KeywordWeaponTypeAnimsAlienBlasterFormId = 0xFF996;
	UInt32 KeywordWeaponTypeAnimsAssBladeModFormId = 0x210B61;
	UInt32 KeywordWeaponTypeAnimsCombatShotgunFormId = 0xB9560;
	UInt32 KeywordWeaponTypeAnimsDelivererFormId = 0xDC8E8;
	UInt32 KeywordWeaponTypeAnimsDoubleBarrelShotgunFormId = 0x166703;
	UInt32 KeywordWeaponTypeAnimsFlareGunFormId = 0x1025AD;
	UInt32 KeywordWeaponTypeAnimsGammaGunFormId = 0xDDB7D;
	UInt32 KeywordWeaponTypeAnimsGatlingLaserFormId = 0xE27BD;
	UInt32 KeywordWeaponTypeAnimsGripPistolFormId = 0x1F948;
	UInt32 KeywordWeaponTypeAnimsMineFormId = 0xE56C4;
	UInt32 KeywordWeaponTypeAnimsMinigunFormId = 0x212FE;
	UInt32 KeywordWeaponTypeAnimsSubmachineGunFormId = 0x1A6AEF;

	UInt32 KeywordWeaponTypeAnimsBroadsiderFormId = 0xFB198;
	UInt32 KeywordWeaponTypeAnimsMiniGun = 0x0212FE;
	UInt32 KeywordWeaponTypeAnimsMissileLauncher = 0xA1B8A;
	UInt32 KeywordWeaponTypeAnimsFatman = 0xBC240;
	UInt32 KeywordWeaponTypeAnimsFlamer = 0x0E5882;
	UInt32 KeywordWeaponTypeFlamer = 0x225760;
	UInt32 KeywordWeaponTypeAnims40Flamer = 0xEB266;
	UInt32 KeywordWeaponTypeAnimsJunkJet = 0x106F77;
	UInt32 KeywordWeaponTypeAnimsCryolator = 0x171B2C;

	UInt32 KeywordWeaponTypeAnimsLaserMusketFormId = 0x1F946;

	UInt32 KeywordArmorTypePoweredFormId = 0x4D8A1;

	UInt32 KeywordObjectTypeAlcohol = 0x10C416;
	UInt32 KeywordObjectTypeCaffeinated = 0x249F31;
	UInt32 KeywordObjectTypeChem = 0xF4AE7;
	UInt32 KeywordObjectTypeDrink = 0xF4AEC;
	UInt32 KeywordObjectTypeExtraCaffeinated = 0x249F9D;
	UInt32 KeywordObjectTypeFood = 0x55ECC;
	UInt32 KeywordObjectTypeStimpak = 0xF4AEB;
	UInt32 KeywordObjectTypeSyringerAmmo = 0x18506F;
	UInt32 KeywordObjectTypeWater = 0xF4AED;

	UInt32 KeywordAnimFurnWater = 0x55ECB;
	UInt32 KeywordFruitOrVegetable = 0x1C63E5;
	UInt32 KeywordHCDiseaseRiskChem = 0x8C6;
	UInt32 KeywordHCDiseaseRiskFoodHigh = 0x89A;
	UInt32 KeywordHCDiseaseRiskFoodStandard = 0x899;
	UInt32 KeywordHCSustenanceTypeIncreasesHunger = 0x249F7A; //chem
	UInt32 KeywordHCSustenanceTypeIncreasesThirst = 0x883;
	UInt32 KeywordHCSustenanceTypeQuenchesThirst = 0x884;

	UInt32 KeywordPowerArmor = 0x4D8A1;
	UInt32 KeywordPowerArmorFrame = 0x15503F;

	UInt32 CritCryoSpellFormId = 0x1478ED;
	UInt32 CritFireSpellFormId = 0x1478EC;
	UInt32 CritLaserSpellFormId = 0x731B2;
	UInt32 CritLaserLtBlueSpellFormId = 0x1E4506;
	UInt32 CritMirelurkQueenSpellFormId = 0x1C6BCA;
	UInt32 CritPlasmaSpellFormId = 0x139F8C;

	UInt32 TeleportInSpellFormId = 0x062BDC;
	UInt32 TeleportOutSpellFormId = 0x062BDB;
	UInt32 TeleportPlayerInSpellFormId = 0x01E5601;
	UInt32 TeleportPlayerOutSpellFormId = 0x01F1022;

	std::vector<EffectSetting*> jetPackMagicEffects;
	std::vector<EffectSetting*> radiationMagicEffects;

	UInt32 StarvingEffectFormId = 0x86A;
	UInt32 DehydratedEffectFormId = 0x8BF;
	UInt32 InfectionEffectFormId = 0x8A9;


	UInt32 HeadCrippleConditionFormId = 0x36C;
	UInt32 TorsoCrippleConditionFormId = 0x36D;
	UInt32 LeftArmCrippleConditionFormId = 0x36E;
	UInt32 RightArmCrippleConditionFormId = 0x36F;
	UInt32 LeftLegCrippleConditionFormId = 0x370;
	UInt32 RightLegCrippleConditionFormId = 0x371;
	UInt32 BrainCrippleConditionFormId = 0x372;

	UInt32 PainTrainKnockbackSpellFormId = 0x171782;

	ActorValueInfo* HeadCrippleAVI;
	ActorValueInfo* TorsoCrippleAVI;
	ActorValueInfo* RightArmCrippleAVI;
	ActorValueInfo* LeftArmCrippleAVI;
	ActorValueInfo* RightLegCrippleAVI;
	ActorValueInfo* LeftLegCrippleAVI;
	ActorValueInfo* BrainCrippleAVI;

	void FillMagicEffects()
	{
		if (*g_dataHandler)
		{
			EffectSetting* effect = NULL;
			jetPackMagicEffects.clear();
			for (UInt32 i = 0; i < (*g_dataHandler)->arrMGEF.count; i++)
			{
				(*g_dataHandler)->arrMGEF.GetNthItem(i, effect);

				if (!effect)
					continue;

				if (effect->unk0D0 == 0x30)
				{
					if (std::find(jetPackMagicEffects.begin(), jetPackMagicEffects.end(), effect) == jetPackMagicEffects.end())
					{
						//LOG("Magic Effect %x", effect->formID);
						jetPackMagicEffects.emplace_back(effect);
					}
				}
			}
		}
	}

	bool HasAnyMagicEffect(std::vector<EffectSetting*>* magicEffects)
	{
		MagicTargetNew* magicTarget = (MagicTargetNew*)(&(*g_player)->magicTarget);
		tArray<ActiveEffect*>* activeEffectsList = magicTarget->GetActiveEffects();

		for (int i = 0; i < activeEffectsList->count; i++)
		{
			ActiveEffect* activeEffect = activeEffectsList->entries[i];

			if (activeEffect && (activeEffect->m_flags & ActiveEffect::kFlag_Inactive) == 0)
			{
				if (activeEffect->m_item && activeEffect->m_effect && activeEffect->m_effect->m_setting)
				{
					for (UInt32 p = 0; p < magicEffects->size(); p++)
					{
						if (activeEffect->m_effect->m_setting->formID == magicEffects->at(p)->formID)
						{
							//LOG("Has Magic Effect %x", magicEffects->at(p)->formID);

							return true;
						}
					}
				}
			}
		}
		return false;
	}

	void FillActorValueInfo()
	{
		TESForm* form = LookupFormByID(0x2d4);
		if (form)
		{
			HealthAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x855);
		if (form)
		{
			HungerAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(HeadCrippleConditionFormId);
		if (form)
		{
			HeadCrippleAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(TorsoCrippleConditionFormId);
		if (form)
		{
			TorsoCrippleAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(RightArmCrippleConditionFormId);
		if (form)
		{
			RightArmCrippleAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(LeftArmCrippleConditionFormId);
		if (form)
		{
			LeftArmCrippleAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(RightLegCrippleConditionFormId);
		if (form)
		{
			RightLegCrippleAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(LeftLegCrippleConditionFormId);
		if (form)
		{
			LeftLegCrippleAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(BrainCrippleConditionFormId);
		if (form)
		{
			BrainCrippleAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x2e4);
		if (form)
		{
			PoisonResistAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x2e5);
		if (form)
		{
			FireResistAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x2e6);
		if (form)
		{
			ElectricResistAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x2e7);
		if (form)
		{
			FrostResistAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x2e8);
		if (form)
		{
			MagicResistAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x2e9);
		if (form)
		{
			RadResistIngestionAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x2ea);
		if (form)
		{
			RadResistExposureAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
		form = LookupFormByID(0x2eb);
		if (form)
		{
			EnergyResistAVI = DYNAMIC_CAST(form, TESForm, ActorValueInfo);
		}
	}

	bool HasKeyword(AlchemyItem* item, UInt32 keywordFormId)
	{
		if (item)
		{
			for (UInt32 i = 0; i < item->keywordForm.numKeywords; i++)
			{
				if (item->keywordForm.keywords[i])
				{
					if (item->keywordForm.keywords[i]->formID == keywordFormId)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool HasKeyword(TESObjectARMO* armor, UInt32 keywordFormId)
	{
		if (armor)
		{
			for (UInt32 i = 0; i < armor->keywordForm.numKeywords; i++)
			{
				if (armor->keywordForm.keywords[i])
				{
					if (armor->keywordForm.keywords[i]->formID == keywordFormId)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool HasKeyword(TESObjectWEAP* weapon, UInt32 keywordFormId)
	{
		if (weapon)
		{
			for (UInt32 i = 0; i < weapon->keyword.numKeywords; i++)
			{
				if (weapon->keyword.keywords[i])
				{
					if (weapon->keyword.keywords[i]->formID == keywordFormId)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool HasKeyword(TESRace* race, UInt32 keywordFormId)
	{
		if (race)
		{
			for (UInt32 i = 0; i < race->keywordForm.numKeywords; i++)
			{
				if (race->keywordForm.keywords[i])
				{
					if (race->keywordForm.keywords[i]->formID == keywordFormId)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool GetInPowerArmorFrame()
	{
		if (powerArmorValueKnown.load())
		{
			return inPowerArmorFrame.load();
		}
		else if ((*g_player) && (*g_player)->equipData && (*g_player)->equipData->slots[0x03].item != nullptr)
		{
			bool InPowerArmor = false;
			TESForm* equippedForm = (*g_player)->equipData->slots[0x03].item;
			if (equippedForm)
			{
				if (equippedForm->formType == TESObjectARMO::kTypeID)
				{
					TESObjectARMO* armor = DYNAMIC_CAST(equippedForm, TESForm, TESObjectARMO);

					if (armor)
					{
						if (HasKeyword(armor, KeywordPowerArmor) || HasKeyword(armor, KeywordPowerArmorFrame))
						{
							InPowerArmor = true;
						}
					}
				}
			}
			powerArmorValueKnown.store(true);
			inPowerArmorFrame.store(InPowerArmor);
			return InPowerArmor;
		}
		else
		{
			return false;
		}
	}

	std::string UnarmedTypeAnimal(Actor* actor)
	{
		if (actor && actor->race)
		{
			if (HasKeyword(actor->race, KeywordActorTypeSuperMutantFormId)
				|| HasKeyword(actor->race, KeywordActorTypeSuperMutantBehemothFormId))
			{
				return "UnarmedSuperMutant";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeDog)
				|| HasKeyword(actor->race, KeywordActorTypeFeralDog))
			{
				return "UnarmedDog";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeMolerat))
			{
				return "UnarmedMolerat";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeDeathclaw))
			{
				return "UnarmedDeathclaw";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeMirelurk)
				|| HasKeyword(actor->race, KeywordActorTypeMirelurkQueen)
				|| HasKeyword(actor->race, KeywordActorTypeMirelurkKing))
			{
				return "UnarmedMirelurk";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeRadScorpion))
			{
				return "UnarmedRadScorpion";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeGhoul)
				|| HasKeyword(actor->race, KeywordActorTypeFeralGhoul))
			{
				return "UnarmedFeralGhoul";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeRadStag))
			{
				return "UnarmedRadStag";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeRobot)
				|| HasKeyword(actor->race, KeywordActorTypeSynth))
			{
				return "UnarmedRobot";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeBugFormId))
			{
				return "UnarmedBug";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeAnimalFormId))
			{
				return "UnarmedAnimal";
			}
			else if (HasKeyword(actor->race, KeywordActorTypeCreatureFormId))
			{
				return "UnarmedCreature";
			}
			else
			{
				return "Unarmed";
			}
		}
		else
		{
			_MESSAGE("Cannot find actor race.");
			return "Unarmed";
		}
	}

	bool ActorCreature(Actor* actor)
	{
		if (actor && actor->race)
		{
			if (actor->formID == 0x14)
			{
				return false;
			}

			if ((!(HasKeyword(actor->race, (KeywordActorTypeNPCFormId)))
				&& !(HasKeyword(actor->race, (KeywordActorTypeHumanFormId)))))
				/*&& ((actor->race->keywordForm.HasKeyword(KeywordActorTypeAnimal))
				|| (actor->race->keywordForm.HasKeyword(KeywordActorTypeCreature))
				|| (actor->race->keywordForm.HasKeyword(KeywordActorTypeBug))))*/
			{
				//LOG("Actor is an animal.");
				return true;
			}
			else
			{
				//LOG("Actor is not an animal.");
				return false;
			}
		}
		else
		{
			_MESSAGE("Cannot find actor race.");
			return false;
		}
	}

	std::string DecideWeaponType(TESObjectWEAP::InstanceData* instanceData, TESObjectWEAP* weapon)
	{
		if (weapon)
		{
			if (HasKeyword(weapon, KeywordWeaponTypeAlienBlasterFormId)) { return "AlienBlaster"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsAlienBlasterFormId)) { return "AlienBlaster"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeShotgunFormId)) { return "Shotgun"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsCombatShotgunFormId)) { return "Shotgun"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsDoubleBarrelShotgunFormId)) { return "Shotgun"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeLaserFormId)) { return "Laser"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsGatlingLaserFormId)) { return "Laser"; }
			else if (HasKeyword(weapon, KeywordWeaponTypePlasmaFormId)) { return "Plasma"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsGammaGunFormId)) { return "Plasma"; }

			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsCryolator)) { return "Cryolator"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeFlamer)) { return "Flamer"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsFlamer)) { return "Flamer"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnims40Flamer)) { return "Flamer"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsBroadsiderFormId)) { return "Broadsider"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsMiniGun)) { return "MiniGun"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsMissileLauncher)) { return "MissileLauncher"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsFatman)) { return "Fatman"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsJunkJet)) { return "JunkJet"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeHeavyGunFormId)) { return "HeavyGun"; }

			else if (HasKeyword(weapon, KeywordWeaponTypeRifleFormId)) { return "Rifle"; }
			else if (HasKeyword(weapon, KeywordWeaponTypePistolFormId)) { return "Pistol"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsGripPistolFormId)) { return "Pistol"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnims44FormId)) { return "Pistol"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsFlareGunFormId)) { return "Pistol"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsDelivererFormId)) { return "Pistol"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAutomaticFormId)) { return "Automatic"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsMinigunFormId)) { return "Automatic"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsSubmachineGunFormId)) { return "Automatic"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsMineFormId)) { return "Mine"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeBallisticFormId)) { return "Ballistic"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeRipperFormId)) { return "Ripper"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeShishkebabFormId)) { return "Shishkebab"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeMineFormId)) { return "Mine"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeGrenadeFormId)) { return "Grenade"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeThrownFormId)) { return "Thrown"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeExplosiveFormId)) { return "Explosive"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeMelee1HFormId)) { return "Melee1H"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsAssBladeModFormId)) { return "Melee1H"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnims1HMShortFormId)) { return "Melee1H"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnims1HMFormId)) { return "Melee1H"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeMelee2HFormId)) { return "Melee2H"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnims2HMFormId)) { return "Melee2H"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnims2HMWideFormId)) { return "Melee2H"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeAnimsUnarmedFormId) || HasKeyword(weapon, KeywordWeaponTypeUnarmedFormId)) { return "Unarmed"; }
			else if (HasKeyword(weapon, KeywordWeaponTypeHandToHandFormId)) { return "HandToHand"; }
		}

		if (instanceData)
		{
			switch (instanceData->animationType)
			{
			case TESObjectWEAP::kWeaponAnimationType_Hand_To_Hand_Melee:
				return "HandToHand";
				break;
			case TESObjectWEAP::kWeaponAnimationType_Mine:
				return "Mine";
				break;
			case TESObjectWEAP::kWeaponAnimationType_Grenade:
				return "Grenade";
				break;
			case TESObjectWEAP::kWeaponAnimationType_Gun:
				return "Gun";
				break;
			case TESObjectWEAP::kWeaponAnimationType_One_Hand_Sword:
			case TESObjectWEAP::kWeaponAnimationType_One_Hand_Axe:
			case TESObjectWEAP::kWeaponAnimationType_One_Hand_Mace:
			case TESObjectWEAP::kWeaponAnimationType_One_Hand_Dagger:
				return "Melee1H";
				break;
			case TESObjectWEAP::kWeaponAnimationType_Two_Hand_Sword:
			case TESObjectWEAP::kWeaponAnimationType_Two_Hand_Axe:
				return "Melee2H";
				break;
			default:
				return "NoWeapon";
				break;
			}
		}
		return "NoWeapon";
	}

	bool GetEquippedArmorFormPowerArmor(Actor* actor)
	{
		if (actor->equipData)
		{
			auto slots = { 0xB, 0x3, 0x6 };
			for (UInt32 slotId : slots)
			{
				if (actor->equipData->slots[slotId].item != nullptr)
				{
					TESForm* equippedForm = actor->equipData->slots[slotId].item;
					if (equippedForm)
					{
						if (equippedForm->formType == TESObjectARMO::kTypeID)
						{
							TESObjectARMO* armor = DYNAMIC_CAST(equippedForm, TESForm, TESObjectARMO);
							if (HasKeyword(armor, KeywordArmorTypePoweredFormId))
							{
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	TESObjectWEAP* GetEquippedWeaponForm(Actor* actor)
	{
		if (actor->equipData)
		{
			auto slots = { 0x20, 0x21, 0x25, 0x29 };
			for (UInt32 slotId : slots)
			{
				if (actor->equipData->slots[slotId].item != nullptr)
				{
					TESForm* equippedForm = actor->equipData->slots[slotId].item;
					if (equippedForm)
					{
						if (equippedForm->formType == TESObjectWEAP::kTypeID)
						{
							return DYNAMIC_CAST(equippedForm, TESForm, TESObjectWEAP);
						}
					}
				}
			}
		}
		return nullptr;
	}

	TESObjectWEAP::InstanceData* GetEquippedWeaponInstanceData(Actor* actor)
	{
		if (actor->equipData)
		{
			auto slots = { 0x20, 0x21, 0x25, 0x29 };
			for (UInt32 slotId : slots)
			{
				if (actor->equipData->slots[slotId].item != nullptr)
				{
					TESForm* equippedForm = actor->equipData->slots[slotId].item;
					if (equippedForm)
					{
						if (equippedForm->formType == TESObjectWEAP::kTypeID)
						{
							return (TESObjectWEAP::InstanceData*)(actor->equipData->slots[slotId].instanceData);
						}
					}
				}
			}
		}
		return nullptr;
	}

	bool UnArmedFeedback(std::string feedbackType)
	{
		if ((feedbackType == "Unarmed")
			|| (feedbackType == "UnarmedAnimal")
			|| (feedbackType == "UnarmedBug")
			|| (feedbackType == "UnarmedCreature")
			|| (feedbackType == "UnarmedSuperMutant")
			|| (feedbackType == "UnarmedDog")
			|| (feedbackType == "UnarmedMolerat")
			|| (feedbackType == "UnarmedDeathclaw")
			|| (feedbackType == "UnarmedMirelurk")
			|| (feedbackType == "UnarmedRadScorpion")
			|| (feedbackType == "UnarmedFeralGhoul")
			|| (feedbackType == "UnarmedRadStag")
			|| (feedbackType == "UnarmedRobot"))
		{
			return true;
		}

		return false;
	}

	bool ContinuousFeedback(std::string feedbackType)
	{
		if ((feedbackType == "Flame")
			|| (feedbackType == "Frost")
			|| (feedbackType == "FireDamage")
			|| (feedbackType == "FrostDamage")
			|| (feedbackType == "PoisonDamage")
			|| (feedbackType == "RadiationDamage")
			|| (feedbackType == "EnergyDamage")
			|| (feedbackType == "ElectricDamage")
			|| (feedbackType == "MagicDamage"))
		{
			//Add some randomization
			int ran = randomGenerator(0, 5);
			if (ran <= 2)
			{
				return true;
			}
		}
		return false;
	}

	bool OnlyMeleeFeedback(std::string feedbackType)
	{
		if ((feedbackType == "Melee1H")
			|| (feedbackType == "Melee2H")
			|| (feedbackType == "Ripper")
			|| (feedbackType == "Shishkebab")
			|| (feedbackType == "MeleeHead"))
		{
			return true;
		}
		return false;
	}

	bool MeleeFeedback(std::string feedbackType)
	{
		if ((feedbackType == "Melee1H")
			|| (feedbackType == "Melee2H")
			|| (feedbackType == "Ripper")
			|| (feedbackType == "Shishkebab")
			|| (feedbackType == "MeleeHead")
			|| (feedbackType == "PlayerMeleeAttack")
			|| (feedbackType == "PlayerMeleePowerAttack")
			|| (feedbackType == "PlayerBash")
			|| (feedbackType == "PlayerBlock")
			|| (feedbackType == "HandToHand")
			|| (feedbackType == "HandToHandHead")
			|| (feedbackType == "PlayerHandToHand")
			|| (feedbackType == "Unarmed")
			|| (feedbackType == "UnarmedAnimal")
			|| (feedbackType == "UnarmedBug")
			|| (feedbackType == "UnarmedCreature")
			|| (feedbackType == "UnarmedSuperMutant")
			|| (feedbackType == "UnarmedDog")
			|| (feedbackType == "UnarmedMolerat")
			|| (feedbackType == "UnarmedDeathclaw")
			|| (feedbackType == "UnarmedMirelurk")
			|| (feedbackType == "UnarmedRadScorpion")
			|| (feedbackType == "UnarmedFeralGhoul")
			|| (feedbackType == "UnarmedRadStag")
			|| (feedbackType == "UnarmedRobot"))
		{
			return true;
		}

		return false;
	}

	bool GunFeedback(std::string feedbackType)
	{
		if ((feedbackType == "Gun")
			|| (feedbackType == "AlienBlaster")
			|| (feedbackType == "Automatic")
			|| (feedbackType == "Ballistic")
			|| (feedbackType == "HeavyGun")
			|| (feedbackType == "Flame")
			|| (feedbackType == "Frost")
			|| (feedbackType == "Rocket")
			|| (feedbackType == "Laser")
			|| (feedbackType == "Rifle")
			|| (feedbackType == "Pistol")
			|| (feedbackType == "Plasma")
			|| (feedbackType == "Shotgun")
			|| (feedbackType == "EnergyGun")
			|| (feedbackType == "PlayerAlienBlaster")
			|| (feedbackType == "PlayerAutomatic")
			|| (feedbackType == "PlayerBallistic")
			|| (feedbackType == "PlayerEnergyGun")
			|| (feedbackType == "PlayerGun")
			|| (feedbackType == "PlayerHeavyGun")
			|| (feedbackType == "PlayerLaser")
			|| (feedbackType == "PlayerPistol")
			|| (feedbackType == "PlayerPlasma")
			|| (feedbackType == "PlayerRifle")
			|| (feedbackType == "PlayerShotgun")
			|| (feedbackType == "PlayerFlamer")
			|| (feedbackType == "PlayerCryolator")
			|| (feedbackType == "PlayerMiniGun")
			|| (feedbackType == "PlayerMissileLauncher")
			|| (feedbackType == "PlayerBroadsider")
			|| (feedbackType == "PlayerFatman")
			|| (feedbackType == "PlayerJunkJet")
			|| (feedbackType == "LeftHandPistolShoot")
			|| (feedbackType == "RightHandPistolShoot")
			|| (feedbackType == "LeftHandRifleShoot")
			|| (feedbackType == "RightHandRifleShoot")
			|| (feedbackType == "LeftHandShotgunShoot")
			|| (feedbackType == "RightHandShotgunShoot"))
		{
			return true;
		}

		return false;
	}
	
	std::string DecideKickbackFeedbackTypeFromPlayer(TESObjectWEAP* weapon)
	{
		if (HasKeyword(weapon, KeywordWeaponTypeRifleFormId)) { return isLeftHand ? "LeftKickback" : "RightKickback"; }
		else if (HasKeyword(weapon, KeywordWeaponTypeGaussRifleFormId)) { return isLeftHand ? "LeftKickback" : "RightKickback"; }
		else if (HasKeyword(weapon, KeywordWeaponTypeAssaultRifleFormId)) { return isLeftHand ? "LeftKickback" : "RightKickback"; }
		else if ((weapon->equipType.equipSlot) && (weapon->equipType.equipSlot->formID == 0x13F45 || weapon->equipType.equipSlot->formID == 0x4334D)) { return isLeftHand ? "LeftKickback" : "RightKickback"; }
		else
		{
			return "NoFeedback";
		}
	}

	std::string DecideWeaponFeedbackTypeFromPlayer(std::string weaponType)
	{
		if (weaponType == "AlienBlaster")
		{
			//return isLeftHand ? "LeftAlienBlaster" : "RightAlienBlaster";
			return isLeftHand ? "LeftHandPistolShoot" : "RightHandPistolShoot";
		}
		else if (weaponType == "Automatic")
		{
			//return isLeftHand ? "LeftAutomatic" : "RightAutomatic";
			return isLeftHand ? "LeftHandRifleShoot" : "RightHandRifleShoot";
		}
		else if (weaponType == "Ballistic")
		{
			//return isLeftHand ? "LeftBallistic" : "RightBallistic";
			return isLeftHand ? "LeftHandPistolShoot" : "RightHandPistolShoot";
		}
		else if (weaponType == "EnergyGun")
		{
			//return isLeftHand ? "LeftEnergyGun" : "RightEnergyGun";
			return isLeftHand ? "LeftHandPistolShoot" : "RightHandPistolShoot";
		}
		else if (weaponType == "Gun")
		{
			//return isLeftHand ? "LeftGun" : "RightGun";
			return isLeftHand ? "LeftHandPistolShoot" : "RightHandPistolShoot";
		}
		else if (weaponType == "HandToHand")
		{
			//return isLeftHand ? "LeftHandToHand" : "RightHandToHand";
			return isLeftHand ? "LeftHandMeleeHit" : "RightHandMeleeHit";
		}
		else if (weaponType == "Flamer")
		{
			//return isLeftHand ? "LeftFlamer" : "RightFlamer";
			return isLeftHand ? "LeftHandRifleShoot" : "RightHandRifleShoot";
		}
		else if (weaponType == "Cryolator")
		{
			//return isLeftHand ? "LeftCryolator" : "RightCryolator";
			return isLeftHand ? "LeftHandPistolShoot" : "RightHandPistolShoot";
		}
		else if (weaponType == "MiniGun")
		{
			//return isLeftHand ? "LeftMiniGun" : "RightMiniGun";
			return isLeftHand ? "LeftHandShotgunShoot" : "RightHandShotgunShoot";
		}
		else if (weaponType == "MissileLauncher")
		{
			//return isLeftHand ? "LeftMissileLauncher" : "RightMissileLauncher";
			return isLeftHand ? "LeftHandShotgunShoot" : "RightHandShotgunShoot";
		}
		else if (weaponType == "Broadsider")
		{
			//return isLeftHand ? "LeftBroadsider" : "RightBroadsider";
			return isLeftHand ? "LeftHandShotgunShoot" : "RightHandShotgunShoot";
		}
		else if (weaponType == "Fatman")
		{
			//return isLeftHand ? "LeftFatman" : "RightFatman";
			return isLeftHand ? "LeftHandShotgunShoot" : "RightHandShotgunShoot";
		}
		else if (weaponType == "JunkJet")
		{
			//return isLeftHand ? "LeftJunkJet" : "RightJunkJet";
			return isLeftHand ? "LeftHandShotgunShoot" : "RightHandShotgunShoot";
		}
		else if (weaponType == "HeavyGun")
		{
			//return isLeftHand ? "LeftHeavyGun" : "RightHeavyGun";
			return isLeftHand ? "LeftHandShotgunShoot" : "RightHandShotgunShoot";
		}
		else if (weaponType == "Laser")
		{
			//return isLeftHand ? "LeftLaser" : "RightLaser";
			return isLeftHand ? "LeftHandPistolShoot" : "RightHandPistolShoot";
		}
		else if ((weaponType == "Melee1H")
			|| (weaponType == "Melee2H")
			|| (weaponType == "Ripper")
			|| (weaponType == "Shishkebab"))
		{
			//return isLeftHand ? "LeftMeleeAttack" : "RightMeleeAttack";
			return isLeftHand ? "LeftHandMeleeHit" : "RightHandMeleeHit";
		}
		else if (weaponType == "Pistol")
		{
			//return isLeftHand ? "LeftPistol" : "RightPistol";
			return isLeftHand ? "LeftHandPistolShoot" : "RightHandPistolShoot";
		}
		else if (weaponType == "Plasma")
		{
			//return isLeftHand ? "LeftPlasma" : "RightPlasma";
			return isLeftHand ? "LeftHandPistolShoot" : "RightHandPistolShoot";
		}
		else if (weaponType == "Rifle")
		{
			//return isLeftHand ? "LeftRifle" : "RightRifle";
			return isLeftHand ? "LeftHandRifleShoot" : "RightHandRifleShoot";
		}
		else if (weaponType == "Shotgun")
		{
			//return isLeftHand ? "LeftShotgun" : "RightShotgun";
			return isLeftHand ? "LeftHandShotgunShoot" : "RightHandShotgunShoot";
		}
		else if (weaponType == "Unarmed")
		{
			//return isLeftHand ? "LeftUnarmed" : "RightUnarmed";
			return isLeftHand ? "LeftHandMeleeHit" : "RightHandMeleeHit";
		}
		return "NoFeedback";
	}

	std::string DecideWeaponReloadFeedbackTypeFromPlayer(TESObjectWEAP* weapon, std::string weaponType)
	{
		if (weapon)
		{
			std::string feedback = DecideWeaponFeedbackTypeFromPlayer(weaponType);
			if (GunFeedback(feedback))
			{
				if (isLeftHand)
				{
					return "LeftDownReload";
				}
				else
				{
					return "RightDownReload";
				}
			}

			/*if (HasKeyword(weapon, KeywordWeaponTypeAnimsLaserMusketFormId)) 
			{ 
				return "PlayerReloadCharging"; 
			}
			else
			{
				std::string feedback = DecideWeaponFeedbackTypeFromPlayer(weaponType);
				if (GunFeedback(feedback))
				{
					if (isLeftHand)
					{
						return "LeftDownReload";
					}
					else
					{
						return "RightDownReload";
					}
				}
			}*/
		}
		return "NoFeedback";
	}

	std::string DecideExplosionEnchantmentFeedbackType(BGSExplosion* explosion)
	{
		if (explosion)
		{
			if (explosion->formID == 0x15FF5E
				|| explosion->formID == 0x1E55DA
				|| explosion->formID == 0x1E55D8
				|| explosion->formID == 0x16FC23
				|| explosion->formID == 0x165597
				|| explosion->formID == 0x1E55D7)
			{
				return "FlashForward";
			}

			if (explosion->enchantment.enchantment)
			{
				for (UInt32 i = 0; i < explosion->enchantment.enchantment->effectItemList.count; i++)
				{
					if (explosion->enchantment.enchantment->effectItemList[i] && explosion->enchantment.enchantment->effectItemList[i]->mgef)
					{
						if ((explosion->enchantment.enchantment->effectItemList[i]->mgef->flags & EffectSetting::kEffectType_Hostile) == EffectSetting::kEffectType_Hostile)
						{
							if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88)
							{
								if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88 == FireResistAVI)
								{
									return "EnvironmentalFire";
								}
								else if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88 == EnergyResistAVI)
								{
									return "EnvironmentalEnergy";
								}
								else if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88 == ElectricResistAVI)
								{
									return "EnvironmentalElectric";
								}
								else if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88 == FrostResistAVI)
								{
									return "EnvironmentalFrost";
								}
								else if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88 == PoisonResistAVI)
								{
									return "EnvironmentalPoison";
								}
								else if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88 == RadResistExposureAVI)
								{
									return "EnvironmentalRadiation";
								}
								else if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88 == RadResistIngestionAVI)
								{
									return "EnvironmentalRadiation";
								}
								else if (explosion->enchantment.enchantment->effectItemList[i]->mgef->actorValInfo88 == MagicResistAVI)
								{
									return "EnvironmentalMagic";
								}
							}
						}
					}
				}
			}

			if (explosion->data.impactPlacedObject)
			{
				if (explosion->data.impactPlacedObject->formType == BGSExplosion::kTypeID)
				{
					BGSExplosion* explosion2 = DYNAMIC_CAST(explosion->data.impactPlacedObject, TESObjectREFR, BGSExplosion);

					if (explosion2)
					{
						return DecideExplosionEnchantmentFeedbackType(explosion2);
					}
				}
				else if (explosion->data.impactPlacedObject->formType == BGSHazard::kTypeID)
				{
					BGSHazard* hazard = (BGSHazard*)explosion->data.impactPlacedObject;

					if (hazard)
					{
						if (hazard->unk80.spell)
						{
							return DecideMagicFeedbackType(hazard->unk80.spell);
						}
					}
				}
			}
		}
		return "NoFeedback";
	}

	std::string DecideEffectFeedbackType(EffectSetting* effect)
	{
		if (effect)
		{
			if ((effect->flags & EffectSetting::kEffectType_Hostile) == EffectSetting::kEffectType_Hostile)
			{
				if (effect->actorValInfo88)
				{
					if (effect->actorValInfo88 == FireResistAVI)
					{
						return "EnvironmentalFire";
					}
					else if (effect->actorValInfo88 == EnergyResistAVI)
					{
						return "EnvironmentalEnergy";
					}
					else if (effect->actorValInfo88 == ElectricResistAVI)
					{
						return "EnvironmentalElectric";
					}
					else if (effect->actorValInfo88 == FrostResistAVI)
					{
						return "EnvironmentalFrost";
					}
					else if (effect->actorValInfo88 == PoisonResistAVI)
					{
						return "EnvironmentalPoison";
					}
					else if (effect->actorValInfo88 == RadResistExposureAVI)
					{
						return "EnvironmentalRadiation";
					}
					else if (effect->actorValInfo88 == RadResistIngestionAVI)
					{
						return "EnvironmentalRadiation";
					}
					else if (effect->actorValInfo88 == MagicResistAVI)
					{
						return "EnvironmentalMagic";
					}
				}
			}
		}
		return "NoFeedback";
	}

	std::string DecideWeaponEnchantmentFeedbackType(TESObjectWEAP::InstanceData* instanceData, TESObjectWEAP* weapon)
	{
		if (instanceData && instanceData->enchantments)
		{
			for (UInt32 j = 0; j < instanceData->enchantments->count; j++)
			{
				EnchantmentItem* enchantment = instanceData->enchantments->entries[j];
				if (enchantment)
				{
					for (UInt32 i = 0; i < enchantment->effectItemList.count; i++)
					{
						if (enchantment->effectItemList[i] && enchantment->effectItemList[i]->mgef)
						{
							if ((enchantment->effectItemList[i]->mgef->flags & EffectSetting::kEffectType_Hostile) == EffectSetting::kEffectType_Hostile)
							{
								if (enchantment->effectItemList[i]->mgef->actorValInfo88)
								{
									if (enchantment->effectItemList[i]->mgef->actorValInfo88 == FireResistAVI)
									{
										return "FireDamage";
									}
									else if (enchantment->effectItemList[i]->mgef->actorValInfo88 == EnergyResistAVI)
									{
										return "EnergyDamage";
									}
									else if (enchantment->effectItemList[i]->mgef->actorValInfo88 == ElectricResistAVI)
									{
										return "ElectricDamage";
									}
									else if (enchantment->effectItemList[i]->mgef->actorValInfo88 == FrostResistAVI)
									{
										return "FrostDamage";
									}
									else if (enchantment->effectItemList[i]->mgef->actorValInfo88 == PoisonResistAVI)
									{
										return "PoisonDamage";
									}
									else if (enchantment->effectItemList[i]->mgef->actorValInfo88 == RadResistExposureAVI)
									{
										return "RadiationDamage";
									}
									else if (enchantment->effectItemList[i]->mgef->actorValInfo88 == RadResistIngestionAVI)
									{
										return "RadiationDamage";
									}
									else if (enchantment->effectItemList[i]->mgef->actorValInfo88 == MagicResistAVI)
									{
										return "MagicDamage";
									}
								}
							}
						}
					}
				}
			}
		}

		if (weapon)
		{
			if (weapon->enchantable.enchantment)
			{
				for (UInt32 i = 0; i < weapon->enchantable.enchantment->effectItemList.count; i++)
				{
					if (weapon->enchantable.enchantment->effectItemList[i] && weapon->enchantable.enchantment->effectItemList[i]->mgef)
					{
						if ((weapon->enchantable.enchantment->effectItemList[i]->mgef->flags & EffectSetting::kEffectType_Hostile) == EffectSetting::kEffectType_Hostile)
						{
							if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88)
							{
								if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88 == FireResistAVI)
								{
									return "FireDamage";
								}
								else if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88 == EnergyResistAVI)
								{
									return "EnergyDamage";
								}
								else if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88 == ElectricResistAVI)
								{
									return "ElectricDamage";
								}
								else if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88 == FrostResistAVI)
								{
									return "FrostDamage";
								}
								else if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88 == PoisonResistAVI)
								{
									return "PoisonDamage";
								}
								else if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88 == RadResistExposureAVI)
								{
									return "RadiationDamage";
								}
								else if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88 == RadResistIngestionAVI)
								{
									return "RadiationDamage";
								}
								else if (weapon->enchantable.enchantment->effectItemList[i]->mgef->actorValInfo88 == MagicResistAVI)
								{
									return "MagicDamage";
								}
							}
						}
					}
				}
			}
		}
		return "NoFeedback";
	}

	///Decides which type of magic feedback type it is
	std::string DecideEnchantmentFeedbackType(EnchantmentItem* spell)
	{
		bool hostile = false;
		if (spell)
		{
			for (UInt32 i = 0; i < spell->effectItemList.count; i++)
			{
				if (spell->effectItemList[i] && spell->effectItemList[i]->mgef)
				{
					if ((spell->effectItemList[i]->mgef->flags & EffectSetting::kEffectType_Hostile) == EffectSetting::kEffectType_Hostile)
					{
						hostile = true;
						if (spell->effectItemList[i]->mgef->actorValInfo88)
						{
							if (spell->effectItemList[i]->mgef->actorValInfo88 == FireResistAVI)
							{
								return "FireDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == EnergyResistAVI)
							{
								return "EnergyDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == ElectricResistAVI)
							{
								return "ElectricDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == FrostResistAVI)
							{
								return "FrostDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == PoisonResistAVI)
							{
								return "PoisonDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == RadResistExposureAVI)
							{
								return "RadiationDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == RadResistIngestionAVI)
							{
								return "RadiationDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == MagicResistAVI)
							{
								return "MagicDamage";
							}
						}
					}
				}
			}
		}

		return "NoFeedback";
	}

	std::string DecideWeaponMagicFeedbackType(SpellItem* spell)
	{
		bool hostile = false;
		if (spell)
		{
			if (spell->formID == CritFireSpellFormId)
			{
				return "FireDamage";
			}
			else if (spell->formID == CritCryoSpellFormId)
			{
				return "FrostDamage";
			}
			else if (spell->formID == CritLaserSpellFormId)
			{
				return "EnergyDamage";
			}
			else if (spell->formID == CritLaserLtBlueSpellFormId)
			{
				return "EnergyDamage";
			}
			else if (spell->formID == CritMirelurkQueenSpellFormId)
			{
				return "PoisonDamage";
			}
			else if (spell->formID == CritPlasmaSpellFormId)
			{
				return "MagicDamage";
			}
			else if (spell->formID == TeleportInSpellFormId)
			{
				return "FlashForward";
			}
			else if (spell->formID == TeleportOutSpellFormId)
			{
				return "FlashForward";
			}
			else if (spell->formID == TeleportPlayerInSpellFormId)
			{
				return "FlashForward";
			}
			else if (spell->formID == TeleportPlayerOutSpellFormId)
			{
				return "FlashForward";
			}

			for (UInt32 i = 0; i < spell->effectItemList.count; i++)
			{
				if (spell->effectItemList[i] && spell->effectItemList[i]->mgef)
				{
					if ((spell->effectItemList[i]->mgef->flags & EffectSetting::kEffectType_Hostile) == EffectSetting::kEffectType_Hostile)
					{
						hostile = true;
						if (spell->effectItemList[i]->mgef->actorValInfo88)
						{
							if (spell->effectItemList[i]->mgef->actorValInfo88 == FireResistAVI)
							{
								return "FireDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == EnergyResistAVI)
							{
								return "EnergyDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == ElectricResistAVI)
							{
								return "ElectricDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == FrostResistAVI)
							{
								return "FrostDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == PoisonResistAVI)
							{
								return "PoisonDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == RadResistExposureAVI)
							{
								return "RadiationDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == RadResistIngestionAVI)
							{
								return "RadiationDamage";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == MagicResistAVI)
							{
								return "MagicDamage";
							}
						}
					}
				}
			}
		}

		return "NoFeedback";
	}

	///Decides which type of magic feedback type it is
	std::string DecideMagicFeedbackType(SpellItem* spell)
	{
		bool hostile = false;
		if (spell)
		{
			if (spell->formID == CritFireSpellFormId)
			{
				return "EnvironmentalFire";
			}
			else if (spell->formID == CritCryoSpellFormId)
			{
				return "EnvironmentalFrost";
			}
			else if (spell->formID == CritLaserSpellFormId)
			{
				return "EnvironmentalEnergy";
			}
			else if (spell->formID == CritLaserLtBlueSpellFormId)
			{
				return "EnvironmentalEnergy";
			}
			else if (spell->formID == CritMirelurkQueenSpellFormId)
			{
				return "EnvironmentalPoison";
			}
			else if (spell->formID == CritPlasmaSpellFormId)
			{
				return "EnvironmentalMagic";
			}
			else if (spell->formID == TeleportInSpellFormId)
			{
				return "FlashForward";
			}
			else if (spell->formID == TeleportOutSpellFormId)
			{
				return "FlashForward";
			}
			else if (spell->formID == TeleportPlayerInSpellFormId)
			{
				return "FlashForward";
			}
			else if (spell->formID == TeleportPlayerOutSpellFormId)
			{
				return "FlashForward";
			}

			for (UInt32 i = 0; i < spell->effectItemList.count; i++)
			{
				if (spell->effectItemList[i] && spell->effectItemList[i]->mgef)
				{
					if ((spell->effectItemList[i]->mgef->flags & EffectSetting::kEffectType_Hostile) == EffectSetting::kEffectType_Hostile)
					{
						hostile = true;
						if (spell->effectItemList[i]->mgef->actorValInfo88)
						{
							if (spell->effectItemList[i]->mgef->actorValInfo88 == FireResistAVI)
							{
								return "EnvironmentalFire";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == EnergyResistAVI)
							{
								return "EnvironmentalEnergy";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == ElectricResistAVI)
							{
								return "EnvironmentalElectric";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == FrostResistAVI)
							{
								return "EnvironmentalFrost";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == PoisonResistAVI)
							{
								return "EnvironmentalPoison";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == RadResistExposureAVI)
							{
								return "EnvironmentalRadiation";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == RadResistIngestionAVI)
							{
								return "EnvironmentalRadiation";
							}
							else if (spell->effectItemList[i]->mgef->actorValInfo88 == MagicResistAVI)
							{
								return "EnvironmentalMagic";
							}
						}
					}
				}
			}
		}

		_MESSAGE("Couldn't find the damage effect applied");
		if (hostile)
		{
			return "EnvironmentalOther";
		}
		else
		{
			return "NoFeedback";
		}
	}

	std::string DecideIngestibleFeedback(AlchemyItem* potion)
	{
		if (HasKeyword(potion, KeywordObjectTypeAlcohol))
		{
			//return "Alcohol";
			return "Drinking";
		}
		else if (HasKeyword(potion, KeywordObjectTypeExtraCaffeinated))
		{
			//return "ExtraCaffeinated";
			return "Drinking";
		}
		else if (HasKeyword(potion, KeywordObjectTypeCaffeinated))
		{
			//return "Caffeinated";
			return "Drinking";
		}
		else if (HasKeyword(potion, KeywordObjectTypeStimpak))
		{
			//return "Stimpak";
			return "Healing";
		}
		else if (HasKeyword(potion, KeywordObjectTypeSyringerAmmo))
		{
			//return "Syringe";
			return "Healing";
		}
		else if (HasKeyword(potion, KeywordObjectTypeChem))
		{
			//return "Chem";
			return "Healing";
		}
		else if (HasKeyword(potion, KeywordObjectTypeDrink)
			|| HasKeyword(potion, KeywordObjectTypeWater)
			|| HasKeyword(potion, KeywordAnimFurnWater))
		{
			return "Drinking";
		}
		else if (HasKeyword(potion, KeywordObjectTypeFood))
		{
			return "Eating";
		}
		else if (HasKeyword(potion, KeywordFruitOrVegetable)
			|| HasKeyword(potion, KeywordHCDiseaseRiskFoodHigh)
			|| HasKeyword(potion, KeywordHCDiseaseRiskFoodStandard)
			|| HasKeyword(potion, KeywordHCSustenanceTypeQuenchesThirst))
		{
			return "Eating";
		}
		else if (HasKeyword(potion, KeywordHCDiseaseRiskChem)
			|| HasKeyword(potion, KeywordHCSustenanceTypeIncreasesHunger)
			|| HasKeyword(potion, KeywordHCSustenanceTypeIncreasesThirst))
		{
			return "Healing";
		}

		return "Healing";
	}

	float distanceNoSqrt(NiPoint3 po1, NiPoint3 po2)
	{
		float x = po1.x - po2.x;
		float y = po1.y - po2.y;
		float z = po1.z - po2.z;
		float result = x * x + y * y + z * z;

		return result;
	}

	float distanceNoSqrt2d(NiPoint3 po1, NiPoint3 po2)
	{
		float x = po1.x - po2.x;
		float y = po1.y - po2.y;
		float result = x * x + y * y;

		return result;
	}

	EventResult WeaponFiredEventHandler::ReceiveEvent(WeaponFiredEvent* evn, void* dispatcher)
	{
		if (evn)
		{
			WeaponFiredEventNew* weaponFired = (WeaponFiredEventNew*)evn;

			if (evn && evn->source && evn->source->formID == 0x14 && weaponFired && weaponFired->proj1 != 0)
			{
				//DumpClass(evn, 100);
				//LOG("WeaponFiredEvent Source:%x", evn->source ? evn->source->formID : 0);
				if (evn->weapon != nullptr)
				{
					auto equippedWeapon = GetEquippedWeaponForm(*g_player);
					auto equippedWeaponData = GetEquippedWeaponInstanceData(*g_player);

					if (!equippedWeaponData && equippedWeapon)
					{
						equippedWeaponData = &equippedWeapon->weapData;
					}

					if (equippedWeapon && equippedWeaponData)
					{
						const std::string weaponType = DecideWeaponType(equippedWeaponData, equippedWeapon);

						if (weaponType != "NoWeapon")
						{
							_MESSAGE("Player fired weapon. Weapon Fire Effect %d", weaponType);

							const std::string feedback = DecideWeaponFeedbackTypeFromPlayer(weaponType);
							if (feedback != "NoFeedback")
							{
								//const FeedbackType kickback = DecideKickbackFeedbackTypeFromPlayer(equippedWeapon);

								//ProvideHapticFeedback(0, 0, feedback, FeedbackIntensity(feedback), leftHandedMode);
								_MESSAGE("---------------------------------------");
								_MESSAGE(feedback.c_str());
								Play(feedback);
							}
						}
					}
				}
			}
		}

		return kEvent_Continue;
	}
	WeaponFiredEventHandler g_WeaponFiredEventHandler;

	std::atomic<bool> playerReloadPlaying;

	void PlayerReloadPlay(std::string feedback)
	{
		if (!playerReloadPlaying.load())
		{
			playerReloadPlaying.store(true);
			_MESSAGE("Player reloaded weapon - Weapon Reload Effect");
			//ProvideHapticFeedback(0, 0, feedback, FeedbackIntensity(feedback), leftHandedMode);
			_MESSAGE("---------------------------------------");
			_MESSAGE(feedback.c_str());
			Play(feedback);
			Sleep(2000);
			playerReloadPlaying.store(false);
		}
	}

	EventResult PlayerWeaponReloadEventHandler::ReceiveEvent(PlayerWeaponReloadEvent* evn, void* dispatcher)
	{
		if (evn)
		{
			auto equippedWeapon = GetEquippedWeaponForm(*g_player);
			auto equippedWeaponData = GetEquippedWeaponInstanceData(*g_player);

			if (!equippedWeaponData && equippedWeapon)
			{
				equippedWeaponData = &equippedWeapon->weapData;
			}

			if (equippedWeapon && equippedWeaponData)
			{
				std::string weaponType = DecideWeaponType(equippedWeaponData, equippedWeapon);

				if (weaponType != "NoWeapon")
				{
					std::string feedback = DecideWeaponReloadFeedbackTypeFromPlayer(equippedWeapon, weaponType);
					std::thread t5(PlayerReloadPlay, feedback);
					t5.detach();
				}
			}
		}

		return kEvent_Continue;
	}
	PlayerWeaponReloadEventHandler g_PlayerWeaponReloadEventHandler;

	TESEquipEventHandler g_TESEquipEventHandler;

	EventResult TESEquipEventHandler::ReceiveEvent(TESEquipEvent* evn, void* dispatcher)
	{
		if (evn)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				return EventResult::kEvent_Continue;
			}

			if (evn->equip)
			{
				TESObjectREFR* playerref = DYNAMIC_CAST((*g_player), Actor, TESObjectREFR);

				if (playerref)
				{
					if (evn->ref && evn->ref == playerref)
					{
						_MESSAGE("TESEquipEvent FormId:%x equip:%s unk0C:%x pad10:%s", evn->FormID, evn->equip ? "true" : "false", evn->unk0C, evn->pad10);

						TESForm* item = LookupFormByID(evn->FormID);

						if (item != nullptr)
						{
							if (item->formType == TESObjectARMO::kTypeID)
							{
								TESObjectARMO* armor = DYNAMIC_CAST(item, TESForm, TESObjectARMO);

								if (armor)
								{
									if (HasKeyword(armor, KeywordPowerArmor) || HasKeyword(armor, KeywordPowerArmorFrame))
									{
										if (evn->equip)
										{
											//ProvideHapticFeedback(0, 0, FeedbackType::PowerArmorEnterVest, FeedbackIntensity(FeedbackType::PowerArmorEnterVest), false, true);

											_MESSAGE("---------------------------------------");
											_MESSAGE("EnterPowerArmor");
											Play("EnterPowerArmor");
											inPowerArmorFrame.store(true);
											powerArmorValueKnown.store(true);
											//LOG("Entered Power Armor Frame %x", armor->formID);
										}
									}
								}
							}
							else if (item->formType == AlchemyItem::kTypeID)
							{
								AlchemyItem* potion = DYNAMIC_CAST(item, TESForm, AlchemyItem);

								if (potion != nullptr)
								{
									const std::string feedback = DecideIngestibleFeedback(potion);
									if (feedback != "NoFeedback")
									{										
										//ProvideHapticFeedback(0, 0, feedback, FeedbackIntensity(feedback), false);

										_MESSAGE("---------------------------------------");
										_MESSAGE(feedback.c_str());
										Play(feedback);
									}
								}
							}
						}
					}
				}
			}
		}
		return EventResult::kEvent_Continue;
	}

	ContainerChangedEventHandler g_ContainerChangedEventHandler;

	EventResult ContainerChangedEventHandler::ReceiveEvent(TESContainerChangedEvent* evn, void* dispatcher)
	{
		if (evn)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				return EventResult::kEvent_Continue;
			}

			if (evn && evn->sourceID == 0x14 && evn->targetID == 0 && evn->formID != 0 && evn->refID == 0 && evn->uniqueID == 0 && evn->count <= 3)
			{
				_MESSAGE("Source:%x Target:%x FormId:%x RefId:%x UniqueId:%x Count:%d", evn->sourceID, evn->targetID, evn->formID, evn->refID, evn->uniqueID, evn->count);

				TESForm* item = LookupFormByID(evn->formID);

				if (item != nullptr)
				{
					if (item->formType == TESAmmo::kTypeID)
					{
						TESAmmo* ammo = DYNAMIC_CAST(item, TESForm, TESAmmo);

						if (ammo)
						{
							auto equippedWeapon = GetEquippedWeaponForm(*g_player);
							auto equippedWeaponData = GetEquippedWeaponInstanceData(*g_player);

							if (!equippedWeaponData && equippedWeapon)
							{
								equippedWeaponData = &equippedWeapon->weapData;
							}

							if (equippedWeapon && equippedWeaponData && equippedWeaponData->ammo == ammo)
							{
								std::string weaponType = DecideWeaponType(equippedWeaponData, equippedWeapon);

								if (weaponType != "NoWeapon")
								{
									_MESSAGE("Player fired weapon. Ammo type: %x. Weapon Fire Effect %d", item->formID, weaponType);

									std::string feedback = DecideWeaponFeedbackTypeFromPlayer(weaponType);

									_MESSAGE("---------------------------------------");
									_MESSAGE(feedback.c_str());
									Play(feedback);
									//ProvideHapticFeedback(0, 0, feedback, FeedbackIntensity(feedback) * evn->count, leftHandedMode);
								}
							}
						}
					}
				}
			}
		}

		return kEvent_Continue;
	}

	HitEventHandler g_HitEventHandler;

	EventResult HitEventHandler::ReceiveEvent(TESHitEvent* evn, void* dispatcher)
	{
		if (evn)
		{
			TESHitEventNew* hitEvent = (TESHitEventNew*)evn;

			TESObjectREFR* attacker = hitEvent->attacker;
			TESObjectREFR* target = hitEvent->target;

			if (!attacker)
			{
				LookupREFRByHandle(&hitEvent->attackerHandle, &attacker);
			}
			if (!target)
			{
				LookupREFRByHandle(&hitEvent->targetHandle, &target);
			}

			if (target && target->formID == 0x14)
			{
				_MESSAGE("Something hit player - attacker:%x, source:%x, target:%x", attacker ? attacker->formID : 0, hitEvent->source ? hitEvent->source->formID : hitEvent->sourceFormID, target ? target->formID : 0);
				Actor* targetActor = DYNAMIC_CAST(target, TESObjectREFR, Actor);

				if (targetActor)
				{
					float headingAngle = 0.0f;
					float heightdiff = 0.0f;
					float distance = 9999.0f;

					bool attackerIsNPC = false;
					bool attackerIsAnimal = false;

					//LOG("hitevent pos: %g %g %g", hitEvent->position.x, hitEvent->position.y, hitEvent->position.z);

					Actor* actor = nullptr;
					if (attacker)
					{
						actor = DYNAMIC_CAST(attacker, TESObjectREFR, Actor);

						if (actor && actor->loadedState)
						{
							if (!(actor->loadedState->node))
							{
								_MESSAGE("Actor main node is wrong");
							}
							if (!(targetActor->loadedState->node))
							{
								_MESSAGE("Player main node is wrong");
							}

							float heading = 0.0;
							float attitude = 0.0;
							float bank = 0.0;

							NiPoint3 position = actor->loadedState->node->m_worldTransform.pos;
							//LOG("attacker pos: %g %g %g", position.x, position.y, position.z);

							NiMatrix43 playerrotation = targetActor->loadedState->node->m_worldTransform.rot;
							playerrotation.GetEulerAngles(&heading, &attitude, &bank);
							NiPoint3 playerposition = targetActor->loadedState->node->m_worldTransform.pos;

							float playerHeading = heading * (180 / MATH_PI);

							float playerAttitude = attitude * (180 / MATH_PI);

							float calcPlayerHeading = 0.0;

							if (playerHeading == -180)
							{
								calcPlayerHeading = 180 - playerAttitude;
							}
							else
							{
								if (playerAttitude < 0)
								{
									calcPlayerHeading = 360 + playerAttitude;
								}
								else
								{
									calcPlayerHeading = playerAttitude;
								}
							}
							float angle = (std::atan2(position.y - playerposition.y, position.x - playerposition.x) - std::atan2(1, 0)) * (180 / MATH_PI);
							if (angle < 0) {
								angle = angle + 360;
							}

							headingAngle = angle - calcPlayerHeading;
							headingAngle = fmod(headingAngle,360);
							
							_MESSAGE("------------------------------------------------------");
							_MESSAGE("angle :%f , calcPlayerHeading :%f ,playerAttitude :%f ",angle,calcPlayerHeading,playerAttitude);

							if (headingAngle < 0)
								headingAngle += 360;
							else if (headingAngle > 360)
								headingAngle -= 360;

							//LOG("Attacker pos: %g, player pos: %g", position.z, playerposition.z);
							heightdiff = position.z - playerposition.z;
							distance = distanceNoSqrt(position, playerposition);

							attackerIsNPC = true;

							attackerIsAnimal = ActorCreature(actor);
						}
						else
						{
							_MESSAGE("Caster is not another npc. FormID: %d", attacker->formID);
						}
					}
					else
					{
						_MESSAGE("player attacked by other stuff");
					}

					bool unarmedAttack = false;
					bool blockedAttack = false;
					bool powerAttack = false;
					if (((hitEvent->flags & TESHitEventNew::kFlag_Blocked1) == TESHitEventNew::kFlag_Blocked1)
						|| ((hitEvent->flags & TESHitEventNew::kFlag_Blocked2) == TESHitEventNew::kFlag_Blocked2))
					{
						_MESSAGE("Attack is blocked by player.");
						blockedAttack = true;
					}
					else if (((hitEvent->flags & TESHitEventNew::kFlag_Bash1) == TESHitEventNew::kFlag_Bash1)
						|| ((hitEvent->flags & TESHitEventNew::kFlag_Bash2) == TESHitEventNew::kFlag_Bash2))
					{
						_MESSAGE("Attack is a bash attack.");
						unarmedAttack = true;
					}
					else if ((hitEvent->flags & TESHitEventNew::kFlag_PowerAttack) == TESHitEventNew::kFlag_PowerAttack)
					{
						_MESSAGE("Attack is a power attack.");
						unarmedAttack = true;
						powerAttack = true;
					}

					std::string feedback = "NoFeedback";
					std::string enchantmentFeedback = "NoFeedback";
					float reach = 1.0f;							
					bool additionalEnchantment = false;

					if (hitEvent->attackData)
					{
						if ((hitEvent->attackData->data.flags & AttackData::kChargeAttack) == AttackData::kChargeAttack)
						{
							_MESSAGE("Attack is a charge attack");
							unarmedAttack = true;
						}
						if ((hitEvent->attackData->data.flags & AttackData::kBashAttack) == AttackData::kBashAttack)
						{
							_MESSAGE("Attack is a bash attack");
							unarmedAttack = true;
						}
						if ((hitEvent->attackData->data.flags & AttackData::kIgnoreWeapon) == AttackData::kIgnoreWeapon)
						{
							_MESSAGE("Attack is a ignore weapon attack");
							unarmedAttack = true;
						}
						if ((hitEvent->attackData->data.flags & AttackData::kPowerAttack) == AttackData::kPowerAttack)
						{
							_MESSAGE("Attack is a power attack");
							unarmedAttack = true;
							powerAttack = true;
						}
						if ((hitEvent->attackData->data.flags & AttackData::kChargeAttack) != AttackData::kNone)
						{
							_MESSAGE("Attack is a left attack");
							unarmedAttack = true;
						}
					}

					if (blockedAttack)
					{
						feedback = "PlayerBlock";
					}
					else if (hitEvent->source || hitEvent->sourceFormID != 0)
					{
						TESForm* source = hitEvent->source;
						if (!source)
						{
							source = LookupFormByID(hitEvent->sourceFormID);
						}

						if (source)
						{
							_MESSAGE("There is a source for this hitevent: %x - FormType: %d", source->formID, source->formType);
							if (source->formType == SpellItem::kTypeID)
							{
								_MESSAGE("Source is a spell: %x", source->formID);
								SpellItem* spell = DYNAMIC_CAST(source, TESForm, SpellItem);

								if (spell)
								{
									_MESSAGE("spell:%x", spell->formID);

									//play spell vibration on vest
									_MESSAGE("spell vibration on vest");

									std::string feedbackType = DecideMagicFeedbackType(spell);

									if (feedbackType != "NoFeedback")
									{
										feedback = feedbackType;
									}
								}
							}
							else if (source->formType == TESObjectWEAP::kTypeID)
							{
								_MESSAGE("Source is a weapon: %x", source->formID);
								TESObjectWEAP* weapon = DYNAMIC_CAST(source, TESForm, TESObjectWEAP);

								TESObjectWEAP::InstanceData* instanceData = nullptr;

								if (hitEvent->sourceInstanceData)
								{
									instanceData = ((TESObjectWEAP::InstanceData*)(hitEvent->sourceInstanceData));
								}
								else if (weapon)
								{
									instanceData = &weapon->weapData;
								}

								if (instanceData)
								{
									reach = instanceData->reach;
								}

								enchantmentFeedback = DecideWeaponEnchantmentFeedbackType(instanceData, weapon);

								std::string weaponType = DecideWeaponType(instanceData, weapon);

								

								if (weaponType != "NoWeapon")
								{
									feedback = weaponType;
								}

								if (!UnArmedFeedback(feedback) && !GunFeedback(feedback))
								{
									if (instanceData && instanceData->spell)
									{
										_MESSAGE("Weapon has a spell in instancedata: %x", instanceData->spell->formID);
										enchantmentFeedback = DecideMagicFeedbackType(instanceData->spell);
									}
									else if (weapon->formID == 0xFF21F || weapon->formID == 0x18325E)
									{
										enchantmentFeedback = "EnvironmentalElectric";
									}
								}
								else
								{
									if (instanceData && instanceData->spell)
									{
										_MESSAGE("Weapon has a spell in instancedata: %x", instanceData->spell->formID);
										enchantmentFeedback = DecideWeaponMagicFeedbackType(instanceData->spell);
									}
								}

								if (enchantmentFeedback != "NoFeedback"
									&& feedback != "Explosive"
									&& feedback != "Grenade"
									&& feedback != "Mine"
									&& feedback != "Thrown"
									&& feedback != "Gun"
									&& feedback != "Default")
								{
									additionalEnchantment = true;
								}
								else if (enchantmentFeedback != "NoFeedback")
								{
									feedback = "Ignore";
								}

								if (actor && feedback == "Unarmed" && attackerIsAnimal)
								{
									feedback = UnarmedTypeAnimal(actor);
								}
							}
							else if (source->formType == BGSExplosion::kTypeID)
							{
								_MESSAGE("Source is an explosion: %x", source->formID);

								BGSExplosion* explosion = DYNAMIC_CAST(source, TESForm, BGSExplosion);
								if (explosion)
								{
									enchantmentFeedback = DecideExplosionEnchantmentFeedbackType(explosion);

									feedback = "Ignore";
								}
							}
							else if (source->formType == BGSHazard::kTypeID)
							{
								BGSHazard* hazard = DYNAMIC_CAST(source, TESForm, BGSHazard);

								if (hazard)
								{
									if (hazard->unk80.spell)
									{
										enchantmentFeedback = DecideMagicFeedbackType(hazard->unk80.spell);
										feedback = "Ignore";
									}
								}
							}
							else if (source->formType == EnchantmentItem::kTypeID)
							{
								EnchantmentItem* ench = DYNAMIC_CAST(source, TESForm, EnchantmentItem);

								if (ench)
								{
									_MESSAGE("Enchantment effect %x", ench->formID);
									enchantmentFeedback = DecideEnchantmentFeedbackType(ench);

									feedback = "Ignore";
								}
							}
							else
							{
								_MESSAGE("Source is an unknown type: %x -> Type: %d", source->formID, source->formType);
							}
						}
					}

					int heightrand = randomGenerator(0, 1000);
					heightdiff = ((float)heightrand / 1000.0f) - 0.5f;

					if (unarmedAttack)
					{
						if (GunFeedback(feedback))
						{
							feedback = "Unarmed";
							enchantmentFeedback = "NoFeedback";
						}
					}
					bool continuous = ContinuousFeedback(feedback);

					bool gunFeedbackPlayed = false;
					if (feedback != "Ignore")
					{
						if (feedback != "NoFeedback")
						{
							
							if (GunFeedback(feedback))
							{
								gunFeedbackPlayed = true;
							}

							//ProvideHapticFeedback(headingAngle, heightdiff, feedback, FeedbackIntensity(feedback) * damageMultiplier, false, continuous ? true : false);
							_MESSAGE("---------------------------------------"); 
							std::string message = feedback + "," + std::to_string(headingAngle) + "," + std::to_string(heightdiff);
							_MESSAGE(message.c_str());
							PlayAngle("PlayerBulletDamage", headingAngle, heightdiff);
						}
						else
						{
							if (!attackerIsNPC)
							{
								//ProvideHapticFeedback(0, 0, "Default", FeedbackIntensity("Default) * damageMultiplier, false);
								_MESSAGE("---------------------------------------");
								_MESSAGE("FallDamage");
								Play("FallDamage");
							}
							else
							{
								if (attackerIsAnimal)
								{
									if (actor)
									{
										feedback = UnarmedTypeAnimal(actor);
									}
									else
									{
										feedback = "HandToHand";
									}
									//ProvideHapticFeedback(headingAngle, heightdiff, feedback, FeedbackIntensity(feedback) * damageMultiplier, false);
									_MESSAGE("---------------------------------------");
									std::string message = feedback + "," + std::to_string(headingAngle) + "," + std::to_string(heightdiff);
									_MESSAGE(message.c_str());
									PlayAngle("BodyDamage", headingAngle, heightdiff);
								}
								else
								{
									//ProvideHapticFeedback(headingAngle, heightdiff, "Melee1H, FeedbackIntensity("Melee1H) * damageMultiplier, false);
									_MESSAGE("---------------------------------------");
									std::string message = "DefaultDamage," + std::to_string(headingAngle) + "," + std::to_string(heightdiff);
									_MESSAGE(message.c_str());
									PlayAngle("DefaultDamage",headingAngle,heightdiff);
								}
							}
						}
					}
					if (enchantmentFeedback != "NoFeedback")
					{
						
						//ProvideHapticFeedback(headingAngle, heightdiff, enchantmentFeedback, FeedbackIntensity(enchantmentFeedback) * damageMultiplier, false, continuous ? true : false);
						_MESSAGE("---------------------------------------");
						std::string message = enchantmentFeedback + "," + std::to_string(headingAngle) + "," + std::to_string(heightdiff);
						_MESSAGE(message.c_str());
						PlayAngle("DefaultDamage", headingAngle, heightdiff);
					}
				}
			}
			else if (attacker && attacker->formID == 0x14)
			{
				_MESSAGE("Player Hit something - attacker:%x, source:%x, target:%x", attacker ? attacker->formID : 0, hitEvent->source ? hitEvent->source->formID : hitEvent->sourceFormID, target ? target->formID : 0);

				TESObjectWEAP::InstanceData* instanceData = nullptr;
				TESObjectWEAP* weapon = nullptr;

				if (hitEvent->source)
				{
					weapon = DYNAMIC_CAST(hitEvent->source, TESForm, TESObjectWEAP);
				}

				if (hitEvent->source || hitEvent->sourceFormID != 0)
				{
					TESForm* source = hitEvent->source;
					if (!source)
					{
						source = LookupFormByID(hitEvent->sourceFormID);
					}

					if (source)
					{
						_MESSAGE("There is a source for this hitevent: %x - FormType: %d", source->formID, source->formType);
						if (source->formType == SpellItem::kTypeID)
						{
							_MESSAGE("Source is a spell: %x", source->formID);

							if (source->formID == PainTrainKnockbackSpellFormId)
							{
								//ProvideHapticFeedback(0, 0, FeedbackType::PlayerPainTrainCharge, FeedbackIntensity(FeedbackType::PlayerPainTrainCharge), false, true);
								
								_MESSAGE("---------------------------------------");
								_MESSAGE("PlayerPainTrainCharge");
								Play("PlayerPainTrainCharge");
								return EventResult::kEvent_Continue;
							}
						}
						else if (source->formType == TESObjectWEAP::kTypeID)
						{
							_MESSAGE("Source is a weapon: %x", source->formID);
							weapon = DYNAMIC_CAST(source, TESForm, TESObjectWEAP);

							if (hitEvent->sourceInstanceData)
							{
								instanceData = ((TESObjectWEAP::InstanceData*)(hitEvent->sourceInstanceData));
							}
							else if (weapon)
							{
								instanceData = &weapon->weapData;
							}

							/*if (instanceData && instanceData->spell)
							{
								LOG("Weapon has a spell in instancedata: %x", instanceData->spell->formID);
							}*/
						}
						else if (source->formType == BGSExplosion::kTypeID)
						{
							_MESSAGE("Source is an explosion: %x", source->formID);
						}
						else
						{
							_MESSAGE("Source is an unknown type: %x -> Type: %d", source->formID, source->formType);
						}
					}
				}

				if (((hitEvent->flags & TESHitEventNew::kFlag_Bash1) == TESHitEventNew::kFlag_Bash1)
					|| ((hitEvent->flags & TESHitEventNew::kFlag_Bash2) == TESHitEventNew::kFlag_Bash2))
				{
					_MESSAGE("Flag: Attack is a bash attack.");
				}
				else if ((hitEvent->flags & TESHitEventNew::kFlag_PowerAttack) == TESHitEventNew::kFlag_PowerAttack)
				{
					_MESSAGE("Flag: Attack is a power attack.");
				}

				if (hitEvent->attackData)
				{
					if ((hitEvent->attackData->data.flags & AttackData::kChargeAttack) == AttackData::kChargeAttack)
					{
						_MESSAGE("AttackData: Attack is a charge attack");
					}
					if ((hitEvent->attackData->data.flags & AttackData::kBashAttack) == AttackData::kBashAttack)
					{
						_MESSAGE("AttackData: Attack is a bash attack");
						//ProvideHapticFeedback(0, 0, FeedbackType::PlayerBash, FeedbackIntensity(FeedbackType::PlayerBash), leftHandedMode);

						_MESSAGE("---------------------------------------");
						_MESSAGE(isLeftHand ? "LeftHandMeleeMajorHit" : "RightHandMeleeMajorHit");
						Play(isLeftHand ? "LeftHandMeleeMajorHit" : "RightHandMeleeMajorHit");
						return EventResult::kEvent_Continue;
					}
					if ((hitEvent->attackData->data.flags & AttackData::kIgnoreWeapon) == AttackData::kIgnoreWeapon)
					{
						_MESSAGE("AttackData: Attack is a ignore weapon attack");
					}
					if ((hitEvent->attackData->data.flags & AttackData::kPowerAttack) == AttackData::kPowerAttack)
					{
						_MESSAGE("AttackData: Attack is a power attack");
						//ProvideHapticFeedback(0, 0, FeedbackType::PlayerMeleePowerAttack, FeedbackIntensity(FeedbackType::PlayerMeleePowerAttack), leftHandedMode);
						_MESSAGE("---------------------------------------");
						_MESSAGE(isLeftHand ? "LeftHandMeleeBombHit" : "RightHandMeleeBombHit");
						Play(isLeftHand ? "LeftHandMeleeBombHit" : "RightHandMeleeBombHit");
						return EventResult::kEvent_Continue;
					}
					if ((hitEvent->attackData->data.flags & AttackData::kChargeAttack) != AttackData::kNone)
					{
						_MESSAGE("AttackData: Attack is a left attack");
					}
				}

				if (((hitEvent->flags & TESHitEventNew::kFlag_Blocked1) == TESHitEventNew::kFlag_Blocked1)
					|| ((hitEvent->flags & TESHitEventNew::kFlag_Blocked2) == TESHitEventNew::kFlag_Blocked2))
				{
					//ProvideHapticFeedback(0, 0, FeedbackType::PlayerBlock, FeedbackIntensity(FeedbackType::PlayerBlock), leftHandedMode);
					_MESSAGE("---------------------------------------");
					_MESSAGE(isLeftHand ? "LeftHandMeleeHit" : "RightHandMeleeHit");
					Play(isLeftHand ? "LeftHandMeleeHit" : "RightHandMeleeHit");
					return EventResult::kEvent_Continue;
				}
				else if (((hitEvent->flags & TESHitEventNew::kFlag_Bash1) == TESHitEventNew::kFlag_Bash1)
					|| ((hitEvent->flags & TESHitEventNew::kFlag_Bash2) == TESHitEventNew::kFlag_Bash2))
				{
					//ProvideHapticFeedback(0, 0, FeedbackType::PlayerBash, FeedbackIntensity(FeedbackType::PlayerBash), leftHandedMode);
					_MESSAGE("---------------------------------------");
					_MESSAGE(isLeftHand ? "LeftHandMeleeMajorHit" : "RightHandMeleeMajorHit");
					Play(isLeftHand ? "LeftHandMeleeMajorHit" : "RightHandMeleeMajorHit");
					return EventResult::kEvent_Continue;
				}
				else if ((hitEvent->flags & TESHitEventNew::kFlag_PowerAttack) == TESHitEventNew::kFlag_PowerAttack)
				{
					//ProvideHapticFeedback(0, 0, FeedbackType::PlayerMeleePowerAttack, FeedbackIntensity(FeedbackType::PlayerMeleePowerAttack), leftHandedMode);
					_MESSAGE("---------------------------------------");
					_MESSAGE(isLeftHand ? "LeftHandMeleeBombHit" : "RightHandMeleeBombHit");
					Play(isLeftHand ? "LeftHandMeleeBombHit" : "RightHandMeleeBombHit");
					return EventResult::kEvent_Continue;
				}
				else
				{
					std::string weaponType = DecideWeaponType(instanceData, weapon);

					if (weaponType != "NoWeapon")
					{
						std::string feedback = DecideWeaponFeedbackTypeFromPlayer(weaponType);
						if (MeleeFeedback(feedback))
						{
							_MESSAGE("Player used melee weapon on something. Weapon Effect %d", weaponType);
							//ProvideHapticFeedback(0, 0, feedback, FeedbackIntensity(feedback), leftHandedMode);

							_MESSAGE("---------------------------------------");
							_MESSAGE(feedback.c_str());
							Play(feedback);
							return EventResult::kEvent_Continue;
						}
					}
				}
			}
		}
		return kEvent_Continue;
	}


	void RaindropEffect()
	{
		while (raining.load() == true)
		{
			
			Sleep(rainSleepDuration);
		}
	}


	int GetClassification(TESWeather* weather)
	{
		const auto flags = *((byte*)weather + 0xA77);

		if (flags & 1)
			return 0;
		if (flags & 2)
			return 1;
		if (flags & 4)
			return 2;
		if (flags & 8)
			return 3;

		return -1;
	}

	TESWeather* GetCurrentWeather()
	{
		const auto skyPtr = *g_SkyPtr;
		return (TESWeather*)(skyPtr->array[8]);
	}

	TESWeather* GetOutgoingWeather()
	{
		const auto skyPtr = *g_SkyPtr;
		return (TESWeather*)(skyPtr->array[9]);
	}

	float GetTransition()
	{
		const auto skyPtr = *g_SkyPtr;
		return *((float*)skyPtr + 0xD4);
	}

	void GetCurrentWeatherClassification(int& classification)
	{
		const auto skyPtr = *g_SkyPtr;
		if (skyPtr)
		{
			TESWeather* weather = GetCurrentWeather();
			if (weather)
			{
				classification = GetClassification(weather);
				_MESSAGE("Current Weather is %x - class: %d", weather->formID, classification);
			}
			else
			{
				_MESSAGE("Current weather is null");
				classification = -1;
			}
		}
	}

	void GetOutgoingWeatherClassification(int& classification)
	{
		const auto skyPtr = *g_SkyPtr;
		if (skyPtr)
		{
			TESWeather* weather = GetOutgoingWeather();
			if (weather)
			{
				_MESSAGE("Outgoing Weather is %x - class: %d", weather->formID, classification);
				classification = GetClassification(weather);
			}
			else
			{
				_MESSAGE("Outgoing weather is null");
				classification = -1;
			}
		}
	}

	void ArmorCheck()
	{
		bool first = true;
		while (true)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				Sleep(5000);
				continue;
			}

			if (isGameStoppedNoDialogue())
			{
				Sleep(3000);
			}
			else
			{
				if ((*g_player)->equipData)
				{
					if (first)
					{
						first = false;
						GetInPowerArmorFrame();
					}
					if ((*g_player)->equipData->slots[0x03].item != nullptr)
					{
						TESForm* equippedForm = (*g_player)->equipData->slots[0x03].item;
						if (equippedForm)
						{
							if (equippedForm->formType == TESObjectARMO::kTypeID)
							{
								TESObjectARMO* armor = DYNAMIC_CAST(equippedForm, TESForm, TESObjectARMO);

								if (armor)
								{
									if (!(HasKeyword(armor, KeywordPowerArmor) || HasKeyword(armor, KeywordPowerArmorFrame)))
									{
										if (inPowerArmorFrame.load())
										{
											_MESSAGE("---------------------------------------");
											_MESSAGE("ExitPowerArmor");
											Play("ExitPowerArmor");
											_MESSAGE("Exited Power Armor Frame %x", armor->formID);
											inPowerArmorFrame.store(false);
										}
									}
								}
							}
						}
					}
				}

				Sleep(500);
			}
		}
	}

	void WeatherCheck()
	{
		//Address found by: Find "const Sky::`vftable'", then go to the first subroutine that uses it, then right click "Jump to xref to operand", go to the first one(the subroutine), address is the first qword you see after that call sub.
		//for fallout vr: 0x5A3D000

		TESObjectCELL* cell = nullptr;

		bool isItRaining = false;


		int32_t curWeatherClassification = -1;
		int32_t outWeatherClassification = -1;
		int32_t nextWeatherClassification = -1;

		g_SkyPtr = RelocPtr<Sky2*>(0x5A3D000);

		while (true)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				//LOG("player null. Waiting for 5seconds");
				raining.store(false);
				Sleep(5000);
				continue;
			}

			cell = (*g_player)->parentCell;

			if (!cell)
			{
				raining.store(false);
				continue;
			}

			if ((cell->flags & TESObjectCELL::kFlag_IsInterior) == TESObjectCELL::kFlag_IsInterior) //Interior cell
			{
				//LOG("In interior cell. Waiting for 5 seconds");
				raining.store(false);
				Sleep(5000);
				continue;
			}

			if (GetInPowerArmorFrame())
			{
				raining.store(false);
				Sleep(5000);
				continue;
			}

			isItRaining = false;

			const auto skyPtr = *g_SkyPtr;
			if (skyPtr != nullptr)
			{
				GetCurrentWeatherClassification(curWeatherClassification);
				GetOutgoingWeatherClassification(outWeatherClassification);
				float transition = GetTransition();
				_MESSAGE("Weather Transition value: %g", transition);

				if (curWeatherClassification == 2 || outWeatherClassification == 2)
				{
					isItRaining = true;

					float curWeatherIntensity = 0;
					float outWeatherIntensity = 0;

					float curWeatherDensity = 0;
					float outWeatherDensity = 0;

					if (curWeatherClassification == 2)
					{
						curWeatherIntensity = 0.52f;
						curWeatherDensity = 7.0f;
					}
					else
					{
						curWeatherIntensity = 0;
						curWeatherDensity = 0;
					}
					if (outWeatherClassification == 2)
					{
						outWeatherIntensity = 0.52f;
						outWeatherDensity = 7.0f;
					}
					else
					{
						outWeatherIntensity = 0;
						outWeatherDensity = 0;
					}

					if (curWeatherClassification == 2)
					{
						if (outWeatherClassification == 2)
						{
							rainIntensity.store(((curWeatherIntensity - outWeatherIntensity) * transition) + outWeatherIntensity);
							rainDensity.store(((curWeatherDensity - outWeatherDensity) * transition) + outWeatherDensity);
						}
						else
						{
							float transMultiplier = transition;
							/*if (transMultiplier < 0.4f)
								transMultiplier = 0.0f;*/

							rainIntensity.store(curWeatherIntensity * transMultiplier);
							rainDensity.store(curWeatherDensity * transMultiplier);
						}
					}
					else
					{
						if (outWeatherClassification == 2)
						{
							float transMultiplier = (1.0f - transition);
							/*if (transMultiplier < 0.5f)
								transMultiplier = 0.0f;*/

							rainIntensity.store(outWeatherIntensity * transMultiplier);
							rainDensity.store(outWeatherDensity * transMultiplier);
						}
						else
						{
							rainIntensity.store(0);
							rainDensity.store(0);
						}
					}
				}
				//LOG("Intensity: %g - Density: %g", rainIntensity.load(), rainDensity.load());
				if (rainIntensity.load() <= 0.25f || rainDensity.load() <= 3.31)
				{
					isItRaining = false;
				}

				if (isItRaining)
				{
					//LOG("Transition: %g", skyPtr->transition);
					if (raining.load() == false)
					{
						_MESSAGE("Enabling rain effects...");
						raining.store(true);
						std::thread t12(RaindropEffect);
						t12.detach();
					}
				}
				else
				{
					raining.store(false);
				}
				Sleep(1000);
			}
			else
			{
				//LOG("Sky is null. waiting for 5 seconds.");
				raining.store(false);
				Sleep(5000);
			}
		}
	}

	void CrippledEffect(std::string feedback, float cripple, float crippleMaximum)
	{
		//const int randDuration = randomGenerator(0, 500);
		//Sleep(randDuration);
		//ProvideHapticFeedback(0, 0, feedback, FeedbackIntensity(feedback) * ((crippleMaximum - cripple) / crippleMaximum), false);

		_MESSAGE("---------------------------------------");
		_MESSAGE(feedback.c_str());
		Play(feedback);
	}


	void ActorValueFunc()
	{
		float playerHealth = 100.0;
		float playerHealthMaximum = 100.0;

		float headCripple = 100.0;
		float headCrippleMaximum = 100.0;

		float torsoCripple = 100.0;
		float torsoCrippleMaximum = 100.0;

		float leftLegCripple = 100.0;
		float leftLegCrippleMaximum = 100.0;

		float rightLegCripple = 100.0;
		float rightLegCrippleMaximum = 100.0;

		float leftArmCripple = 100.0;
		float leftArmCrippleMaximum = 100.0;

		float rightArmCripple = 100.0;
		float rightArmCrippleMaximum = 100.0;

		float brainCripple = 100.0;
		float brainCrippleMaximum = 100.0;

		bool effectPlayed = false;

		//headCrippleMaximum = 100 * crippledEffectPercentage;// HeadCrippleAVI ? (*g_player)->actorValueOwner.GetMaximum(HeadCrippleAVI) : 100;
		//torsoCrippleMaximum = 100 * crippledEffectPercentage;// TorsoCrippleAVI ? (*g_player)->actorValueOwner.GetMaximum(TorsoCrippleAVI) : 100;
		//leftLegCrippleMaximum = 100 * crippledEffectPercentage;// LeftLegCrippleAVI ? (*g_player)->actorValueOwner.GetMaximum(LeftLegCrippleAVI) : 100;
		//rightLegCrippleMaximum = 100 * crippledEffectPercentage;// RightLegCrippleAVI ? (*g_player)->actorValueOwner.GetMaximum(RightLegCrippleAVI) : 100;
		//leftArmCrippleMaximum = 100 * crippledEffectPercentage;// LeftArmCrippleAVI ? (*g_player)->actorValueOwner.GetMaximum(LeftArmCrippleAVI) : 100;
		//rightArmCrippleMaximum = 100 * crippledEffectPercentage;// RightArmCrippleAVI ? (*g_player)->actorValueOwner.GetMaximum(RightArmCrippleAVI) : 100;
		//brainCrippleMaximum = 100 * crippledEffectPercentage;// BrainCrippleAVI ? (*g_player)->actorValueOwner.GetMaximum(BrainCrippleAVI) : 100;

		while (true)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				Sleep(3000);
				continue;
			}
			if (isGameStoppedNoDialogue())
			{
				Sleep(3000);
			}
			else
			{
				effectPlayed = false;

				playerHealthMaximum = HealthAVI ? (*g_player)->actorValueOwner.GetMaximum(HealthAVI) : 100;
				playerHealth = HealthAVI ? (*g_player)->actorValueOwner.GetValue(HealthAVI) : 100;

				headCripple = HeadCrippleAVI ? (*g_player)->actorValueOwner.GetValue(HeadCrippleAVI) : 100;

				torsoCripple = TorsoCrippleAVI ? (*g_player)->actorValueOwner.GetValue(TorsoCrippleAVI) : 100;

				leftLegCripple = LeftLegCrippleAVI ? (*g_player)->actorValueOwner.GetValue(LeftLegCrippleAVI) : 100;

				rightLegCripple = RightLegCrippleAVI ? (*g_player)->actorValueOwner.GetValue(RightLegCrippleAVI) : 100;

				leftArmCripple = LeftArmCrippleAVI ? (*g_player)->actorValueOwner.GetValue(LeftArmCrippleAVI) : 100;

				rightArmCripple = RightArmCrippleAVI ? (*g_player)->actorValueOwner.GetValue(RightArmCrippleAVI) : 100;

				brainCripple = BrainCrippleAVI ? (*g_player)->actorValueOwner.GetValue(BrainCrippleAVI) : 100;

				if (playerHealthMaximum > 0)
				{
					if (playerHealth / playerHealthMaximum < verylowhealthpercentage)
					{
						_MESSAGE("Very Low Health Effect");
						for (int i = 0; i < 7; i++)
						{
							//ProvideHapticFeedback(0, 0, FeedbackType::HeartBeatFast, FeedbackIntensity(FeedbackType::HeartBeatFast), false);
							_MESSAGE("---------------------------------------");
							_MESSAGE("HeartBeat");
							Play("HeartBeat");
							Sleep(heartbeatfastsleepduration);
						}
						effectPlayed = true;
					}
					else if (playerHealth / playerHealthMaximum < lowhealthpercentage)
					{
						_MESSAGE("Low Health Effect");
						for (int i = 0; i < 4; i++)
						{
							//ProvideHapticFeedback(0, 0, FeedbackType::HeartBeat, FeedbackIntensity(FeedbackType::HeartBeat), false);
							_MESSAGE("---------------------------------------");
							_MESSAGE("HeartBeat");
							Play("HeartBeat");
							Sleep(heartbeatsleepduration);
						}
						effectPlayed = true;
					}
				}

				if (headCrippleMaximum > 0)
				{
					if (headCripple < headCrippleMaximum)
					{
						_MESSAGE("Head Crippled: %g/100", headCripple);
						std::thread t0(CrippledEffect, "CrippledHead", headCripple, headCrippleMaximum);
						t0.detach();
					}
				}
				if (torsoCrippleMaximum > 0)
				{
					if (torsoCripple < torsoCrippleMaximum)
					{
						_MESSAGE("Torso Crippled: %g/100", torsoCripple);
						std::thread t0(CrippledEffect, "CrippledTorso", torsoCripple, torsoCrippleMaximum);
						t0.detach();
					}
				}
				if (leftLegCrippleMaximum > 0)
				{
					if (leftLegCripple < leftLegCrippleMaximum)
					{
						_MESSAGE("Left Leg Crippled: %g/100", leftLegCripple);
						std::thread t0(CrippledEffect, "CrippledLeftLeg", leftLegCripple, leftLegCrippleMaximum);
						t0.detach();
					}
				}
				if (rightLegCrippleMaximum > 0)
				{
					if (rightLegCripple < rightLegCrippleMaximum)
					{
						_MESSAGE("Right Leg Crippled: %g/100", rightLegCripple);
						std::thread t0(CrippledEffect, "CrippledRightLeg", rightLegCripple, rightLegCrippleMaximum);
						t0.detach();
					}
				}
				if (leftArmCrippleMaximum > 0)
				{
					if (leftArmCripple < leftArmCrippleMaximum)
					{
						_MESSAGE("Left Arm Crippled: %g/100", leftArmCripple);
						std::thread t0(CrippledEffect, "CrippledLeftArm", leftArmCripple, leftArmCrippleMaximum);
						t0.detach();
					}
				}
				if (rightArmCrippleMaximum > 0)
				{
					if (rightArmCripple < rightArmCrippleMaximum)
					{
						_MESSAGE("Right Arm Crippled: %g/100", rightArmCripple);
						std::thread t0(CrippledEffect, "CrippledRightArm", rightArmCripple, rightArmCrippleMaximum);
						t0.detach();
					}
				}
				if (brainCrippleMaximum > 0)
				{
					if (brainCripple < brainCrippleMaximum)
					{
						_MESSAGE("Brain Crippled: %g/100", brainCripple);
						std::thread t0(CrippledEffect, "CrippledBrain", brainCripple, brainCrippleMaximum);
						t0.detach();
					}
				}
				if (!effectPlayed)
				{
					Sleep(3000);
				}
			}
		}
	}

	void SwimmingCheck()
	{
		while (true)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				Sleep(5000);
				continue;
			}

			const bool isSwimming = ((*g_player)->actorFlags & 0x00040000) != 0;

			if (isSwimming)
			{
				//const int randDuration = randomGenerator(0, 200);
				//Sleep(randDuration);
				//ProvideHapticFeedback(0, 0, FeedbackType::PlayerSwimming, FeedbackIntensity(FeedbackType::PlayerSwimming), false, true);
				_MESSAGE("---------------------------------------");
				_MESSAGE("Swimming");
				Play("Swimming");

				Sleep(swimmingsleepduration);
			}
			else
			{
				Sleep(3000);
			}
		}
	}
	
	void VATSCheck()
	{
		while (true)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				Sleep(5000);
				continue;
			}

			const bool isInVats = isVatsActive();

			if (isInVats)
			{
				//ProvideHapticFeedback(0, 0, FeedbackType::VatsHeartBeat, FeedbackIntensity(FeedbackType::VatsHeartBeat), false, true);
				_MESSAGE("---------------------------------------");
				_MESSAGE("HeartBeat");
				Play("HeartBeat");
				Sleep(vatssleepduration);
			}
			else
			{
				Sleep(1500);
			}
		}
	}

	F4SEMyInputHandler myInputHandler;
	void PlayerAliveCheck()
	{
		while (true)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				Sleep(5000);
				continue;
			}

			if (isGameStoppedNoDialogue())
			{
				Sleep(3000);
			}
			else
			{
				const UInt32 beforeCount = GetSingletonEventDispatcher(WeaponFiredEvent).eventSinks.count;

				if (beforeCount > 0)
				{
					///*LOG("inputEvents before count: %d", (*g_playerControls)->inputEvents1.count);
					//(*g_playerControls)->inputEvents1.Push(&myInputHandler);
					//LOG("inputEvents after count: %d", (*g_playerControls)->inputEvents1.count);
					//*/
					_MESSAGE("WeaponFiredEvent sinks before count: %d", beforeCount);
					GetSingletonEventDispatcher(WeaponFiredEvent).AddEventSink(&F4VR_TrueGear::g_WeaponFiredEventHandler);
					_MESSAGE("WeaponFiredEvent sinks after count: %d", GetSingletonEventDispatcher(WeaponFiredEvent).eventSinks.count);
					if (beforeCount < GetSingletonEventDispatcher(WeaponFiredEvent).eventSinks.count)
					{
						_MESSAGE("PlayerWeaponReloadEvent sinks before count: %d", GetGlobalEventDispatcher<PlayerWeaponReloadEvent>().eventSinks.count);
						GetGlobalEventDispatcher<PlayerWeaponReloadEvent>().AddEventSink(&F4VR_TrueGear::g_PlayerWeaponReloadEventHandler);
						_MESSAGE("PlayerWeaponReloadEvent sinks after count: %d", GetGlobalEventDispatcher<PlayerWeaponReloadEvent>().eventSinks.count);

						break;
					}
				}

				Sleep(3000);
			}
		}
	}

	typedef bool(*_IsInCombatNative)(Actor* actor);
	bool ActorInCombat(Actor* actor)
	{
		UInt64* vtbl = *((UInt64**)actor);
		return ((_IsInCombatNative)(vtbl[0xFF]))(actor);
		//LOG("----Actor is %s in combat", combat ? "" : "not");
		//return combat;
	}

	void PlayerMovementCheck()
	{
		NiPoint3 pos;
		bool moving = false;
		bool firstInPowerArmor = false;

		bool movingVertically = false;
		while (true)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				Sleep(5000);
				continue;
			}

			if (isGameStoppedNoDialogue())
			{
				Sleep(3000);
			}
			else
			{
				
				if (pos.x != (*g_player)->loadedState->node->m_worldTransform.pos.x
					|| pos.y != (*g_player)->loadedState->node->m_worldTransform.pos.y
					|| pos.z != (*g_player)->loadedState->node->m_worldTransform.pos.z)
				{
					if (distanceNoSqrt2d(pos, (*g_player)->loadedState->node->m_worldTransform.pos) > 1500)
					{
						moving = true;
					}
					else
					{
						moving = false;
					}
				}
				else
				{
					moving = false;
				}

				if (pos.z <= (*g_player)->loadedState->node->m_worldTransform.pos.z
					|| (pos.z <= (*g_player)->loadedState->node->m_worldTransform.pos.z - 30.0f && moving))
				{
					movingVertically = true;
				}
				else
				{
					movingVertically = false;
				}
				pos = (*g_player)->loadedState->node->m_worldTransform.pos;

				const bool power_armor = GetInPowerArmorFrame();
				if (!firstInPowerArmor && power_armor)
				{
					firstInPowerArmor = true;
					moving = false;
				}
				else if (!power_armor)
				{
					firstInPowerArmor = false;
				}

				if (movingVertically && IsInAir((*g_player)) && HasAnyMagicEffect(&jetPackMagicEffects))
				{
					const int randDuration = randomGenerator(0, 50);
					Sleep(randDuration);
					_MESSAGE("Jetpack active...");
					//ProvideHapticFeedback(0, 0, FeedbackType::JetPack, FeedbackIntensity(FeedbackType::JetPack), false, false);
					_MESSAGE("---------------------------------------");
					_MESSAGE("JetPack");
					Play("JetPack");
					Sleep(jetpacksleepduration);
					continue;
				}
				else if (power_armor && (!ActorInCombat(*g_player)))
				{
					if (((*g_player)->actorState.flags04 & ActorState::kState_Sprinting) == ActorState::kState_Sprinting)
					{
						//LOG("Player Sprinting...");

						//Play power armor sprinting effect
						//ProvideHapticFeedback(0, 0, FeedbackType::PowerArmorSprinting, FeedbackIntensity(FeedbackType::PowerArmorSprinting), false, true);
						_MESSAGE("---------------------------------------");
						if (isPowerArmorLeftRunning)
						{
							isPowerArmorLeftRunning = false;
							_MESSAGE("PowerArmorLeftLegRunning");
							Play("PowerArmorLeftLegRunning");
						}
						else
						{
							isPowerArmorLeftRunning = true;
							_MESSAGE("PowerArmorRightLegRunning");
							Play("PowerArmorRightLegRunning");
						}
						Sleep(powerarmorsprintingsleepduration);
						continue;
					}
					else
					{
						if (moving)
						{
							//LOG("Player moving...");
							float sneakMultiplier = 1.0f;
							if (((*g_player)->actorState.flags & ActorState::kState_Sneaking) == ActorState::kState_Sneaking)
							{
								sneakMultiplier = 0.5f;
							}
							//Play power armor moving effect
							//ProvideHapticFeedback(0, 0, FeedbackType::PowerArmorWalking, FeedbackIntensity(FeedbackType::PowerArmorWalking) * sneakMultiplier, false, true);
							_MESSAGE("---------------------------------------");
							if (isPowerArmorLeftWalking)
							{
								isPowerArmorLeftWalking = false;
								_MESSAGE("PowerArmorLeftLegWalking");
								Play("PowerArmorLeftLegWalking");
							}
							else
							{
								isPowerArmorLeftWalking = true;
								_MESSAGE("PowerArmorRightLegWalking");
								Play("PowerArmorRightLegWalking");
							}							
							
							Sleep(powerarmorwalkingsleepduration);
							continue;
						}
					}
				}

				//LOG("ActorState: %x - %x", (*g_player)->actorState.flags04, (*g_player)->actorState.flags);
				Sleep(500);
			}
		}
	}


	void MonitorActiveEffects()
	{
		while (true)
		{
			if (!(*g_player) || !(*g_player)->loadedState)
			{
				Sleep(5000);
				continue;
			}

			if (isGameStoppedNoDialogue())
			{
				Sleep(4000);
			}
			else
			{
				MagicTargetNew* magicTarget = (MagicTargetNew*)(&(*g_player)->magicTarget);
				tArray<ActiveEffect*>* activeEffectsList = magicTarget->GetActiveEffects();

				for (UInt32 i = 0; i < activeEffectsList->count; i++)
				{
					ActiveEffect* activeEffect = activeEffectsList->entries[i];

					if (activeEffect && (activeEffect->m_flags & ActiveEffect::kFlag_Inactive) == 0)
					{
						if (activeEffect->m_item && activeEffect->m_effect && activeEffect->m_effect->m_setting)
						{
							if (activeEffect->m_effect->m_setting->formID == InfectionEffectFormId)
							{
								//ProvideHapticFeedback(0, 0, FeedbackType::Infection, FeedbackIntensity(FeedbackType::Infection), false, true);
								_MESSAGE("---------------------------------------");
								_MESSAGE("Infection");
								Play("PoisonDamage");
							}
							else if (activeEffect->m_effect->m_setting->formID == StarvingEffectFormId)
							{
								//ProvideHapticFeedback(0, 0, FeedbackType::Starvation, FeedbackIntensity(FeedbackType::Starvation), false, true);
								_MESSAGE("---------------------------------------");
								_MESSAGE("Starvation");
								Play("HungryDamage");
							}
							else if (activeEffect->m_effect->m_setting->formID == DehydratedEffectFormId)
							{
								//ProvideHapticFeedback(0, 0, FeedbackType::Dehydration, FeedbackIntensity(FeedbackType::Dehydration), false, true);
								_MESSAGE("---------------------------------------");
								_MESSAGE("Dehydration");
								Play("ThirstyDamage");
							}
							else
							{
								const std::string feedback = DecideEffectFeedbackType(activeEffect->m_effect->m_setting);
								if (feedback != "NoFeedback")
								{
									//ProvideHapticFeedback(0, 0, feedback, FeedbackIntensity(feedback), false, true);

									_MESSAGE("---------------------------------------");
									_MESSAGE(feedback.c_str());
									Play(feedback);
								}
							}
						}
					}
				}
				Sleep(3000);
			}
		}
	}

	NiNode* getWorldRoot()
	{
		NiNode* node = (*g_player)->loadedState->node;
		while (node && node->m_parent)
		{
			node = node->m_parent;
		}
		return node;
	}


	std::atomic<bool> runOnce = false;
	bool LoadFuncs()
	{
		if (!runOnce.load())
		{
			runOnce.store(true);

			CreateSystem();

			FillActorValueInfo();

			FillMagicEffects();

			std::thread t2(MonitorActiveEffects);
			t2.detach();

			std::thread t3(PlayerMovementCheck);
			t3.detach();

			std::thread t4(ActorValueFunc);
			t4.detach();

			std::thread t5(PlayerAliveCheck);
			t5.detach();

			std::thread t6(ArmorCheck);
			t6.detach();

			std::thread t7(WeatherCheck);
			t7.detach();

			std::thread t8(SwimmingCheck);
			t8.detach();

			std::thread t9(VATSCheck);
			t9.detach();

			std::thread t11(WsLoop);
			t11.detach();
			_MESSAGE("F4VR_TrueGear Start!!!");
		}
		return true;
	}

}