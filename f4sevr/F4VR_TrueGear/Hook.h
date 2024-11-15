#pragma once
//#include "f4se\PapyrusActor.h"
//#include "f4se\GameMenus.h"
//#include "f4se/NiTypes.h"
//#include "f4se/GameRTTI.h"
//#include "f4se/GameForms.h"
//#include "f4se/GameFormComponents.h"
//#include "f4se/GameObjects.h"

#include "F4VR_TrueGear.h"
#include "config.h"
#include "Sky.h"
#include "GameStop.h"

//#include <thread>
//#include <atomic>
//#include <common/ITypes.h>
#include <common/IDebugLog.h>

namespace F4VR_TrueGear
{
	typedef bool(*_IsInAir) (Actor* actor);
	extern RelocAddr<_IsInAir> IsInAir;
	extern bool systemInitialized;

	bool LoadFuncs();

	extern float lowhealthpercentage;
	extern float verylowhealthpercentage;

	extern ActorValueInfo* HealthAVI;
	extern ActorValueInfo* PoisonResistAVI;
	extern ActorValueInfo* FireResistAVI;
	extern ActorValueInfo* ElectricResistAVI;
	extern ActorValueInfo* FrostResistAVI;
	extern ActorValueInfo* MagicResistAVI;
	extern ActorValueInfo* RadResistIngestionAVI;
	extern ActorValueInfo* RadResistExposureAVI;
	extern ActorValueInfo* EnergyResistAVI;

	extern UInt32 KeywordActorTypeNPCFormId;
	extern UInt32 KeywordActorTypeHumanFormId;
	extern UInt32 KeywordActorTypeSuperMutantFormId;
	extern UInt32 KeywordActorTypeAnimalFormId;
	extern UInt32 KeywordActorTypeCreatureFormId;
	extern UInt32 KeywordActorTypeBugFormId;


	extern UInt32 KeywordWeaponTypeAlienBlasterFormId;
	extern UInt32 KeywordWeaponTypeAutomaticFormId;
	extern UInt32 KeywordWeaponTypeBallisticFormId;
	extern UInt32 KeywordWeaponTypeExplosiveFormId;
	extern UInt32 KeywordWeaponTypeHeavyGunFormId;
	extern UInt32 KeywordWeaponTypeThrownFormId;
	extern UInt32 KeywordWeaponTypeLaserFormId;
	extern UInt32 KeywordWeaponTypeRifleFormId;
	extern UInt32 KeywordWeaponTypePistolFormId;
	extern UInt32 KeywordWeaponTypeGrenadeFormId;
	extern UInt32 KeywordWeaponTypeMineFormId;
	extern UInt32 KeywordWeaponTypePlasmaFormId;
	extern UInt32 KeywordWeaponTypeShotgunFormId;
	extern UInt32 KeywordEnergyGunFormId;
	extern UInt32 KeywordWeaponTypeHandToHandFormId;
	extern UInt32 KeywordWeaponTypeUnarmedFormId;
	extern UInt32 KeywordWeaponTypeAnimsUnarmedFormId;
	extern UInt32 KeywordWeaponTypeMelee1HFormId;
	extern UInt32 KeywordWeaponTypeMelee2HFormId;
	extern UInt32 KeywordWeaponTypeRipperFormId;
	extern UInt32 KeywordWeaponTypeShishkebabFormId;

	extern UInt32 KeywordWeaponTypeAnims1HMShortFormId;
	extern UInt32 KeywordWeaponTypeAnims1HMFormId;
	extern UInt32 KeywordWeaponTypeAnims2HMFormId;
	extern UInt32 KeywordWeaponTypeAnims2HMWideFormId;
	extern UInt32 KeywordWeaponTypeAnims44FormId;
	extern UInt32 KeywordWeaponTypeAnimsAlienBlasterFormId;
	extern UInt32 KeywordWeaponTypeAnimsAssBladeModFormId;
	extern UInt32 KeywordWeaponTypeAnimsBroadsiderFormId;
	extern UInt32 KeywordWeaponTypeAnimsCombatShotgunFormId;
	extern UInt32 KeywordWeaponTypeAnimsDelivererFormId;
	extern UInt32 KeywordWeaponTypeAnimsDoubleBarrelShotgunFormId;
	extern UInt32 KeywordWeaponTypeAnimsFlareGunFormId;
	extern UInt32 KeywordWeaponTypeAnimsGatlingLaserFormId;
	extern UInt32 KeywordWeaponTypeAnimsGripPistolFormId;
	extern UInt32 KeywordWeaponTypeAnimsMineFormId;
	extern UInt32 KeywordWeaponTypeAnimsMinigunFormId;
	extern UInt32 KeywordWeaponTypeAnimsSubmachineGunFormId;

	extern UInt32 KeywordArmorTypePoweredFormId;

	NiNode* getWorldRoot();

	void FillActorValueInfo();

	bool ActorCreature(Actor* actor);


	TESObjectWEAP* GetEquippedWeaponForm(Actor* actor);

	TESObjectWEAP::InstanceData* GetEquippedWeaponInstanceData(Actor* actor);


	std::string DecideWeaponType(TESObjectWEAP::InstanceData* instanceData, TESObjectWEAP* weapon);

	std::string DecideWeaponFeedbackTypeFromPlayer(std::string weaponType);

	std::string DecideMagicFeedbackType(SpellItem* spell);

	std::string DecideWeaponEnchantmentFeedbackType(TESObjectWEAP::InstanceData* instanceData, TESObjectWEAP* weapon);

	DECLARE_EVENT_CLASS(WeaponFiredEvent);
	extern WeaponFiredEventHandler g_WeaponFiredEventHandler;

	DECLARE_EVENT_CLASS(PlayerWeaponReloadEvent);
	extern PlayerWeaponReloadEventHandler g_PlayerWeaponReloadEventHandler;


	class HitEventHandler : public BSTEventSink <TESHitEvent>
	{
	public:
		virtual	EventResult ReceiveEvent(TESHitEvent* evn, void* dispatcher);
	};

	extern HitEventHandler g_HitEventHandler;

	class ContainerChangedEventHandler : public BSTEventSink <TESContainerChangedEvent>
	{
	public:
		virtual	EventResult ReceiveEvent(TESContainerChangedEvent * evn, void * dispatcher);
	};

	extern ContainerChangedEventHandler g_ContainerChangedEventHandler;

	class TESEquipEventHandler : public BSTEventSink <TESEquipEvent>
	{
	public:
		virtual	EventResult ReceiveEvent(TESEquipEvent * evn, void * dispatcher);
	};

	extern TESEquipEventHandler g_TESEquipEventHandler;


	class TESTexture1024 : public TESTexture
	{

	};

	class BGSLightingTemplate : public TESForm
	{
	public:
		enum { kTypeID = kFormType_LGTM };

		// 5C
		struct Data
		{
			// 20 - used elsewhere
			struct Color
			{
				UInt32	x[2];				// 00 - init'd to 00FFFFFF
				UInt32	y[2];
				UInt32	z[2];
				UInt32	specular;			// 18 - init'd to 0
				float	fresnelPower;		// 1C - init'd to 1
			};

			UInt32	unk00;			// 00 - init'd to 0
			UInt32	unk04;			// 04 - init'd to 0
			UInt32	unk08;			// 08 - init'd to 0
			UInt32	unk0C;			// 0C - init'd to 0
			UInt32	unk10;			// 10 - init'd to 0
			UInt32	unk14;			// 14 - init'd to 0
			UInt32	unk18;			// 18 - init'd to 0
			float	unk1C;			// 1C - init'd to 1
			UInt32	unk20;			// 20 - init'd to 0
			float	unk24;			// 24 - init'd to 1
			Color	unk28;			// 28
			UInt32	unk48;			// 48 - init'd to 0
			float	unk4C;			// 4C - init'd to 1
			float	lodStartFade;	// 50 - fLightLODStartFade
			float	lodStopFade;	// 54 - fLightLODStartFade + fLightLODRange
			UInt32	unk58;			// 58 - init'd to 0000079F
		};

		Data			unk20;	// 20
		UInt32			pad7C;	// 7C
		Data::Color		unk80;	// 80
	};
	STATIC_ASSERT(sizeof(BGSLightingTemplate) == 0xA0);

	class BGSShaderParticleGeometryData : public TESForm
	{
	public:
		enum { kTypeID = kFormType_SPGD };

		UnkArray	unk20;		// 20
		TESTexture	texture;	// 38
	};

	class BGSReferenceEffect : public TESForm
	{
	public:
		enum { kTypeID = kFormType_RFCT };

		// C
		struct Data
		{
			UInt64	unk00;
			UInt64	unk08;
			UInt32	unk10;
		};

		Data	unk20; // 20
	};

	class TESWeather : public TESForm
	{
	public:
		enum { kTypeID = kFormType_WTHR };

		enum { kNumColorTypes = 17 };
		enum { kNumTimeOfDay = 4 };

		enum ColorTypes {
			kColorType_SkyUpper = 0,
			kColorType_FogNear = 1,
			kColorType_Unk = 2,
			kColorType_Ambient = 3,
			kColorType_Sunlight = 4,
			kColorType_Sun = 5,
			kColorType_Stars = 6,
			kColorType_SkyLower = 7,
			kColorType_Horizon = 8,
			kColorType_EffectLighting = 9,
			kColorType_CloudLODDiffuse = 10,
			kColorType_CloudLODAmbient = 11,
			kColorType_FogFar = 12,
			kColorType_SkyStatics = 13,
			kColorType_WaterMultiplier = 14,
			kColorType_SunGlare = 15,
			kColorType_MoonGlare = 16
		};

		enum TimeOfDay {
			kTime_Sunrise = 0,
			kTime_Day = 1,
			kTime_Sunset = 2,
			kTime_Night = 3
		};

		// 10
		struct ColorType
		{
			UInt32	time[kNumTimeOfDay];
		};

		// 14
		struct General
		{
			//UInt8	unk00[0x13];			// 00
			UInt8	windSpeed;
			UInt8	unk01[2];
			UInt8	transDelta;				// Div 1000
			UInt8	sunGlare;				// Div 256
			UInt8	sunDamage;				// Div 256
			UInt16	unk06;					// precipitation fadein/out
			UInt32	unk08;					// thunder ligting fadein/out/frequency/flags
			UInt32	lightingColor;
			UInt8	unk10;
			UInt8	windDirection;			// Div (256/360)
			UInt8	windDirRange;			// Div (256/180)
			UInt8	pad13;
		};

		// 20
		struct FogDistance
		{
			float	nearDay;
			float	farDay;				// 10
			float	nearNight;			// 14
			float	farNight;			// 18
			float	powerDay;			// 1C
			float	powerNight;
			float	maxDay;
			float	maxNight;
		};

		// 10
		struct CloudAlpha
		{
			float	time[kNumTimeOfDay];
		};

		TESTexture1024	texture[0x20];		// 020
		UInt8			unk220[0x20];		// 220 - cleared to 0x7F
		UInt8			unk240[0x20];		// 240 - cleared to 0x7F
		UInt8			unk260[0x200];		// 260
		CloudAlpha		cloudAlpha[0x20];	// 460
		UInt32			unk660;				// 660
		General			general;			// 664
		FogDistance		fogDistance;		// 678
		ColorType		colorTypes[kNumColorTypes];		// 698
		TESAIForm::Data	unk7A8;				// 7A8
		UnkArray		unk7B8;				// 7B8
		UInt32			unk7D0;				// 7D0 - not init'd - LNAM unknown
		TESImageSpace* imageSpaces[kNumTimeOfDay]; // 7D8
		BGSLightingTemplate::Data::Color	directionalAmbient[kNumTimeOfDay];	// 7F8
		TESModel		unk878;	// 878
		TESForm* lensFlare; // 8A0 - TODO: replace with actual form pointer when a definition is available
		TESForm* volumetricLightings[kNumTimeOfDay]; // 8A8 - TODO: replace with actual form pointer when a definition is available
		BGSShaderParticleGeometryData* particleShader;	// 8C8
		BGSReferenceEffect* referenceEffect;	// 8D0
	};

	class ActiveEffect
	{
	public:
		enum {
			kFlag_Inactive = 0x8000
		};

		void* m_vtable;                   // 0x00
		uint8_t		m_pad1[0x40];
		TESForm* m_item;						// 0x48 = 72 - probably this is a MagicItem instance (AlchemyItem, EnchantmentItem, SpellItem etc...)

		struct {
			float			m_magnitude;		// 00
			UInt32			m_unk1;				// 04
			UInt32			m_unk2;				// 08
			UInt32			m_unk3;				// 1C
			EffectSetting* m_setting;			// 10
			uint8_t			m_pad[16];			// ??
		} *m_effect;							// 0x50 = 80

		uint64_t	m_unkPtr;					// 0x58 = 88 - don't know
		TESForm* m_sourceItem;				// 0x60 = 96 - probably the source item (for example the armor piece for enchantments)
		uint8_t		m_pad2[0x10];
		float       m_elapsed;                  // 0x78 = 120
		float       m_duration;                 // 0x7C = 124
		float       m_magnitude;                // 0x80 = 128
		UInt32		m_flags;                    // 0x84 = 132
		uint8_t		m_pad3[0x28];
	};

	STATIC_ASSERT(sizeof(ActiveEffect) == 0xB0);
	STATIC_ASSERT(offsetof(ActiveEffect, m_vtable) == 0x00);
	STATIC_ASSERT(offsetof(ActiveEffect, m_item) == 0x48);
	STATIC_ASSERT(offsetof(ActiveEffect, m_elapsed) == 0x78);
	STATIC_ASSERT(offsetof(ActiveEffect, m_duration) == 0x7C);
	STATIC_ASSERT(offsetof(ActiveEffect, m_magnitude) == 0x80);
	STATIC_ASSERT(offsetof(ActiveEffect, m_flags) == 0x84);

	class MagicTargetNew
	{
	public:
		virtual ~MagicTargetNew();

		virtual void	Unk_01(void);
		virtual void	Unk_02(void);
		virtual void	Unk_03(void);
		virtual void	Unk_04(void);
		virtual void	Unk_05(void);
		virtual void	Unk_06(void);
		virtual tArray<ActiveEffect*>* GetActiveEffects();
		virtual void	Unk_08(void);
		virtual void	Unk_09(void);
		virtual void	Unk_0A(void);
		virtual void	Unk_0B(void);
		virtual void	Unk_0C(void);

		void* m_unk08;		// 0x08
		void* m_unk10;		// 0x10
	};



	struct AttackData  // ATKD
	{
		enum
		{
			kNone = 0,
			kIgnoreWeapon = 1 << 0,
			kBashAttack = 1 << 1,
			kPowerAttack = 1 << 2,
			kChargeAttack = 1 << 3,
			kRotatingAttack = 1 << 4,
			kContinuousAttack = 1 << 5,
			kOverrideData = (UInt32)1 << 31
		};


		float		damageMult;		// 00
		float		attackChance;	// 04
		SpellItem* attackSpell;	// 08
		UInt32		flags;			// 10
		float		attackAngle;	// 14
		float		strikeAngle;	// 18
		float		staggerOffset;	// 1C
		BGSKeyword* attackType;		// 20
		float		knockDown;		// 28
		float		recoveryTime;	// 2C
		float		staminaMult;	// 30
		UInt32		pad34;			// 34
	};
	STATIC_ASSERT(sizeof(AttackData) == 0x38);

	class BGSAttackData : public NiRefObject
	{
	public:
		virtual ~BGSAttackData();  // 00

		bool IsLeftAttack() const;

		// members
		BSFixedString event;  // 10 - ATKE
		AttackData	  data;	  // 18 - ATKD
	};
	STATIC_ASSERT(sizeof(BGSAttackData) == 0x50);

	struct WeaponFiredEventNew
	{
		UInt64                         proja;
		UInt64                         projb;
		UInt64                         projc;
		UInt64                         projd;
		UInt64                         proje;
		UInt64                         proj1; // Projectile?
	};
	STATIC_ASSERT(offsetof(WeaponFiredEventNew, proj1) == 0x028);
	STATIC_ASSERT(sizeof(WeaponFiredEventNew) == 0x030);


	struct TESHitEventNew
	{
		enum HitEventFlags {
			kFlag_Blocked1 = (1 << 0),     // (Unk0 | Unk1) - blocked
			kFlag_Blocked2 = (1 << 1),
			kFlag_CriticalHit = (1 << 3),
			kFlag_SneakAttack = (1 << 11),
			kFlag_Bash1 = (1 << 15),    // (Unk15 | Unk16) - bash
			kFlag_Bash2 = (1 << 16),
			kFlag_PowerAttack = (1 << 17),
		};

		NiPoint3        position;                   // 00
		UInt32          unk0C[(0x40 - 0x0C) / 4];       // 0C
		UInt32          attackerHandle;             // 40
		UInt32          targetHandle;               // 44
		UInt64          unk48;                      // 48
		BGSAttackData* attackData;                 // 50 - BGSAttackData*
		TESForm* source;                     // 58 - e.g. TESObjectWEAP*
		void* sourceInstanceData;         // 60
		UInt64          unk68[(0x80 - 0x68) / 8];       // 68
		TESAmmo* ammo;                       // 80
		UInt64          unk88;                      // 88
		float           effectiveDamage;            // 90 - effectiveDamage = baseDamage + damage bonus (body part multiplier)
		float           incomingDamage;             // 94
		float           baseDamage;                 // 98 - baseDamage = incomingDamage - negatedDamage
		float           unk9C;                      // 9C
		float           unkA0;                      // A0
		float           negatedDamage;              // A4
		UInt64          unkA8;                      // A8
		float           attackDamageMultiplier;     // B0 - Sneak attack multiplier
		UInt32          unkB4[(0xC4 - 0xB4) / 4];       // B4
		UInt32          flags;                      // C4
		UInt64          unkC8[(0xE0 - 0xC8) / 8];       // C8
		TESObjectREFR* target;                     // E0 - If null, use handle
		TESObjectREFR* attacker;                   // E8 - If null, use handle
		UInt64          unkF0;                      // F0
		UInt32          sourceFormID;               // F8 - May be null
		UInt32          projectileFormID;           // FC - May be null
		bool            unk100;                     // 100
		char            pad101[7];                  // 101
	};
	STATIC_ASSERT(offsetof(TESHitEventNew, unk100) == 0x100);


	class F4SEMyInputHandler : public PlayerInputHandler
	{
	public:
		F4SEMyInputHandler() : PlayerInputHandler() { }

		virtual void OnButtonEvent(ButtonEvent* inputEvent)
		{
			if (inputEvent)
			{
				BSFixedString	control = *inputEvent->GetControlID();
				float			timer = inputEvent->timer;

				bool isDown = inputEvent->isDown == 1.0f && timer == 0.0f;
				bool isUp = inputEvent->isDown == 0.0f && timer != 0.0f;

				_MESSAGE("Button event: %s  -  %s", control.c_str(), isDown ? "is down" : "is up");
			}
		}
	};
	extern F4SEMyInputHandler myInputHandler;

}