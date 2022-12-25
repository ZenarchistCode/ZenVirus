modded class JMAnimRegister
{
	override void OnRegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.OnRegisterOneHanded(pType, pBehavior);

		pType.AddItemInHandsProfileIK("Zen_Virus_Cure_Injector", "dz/anims/workspaces/player/player_main/props/player_main_1h_morphine.asi", pBehavior, "dz/anims/anm/player/ik/gear/morphine.anm");
		pType.AddItemInHandsProfileIK("Zen_Virus_Cure_Injector_Empty", "dz/anims/workspaces/player/player_main/props/player_main_1h_morphine.asi", pBehavior, "dz/anims/anm/player/ik/gear/morphine.anm");
		pType.AddItemInHandsProfileIK("Zen_Virus_Injector", "dz/anims/workspaces/player/player_main/props/player_main_1h_morphine.asi", pBehavior, "dz/anims/anm/player/ik/gear/morphine.anm");
		pType.AddItemInHandsProfileIK("Zen_Virus_Injector_Empty", "dz/anims/workspaces/player/player_main/props/player_main_1h_morphine.asi", pBehavior, "dz/anims/anm/player/ik/gear/morphine.anm");
		pType.AddItemInHandsProfileIK("Zen_Virus_PathogenVial", "dz/anims/workspaces/player/player_main/props/player_main_1h_pills.asi", pBehavior, "dz/anims/anm/player/ik/gear/VitaminBottle.anm");
		pType.AddItemInHandsProfileIK("Zen_Virus_AntiBodiesVial", "dz/anims/workspaces/player/player_main/props/player_main_1h_pills.asi", pBehavior, "dz/anims/anm/player/ik/gear/VitaminBottle.anm");
		pType.AddItemInHandsProfileIK("Zen_Virus_Cure_Petridish", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/powdered_milk.anm");

	}

	override void OnRegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.OnRegisterTwoHanded(pType, pBehavior);

		pType.AddItemInHandsProfileIK("Zen_Virus_Cure_Microscope", "dz/anims/workspaces/player/player_main/player_main_2h.asi", pBehavior, "dz/anims/anm/player/ik/two_handed/BatteryCar.anm");
	}
};