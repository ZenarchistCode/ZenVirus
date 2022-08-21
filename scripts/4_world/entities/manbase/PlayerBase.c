class ZombieSoundEffects
{
	ref static const array<string> Zombies_InfectSounds = { "ZombieSickness1_SoundSet", "ZombieSickness2_SoundSet", "ZombieSickness3_SoundSet" };
	ref static const array<string> Zombies_InfectSounds_Vanilla =
	{
		"bush_walkCro_SoundSet",
		"hardBushFall_SoundSet",
		"softBushFall_SoundSet",
		"hardTreeFall_SoundSet",
		"softTreeFall_SoundSet",
		"ZmbM_Normal_CallToArmsShort_Soundset",
		"ZmbF_Normal_CallToArmsShort_Soundset",
		"Mosin_jam_SoundSet",
		"ZmbM_Normal_HeavyHit_Soundset",
		"ZmbF_Normal_HeavyHit_Soundset"

		//"BearSnarl_SoundSet",
		//"WolfBark_SoundSet",
		//"BearRoarShort_SoundSet",
	};
	ref static const array<string> Zombies_AngrySounds_Male = // TODO: Add more?
	{
		"ZmbM_Normal_CallToArmsShort_Soundset",
		"ZmbM_Normal_HeavyHit_Soundset",
	};
	ref static const array<string> Zombies_AngrySounds_Female =
	{
		"ZmbF_Normal_CallToArmsShort_Soundset",
		"ZmbF_Normal_HeavyHit_Soundset",
	};
};

modded class PlayerBase
{
	// Sickness variables sync'd
	bool m_ForceUpdate = false;
	float m_LastZombieInfection = 0.0;
	float m_ZombieInfection = 0.0;
	int m_MakeZombieSound = -1;
	int m_LastMakeZombieSound = -1;
	bool m_VomitBlood = false;
	bool m_ZombieRedScreen = false;
	float m_ChanceOfZombieWhispers = 0.0;

	// Sound effects
	ref EffectSound m_ZombieSicknessSound = NULL;
	ref EffectSound m_ZombieAngrySound = NULL;

	void ~PlayerBase()
	{
		if (m_ZombieSicknessSound)
			m_ZombieSicknessSound.Stop();

		if (m_ZombieAngrySound)
			m_ZombieAngrySound.Stop();

		m_ZombieSicknessSound = null;
		m_ZombieAngrySound = null;
	}

	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		AddAction(ActionAnalyseVirus, InputActionMap);
	}

	// Init player
	override void Init()
	{
		super.Init();

		// Register variables that need to be sync'd to the client
		RegisterNetSyncVariableFloat("m_ZombieInfection");
		RegisterNetSyncVariableBool("m_VomitBlood");
		RegisterNetSyncVariableInt("m_MakeZombieSound");
		RegisterNetSyncVariableFloat("m_ChanceOfZombieWhispers");
	}

	// Triggered when variables are synchronized from the server to the client
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (m_MakeZombieSound != m_LastMakeZombieSound) // Everyone can hear this sound effect if the player is this badly infected
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(this.PlayRandomZombieAngrySound);
			if (m_MakeZombieSound > 10)
				m_MakeZombieSound = -1;
		}

		// If our 'last' zombie infection check was 0 and the latest infection sync is not zero, we likely just logged in so force a player check update for the red screen effect.
		if (m_LastZombieInfection == 0 && m_ZombieInfection > 0)
		{
			m_ForceUpdate = true;
			m_LastZombieInfection = m_ZombieInfection;
		}

		//ZV_ClientDebugMessage("Virus level: " + m_ZombieInfection + " (HasVirus=" + this.HasVirus() + ")");
	}

	// (Client) Plays a zombie angry sound
	void PlayRandomZombieAngrySound()
	{
		string soundSetAngryZ;
		if (IsMale())
		{
			soundSetAngryZ = ZombieSoundEffects.Zombies_AngrySounds_Male.GetRandomElement();
		}
		else
		{
			soundSetAngryZ = ZombieSoundEffects.Zombies_AngrySounds_Female.GetRandomElement();
		}

		m_ZombieAngrySound = SEffectManager.PlaySound(soundSetAngryZ, GetPosition());
		m_ZombieAngrySound.SetSoundAutodestroy(true);
		m_LastMakeZombieSound = m_MakeZombieSound;
	}

	// (Client) Plays a zombie sicknes sound
	void PlayRandomZombieSicknessSound()
	{
		float rand = Math.RandomFloat01();
		float whisperChance = m_ChanceOfZombieWhispers;

		if (rand > m_ChanceOfZombieWhispers)
		{
			return;
		}

		// Play sound at random location around player
		vector xyzRand = GetPosition();
		xyzRand[0] = xyzRand[0] + Math.RandomFloatInclusive(-20, 20);
		xyzRand[2] = xyzRand[2] + Math.RandomFloatInclusive(-20, 20);
		xyzRand[1] = GetGame().SurfaceY(xyzRand[0], xyzRand[2]) + Math.RandomInt(0, 10);

		// Play random sound
		string soundSetZ = "";

		if (Math.RandomFloat01() <= 0.1 && m_ChanceOfZombieWhispers >= 0.2) // 10% chance to play a vanilla scary sound if we are very infected
		{
			soundSetZ = ZombieSoundEffects.Zombies_InfectSounds_Vanilla.GetRandomElement();
		}
		else
		{
			soundSetZ = ZombieSoundEffects.Zombies_InfectSounds.GetRandomElement();
		}
		
		m_ZombieSicknessSound = SEffectManager.PlaySound(soundSetZ, xyzRand);
		//m_ZombieSicknessSound.SetSoundAutodestroy(true);
	}

	// Check if player has eaten bad food
	override bool Consume(ItemBase source, float amount, EConsumeType consume_type)
	{
		if (!source)
			return super.Consume(source, amount, consume_type);

		string type = source.GetType();
		type.ToLower();

		foreach(string s : GetZenVirusConfig().FoodVirus)
		{
			ZV_SendMessageDebug("bad food - " + s + "/" + type + " (kuru=" + GetSingleAgentCount(eAgents.BRAIN) + ")");
			if (type.Contains(s))
			{
				// Make player sick
				int rand = Math.RandomIntInclusive(1, GetZenVirusConfig().FoodVirusAdd);

				if (this.GetModifiersManager().IsModifierActive(eModifiers.MDF_IMMUNITYBOOST))
					rand = rand / 2;

				this.InsertAgent(VirusAgents.VIRUS, rand);
				ZV_SendMessageDebug("Inserted random virus for bad food - " + GetSingleAgentCount(VirusAgents.VIRUS));
				break;
			}
		}

		// If player is infected and consumes human steak, handle it according to server config.
		if (source.GetType() == "HumanSteakMeat" && this.HasVirus() && GetZenVirusConfig().HumanMeatVirusAdd != 0)
		{
			this.InsertAgent(VirusAgents.VIRUS, GetZenVirusConfig().HumanMeatVirusAdd);
			ZV_SendMessageDebug("Reduced virus agent by =" + GetZenVirusConfig().HumanMeatVirusAdd + "/" + GetSingleAgentCount(VirusAgents.VIRUS));

			if (GetZenVirusConfig().HumanMeatDisableKuru) // Allow bypassing kuru if player is infected with virus
			{
				int food_stage_type;
				Edible_Base edible_item = Edible_Base.Cast(source);

				if (!edible_item)
					return false;

				if (edible_item.GetFoodStage())
				{
					food_stage_type = edible_item.GetFoodStage().GetFoodStageType();
				}

				m_PlayerStomach.AddToStomach(source.GetType(), amount, food_stage_type, 0);
				edible_item.Consume(amount, this);
				return true; // Don't super.Consume() as this will give Kuru
			}
		}

		return super.Consume(source, amount, consume_type);
	}

	// Item - the instance of the item if player has item type
	bool HasItemType(string type)
	{
		array<EntityAI> items = {}; // Array for enumeration
		GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items); // Enumerate inventory
		for (int i = 0; i < items.Count(); i++) // Loop through items
		{
			// Check null and if type is what we're looking for
			if (!items[i] || items[i].GetType() != type)
				continue; // Continue iterating if not

			return true;
		}

		return false; // Return false if not found
	}

	// Sends a text message to the client
	// Print a debug message (client-only)
	void ZV_ClientDebugMessage(string message) { GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", "[" + GetIdentity().GetName() + "] " + message, "")); }
	void ZV_SendMessageDebug(string message) { if (GetZenVirusConfig().DebugOn) ZV_SendMessage(message); }
	void ZV_SendMessage(string message)
	{
		if (!IsAlive() || IsPlayerDisconnected())
		{
			return;
		}

		Param1<string> m_MessageParam = new Param1<string>("");
		if (GetGame().IsServer() && m_MessageParam && IsAlive() && message != "")
		{
			m_MessageParam.param1 = message;
			GetGame().RPCSingleParam(this, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, GetIdentity());
		}
	}

	// Called on each server and client tick
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);
		PlayerVirusCheck(deltaTime);
	}

	// Returns true if the player has been infected by the zombie virus
	bool HasVirus()
	{
		return m_ZombieInfection > 0 || m_ZombieInfection == -1; // "Hack" way to disable red screen based on server config. If virus = -1 it means we're infected, but don't change screen color.
	}

	// Analyze player virus info
	float m_VirusTicks = 0;
	float m_VirusRandCheck = 15.0;
	float m_VirusAgentsLastTick = 0;
	void PlayerVirusCheck(float deltaTime)
	{
		m_VirusTicks += deltaTime;

		if (m_VirusTicks < m_VirusRandCheck && !m_ForceUpdate)
		{
			return;
		}

		m_VirusRandCheck = Math.RandomFloat(15, 30);
		m_VirusTicks = 0;
		m_ForceUpdate = false;

		if (!GetGame().IsServer()) // Client-side - play hallucination sounds if infected
		{
			if (HasVirus())
			{
				PlayRandomZombieSicknessSound();
			}

			UpdateZombieVisualEffect();
		}
		else // Server-side - perform important virus checks on this player
		{
			if (GetSingleAgentCount(VirusAgents.VIRUS) <= 0)
			{
				ZV_SendMessageDebug("HasVirus = false");
				return;
			}

			// This makes sure the virus infection amount shrinks if it's below Stage 1 infection.
			if (GetSingleAgentCountNormalized(VirusAgents.VIRUS) < GetZenVirusConfig().Stage1)
			{
				InsertAgent(VirusAgents.VIRUS, -(m_VirusAgentsLastTick * (Math.RandomInt(100, 2000)))); // Normalized is a % of infection, so multiplying by 100-1200 is necessary to have an effect on infection agents (0.001 * 1000 = 1 agent)
				if (GetSingleAgentCount(VirusAgents.VIRUS) <= 0)
				{
					RemoveAgent(VirusAgents.VIRUS);
				}
			}

			// Server-side debug update
			m_VirusAgentsLastTick = GetSingleAgentCountNormalized(VirusAgents.VIRUS);
		}
	}

	// Check for zombie hits (or infected animals) - only infect player if they are not already infected
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (source && source.IsZombie() && HasVirus()) // Don't add more virus if we're already infected
		{
			// Do this first - that way player only gets wound infection if hit AFTER they are made to bleed by super.EEHitBy()
			if (GetSingleAgentCount(eAgents.WOUND_AGENT) <= 0 && GetBleedingManagerServer() && GetBleedingManagerServer().m_BleedingSources.Count() > 0 && Math.RandomFloat01() < GetZenVirusConfig().ChanceOfWoundInfectionBleed)
			{
				this.InsertAgent(eAgents.WOUND_AGENT, 1);
				ZV_SendMessageDebug("Inserted wound infection due to bleeding scratch - Count=" + GetSingleAgentCount(eAgents.WOUND_AGENT));
			}
		}

		// If player is bleeding, inject wound agent
		if (source && source.IsZombie() && GetSingleAgentCount(eAgents.WOUND_AGENT) <= 0 && GetBleedingManagerServer() && GetBleedingManagerServer().m_BleedingSources.Count() > 0 && Math.RandomFloat01() < GetZenVirusConfig().ChanceOfWoundInfectionBleed)
		{
			this.InsertAgent(eAgents.WOUND_AGENT, 1);
			ZV_SendMessageDebug("Inserted wound infection due to bleeding scratch - Count=" + GetSingleAgentCount(eAgents.WOUND_AGENT));
		}

		// Check if this creature is on the list
		bool infectedCreature = false;
		string type = source.GetType();
		type.ToLower();
		foreach(string s : GetZenVirusConfig().CreatureGuaranteedVirus)
		{
			s.ToLower();
			if (type.Contains(s))
			{
				infectedCreature = true;
				break;
			}
		}

		// Analyze hit to see if we need to add virus agents
		if (!HasVirus() && (source.IsZombie() || infectedCreature))
		{
			if (m_MeleeFightLogic.IsInBlock()) // Don't infect player if they blocked the attack
			{
				return;
			}

			float rand;
			if (Math.RandomFloat01() < GetZenVirusConfig().VirusChancePerScratch)
			{
				rand = Math.RandomFloat(GetZenVirusConfig().VirusAddPerScratchMin, GetZenVirusConfig().VirusAddPerScratchMax);

				if (this.GetModifiersManager().IsModifierActive(eModifiers.MDF_IMMUNITYBOOST))
					rand = rand / 2;

				this.InsertAgent(VirusAgents.VIRUS, rand);
				ZV_SendMessageDebug("Inserted virus agent due to zed scratch - Count=" + GetSingleAgentCount(VirusAgents.VIRUS) + "/1000");
			}

			if (GetBleedingManagerServer() && GetBleedingManagerServer().m_BleedingSources && GetBleedingManagerServer().m_BleedingSources.Count() > 0 && !HasVirus())
			{
				rand = Math.RandomInt(GetZenVirusConfig().VirusAddPerBleedMin, GetZenVirusConfig().VirusAddPerBleedMax);

				if (this.GetModifiersManager().IsModifierActive(eModifiers.MDF_IMMUNITYBOOST))
					rand = rand / 2;

				this.InsertAgent(VirusAgents.VIRUS, rand);
				ZV_SendMessageDebug("Inserted virus agent due to bleed - Count=" + GetSingleAgentCount(VirusAgents.VIRUS) + "/1000");
			}

			if (infectedCreature && !HasVirus() && !this.GetModifiersManager().IsModifierActive(eModifiers.MDF_IMMUNITYBOOST)) // Infect player straight away if scratched by an infected animal without an immunity boost
			{
				this.InsertAgent(100);
				ZV_SendMessageDebug("Inserted virus agent due to infected creature - Count=" + GetSingleAgentCount(VirusAgents.VIRUS) + "/1000");
			}
		}
	}

	// Include vomiting blood from zombie virus as particle effect
	override void OnParticleEvent(string pEventType, string pUserString, int pUserInt)
	{
		super.OnParticleEvent(pEventType, pUserString, pUserInt);

		if (!GetGame().IsDedicatedServer())
		{
			if (pUserInt == 123456) // 123456 is ID for vomiting effect. The current implementation is WIP.
			{
				PlayerBase player = PlayerBase.Cast(this);
				int boneIdx = player.GetBoneIndexByName("Head");

				if (boneIdx != -1)
				{
					EffectParticle eff;

					if (m_SyncedModifiers & eModifierSyncIDs.MODIFIER_SYNC_CONTAMINATION2)
					{
						eff = new EffVomitBlood();
					}
					else
					{
						eff = new EffVomit();
					}

					if (m_VomitBlood)
					{
						eff = new EffVomitBlood();
						m_VomitBlood = false;
					}

					eff.SetDecalOwner(player);
					eff.SetAutodestroy(true);
					SEffectManager.PlayInWorld(eff, vector.Zero);
					Particle p = eff.GetParticle();
					player.AddChild(p, boneIdx);
				}
			}
		}
	}

	// Check if killed
	override void EEKilled(Object killer)
	{
		if (!GetZenVirusConfig().TurnDeadInfectedPlayersToZombies)
		{
			super.EEKilled(killer);
			return;
		}

		if (GetSingleAgentCountNormalized(VirusAgents.VIRUS) >= 0.9)
		{
			CreateVirusInfectedZombiePlayer();
		}
		
		super.EEKilled(killer);
	}

	// Spawn an infected zombie on this dead player if they died from the virus
	void CreateVirusInfectedZombiePlayer()
	{
		vector zombieOffset = GetPosition() - "0.3 0 0.3";

		ZombieBase humanZ;

		string zombieType = "ZmbM_CitizenASkinny_Base";
		if (!IsMale())
		{
			zombieType = "ZmbF_SurvivorNormal_Base";
		}

		humanZ = ZombieBase.Cast(GetGame().CreateObjectEx(zombieType, zombieOffset, ECE_PLACE_ON_SURFACE | ECE_INITAI));
		humanZ.TransferAttachmentsFromPlayer(this);
		humanZ.SetOrientation(GetOrientation());

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Delete, 2500);
	}

	// Check if zeds can target us
	override bool CanBeTargetedByAI(EntityAI ai)
	{
		if (ai.IsZombie())
		{
			if (GetSingleAgentCountNormalized(VirusAgents.VIRUS) >= GetZenVirusConfig().StageGivesIgnoreZombies && GetZenVirusConfig().StageGivesIgnoreZombies != 0)
			{
				ZombieBase zb = ZombieBase.Cast(ai);

				if (!zb)
					return super.CanBeTargetedByAI(ai);

				return zb.m_IsInjured;
			}
		}

		return super.CanBeTargetedByAI(ai);
	}

	// Schedule a delayed tip to the player (if enabled in server json config)
	ref Timer m_TipTimer = null;
	void ScheduleSurvivalTip()
	{
		if (!m_TipTimer)
		{
			m_TipTimer = new Timer(CALL_CATEGORY_SYSTEM);
		}
		else
		if (m_TipTimer.IsRunning())
		{
			return;
		}

		m_TipTimer.Run(4 + Math.RandomIntInclusive(0, 6), this, "ZV_NeedMedsMsg", NULL, false);
	}

	// Sends a tip if enabled in server config
	string m_lastTip = "";
	void ZV_NeedMedsMsg()
	{
		if (GetSingleAgentCountNormalized(VirusAgents.VIRUS) <= 0.2)
		{
			ZV_SendMessage("I don't feel so good... I think I might have caught a virus from the infected...");
			return;
		}

		array<string> tips = new array<string>;
		if (!HasItemType("Zen_Virus_Brain") && m_lastTip != GetZenVirusConfig().Tip1)
		{
			tips.Insert(GetZenVirusConfig().Tip1);
		}
		else
		if (!HasItemType("Zen_Virus_Cure_Microscope") && m_lastTip != GetZenVirusConfig().Tip2)
		{
			tips.Insert(GetZenVirusConfig().Tip2);
		}
		else
		if (!HasItemType("Zen_Virus_Cure_Petridish") && m_lastTip != GetZenVirusConfig().Tip3)
		{
			tips.Insert(GetZenVirusConfig().Tip3);
		}
		else
		if (!HasItemType("Syringe") && m_lastTip != GetZenVirusConfig().Tip4)
		{
			tips.Insert(GetZenVirusConfig().Tip4);
		}
		else
		if (!HasItemType("BloodBagFull") && m_lastTip != GetZenVirusConfig().Tip5)
		{
			tips.Insert(GetZenVirusConfig().Tip5);
		}
		else
		{
			tips.Insert(GetZenVirusConfig().Tip6);
		}

		m_lastTip = tips.GetRandomElement();
		ZV_SendMessage(m_lastTip);
	}

	// Zombie Visual Effects
	bool m_StoppedZombieVisualEffect = false;
	void UpdateZombieVisualEffect()
	{
		if (m_ZombieInfection <= 0.0 && !m_StoppedZombieVisualEffect)
		{
			auto requester1 = PPERequesterBank.GetRequester(PPERequester_ZenVirusEffect);
			if (requester1)
				requester1.Stop();

			m_StoppedZombieVisualEffect = true;
		}
		else
		{
			if (m_ZombieInfection != -1)
			{
				m_StoppedZombieVisualEffect = false;
				auto requester2 = PPERequester_ZenVirusEffect.Cast(PPERequesterBank.GetRequester(PPERequester_ZenVirusEffect));
				requester2.ZV_SetEffectValues(m_ZombieInfection);
			}
		}
	}
};