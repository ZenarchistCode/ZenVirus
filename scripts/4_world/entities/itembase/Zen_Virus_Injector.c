class Zen_Virus_Injector : Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionInjectVirusTarget);
		AddAction(ActionInjectVirusSelf);
	}
};