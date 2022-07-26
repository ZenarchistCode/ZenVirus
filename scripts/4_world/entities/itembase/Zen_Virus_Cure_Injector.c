class Zen_Virus_Cure_Injector : ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionInjectVirusCureSelf);
		AddAction(ActionInjectVirusCureTarget);
	}
}