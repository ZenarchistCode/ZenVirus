modded class PluginRecipesManager extends PluginBase
{
    override void RegisterRecipies()
    {
        super.RegisterRecipies();
        RegisterRecipe(new CraftCureSyringe);
        RegisterRecipe(new CraftVirusSyringe);
    }
}