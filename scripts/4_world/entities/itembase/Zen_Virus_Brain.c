/*class Zen_VirusBrain extends ItemBase
{
	// This code is used for adding MuchStuffPack Fridge compatability
	protected float m_DecayTimer = 0.0;
	protected float m_DecayDelta = 0.0;

	void Zen_VirusBrain()
	{
		m_DecayTimer = (GameConstants.DECAY_FOOD_DRIED_MEAT + (Math.RandomFloat01() * (GameConstants.DECAY_FOOD_DRIED_MEAT * (GameConstants.DECAY_TIMER_RANDOM_PERCENTAGE / 100.0))));
	}

	override bool CanDecay() // Virus cure can decay
	{
		return GetZenVirusConfig().VirusCureAndBrainDecay;
	}

	override protected bool CanProcessDecay() // Virus cure can decay
	{
		return GetZenVirusConfig().VirusCureAndBrainDecay;
	}

	override void ProcessDecay(float delta, bool hasRootAsPlayer)
	{
		if (IsRuined() || !GetZenVirusConfig().VirusCureAndBrainDecay || m_StoredInFridge)
		{
			return;
		}

		super.ProcessDecay(delta, hasRootAsPlayer);
		// TODO: PROCESS DECAY!!! Make them last a couple days?
		// TODO: Make brains decay too!
		//super.ProcessDecay(delta, hasRootAsPlayer);
		delta *= DayZGame.Cast(GetGame()).GetFoodDecayModifier();
		m_DecayDelta += (1 + (1 - GetHealth01("", "")));
		if (hasRootAsPlayer)
			m_DecayDelta += GameConstants.DECAY_RATE_ON_PLAYER;

		m_DecayTimer -= (delta * m_DecayDelta);

		//if (Math.RandomFloat01() < 0.01)
		//	ZenModLogger.Log("m_DecayTimer = " + m_DecayTimer);

		if (m_DecayTimer <= 0)
		{
			SetHealth(0);
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_DecayTimer);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_DecayTimer))
		{
			m_DecayTimer = 0.0;
			return false;
		}

		return true;
	}
}*/