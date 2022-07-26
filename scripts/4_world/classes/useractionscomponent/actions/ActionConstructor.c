modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionInjectVirusCureSelf);
		actions.Insert(ActionInjectVirusCureTarget);
		actions.Insert(ActionInjectVirusSelf);
		actions.Insert(ActionInjectVirusTarget);
		actions.Insert(ActionAnalyseVirus);
	}
};