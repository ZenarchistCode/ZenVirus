modded class Syringe extends BloodContainerBase
{
	override void SetActions()
	{
		super.SetActions();

		RemoveAction(ActionCollectSampleTarget);
		RemoveAction(ActionCollectSampleSelf);
	}
}