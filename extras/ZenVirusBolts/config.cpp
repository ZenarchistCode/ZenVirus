class CfgPatches
{
	class ZenVirusBolts
	{
		requiredVersion = 0.1;
		requiredAddons[] = { "ZenVirus","GDZ_Crossbow_Asset","DZ_Weapons_Firearms","DZ_Weapons_Ammunition","DZ_Weapons_Projectiles","DZ_Sounds_Effects","DZ_Weapons_Optics","DZ_Weapons_Archery_Crossbow" };
		magazines[] = { "Zen_Crossbow_ArrowBoltVirus" };
		ammo[] = { "Arrow_Bolt_Virus" };
	};
};

class CfgMods
{
	class ZenVirusBolts
	{
		dir = "ZenVirusBolts";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ZenVirusBolts";
		credits = "";
		author = "Zenarchist";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = { "Game","World","Mission" };
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenVirusBolts/scripts/4_World" };
			};
		};
		
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class Zen_Virus_PathogenVial : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_PATHOGENVIAL";
		descriptionShort = "$STR_ZEN_VIRUS_PATHOGENVIAL_DESC";
		model = "\dz\gear\medical\InjectionVial.p3d";
		itemSize[] = { 2,2 };
		weight = 50;
		lootCategory = "Medical";
		stackedUnit = "percentage";
		quantityBar = 1;
		varQuantityInit = 100;
		varQuantityMin = 0;
		varQuantityMax = 100;
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenVirus\data\textures\Ragevirusvial_co.paa","ZenVirus\data\textures\Ragevirusvial_co.paa","ZenVirus\data\textures\Ragevirusvial_co.paa" };
	};
};

class cfgWeapons
{
	class Rifle_Base;
	class Crossbow_Base_gdz : Rifle_Base
	{
		scope = 0;
		chamberableFrom[] += { "Zen_Crossbow_ArrowBoltVirus" };
	}
};

class CfgMagazines
{
	class Ammunition_Base;
	class Crossbow_ArrowBolt : Ammunition_Base
	{
		scope = 2;
		displayName = "Crossbow Bolt";
		descriptionShort = "A short type of arrow designed for a crossbow, perfect for killing zombies quietly. I wonder if I could poison this with a virus pathogen vial to make a poison arrow I can use to infect other survivors...";
		model = "\DZ\weapons\projectiles\arrow_hunting.p3d";
		iconCartridge = 1;
		rotationFlags = 34;
		itemSize[] = { 4,1 };
		weight = 10;
		count = 20;
		ammo = "Arrow_Bolt";

		destroyOnEmpty = 1;
		varQuantityDestroyOnMin = 0;
		canBeSplit = 1;
		simpleHeap = 1;

		varQuantityMin = 0;
		varQuantityMax = 20;
		varStackMax = 20;
		varStackMin = 1;

		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = { {1.0,{"DZ\weapons\projectiles\data\arrows.rvmat"}},{0.7,{"DZ\weapons\projectiles\data\arrows.rvmat"}},{0.5,{"DZ\weapons\projectiles\data\arrows_damage.rvmat"}},{0.3,{"DZ\weapons\projectiles\data\arrows_damage.rvmat"}},{0.0,{"DZ\weapons\projectiles\data\arrows_destruct.rvmat"}} };
				};
			};
		};
	};
	class Zen_Crossbow_ArrowBoltVirus : Crossbow_ArrowBolt
	{
		scope = 2;
		displayName = "Poisoned Crossbow Bolt";
		descriptionShort = "A short type of arrow designed for a crossbow. It seems to have been poisoned with a virus...";
		model = "\DZ\weapons\projectiles\arrow_hunting.p3d";
		iconCartridge = 1;
		rotationFlags = 34;
		itemSize[] = { 4,1 };
		weight = 10;
		count = 20;
		ammo = "Arrow_Bolt_Virus";

		destroyOnEmpty = 1;
		varQuantityDestroyOnMin = 0;
		canBeSplit = 1;
		simpleHeap = 1;

		varQuantityMin = 0;
		varQuantityMax = 20;
		varStackMax = 20;
		varStackMin = 1;

		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = { {1.0,{"DZ\weapons\projectiles\data\arrows.rvmat"}},{0.7,{"DZ\weapons\projectiles\data\arrows.rvmat"}},{0.5,{"DZ\weapons\projectiles\data\arrows_damage.rvmat"}},{0.3,{"DZ\weapons\projectiles\data\arrows_damage.rvmat"}},{0.0,{"DZ\weapons\projectiles\data\arrows_destruct.rvmat"}} };
				};
			};
		};
	};
};
class cfgAmmoTypes
{
	class AType_Arrow_Bolt_Virus
	{
		name = "Arrow_Bolt_Virus";
	};
};
class cfgAmmo
{
	class Bullet_Base;
	class Arrow_Bolt_Virus : Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\arrow_hunting_flying.p3d";
		spawnPileType = "Zen_Crossbow_ArrowBoltVirus";
		proxyShape = "\dz\weapons\projectiles\arrow_hunting.p3d";
		hit = 12;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "FxRound_arrow_hunting";
		deflecting = 20;
		caliber = 0.5;
		airFriction = -0.00215;
		typicalSpeed = 150;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		initSpeed = 150;
		weight = 0.025;
		tracerScale = 1;
		tracerStartTime = 1e-05;
		tracerEndTime = -1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0;
			bleedThreshold = 1;
			defaultDamageOverride[] = { {0.5,1} };
			class Health
			{
				damage = 20;
			};
			class Blood
			{
				damage = 500;
			};
			class Shock
			{
				damage = 100;
			};
		};
	};
};