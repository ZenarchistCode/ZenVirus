class ZombieVirusMdfr : ModifierBase
{
	float m_Time = 999999; // Force a virus tick update initially.
	float m_RandomTickCheck = 0;

	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID = VirusModifiers.MDF_VIRUS;
		m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive = 0.1;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		if (player.GetSingleAgentCount(VirusAgents.VIRUS) >= GetZenVirusConfig().VirusActivateAmount)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	override protected void OnActivate(PlayerBase player)
	{
		player.m_VirusAgentsLastTick = 0;
		player.IncreaseDiseaseCount();
		player.ZV_SendMessageDebug("Virus Stage 1 activated. - Count=" + player.GetSingleAgentCount(VirusAgents.VIRUS));

		if (GetZenVirusConfig().VirusRedScreen)
		{
			player.m_ZombieInfection = player.GetSingleAgentCountNormalized(VirusAgents.VIRUS); // Used for starting client-side hallucinations
		}
		else
		{
			player.m_ZombieInfection = -1;
		}
		player.SetSynchDirty();
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		player.DecreaseDiseaseCount();
		player.m_ZombieInfection = 0; // Used to stop client-side hallucinations
		player.SetSynchDirty();
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		if (player.GetSingleAgentCount(VirusAgents.VIRUS) < GetZenVirusConfig().VirusDeactivateAmount)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Display a random tip to the player to let them know they're sick and what to do
	// TODO: Improve and config
	void DisplayTip(PlayerBase player)
	{
		if (GetZenVirusConfig().SurvivalTipChance > 0)
		{
			float r = Math.RandomFloat01();
			player.ZV_SendMessageDebug("Schedule survival tip = " + r + " / " + GetZenVirusConfig().SurvivalTipChance);
			if (r < GetZenVirusConfig().SurvivalTipChance)
			{
				player.ScheduleSurvivalTip();
			}
		}
	}

	// Called each server tick to update the player's virus status
	override protected void OnTick(PlayerBase player, float deltaT)
	{
		m_Time += deltaT;

		if (m_Time < (GetZenVirusConfig().VirusTickSecs + m_RandomTickCheck))
		{
			return;
		}

		// Get normalized % of infection (eg. 0.1 = 10%)
		float virusLvl = player.GetSingleAgentCountNormalized(VirusAgents.VIRUS);

		// Reset timer
		m_Time = 0;
		m_RandomTickCheck = Math.RandomFloat(0, (1 - virusLvl) * GetZenVirusConfig().VirusTickSecsRand); // Check more and more frequently the more the player gets sick
		int r;

		// If the virus has shrunk to zero, deactivate the condition
		if (virusLvl == 0)
		{
			DeactivateCondition(player);
			player.m_ZombieInfection = 0;
			return;
		}

		if (virusLvl >= GetZenVirusConfig().Stage5)
		{
			// Stop playing whispers as I'm sure the player is sick of them by now lol
			player.m_ChanceOfZombieWhispers = 0; // Client-side. Player is so sick they're making real zombie noises now, so stop the hallucination ones.
			player.SetSynchDirty();
		}
		else
		{
			player.m_ChanceOfZombieWhispers = virusLvl / 4; // Client-side. Player is not extremely sick yet. Gradually increase the odds of hallucinations.
			player.SetSynchDirty();
		}

		player.ZV_SendMessageDebug("Virus tick - Normal=" + virusLvl + " (" + player.GetSingleAgentCount(VirusAgents.VIRUS) + "/1000) - Health = " + player.GetHealth() + " Blood = " + player.GetHealth("GlobalHealth", "Blood") + " ChanceOfWhisper=" + player.m_ChanceOfZombieWhispers);

		if (virusLvl < GetZenVirusConfig().Stage1) // Not sick enough yet for symptoms
		{
			return;
		}

		// Sync zombie infection % to client (used for visual effect - making screen turn red gradually over time)
		if (GetZenVirusConfig().VirusRedScreen)
		{
			player.m_ZombieInfection = virusLvl;
		}
		else
		{
			player.m_ZombieInfection = -1;
		}

		// STAGE 6 INFECTION (99%) - BEGIN LOSING HEALTH & LAUGHING
		if (virusLvl >= GetZenVirusConfig().Stage6)
		{
			if (Math.RandomFloat01() <= GetZenVirusConfig().Stage6ZombieYellChance) // 10% chance of a stage 6 symptom by default
			{
				player.ZV_SendMessageDebug("STAGE 6 SYMPTOM");

				if (Math.RandomFloat01() < 0.25) // 25% chance of laughing, 75% chance of making a zombie sound
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_LAUGHTER);
					player.SetSynchDirty();
					player.ZV_SendMessageDebug("Trigger zombie virus laughter");
				}
				else
				{
					player.m_MakeZombieSound++;
					player.SetSynchDirty();
					player.ZV_SendMessageDebug("Trigger zombie virus scream");
				}

				// Remove a small percentage of health from the player
				player.AddHealth(-(player.GetHealth() * Math.RandomFloat(GetZenVirusConfig().MinStage6DamagePercent, GetZenVirusConfig().MaxStage6DamagePercent)));

				// 20% chance of vomiting blood
				if (Math.RandomInt(0, 10) < 2)
				{
					player.AddHealth("GlobalHealth", "Blood", -(Math.RandomInt(GetZenVirusConfig().VomitBloodLossMin, GetZenVirusConfig().VomitBloodLossMax)));
					player.m_VomitBlood = true;
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
					player.SetSynchDirty();
				}

				// Display tip
				DisplayTip(player);
				return;
			}
		}

		// STAGE 5 INFECTION (90%) - BEGIN RANDOM BLEEDS, UNCON AND MAKE ZOMBIE SOUNDS
		if (virusLvl >= GetZenVirusConfig().Stage5)
		{
			if (Math.RandomFloat01() < virusLvl / Math.RandomInt(20, 100))
			{
				r = Math.RandomIntInclusive(1, 3);
				player.ZV_SendMessageDebug("STAGE 5 SYMPTOM - " + r);

				if (r == 3)
				{
					player.m_UnconsciousEndTime = -Math.RandomInt(8, 12);
					player.SetHealth("", "Shock", 0);
					DisplayTip(player);
					return;
				}

				if (player.GetBleedingManagerServer().m_BleedingSources.Count() <= 0)
				{
					if (r == 1)
					{
						if (!player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(player.m_BleedingSourcesLow.GetRandomElement()))
						{
							player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(player.m_BleedingSourcesUp.GetRandomElement());
						}
					}
					else
					if (r == 2)
					{
						if (!player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(player.m_BleedingSourcesUp.GetRandomElement()))
						{
							player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(player.m_BleedingSourcesLow.GetRandomElement());
						}
					}
				}

				player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);

				// Display tip
				DisplayTip(player);
				return;
			}
			else
			if (Math.RandomFloat01() < virusLvl / Math.RandomInt(10, 30))
			{
				DayZPlayerSyncJunctures.SendKuruRequest(player, 5000);
				player.m_MakeZombieSound++;
				player.SetSynchDirty();
				return;
			}
		}

		// STAGE 4 INFECTION (75%) - BEGIN VOMITING BLOOD
		if (virusLvl >= GetZenVirusConfig().Stage4)
		{
			if (Math.RandomFloat01() < virusLvl / Math.RandomInt(5, 20))
			{
				r = Math.RandomIntInclusive(1, 2);
				player.ZV_SendMessageDebug("STAGE 4 SYMPTOM - " + r);
				if (r == 1)
				{
					player.m_VomitBlood = true;
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
					player.SetSynchDirty();
					player.AddHealth("GlobalHealth", "Blood", -(Math.RandomInt(GetZenVirusConfig().VomitBloodLossMin, GetZenVirusConfig().VomitBloodLossMax)));
				}
				else
				{
					DayZPlayerSyncJunctures.SendKuruRequest(player, 5000);
					player.m_MakeZombieSound++;
					player.SetSynchDirty();
				}
				
				// Display tip
				DisplayTip(player);
				return;
			}
		}

		// STAGE 3 INFECTION (50%) - BEGIN SHIVER & BLUR
		if (virusLvl >= GetZenVirusConfig().Stage3)
		{
			if (Math.RandomFloat01() < virusLvl / Math.RandomInt(1, 10))
			{
				r = Math.RandomIntInclusive(1, 3);
				player.ZV_SendMessageDebug("STAGE 3 SYMPTOM - " + r);
				switch (r)
				{
					case 1:
						player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);

						if (virusLvl >= 0.75) // Cough blood
						{
							player.AddHealth("GlobalHealth", "Blood", -Math.RandomIntInclusive(10, 100));
							if (!player.FindAttachmentBySlotName("Gloves"))
							{
								PluginLifespan module_lifespan = PluginLifespan.Cast(GetPlugin(PluginLifespan));
								module_lifespan.UpdateBloodyHandsVisibility(player, true);
							}
						}
						
						break;
					case 2:
						player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_FEVERBLUR);
						break;
					case 3:
						player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
						player.AddHealth(Math.RandomFloat(-1.0, -2.5));
						break;
				}

				// Small chance to start making zombie sounds
				if (Math.RandomFloat01() < virusLvl / Math.RandomInt(20, 60))
				{
					player.m_MakeZombieSound++;
					player.SetSynchDirty();
					return;
				}

				// Display tip
				DisplayTip(player);
				return;
			}
		}

		// STAGE 2 INFECTION (25%) - BEGIN PHYSICAL SYMPTOMS
		if (virusLvl >= GetZenVirusConfig().Stage2)
		{
			if (Math.RandomFloat01() < (virusLvl / Math.RandomInt(1, 20)))
			{
				r = Math.RandomIntInclusive(1, 3);
				player.ZV_SendMessageDebug("STAGE 2 SYMPTOM - " + r);
				switch (r)
				{
					case 1:
						player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HOT);
						break;
					case 2:
						player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_FREEZE);
						break;
					case 3:
						player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);
						if (virusLvl >= GetZenVirusConfig().Stage3 && !player.FindAttachmentBySlotName("Gloves"))
						{
							PluginLifespan module_lifespan2 = PluginLifespan.Cast(GetPlugin(PluginLifespan));
							module_lifespan2.UpdateBloodyHandsVisibility(player, true);
						}
						break;
				}

				// Display tip
				DisplayTip(player);
				return;
			}
		}

		// STAGE 1 INFECTION - BEGIN AUDIBLE HALLUCINATIONS & VERY RARE SYMPTOMS
		// (Hallucinations are handled client-side)

		if (Math.RandomFloat01() <= GetZenVirusConfig().ChanceOfRandomVomit)
		{
			player.ZV_SendMessageDebug("STAGE 1 SYMPTOM - RANDOM VOMIT");
			player.AddHealth("GlobalHealth", "Blood", -(Math.RandomInt(GetZenVirusConfig().VomitBloodLossMin, GetZenVirusConfig().VomitBloodLossMax)));
			player.m_VomitBlood = true;
			player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
			return;
		}

		if (Math.RandomFloat01() <= GetZenVirusConfig().ChanceOfRandomZombieYell)
		{
			player.ZV_SendMessageDebug("STAGE 1 SYMPTOM - RANDOM ZOMBIE GROWL");
			DayZPlayerSyncJunctures.SendKuruRequest(player, 5000);
			player.m_MakeZombieSound++;
			player.SetSynchDirty();
			return;
		}

		//player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HOT);
		//player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
		//player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);
		//player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
		//player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
		//player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HAND_SHIVER);
		//player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_LAUGHTER);
		//player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_SNEEZE);
	}
};