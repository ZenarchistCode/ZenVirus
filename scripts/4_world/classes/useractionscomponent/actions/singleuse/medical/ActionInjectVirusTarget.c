class ActionInjectVirusTarget : ActionInjectTarget
{
	override void ApplyModifiers(ActionData action_data)
	{
		PlayerBase ntarget = PlayerBase.Cast(action_data.m_Target.GetObject());

		if (!ntarget)
		{
			return;
		}

		ntarget.InsertAgent(VirusAgents.VIRUS, GetZenVirusConfig().VirusInjectorAmount);
		// Drop used syringe
		ItemBase junk = ItemBase.Cast(GetGame().CreateObjectEx("Syringe", ntarget.GetPosition(), ECE_PLACE_ON_SURFACE));
		if (junk)
		{
			junk.SetHealth("", "Health", 1);
			junk.SetQuantity(0, false, false); // false, false overrides the game deleting edibles with <= 0 quantity.
		}
	}
};