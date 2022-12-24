/* 
 * This mod is based on Munghard's RAGE Virus mod: https://steamcommunity.com/workshop/filedetails/?id=1674233729
 */
class CfgPatches
{
	class ZenVirus
	{
		requiredVersion = 0.1;
		units[] =
		{
			"Zen_Virus_PathogenVial", "Zen_Virus_AntiBodiesVial", "Zen_Virus_Cure_Injector", "Zen_Virus_Cure_Petridish", "Zen_Virus_Brain", "Zen_Virus_Cure_Microscope", "Zen_Virus_Injector",
		};
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class ZenVirus
	{
		dir = "ZenVirus";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ZenVirus";
		credits = "munghard, jadesnood, saltybob, tom";
		author = "Zenarchist";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = { "Game","World","Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "ZenVirus/scripts/3_game"; };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenVirus/scripts/4_World" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "ZenVirus/scripts/5_mission" };
			};
		};
	};
};

class CfgVehicles
{
	// Custom items
	class Inventory_Base;
	class Zen_Virus_Brain : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_BRAIN";
		descriptionShort = "$STR_ZEN_VIRUS_BRAIN_DESC";
		model = "\ZenVirus\data\models\brain\zv_brain_model.p3d";
		inventorySlot = "Material_Brain";
		rotationFlags = 34;
		itemSize[] = { 2,2 };
		weight = 265;
		isMeleeWeapon = 1;
		class GlobalHealth
		{
			class Health
			{
				hitpoints = 100;
				healthLevels[] = { {1,{"\ZenVirus\data\models\brain\brain.rvmat"}},{0.7,{"\ZenVirus\data\models\brain\brain.rvmat"}},{0.5,{"\ZenVirus\data\models\brain\brain.rvmat"}},{0.3,{"\ZenVirus\data\models\brain\brain.rvmat"}},{0,{"\ZenVirus\data\models\brain\brain.rvmat"}} };
			};
		};
	};
	class Zen_Virus_PathogenVial : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_PATHOGENVIAL";
		descriptionShort = "$STR_ZEN_VIRUS_PATHOGENVIAL_DESC";
		model = "\dz\gear\medical\InjectionVial.p3d";
		itemSize[] = { 2,2 };
		weight = 50;
		lootCategory = "Medical";
		//varQuantityInit = 1;
		//varQuantityMin = 0;
		//varQuantityMax = 1;
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenVirus\data\textures\Ragevirusvial_co.paa","ZenVirus\data\textures\Ragevirusvial_co.paa","ZenVirus\data\textures\Ragevirusvial_co.paa" };
	};
	class Zen_Virus_AntiBodiesVial : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_ANTIBODIESVIAL";
		descriptionShort = "$STR_ZEN_VIRUS_ANTIBODIESVIAL_DESC";
		model = "\dz\gear\medical\InjectionVial.p3d";
		itemSize[] = { 2,2 };
		weight = 50;
		lootCategory = "Medical";
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenVirus\data\textures\Antibodiesvial_co.paa","ZenVirus\data\textures\Antibodiesvial_co.paa","ZenVirus\data\textures\Antibodiesvial_co.paa" };
	};
	class Zen_Virus_Cure_Petridish : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_CURE_PETRIDISH";
		descriptionShort = "$STR_ZEN_VIRUS_CURE_PETRIDISH_DESC";
		model = "\dz\structures\furniture\school_equipment\lab_petri_dish.p3d";
		weight = 0;
		interactionWeight = 1;
		itemSize[] = { 2,1 };
		inventorySlot = "Material_Petridish";
		hiddenSelections[] = { "component1" };
		hiddenSelectionsTextures[] = { "\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa","\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa","\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa" };
		hiddenSelectionsMaterials[] = { "\DZ\data\data\penetration\glass.rvmat","\DZ\data\data\penetration\glass.rvmat","\DZ\data\data\penetration\glass.rvmat" };
	};
	class BloodBagFull : Inventory_Base
	{
		inventorySlot = "Material_BloodBagFull";
	};
	class BloodBagIV : Inventory_Base
	{
		inventorySlot = "Material_BloodBagFull";
	};
	class ZV_Injector_Base : Inventory_Base
	{
		model = "\dz\gear\medical\Epinephrine.p3d";
		rotationFlags = 17;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 1;
		itemSize[] = { 1,2 };
		weight = 60;
		lootCategory = "Medical";
		lootTag[] = { "Medic" };
		hiddenSelections[] = { "zbytek" };
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = { {1,{"DZ\gear\medical\data\epipen.rvmat"}},{0.7,{"DZ\gear\medical\data\epipen.rvmat"}},{0.5,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0,{"DZ\gear\medical\data\epipen_destruct.rvmat"}} };
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Morphine_spear
				{
					soundSet = "Morphine_spear_SoundSet";
					id = 201;
				};
				class Morphine_out
				{
					soundSet = "Morphine_out_SoundSet";
					id = 202;
				};
			};
		};
	};
	class Zen_Virus_Cure_Injector : ZV_Injector_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_CURE_INJECTOR";
		descriptionShort = "$STR_ZEN_VIRUS_CURE_INJECTOR_DESC";
		hiddenSelectionsTextures[] = { "ZenVirus\data\textures\RageCure_1_co.paa","ZenVirus\data\textures\RageCure_1_co.paa","ZenVirus\data\textures\RageCure_1_co.paa" };
		/*class Food // Todo: enable "rotting" of virus cure so players can't stockpile them en-masse?
		{
			class FoodStages
			{
				class Raw
				{
					visual_properties[] = { 0,0,0 };
					nutrition_properties[] = { 0,0,0,0,0 };
					cooking_properties[] = { 0,0 };
				};
				class Rotten
				{
					visual_properties[] = { 0,0,0 };
					nutrition_properties[] = { 0,0,0,0,0,0 };
					cooking_properties[] = { 0,0 };
				};
			};
			class NotCookable;
			class FoodStageTransitions : NotCookable
			{
			};
		};*/
	};
	class Zen_Virus_Cure_Injector_Empty : ZV_Injector_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_CURE_INJECTOR_EMPTY";
		descriptionShort = "$STR_ZEN_VIRUS_CURE_INJECTOR_EMPTY_DESC";
		hiddenSelectionsTextures[] = { "ZenVirus\data\textures\RageCure_1_co.paa","ZenVirus\data\textures\RageCure_1_co.paa","ZenVirus\data\textures\RageCure_1_co.paa" };
	};
	class Zen_Virus_Injector : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_INJECTOR";
		descriptionShort = "$STR_ZEN_VIRUS_INJECTOR_DESC";
		itemSize[] = { 1,2 };
		model = "\dz\gear\medical\Epinephrine.p3d";
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenVirus\data\textures\RageCure_2_co.paa","ZenVirus\data\textures\RageCure_2_co.paa","ZenVirus\data\textures\RageCure_2_co.paa" };

		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 20;
					healthLevels[] =
					{

						{
							1,

							{
								"DZ\gear\medical\data\Syringe.rvmat"
							}
						},

						{
							0.69999999,

							{
								"DZ\gear\medical\data\Syringe.rvmat"
							}
						},

						{
							0.5,

							{
								"DZ\gear\medical\data\Syringe_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"DZ\gear\medical\data\Syringe_damage.rvmat"
							}
						},

						{
							0,

							{
								"DZ\gear\medical\data\Syringe_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Syringe_out
				{
					soundSet = "Syringe_out_SoundSet";
					id = 201;
				};
				class Syringe_spear
				{
					soundSet = "Syringe_spear_SoundSet";
					id = 202;
				};
				class Syringe_splash
				{
					soundSet = "Syringe_splash_SoundSet";
					id = 203;
				};
			};
		};
	};
	class Zen_Virus_Injector_Empty : ZV_Injector_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_INJECTOR_EMPTY";
		descriptionShort = "$STR_ZEN_VIRUS_INJECTOR_EMPTY_DESC";
		hiddenSelectionsTextures[] = { "ZenVirus\data\textures\RageCure_2_co.paa","ZenVirus\data\textures\RageCure_2_co.paa","ZenVirus\data\textures\RageCure_2_co.paa" };
	};
	class Zen_Virus_Cure_Microscope : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_CURE_MICROSCOPE";
		descriptionShort = "$STR_ZEN_VIRUS_CURE_MICROSCOPE_DESC";
		model = "\dz\structures\furniture\school_equipment\lab_microscope.p3d";
		itemSize[] = { 3,5 };
		attachments[] = { "BatteryD", "Material_Petridish", "Material_Brain", "Material_BloodBagFull" };
		hiddenSelections[] = { "component1" };
		hiddenSelectionsTextures[] = { "\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa","\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa","\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa" };
		hiddenSelectionsMaterials[] = { "\DZ\structures\furniture\school_equipment\data\lab_set.rvmat" };
		repairableWithKits[] = { 7 };
		repairCosts[] = { 100 };
		class GUIInventoryAttachmentsProps
		{
			class Materials
			{
				name = "Virus Cure Components";
				description = "Requires a petridish, an infected brain and a full blood bag in order to operate.";
				attachmentSlots[] = { "BatteryD", "Material_Petridish", "Material_Brain", "Material_BloodBagFull" };
				icon = "missing";
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] =
					{

						{
							1,

							{
								"DZ\gear\medical\data\Syringe.rvmat"
							}
						},

						{
							0.69999999,

							{
								"DZ\gear\medical\data\Syringe.rvmat"
							}
						},

						{
							0.5,

							{
								"DZ\gear\medical\data\Syringe_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"DZ\gear\medical\data\Syringe_damage.rvmat"
							}
						},

						{
							0,

							{
								"DZ\gear\medical\data\Syringe_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = { 4,2 }; // 8 slots of storage ONLY for cure/pathogen vials
			openable = 0;
			allowOwnedCargoManipulation = 1;
		};
	};
	class Zen_Virus_Cure_Microscope_Static : Zen_Virus_Cure_Microscope
	{
		scope = 2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 99999;
				}
			}
		};
	};
};

// Inventory slots
class CfgSlots
{
	class Slot_Material_Petridish
	{
		name = "Material_Petridish";
		displayName = "Petridish";
		selection = "Material_Petridish";
		ghostIcon = "missing";
		show = "true";
		stackMax = 0;
		description = "Requires a petridish, an infected brain and a full blood bag in order to operate.";
	};
	class Slot_Material_Brain
	{
		name = "Material_Brain";
		displayName = "Infected Brain";
		selection = "Material_Brain";
		ghostIcon = "missing";
		show = "true";
		stackMax = 0;
		description = "Requires a petridish, an infected brain and a full blood bag in order to operate.";
	};
	class Slot_Material_BloodBagFull
	{
		name = "Material_BloodBagFull";
		displayName = "Full Blood Bag";
		selection = "Material_BloodBagFull";
		ghostIcon = "missing";
		show = "true";
		stackMax = 0;
		description = "Requires a petridish, an infected brain and a full blood bag in order to operate.";
	};
};

// Sound curves
class CfgSoundCurves
{
	class CfgSoundCurvesBloodVomit
	{
		points[] = { {0,1},{0.1,0.98},{0.2,0.92},{0.3,0.8},{0.4,0.65},{0.5,0.5},{0.6,0.35},{0.7,0.2},{0.8,0.08},{0.9,0.02},{1,0} };
	};
};

// Sound processors
class CfgSound3DProcessors
{
	class default3DProcessingBloodVomit
	{
		type = "emitter";
		innerRange = 15;
		range = 10;
		radius = 5;
		volume = 8;
	};
	class default3DProcessingTypeSpeech
	{
		type = "emitter";
		innerRange = 15;
		range = 10;
		radius = 5;
		volume = 0.30118722;
	};
};

// Sound shaders
class CfgSoundShaders
{
	class base_SoundShaderBloodVomit
	{
		range = 10;
		rangeCurve = "CfgSoundCurvesBloodVomit";
		volume = 8;
	};
	class base_SoundShaderPlayerInfected
	{
		range = 10;
		rangeCurve = "CfgSoundCurvesBloodVomit";
		volume = 8;
	};
	class BloodVomit_SoundShader : base_SoundShaderBloodVomit
	{
		volume = 8;
		range = 10;
		rangeCurve = "CfgSoundCurvesBloodVomit";
		samples[] = { {"ZenVirus\data\sounds\Puke2",1},{"ZenVirus\data\sounds\vomiting-02",1},{"ZenVirus\data\sounds\vomiting-04",1},{"ZenVirus\data\sounds\vomiting-06",1},{"ZenVirus\data\sounds\vomit_6",1},{"ZenVirus\data\sounds\vomit_3",1} };
	};
};

// Soundsets
class CfgSoundSets
{
	class base_SoundSet
	{
		sound3DProcessingType = "default3DProcessingBloodVomit";
		spatial = 1;
		doppler = 0;
		loop = 1;
	};
	class base_SoundSetSpeech
	{
		sound3DProcessingType = "default3DProcessingTypeSpeech";
		spatial = 1;
		doppler = 0;
		loop = 0;
	};
	class BloodVomit_SoundSet : base_SoundSet
	{
		soundShaders[] = { "BloodVomit_SoundShader" };
		volume = 8;
	};
};