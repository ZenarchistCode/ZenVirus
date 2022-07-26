class Zen_Virus_Cure_Microscope : ItemBase
{
	const string 				ATTACHMENT_SLOT_BRAIN = "Material_Brain";
	const string 				ATTACHMENT_SLOT_BLOODBAG = "Material_BloodBagFull";
	const string 				ATTACHMENT_SLOT_PETRIDISH = "Material_Petridish";
	const string 				ATTACHMENT_SLOT_BATTERY = "BatteryD";
	static const string 		MICROSCOPE_ATTACH_SOUND = "sparkplug_attach_SoundSet";
	static const string 		MICROSCOPE_DETACH_SOUND = "sparkplug_detach_SoundSet";
	bool m_TurnedOn				= false;
	bool m_LastState			= false;
	ChemlightLight 				m_Light;
	ref Timer					m_AnalyseVirusTimer;

	void Zen_Virus_Cure_Microscope()
	{
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
		RegisterNetSyncVariableBool("m_IsPlaceSound");
		RegisterNetSyncVariableBool("m_TurnedOn");
	}

	void ~Zen_Virus_Cure_Microscope()
	{
		if (m_AnalyseVirusTimer)
		{
			m_AnalyseVirusTimer.Stop();
			m_AnalyseVirusTimer = null;
		}
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", "m_TurnedOn=" + m_TurnedOn + " - LastState=" + m_LastState, ""));
		if (m_TurnedOn != m_LastState)
		{
			m_LastState = m_TurnedOn;

			if (m_TurnedOn) // Microscope just turned on
			{
				if (!GetGame().IsServer())
				{
					SEffectManager.PlaySound("turnOnRadio_SoundSet", GetPosition());
				}
				
				//CreateLight();
			}
			else // Microscope just turned off
			{
				if (!GetGame().IsServer())
				{
					SEffectManager.PlaySound("turnOnRadio_SoundSet", GetPosition());
				}

				//if (m_Light)
				//{
				//	m_Light.FadeOut();
				//}
			}
		}
	}

	// Creates a green glow on the microscope when it's being used (todo: fix, this doesn't work currently for some reason even though it works on other mods I've made)
	void CreateLight()
	{
		m_Light = ChemlightLight.Cast(ScriptedLightBase.CreateLight(ChemlightLight, "0 0 0"));
		m_Light.AttachOnMemoryPoint(this, "light");
		m_Light.SetColorToWhite();
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

		if (item && !GetGame().IsServer())
		{
			SEffectManager.PlaySound(MICROSCOPE_ATTACH_SOUND, GetPosition());
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (item && !GetGame().IsServer())
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
		ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_BATTERY));

		if (item)
		{
			item.SetQuantity(0);
			item.SetHealth(0);
		}
	}

	void StartAnalysis()
	{
		if (!m_AnalyseVirusTimer)
		{
			m_AnalyseVirusTimer = new Timer(CALL_CATEGORY_SYSTEM);
		}

		if (!m_AnalyseVirusTimer.IsRunning()) // Make sure the timer is NOT running already
		{
			LockAttachments();
			m_TurnedOn = true;
			SetSynchDirty();
			m_AnalyseVirusTimer.Run(Math.RandomIntInclusive(8 ,12), this, "AnalyseVirus", NULL, false);
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
}