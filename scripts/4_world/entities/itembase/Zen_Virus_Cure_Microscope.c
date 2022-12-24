class Zen_Virus_Cure_Microscope : ItemBase
{
	const string 				ATTACHMENT_SLOT_BRAIN = "Material_Brain";
	const string 				ATTACHMENT_SLOT_BLOODBAG = "Material_BloodBagFull";
	const string 				ATTACHMENT_SLOT_PETRIDISH = "Material_Petridish";
	const string 				ATTACHMENT_SLOT_BATTERY = "BatteryD";
	static const string 		MICROSCOPE_ATTACH_SOUND = "sparkplug_attach_SoundSet";
	static const string 		MICROSCOPE_DETACH_SOUND = "sparkplug_detach_SoundSet";
	bool m_LastState			= false;
	ChemlightLight 				m_Light;
	ref Timer					m_AnalyseVirusTimer;

	// Server->client sync
	bool m_TurnedOn = false;
	float m_TimeTotal = 0;
	float m_TimeRemaining = 0;
	private ref Timer m_LockTimerUpdate;

	void Zen_Virus_Cure_Microscope()
	{
		// Register sync vars
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
		RegisterNetSyncVariableBool("m_IsPlaceSound");
		RegisterNetSyncVariableBool("m_TurnedOn");
		RegisterNetSyncVariableFloat("m_TimeTotal");
		RegisterNetSyncVariableFloat("m_TimeRemaining");
	}

	void ~Zen_Virus_Cure_Microscope()
	{
		if (m_AnalyseVirusTimer && m_AnalyseVirusTimer.IsRunning())
			m_AnalyseVirusTimer.Stop();

		if (m_LockTimerUpdate && m_LockTimerUpdate.IsRunning())
			m_LockTimerUpdate.Stop();
	}

	// Override name when in use
	override bool NameOverride(out string output)
	{
		if (m_TurnedOn)
		{
			float progress = ((m_TimeTotal - m_TimeRemaining) / m_TimeTotal) * 100;
			string progressStr = MiscGameplayFunctions.TruncateToS(progress);

			if (progressStr.IndexOf(".") > 0)
				progressStr = progressStr.Substring(0, progressStr.IndexOf("."));

			output = "#STR_ZEN_ANALYZE_VIRUS" + " (" + progressStr + "%)";
			output.ToUpper();
			return true;
		};

		return false;
	};

	// Allow it to be "placed"
	override bool IsDeployable()
	{
		return true;
	}

	// Allows for placing
	override bool IsOneHandedBehaviour()
	{
		return true;
	}

	// Add territory flag persistence
	override bool IsRefresherSignalingViable()
	{
		return !IsRuined();
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (GetGame().IsDedicatedServer())
			return;

		if (m_TurnedOn != m_LastState)
		{
			m_LastState = m_TurnedOn;

			if (m_TurnedOn) 
			{
				// Microscope just turned on
				SEffectManager.PlaySound("turnOnRadio_SoundSet", GetPosition());
				CreateLight();
			}
			else 
			{
				// Microscope just turned off
				SEffectManager.PlaySound("turnOnRadio_SoundSet", GetPosition());

				if (m_Light)
				{
					m_Light.FadeOut();
				}
			}
		}
	}

	// Creates a green glow on the microscope when it's being used
	void CreateLight()
	{
		if (GetGame().IsClient())
		{
			m_Light = ChemlightLight.Cast(ScriptedLightBase.CreateLight(ChemlightLight, "0 0 0"));
			m_Light.AttachOnObject(this, "0 0.2 0");
			m_Light.SetColorToWhite();
		}
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		if (attachment.GetType() == "BloodBagFull" || attachment.GetType() == "BloodBagIV")
		{
			return attachment.GetQuantity() >= attachment.GetQuantityMax() - 50 && super.CanReceiveAttachment(attachment, slotId);
		}

		return super.CanReceiveAttachment(attachment, slotId);
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		if (item && !GetGame().IsDedicatedServer())
		{
			SEffectManager.PlaySound(MICROSCOPE_ATTACH_SOUND, GetPosition());
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (item && !GetGame().IsDedicatedServer())
		{
			SEffectManager.PlaySound(MICROSCOPE_DETACH_SOUND, GetPosition());
		}
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		if (!super.CanPutInCargo(parent)) 
		{ 
			return false; 
		}

		if (m_TurnedOn)
		{
			return false;
		}

		return true;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		if (!super.CanPutIntoHands(parent))
		{
			return false;
		}

		if (m_TurnedOn)
		{
			return false;
		}

		return true;
	}

	// Only allow vials to be stored in the microscope
	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		return super.CanReceiveItemIntoCargo(item) && (item.GetType() == "Zen_Virus_PathogenVial" || item.GetType() == "Zen_Virus_AntiBodiesVial");
	}

	// Don't display cargo slots if they're empty to avoid confusion about what can go in it
	override bool CanDisplayCargo()
	{
		return super.CanDisplayCargo() && GetInventory().GetCargo().GetItemCount() > 0;
	}

	void LockAttachments()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BATTERY));
		if (item)
		{
			item.LockToParent();
		}

		item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_PETRIDISH));
		if (item)
		{
			item.LockToParent();
		}
		
		item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BRAIN));
		if (item)
		{
			item.LockToParent();
		}

		item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BLOODBAG));
		if (item)
		{
			item.LockToParent();
		}
	}

	void UnlockAttachments()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BATTERY));
		if (item)
		{
			item.UnlockFromParent();
		}

		item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_PETRIDISH));
		if (item)
		{
			item.UnlockFromParent();
		}

		item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BRAIN));
		if (item)
		{
			item.UnlockFromParent();
		}

		item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BLOODBAG));
		if (item)
		{
			item.UnlockFromParent();
		}
	}

	bool HasBattery()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BATTERY));
		return item && !item.IsRuined();
	}

	bool HasPetridish()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_PETRIDISH));
		return item && !item.IsRuined();
	}

	bool HasBrain()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BRAIN));
		return item && !item.IsRuined();
	}

	bool HasBloodBagFull()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BLOODBAG));
		return item && !item.IsRuined();
	}

	bool HasRequiredIngredients()
	{
		return HasBloodBagFull() && HasBrain() && HasPetridish() && HasBattery();
	}

	void Delete_BloodBag()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BLOODBAG));

		if (item)
		{
			GetGame().ObjectDelete(item);
		}
	}

	void Delete_Brain()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BRAIN));

		if (item)
		{
			GetGame().ObjectDelete(item);
		}
	}

	void Delete_Petridish()
	{
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_PETRIDISH));

		if (item)
		{
			GetGame().ObjectDelete(item);
		}
	}

	void Ruin_Battery()
	{
		Battery9V item = Battery9V.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BATTERY));

		if (item)
		{
			item.GetCompEM().AddEnergy(-100);
		}
	}

	void StartAnalysis(float actionTime)
	{
		if (!HasRequiredIngredients())
		{
			m_TimeRemaining = 0;
			SetSynchDirty();
			return;
		}

		if (!m_AnalyseVirusTimer)
			m_AnalyseVirusTimer = new Timer();

		if (!m_AnalyseVirusTimer.IsRunning()) // Make sure the timer is NOT running already
		{
			// Begin analysis
			LockAttachments();
			m_TurnedOn = true;
			m_AnalyseVirusTimer.Run(actionTime, this, "AnalyseVirus", NULL, false);

			// Start client updater timer (shows progression client-side)
			if (!m_LockTimerUpdate)
				m_LockTimerUpdate = new Timer();

			m_TimeRemaining = actionTime;
			m_TimeTotal = GetZenVirusConfig().VirusAnalysisDelay;
			m_LockTimerUpdate.Run(10, this, "UpdateTimer", NULL, true);

			// Sync to client
			SetSynchDirty();
		}
	}

	void UpdateTimer()
	{
		m_TimeRemaining = m_TimeRemaining - 10;

		if (m_TimeRemaining <= 0 && m_LockTimerUpdate && m_LockTimerUpdate.IsRunning())
		{
			m_TimeRemaining = 0;
			m_LockTimerUpdate.Stop();
		}

		// Notify client of progress
		if (GetGame().IsDedicatedServer())
		{
			SetSynchDirty();
		}
	}

	void AnalyseVirus()
	{
		vector pos_rnd;
		if (!GetInventory().CreateInInventory("Zen_Virus_AntiBodiesVial"))
		{
			GetGame().CreateObject("Zen_Virus_AntiBodiesVial", this.GetPosition() + "0 0 0.2", false);
		}

		if (!GetInventory().CreateInInventory("Zen_Virus_PathogenVial"))
		{
			GetGame().CreateObject("Zen_Virus_PathogenVial", this.GetPosition() + "0 0 0.3", false);
		}

		UnlockAttachments();
		Delete_BloodBag();
		Delete_Brain();
		Delete_Petridish();
		Ruin_Battery();

		if (GetZenVirusConfig().DamageMicroscope != 0)
		{
			this.AddHealth(GetZenVirusConfig().DamageMicroscope);
		}

		m_TurnedOn = false;
		SetSynchDirty();

		m_AnalyseVirusTimer.Stop();
		m_AnalyseVirusTimer = null;
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}

	// Save microscope state
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		ctx.Write(m_TimeRemaining);
	}

	// Load microscope state
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_TimeRemaining))
		{
			m_TimeRemaining = 0;
		}

		if (m_TimeRemaining > 0)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(StartAnalysis, 1000, false, m_TimeRemaining);
		}

		return true;
	}
}

// Static version of microscope which can be spawned/placed by server admin but not touched by player
class Zen_Virus_Cure_Microscope_Static : Zen_Virus_Cure_Microscope
{
	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}

	override bool CanPutIntoHands(EntityAI player)
	{
		return false;
	}

	override bool IsRefresherSignalingViable()
	{
		return false;
	}
}