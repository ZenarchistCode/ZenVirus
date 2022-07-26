modded class PluginRecipesManager extends PluginBase
{
    override void RegisterRecipies()
    {
        super.RegisterRecipies();
        RegisterRecipe(new CraftVirusBolt);
    }
}