WHAT IS THIS?

This mod adds a new virus to the game that the player can only contract from zombies. Getting hit by zombies has a chance to slowly infect the player with this virus agent, and once the player is infected past a certain point they are then stuck with the virus until they cure it (like wound infection and other vanilla diseases).

Once the player is sick with the zombie virus they will gradually become affected by various symptoms that start off benign and mostly just an inconvenience, but over time become life-threatening and eventually fatal.

At first they will exhibit signs of sickness like coughing and blurry vision. They will also start to hear audible hallucinations such as whispers, footsteps, trees falling down etc - generally annoying symptoms that put the player on edge. But if they do not cure the virus in time eventually they will begin to vomit blood, develop wounds, fall unconscious and slowly lose health until they either find a cure - or die.

If the player is fast to identify the symptoms then they can take tetracycline AND vitamins to cure the virus. This only works if both vitamins and tetracycline are in the player's system and their infection stage is below 20%.

This information is according to default mod settings - all of these parameters can be adjusted by server admins so use this as a rough guide and consult your server mods if you want to know which parameters are used on the server you play on.

The code for this mod is based on the project VIRUS by Munghard & Tom, so most credit goes to them (https://steamcommunity.com/sharedfiles/filedetails/?id=1674233729)

Support for all languages is included (although translations are almost certainly going to be bad - feel free to repack this mod with edits if you know what you're doing).

VIRUS SYMPTOMS

Here is a list of stages and their symptoms:

Stage 0: No symptoms.
Stage 1 (10% infected):
 - Audible hallucinations. 
 - Very rare vomiting of blood or making a zombie scream that other players can hear.
Stage 2 (25% infected): 
 - Screen begins to turn red (more red colorization - this color gets worse the more infected you become).
 - Can no longer be cured by tetra & vitamins.
 - May develop fever symptoms (shivering, sweating).
 - May cough up blood sometimes.
Stage 3 (50% infected):
 - Player will cough up blood more often.
 - Blurry vision and light pains can be felt.
 - Chance of making a zombie scream increases.
Stage 4 (75% infected):
 - Player will begin to vomit blood randomly.
 - Hands will begin to shake when aiming (kuru symptoms).
 - Chance of making a zombie scream increases significantly.
Stage 5 (90% infected):
 - Player will begin falling unconscious randomly.
 - Player will develop random bleeding wounds.
Stage 6 (99% infected):
 - Player will begin to laugh randomly (kuru symptoms).
 - Player will scream like a zombie frequently (can be heard by other players).
 - Player begins to lose health randomly, as well as vomit blood more frequently.
 - Certain death awaits any player who doesn't have an endless supply of blood bags and bandages.

OPTIONAL FEATURES (SERVERS CAN CHOOSE TO DEACTIVE THESE)

- When the player becomes 80% infected they will get a boost to stamina (consumes stamina slower, recovers stamina faster).
- When the player becomes 100% infected zombies will ignore the player entirely (unless the player attacks the zombie).
- While these three features seem OP, keep in mind by this stage the player will be vomiting blood and bleeding all over the place regularly and is almost certainly going to die soon.
- If the player dies to zombie infection, a zombie can spawn on their corpse with some of their gear (disabled by default - experimental feature).
- If the player eats human meat while infected it might reduce their infection without giving them kuru unless they over-indulge, based on the config options in the CONFIG_INFECTION server settings. HumanMeatVirusAdd= -5 is the default setting and means eating human meat will reduce virus infection by -5 for each bite. HumanMeatDisableKuru=1 means the player will NOT contract kuru when eating human flesh AND infected with the virus - once the virus infection is cured this exemption no longer applies.
- Check the 'extras' folder for an extra mod which adds the ability to poison crossbow bolts with the virus pathogen vial or injection syringe.

VIRUS CURE

Once the virus infection spreads through more than 20% of the player's system, then the only chance of survival is manufacturing a virus cure injector.

The default server setting gives the player at least 5 hours before the infection spreads through their entire body which is plenty of time to find all of the items needed to make a cure. This infection time can be adjusted by server owners however, so depending on the style of the server you're playing on it might be more or less forgiving, and the cure items might be common or much rarer.

To manufacture a cure the player needs the following items:
- A microscope (with a 9v battery)
- A petridish
- A full blood bag
- An empty syringe
- An infected brain (skin dead zombies)

The default settings have most of these items spawning in medical loot spawns, but this can be changed in the server types.xml files if desired. The infected brain can only be retrieved by skinning dead zombies. Skinning dead zombies will also have a chance to drop bones, worms and guts (can be disabled in config or you can give these items 100% chance to be ruined and unusable for hardcore servers).

Once the player has all of these items they need to place them into the microscope and use the "Analyze Virus" action on the Microscope. 

After a few seconds the microscope will generate two vials - one with antibodies, one with virus agents. Using an empty syringe on these vials will give the player an injection syringe to either cure themselves - or intentionally infect others with the virus if they get close enough to them to use the syringe.

NOTE: Due to a DayZ bug with 1.18 you may need to put the microscope into your hands to see its cargo inventory - this is a vanilla bug that will hopefully be fixed soon.

OTHER NOTES FOR SERVER ADMINS

There are a ton of config options to adjust this mod to your preference. By default the mod will also send the player random tips on how to manufacture a cure as there are so many parts to it that it might be difficult for them to figure out the cure without help (but this can be disabled in the config settings for servers where you have a discord or website with information on how your mods work). The tips are included in the config file so they can also be translated to other languages if needed.

You can find a complete list of the config settings, types.xml and other info in the mod folder.

INSTALLATION

Install this mod like any other mod - copy it into your server folder and add it to your mods list. Make sure to copy the .bikey into your server keys and merge the types.xml entries with your server types.xml.

REPACK & SOURCE CODE

You can repack this mod if you like, and do anything else you want with it for that matter. Keep in mind that repacking will stop my updates & bug fixes being automatically applied. The source code is available on my GitHub at www.zenarchist.io




CONFIG EXPLANATIONS:

// Main config data
ConfigVersion = X; // Don't touch this or it will reset your entire config file. It's for me to update config structure
VirusAnalysisDelay = 60; // How many seconds it takes to analyze virus (persistent over server restarts)
VirusTickSecs = 10; // How often the server checks virus levels & symptoms (base level ticks)
VirusTickSecsRand = 60; // How often the server checks virus levels & symptoms (randomly added to base level ticks to give symptoms a more random nature)
VirusAddPerSecond = 0.05; // 0.05 sec/1000 max = ~5.5 hours until full infection & death. Increase this to infect faster, decrease to infect slower.
VirusRedScreen = true; // Sets whether or not to make the player's screen slowly turn to a red tint as they become more infected

// Config for injection settings
VirusInjectorAmount = 250; // How much of the virus to inject when the virus syringe is used
VirusAddPerScratchMin = 1; // Minimum amount of virus agents to inject when player gets hit by a zombie
VirusAddPerScratchMax = 10; // Maximum amount of agents to inject when player gets hit by a zombie (random between these two)
VirusChancePerScratch = 0.5; // Chance of being infected each time the player is hit by a zombie
VirusAddPerBleedMin = 10; // Minimum amount of virus agents to inject when the player is hit by a zombie while bleeding
VirusAddPerBleedMax = 20; // Maximum amount of virus agents to inject when the player is hit by a zombie while bleeding
CreatureGuaranteedVirus = { "infected", "add_scary_monster_types_here" }; // These creature types guarantee a high infection chance when attacked

// Config for infection settings
ChanceOfWoundInfectionBleed = 0.5; // Chance of getting a wound infection if player is hit while bleeding
VomitBloodLossMin = 75; // Maximum amount of blood to lose when vomiting blood
VomitBloodLossMax = 75; // Maximum amount of blood to lose when vomiting blood
ChanceOfRandomVomit = 0.001; // Percent chance of randomly vomiting blood after Stage 1 infection (gets higher as stages go up)
ChanceOfRandomZombieYell = 0.002; // Percent chance of randomly vomiting blood after Stage 1 infection (gets higher as stages go up)

// Config for food settings
HumanMeatVirusAdd = -5; // How many virus agents to add/remove when consuming human meat (still gives you Kuru once cured of virus, so nibble small bits! Set to 0 to disable)
HumanMeatDisableKuru = false; // If true, the player will not contract kuru while infected with the zombie virus
FoodVirusAdd = 10; // How many virus agents to inject when consuming a food from the FoodVirus list
FoodVirus = { "radioactive", "add_bad_food_types_shere" }; // These food types guarantee a high infection chance when consumed

// Config for survival tips
SurvivalTipChance = 0.05; // Percent chance of the server sending a survival tip message along with a symptom
"Tip1": "I don't feel so good... I think I might have caught a virus from the infected...",
"Tip2": "I definitely have the virus... I need to cut open a zombie to get an infected brain so I can make a cure...",
"Tip3": "I definitely have the virus... I need to find a microscope so I can engineer a cure. Maybe I'll find one at a hospital...",
"Tip4": "I definitely have the virus... I need to find a petridish so I can engineer a cure. Maybe I'll find one at a hospital...",
"Tip5": "I definitely have the virus... I need to find an empty syringe so I can engineer a cure. Maybe I'll find one at a hospital...",
"Tip6": "I definitely have the virus... I need to get my hands on a full blood bag so I can engineer a cure...",
"Tip7": "I have everything I need to cure the virus... I just need to attach them to the microscope...",
"Tip8": "I don't think the cure worked. I might be too infected to be cured...",

// Config for virus stages
Stage1 = 0.1; // Stage 1 infection 10%
Stage2 = 0.25; // Stage 2 infection 25% - triggers new symptoms
Stage3 = 0.5; // Stage 3 infection 50% - triggers new symptoms
Stage4 = 0.75; // Stage 4 infection 75% - triggers new symptoms
Stage5 = 0.9; // Stage 5 infection 90% - triggers new symptoms
Stage6 = 0.99; // Stage 6 infection 99% - triggers new symptoms leading to certain death
Stage6ZombieYellChance = 0.2; // % chance of zombie yells when fully infected
StageTetraVitaminWorks = 0.2; // Percentage of infection where tetra & vitamins can still cure the illness (above this = need virus cure)
StageGivesIgnoreZombies = 1.0; // Enables/disables zombies ignoring the player when stage 6 terminal infection is reached
StageGivesBoostedStamina = 0.8; // Enables/disables unlimited stamina when stage 6 terminal infection is reached (set to 0 to disable)
BoostedStaminaConsumed = 0.5; // How much slower stamina is consumed when player's stamina boost is activated from infection
BoostedStaminaRecovery = 2.0; // How much faster stamina recovers when player's stamina boost is activated from infection
StageNoCure = 0; // If the player is infected past this %, they cannot be cured. (1 = 100%)
MinStage6DamagePercent = 0.01; // 1% health
MaxStage6DamagePercent = 0.025; // 2.5% health (player randomly loses a random amount of health between these two numbers every few mins when at Stage 6)

// Config for miscellaneous settings
DamageMicroscope = 0; // How much to damage the microscope after creating a cure (0 = disable, 90 = badly damage, 100 = ruin etc)	
TurnDeadInfectedPlayersToZombies = false; // (Experimental) if true then if the player dies while infected they'll turn into a zombie (some loot is dropped)
PlayerInfectedPercentageToZombify = 0.9; // How infected the player must be between 0.0 and 1.0 to turn into a zombie if they die

// Config for zombie skinned loot
ChanceOfBrain = 1.0; // 100% chance of a brain
ChanceOfBrainRuined = 0; // 0% chance of a ruined brain dropped by zombies by default
ChanceOfBones = 1.0; // 100% chance of dropping bones
ChanceOfBonesRuined = 0.95; // 95% chance of bones being ruined
ChanceOfGuts = 0.5; // 50% chance of dropping guts
ChanceOfGutsRuined = 0.95; // 95% chance of ruined
ChanceOfWorm = 0.5; // 50% chance of dropping a worm
ChanceOfWormRuined = 0.95; // 95% chance of worm being ruined

// Config for debugging & advanced settings
VirusMaxAmount = 1000; // Maxmimum virus agent count (don't touch unless you know what you're doing with DayZ virus invasibility etc)
VirusActivateAmount = 100; // Minimum virus agent count (don't touch unless you know what you're doing with DayZ virus invasibility etc)
VirusDeactivateAmount = 100; // Deactivation virus agent count (don't touch unless you know what you're doing with DayZ virus invasibility etc)
DebugOn = false; // Turns debug messages on/off