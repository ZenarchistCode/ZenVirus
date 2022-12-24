class ActionInjectVirusCureTarget : ActionInjectTarget
{
	override void ApplyModifiers(ActionData action_data)
	{
		PlayerBase ntarget = PlayerBase.Cast(action_data.m_Target.GetObject());

		if (!ntarget)
			return;

		if (ntarget.GetSingleAgentCountNormalized(VirusAgents.VIRUS) >= GetZenVirusConfig().StageNoCure && GetZenVirusConfig().StageNoCure != 0)
		{
			ItemBase droppedItem = ItemBase.Cast(GetGame().CreateObjectEx("Zen_Virus_Cure_Injector", ntarget.GetPosition(), ECE_PLACE_ON_SURFACE));
			if (droppedItem)
			{
				droppedItem.SetHealth("", "Health", 1);
			}

			ntarget.ZV_SendMessage(GetZenVirusConfig().Tip8);
			return;
		}

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CurePlayer, 5000, false, ntarget);
		ntarget.SetHealth("GlobalHealth", "Shock", 0);
		ntarget.SetSynchDirty();

		// Drop used syringe
		ItemBase junk = ItemBase.Cast(GetGame().CreateObjectEx("Zen_Virus_Cure_Injector_Empty", ntarget.GetPosition(), ECE_PLACE_ON_SURFACE));
		if (junk)
		{
			junk.SetHealth("", "Health", 1);
			junk.SetQuantity(0, false, false); // false, false overrides the game deleting edibles with <= 0 quantity.
		}
	}

	// Delayed cure slightly to stop screen flashing when red tint is removed
	void CurePlayer(PlayerBase player)
	{
		if (player && player.IsAlive() && !player.IsPlayerDisconnected())
		{
			player.InsertAgent(VirusAgents.VIRUS, -player.GetSingleAgentCount(VirusAgents.VIRUS));
			player.m_ModifiersManager.DeactivateModifier(VirusModifiers.MDF_VIRUS);
			player.RemoveAgent(VirusAgents.VIRUS);
			player.SetSynchDirty();
		}
	}
};