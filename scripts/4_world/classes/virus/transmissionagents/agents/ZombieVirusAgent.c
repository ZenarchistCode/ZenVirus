class ZombieVirusAgent extends AgentBase
{
	override void Init()
	{
		m_Type = VirusAgents.VIRUS;
		m_Invasibility = GetZenVirusConfig().VirusAddPerSecond;//0.1; //increase the agent count by this number per second if potent enough to grow
		m_TransferabilityIn = 0.5; //to the player
		m_TransferabilityOut = 1; //from the player
		m_AntibioticsResistance = 1; //[0..1], 0 means antibiotics have full effect, 1 means no effect
		m_MaxCount = GetZenVirusConfig().VirusMaxAmount;
		m_TransferabilityAirOut = 0.1; // transferibility airborne out
		m_AutoinfectProbability = 0; // [0..1], 0 = zero chance, 1 = 100% chance of getting this agent once per hour
		m_Potency = EStatLevels.GREAT; //grow when player's immune system is at this level or lower
		m_DieOffSpeed = 0.25; //how fast the agent dies off when not potent enough to grow(per sec)
	}

	override float GetAntibioticsResistanceEx(PlayerBase player)
	{
		if (player.GetSingleAgentCountNormalized(VirusAgents.VIRUS) <= GetZenVirusConfig().StageTetraVitaminWorks && player.GetModifiersManager().IsModifierActive(eModifiers.MDF_IMMUNITYBOOST))
		{
			return 0.5;
		}
		else
		{
			return 1.0;
		}
	}
}