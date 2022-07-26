class ActionAnalyseVirusCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
};

class ActionAnalyseVirus : ActionContinuousBase
{
	void ActionAnalyseVirus()
	{
		m_CallbackClass = ActionAnalyseVirusCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "Analyse Virus";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined;
	}

	void ~ActionAnalyseVirus()
	{
	}

	override void OnStart(ActionData action_data)
	{
		super.OnStart(action_data);
		action_data.m_Player.TryHideItemInHands(true);
	}

	override void OnEnd(ActionData action_data)
	{
		action_data.m_Player.TryHideItemInHands(false);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (item && item.IsHeavyBehaviour())
			return false;

		Object targetObject = target.GetObject();
		Zen_Virus_Cure_Microscope curemicroscope = Zen_Virus_Cure_Microscope.Cast(targetObject);

		if (!curemicroscope)
		{
			return false;
		}

		if (curemicroscope.m_TurnedOn)
		{
			return false;
		}

		return curemicroscope.HasBloodBagFull() && curemicroscope.HasBrain() && curemicroscope.HasPetridish() && curemicroscope.HasBattery();
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		Object targetObject = action_data.m_Target.GetObject();

		if (targetObject)
		{
			Zen_Virus_Cure_Microscope curemicroscope = Zen_Virus_Cure_Microscope.Cast(targetObject);

			if (!curemicroscope)
			{
				return;
			}

			action_data.m_Player.ZV_SendMessageDebug("Alright, this might take a few seconds...");
			curemicroscope.StartAnalysis();
		}
	}
};