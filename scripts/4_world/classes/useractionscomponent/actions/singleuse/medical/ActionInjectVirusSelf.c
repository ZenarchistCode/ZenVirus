class ActionInjectVirusSelf : ActionInjectSelf
{
	override void ApplyModifiers(ActionData action_data)
	{
		if (!action_data.m_Player)
		{
			return;
		}

		action_data.m_Player.InsertAgent(VirusAgents.VIRUS, GetZenVirusConfig().VirusInjectorAmount);

		// Drop used syringe
		ItemBase junk = ItemBase.Cast(GetGame().CreateObjectEx("Syringe", action_data.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
		if (junk)
		{
			junk.SetHealth("", "Health", 1);
			junk.SetQuantity(0, false, false); // false, false overrides the game deleting edibles with <= 0 quantity.
		}
	}
};