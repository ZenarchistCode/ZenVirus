class CraftVirusBolt extends RecipeBase
{
	override void Init()
	{
		m_Name = "Poison bolt with virus";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 0.5;//animation length in relative time units
		m_Specialty = -0.02;// value > 0 for roughness, value < 0 for precision

		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check

		m_MinQuantityIngredient[0] = -1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check

		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check

		m_MinQuantityIngredient[1] = -1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------

		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0, "Crossbow_ArrowBolt");//you can insert multiple ingredients this way

		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0;// 0 = do nothing
		m_IngredientDestroy[0] = true;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient

		//ingredient 2
		InsertIngredient(1, "Zen_Virus_PathogenVial");//you can insert multiple ingredients this way
		InsertIngredient(1, "Zen_Virus_Injector");

		m_IngredientAddHealth[1] = -10;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = -1;// 0 = do nothing
		m_IngredientDestroy[1] = false;// false = do nothing
		m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		//----------------------------------------------------------------------------------------------------------------------
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)//final check for recipe's validity
	{
		return ingredients[0].GetType() != "Zen_Crossbow_ArrowBoltVirus";
	}

	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		Ammunition_Base bolt = Ammunition_Base.Cast(GetGame().CreateObjectEx("Zen_Crossbow_ArrowBoltVirus", player.GetPosition(), ECE_PLACE_ON_SURFACE));

		if (bolt)
		{
			Ammunition_Base old_bolt = Ammunition_Base.Cast(ingredients[0]);

			if (old_bolt)
			{
				bolt.SetHealth("", "Health", ingredients[0].GetHealth());
				bolt.ServerSetAmmoCount(old_bolt.GetAmmoCount());
			}
		}
	}
};