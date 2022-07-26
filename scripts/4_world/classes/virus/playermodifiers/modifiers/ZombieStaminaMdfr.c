// Stamina boost modifier (boosts stamina speed recovery & reduced speed of consumption while infected if enabled in server config)
class ZombieStaminaMdfr : ModifierBase
{
	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID = VirusModifiers.MDF_VIRUS_STAMINA;
		m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive = DEFAULT_TICK_TIME_ACTIVE_SHORT;
	}

	override bool ActivateCondition(PlayerBase player)
	{
		return GetZenVirusConfig().StageGivesBoostedStamina != 0 && player.GetSingleAgentCountNormalized(VirusAgents.VIRUS) >= GetZenVirusConfig().StageGivesBoostedStamina;
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		return !ActivateCondition(player);
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
	}

	override void OnActivate(PlayerBase player)
	{
		player.GetStaminaHandler().ActivateRecoveryModifier(VirusModifiers.MDF_VIRUS_STAMINA);
		player.GetStaminaHandler().ActivateDepletionModifier(VirusModifiers.MDF_VIRUS_STAMINA);
		player.ZV_SendMessageDebug("Zombie stamina activated");
	}

	override void OnDeactivate(PlayerBase player)
	{
		player.GetStaminaHandler().DeactivateRecoveryModifier(VirusModifiers.MDF_VIRUS_STAMINA);
		player.GetStaminaHandler().DeactivateDepletionModifier(VirusModifiers.MDF_VIRUS_STAMINA);
		player.ZV_SendMessageDebug("Zombie stamina activated");
	}
};