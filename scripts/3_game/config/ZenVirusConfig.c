class ZenVirusConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenVirusConfig.json";

	// Static constant config version (is NOT saved to json)
	static const string CONFIG_VERSION = "1";

	// Main config data
	string ConfigVersion = "";
	string CONFIG_MAIN = "-----------------------------------------------------------------------------------------------------------------------";
	int VirusAnalysisDelay = 60; // How long it takes in seconds for the virus to be analyzed by the microscope
	int VirusTickSecs = 10; // How often the server checks virus levels & symptoms (base level ticks)
	int VirusTickSecsRand = 60; // How often the server checks virus levels & symptoms (randomly added to base level ticks)
	float VirusAddPerSecond = 0.05; // How much virus agent to add to the player each second they're infected. 0.05 sec/1000 max = ~5.5 hours until full infection & death.
	bool VirusRedScreen = true; // Sets whether or not to make the player's screen slowly turn to a red tint as they become more infected
	string CONFIG_INJECTION = "------------------------------------------------------------------------------------------------------------------";
	int VirusInjectorAmount = 250; // How much of the virus to inject when the virus syringe is used
	int VirusAddPerScratchMin = 1; // Minimum amount of virus agents to inject when player gets hit by a zombie
	int VirusAddPerScratchMax = 10; // Maximum amount of agents to inject when player gets hit by a zombie (random between these two)
	float VirusChancePerScratch = 0.5; // Chance of being infected each time the player is hit by a zombie
	int VirusAddPerBleedMin = 10; // Minimum amount of virus agents to inject when the player is hit by a zombie while bleeding
	int VirusAddPerBleedMax = 20; // Maximum amount of virus agents to inject when the player is hit by a zombie while bleeding
	ref TStringArray CreatureGuaranteedVirus = { "infected", "add_scary_monster_types_here" }; // These creature types guarantee a high infection chance when attacked
	string CONFIG_INFECTION = "------------------------------------------------------------------------------------------------------------------";
	float ChanceOfWoundInfectionBleed = 0.5; // Chance of getting a wound infection if player is hit while bleeding
	int VomitBloodLossMin = 75; // Maximum amount of blood to lose when vomiting blood
	int VomitBloodLossMax = 75; // Maximum amount of blood to lose when vomiting blood
	float ChanceOfRandomVomit = 0.001; // Percent chance of randomly vomiting blood after Stage 1 infection (gets higher as stages go up)
	float ChanceOfRandomZombieYell = 0.002; // Percent chance of randomly vomiting blood after Stage 1 infection (gets higher as stages go up)
	string CONFIG_FOOD = "-----------------------------------------------------------------------------------------------------------------------";
	int HumanMeatVirusAdd = -5; // How many virus agents to add/remove when consuming human meat (still gives you Kuru once cured of virus, so nibble small bits!)
	bool HumanMeatDisableKuru = false; // If true, the player will not contract kuru while infected with the zombie virus
	int FoodVirusAdd = 10; // How many virus agents to inject when consuming a food from the FoodVirus list
	ref TStringArray FoodVirus = { "radioactive", "add_bad_food_types_shere" }; // These food types guarantee a high infection chance when consumed
	string CONFIG_TIPS = "-----------------------------------------------------------------------------------------------------------------------";
	float SurvivalTipChance = 0.05; // Percent chance of the server sending a survival tip message along with a symptom
	string Tip1 = "I don't feel so good... I think I might have caught a virus from the infected...";
	string Tip2 = "I definitely have the virus... I need to cut open a zombie to get an infected brain so I can make a cure...";
	string Tip3 = "I definitely have the virus... I need to find a microscope so I can engineer a cure. Maybe I'll find one at a hospital...";
	string Tip4 = "I definitely have the virus... I need to find a petridish so I can engineer a cure. Maybe I'll find one at a hospital...";
	string Tip5 = "I definitely have the virus... I need to find an empty syringe so I can engineer a cure. Maybe I'll find one at a hospital...";
	string Tip6 = "I definitely have the virus... I need to get my hands on a full blood bag so I can engineer a cure...";
	string Tip7 = "I have everything I need to cure the virus... I just need to attach them to the microscope...";
	string Tip8 = "I don't think the cure worked. I might be too infected to be cured...";
	string CONFIG_STAGES = "---------------------------------------------------------------------------------------------------------------------";
	float Stage1 = 0.1; // Stage 1 infection %
	float Stage2 = 0.25; // Stage 2 infection % - triggers new symptoms
	float Stage3 = 0.5; // Stage 3 infection % - triggers new symptoms
	float Stage4 = 0.75; // Stage 4 infection % - triggers new symptoms
	float Stage5 = 0.9; // Stage 5 infection % - triggers new symptoms
	float Stage6 = 0.99; // Stage 6 infection % - triggers new symptoms leading to certain death
	float Stage6ZombieYellChance = 0.2; // % chance of zombie yells when fully infected
	float StageTetraVitaminWorks = 0.2; // Percentage of infection where tetra & vitamins can still cure the illness (above this = need virus cure)
	float StageGivesIgnoreZombies = 1.0; // Enables/disables zombies ignoring the player when stage 6 terminal infection is reached
	float StageGivesBoostedStamina = 0.8; // Enables/disables unlimited stamina when stage 6 terminal infection is reached
	float BoostedStaminaConsumed = 0.5; // How much slower stamina is consumed when player's stamina boost is activated from infection
	float BoostedStaminaRecovery = 2.0; // How much faster stamina recovers when player's stamina boost is activated from infection
	float StageNoCure = 0; // If the player is infected past this %, they cannot be cured. (1 = 100%)
	float MinStage6DamagePercent = 0.01; // 1% health
	float MaxStage6DamagePercent = 0.025; // 2.5% health (player randomly loses a random amount of health between these two numbers every few mins when at Stage 6)
	string CONFIG_MISC = "-----------------------------------------------------------------------------------------------------------------------";
	int DamageMicroscope = 0; // How much to damage the microscope after creating a cure
	bool TurnDeadInfectedPlayersToZombies = false; // (Experimental) if true then if the player dies while infected they'll turn into a zombie (some loot is dropped)
	float PlayerInfectedPercentageToZombify = 0.9; // How infected the player must be between 0.0 and 1.0 to turn into a zombie if they die
	string CONFIG_ZOMBIE_LOOT = "----------------------------------------------------------------------------------------------------------------";
	float ChanceOfBrain = 1.0; // 100% chance of a brain
	float ChanceOfBrainRuined = 0; // 0% chance of a ruined brain dropped by zombies by default
	float ChanceOfBones = 1.0; // 100% chance of dropping bones
	float ChanceOfBonesRuined = 0.95; // 95% chance of bones being ruined
	float ChanceOfGuts = 0.5; // 50% chance of dropping guts
	float ChanceOfGutsRuined = 0.95; // 95% chance of ruined
	float ChanceOfWorm = 0.5; // 50% chance of dropping a worm
	float ChanceOfWormRuined = 0.95; // 95% chance of worm being ruined
	string CONFIG_DEBUG = "----------------------------------------------------------------------------------------------------------------------";
	int VirusMaxAmount = 1000; // Maxmimum virus agent count (don't touch unless you know what you're doing with DayZ virus invasibility etc)
	int VirusActivateAmount = 100; // Minimum virus agent count (don't touch unless you know what you're doing with DayZ virus invasibility etc)
	int VirusDeactivateAmount = 100; // Deactivation virus agent count (don't touch unless you know what you're doing with DayZ virus invasibility etc)
	bool DebugOn = false; // Turns debug messages on/off
	string STATIC_MICROSCOPES = "-----------------------------------------------------------------------------------------------------------------";
	ref array<ref ZenMicroscope> StaticMicroscopes = new ref array<ref ZenMicroscope>;

	// Load config file or create default file if config doesn't exsit
	void Load()
	{
		if (FileExist(zenModFolder + zenConfigName))
		{ 
			// If config exists, load file
			JsonFileLoader<ZenVirusConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			// If version mismatch, backup old version of json before replacing it
			if (ConfigVersion != CONFIG_VERSION)
			{
				JsonFileLoader<ZenVirusConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Config exists and version matches, stop here.
				return;
			}
		}

		// Config file does not exist, create default file
		ConfigVersion = CONFIG_VERSION;
		StaticMicroscopes.Insert(new ZenMicroscope("Example", "0 0 0", "0 0 0"));

		// Save file
		Save();
	}

	// Save config
	void Save()
	{
		if (!FileExist(zenModFolder))
		{ 
			// If config folder doesn't exist, create it.
			MakeDirectory(zenModFolder);
		}

		// Save JSON config
		JsonFileLoader<ZenVirusConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}
}

class ZenMicroscope
{
	string Name;
	vector Location;
	vector Orientation;

	void ZenMicroscope(string p_Name, vector p_Location, vector p_Orientation)
	{
		Name = p_Name;
		Location = p_Location;
		Orientation = p_Orientation;
	}
};

// Save config data
ref ZenVirusConfig m_ZenVirusConfig;

// Helper function to return Config data storage object
static ZenVirusConfig GetZenVirusConfig()
{
	if (!m_ZenVirusConfig && GetGame().IsDedicatedServer())
	{
		Print("[ZenVirusConfig] Init");
		m_ZenVirusConfig = new ZenVirusConfig;
		m_ZenVirusConfig.Load();
	}

	return m_ZenVirusConfig;
};