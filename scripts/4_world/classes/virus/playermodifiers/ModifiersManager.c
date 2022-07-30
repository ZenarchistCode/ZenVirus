modded class ModifiersManager
{
	override void Init()
	{
		super.Init();
		AddModifier(new ZombieVirusMdfr);
		AddModifier(new ZombieStaminaMdfr);
	}
};

modded class StaminaHandler
{
	void Init()
	{
		super.Init();
		m_RegisteredDepletionModifiers.Insert(VirusModifiers.MDF_VIRUS_STAMINA, GetZenVirusConfig().BoostedStaminaConsumed);
		m_RegisteredRecoveryModifiers.Insert(VirusModifiers.MDF_VIRUS_STAMINA, GetZenVirusConfig().BoostedStaminaRecovery);
	}
};