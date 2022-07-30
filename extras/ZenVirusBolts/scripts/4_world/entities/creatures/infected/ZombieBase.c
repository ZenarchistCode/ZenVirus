modded class ZombieBase
{
	protected ref Timer m_PoisonTimer = NULL;

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (ammo == "Arrow_Bolt_Virus")
		{
			this.SetHealth(this.GetHealth() - 120);

			if (this.GetHealth() > 0 && !this.GetType().Contains("ZmbM_DH_Master_")) // DOn't allow zombie horde master to be poisoned as it'll make him too easy.
			{
				if (!m_PoisonTimer)
					m_PoisonTimer = new Timer();

				if (!m_PoisonTimer.IsRunning())
					m_PoisonTimer.Run(10, this, "PoisonVirusEffect", NULL, true);
			}
		}
	}

	void PoisonVirusEffect()
	{
		if (this.GetHealth() <= 0)
		{
			if (m_PoisonTimer && m_PoisonTimer.IsRunning())
				m_PoisonTimer.Stop();

			return;
		}

		this.SetHealth(this.GetHealth() - 25);
	}

	void ~ZombieBase()
	{
		if (m_PoisonTimer && m_PoisonTimer.IsRunning())
			m_PoisonTimer.Stop();
	}
}

modded class AnimalBase
{
	protected ref Timer m_PoisonTimer = NULL;

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (ammo == "Arrow_Bolt_Virus")
		{
			this.SetHealth(this.GetHealth() - 120);

			if (this.GetHealth() > 0)
			{
				if (!m_PoisonTimer)
					m_PoisonTimer = new Timer();

				if (!m_PoisonTimer.IsRunning())
					m_PoisonTimer.Run(10, this, "PoisonVirusEffect", NULL, true);
			}
		}
	}

	void PoisonVirusEffect()
	{
		if (this.GetHealth() <= 0)
		{
			if (m_PoisonTimer && m_PoisonTimer.IsRunning())
				m_PoisonTimer.Stop();

			return;
		}

		this.SetHealth(this.GetHealth() - 25);
	}

	void ~AnimalBase()
	{
		if (m_PoisonTimer && m_PoisonTimer.IsRunning())
			m_PoisonTimer.Stop();
	}
}