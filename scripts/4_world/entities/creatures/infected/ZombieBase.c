modded class ZombieBase extends DayZInfected
{
	ref BloodVomitZombie m_BloodVomitEffect;
	ref BloodVomitSplash m_Bloodsplash;
	Particle m_BloodVomit;
	Particle m_BloodVomitsplash;
	ref Timer BloodVomitTimer;
	float ZombieVomitTime = Math.RandomInt(60, 300);
	bool m_IsInjured = false;

	void ZombieBase()
	{
		StartVomit();
	}

	override bool CanBeSkinned()
	{
		return true;
	}

	void StartVomit()
	{
		BloodVomitTimer = new Timer();
		BloodVomitTimer.Run(ZombieVomitTime, this, "BloodVomit", NULL, true);
	}

	void BloodVomit()
	{
		if (!IsAlive())
		{
			BloodVomitTimer.Stop();
		}
		else 
		{
			if (!GetGame().IsServer())
			{
				int mouth = GetBoneIndex("rMouth");
				m_BloodVomitEffect = new BloodVomitZombie();
				SEffectManager.PlayInWorld(m_BloodVomitEffect, "0 1.5 0.3");
				m_BloodVomit = m_BloodVomitEffect.GetParticle();
				AddChild(m_BloodVomit, mouth);

				m_Bloodsplash = new BloodVomitSplash();
				SEffectManager.PlayInWorld(m_Bloodsplash, GetPosition());
				m_BloodVomitsplash = m_Bloodsplash.GetParticle();
				m_BloodVomitsplash.ScaleParticleParam(EmitorParam.LIFETIME, 0.1);

				VomitSound();
			}
		}
	}

	// Sounds
	ref SoundObject soundObjVomit; // Sound for Vomit
	ref SoundObjectBuilder soundBuilderVomit;
	AbstractWave BloodVomitSounds;

	private bool m_playStatus = true; // Will always play sound, make a setter/getter if you wish to control this via conditions via other classes

	AbstractWave MSaySoundSet(string name)
	{
		SoundParams soundParams = new SoundParams(name);
		soundBuilderVomit = new SoundObjectBuilder(soundParams);
		soundObjVomit = soundBuilderVomit.BuildSoundObject();
		soundObjVomit.SetPosition(GetPosition());
		return GetGame().GetSoundScene().Play3D(soundObjVomit, soundBuilderVomit);
	}

	void VomitSound()
	{
		if (!GetGame().IsServer() && m_playStatus) // Check if its a client entity running this class and sound is set to trigger
		{
			BloodVomitSounds = MSaySoundSet("BloodVomit_SoundSet"); // Hook sound to body
			BloodVomitSounds.Loop(false);
			soundObjVomit.SetPosition(GetPosition());
		}
	}

	// Transfers attachmanets to a zombie after the player dies from the virus
	void TransferAttachmentsFromPlayer(EntityAI entity)
	{
		for (int i = 0; i < entity.GetInventory().GetAttachmentSlotsCount(); i++)
		{
			int slot = entity.GetInventory().GetAttachmentSlotId(i);
			EntityAI item = entity.GetInventory().FindAttachment(slot);

			if (item)
			{
				float health;

				if (GetGame().IsServer())
				{
					health = item.GetHealth();
					item.SetHealth(item.GetMaxHealth());
				}

				if (GetInventory().CanAddAttachment(item))
				{
					if (GetGame().IsMultiplayer())
						entity.ServerTakeEntityToTargetInventory(this, FindInventoryLocationType.ATTACHMENT, item);
					else
						entity.LocalTakeEntityToTargetInventory(this, FindInventoryLocationType.ATTACHMENT, item);
				}
				else
				{
					if (GetGame().IsMultiplayer())
						entity.GetInventory().DropEntity(InventoryMode.SERVER, entity, item);
					else
						entity.GetInventory().DropEntity(InventoryMode.LOCAL, entity, item);
				}

				if (GetGame().IsServer())
					item.SetHealth(health);
			}
		}

		SetSynchDirty();
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (damageResult.GetDamage(dmgZone, "Health") > 0)
			m_IsInjured = true;

		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
}