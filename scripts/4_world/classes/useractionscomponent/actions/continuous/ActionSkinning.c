modded class ActionSkinning extends ActionContinuousBase
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);

		if (action_data.m_Target)
		{
			EntityAI body;
			Class.CastTo(body, action_data.m_Target.GetObject());

			if (body.IsKindOf("ZombieBase"))
			{
				ItemBase added_item;

				if (Math.RandomFloat01() < GetZenVirusConfig().ChanceOfBrain) // 100% chance of brain
				{
					vector pos_rnd = body.GetPosition() + Vector(Math.RandomFloat01() - 0.5, 0, Math.RandomFloat01() - 0.5);
					pos_rnd[1] = GetGame().SurfaceY(pos_rnd[0], pos_rnd[2]);
					Class.CastTo(added_item, GetGame().CreateObject("Zen_Virus_Brain", pos_rnd, false));
					added_item.PlaceOnSurface();

					if (Math.RandomFloat01() < GetZenVirusConfig().ChanceOfBrainRuined) // 0% chance of ruined brain
					{
						added_item.SetHealth(0);
					}
				}

				if (Math.RandomFloat01() < GetZenVirusConfig().ChanceOfGuts) // 50% chance of guts
				{
					pos_rnd = body.GetPosition() + Vector(Math.RandomFloat01() - 0.5, 0, Math.RandomFloat01() - 0.5);
					pos_rnd[1] = GetGame().SurfaceY(pos_rnd[0], pos_rnd[2]);
					Class.CastTo(added_item, GetGame().CreateObject("Guts", pos_rnd, false));
					added_item.PlaceOnSurface();
					if (Math.RandomFloat01() < GetZenVirusConfig().ChanceOfGutsRuined) // 95% chance they're ruined
					{
						added_item.SetHealth(0);
					}
				}

				if (Math.RandomFloat01() < GetZenVirusConfig().ChanceOfBones) // 100% chance of bones
				{
					pos_rnd = body.GetPosition() + Vector(Math.RandomFloat01() - 0.5, 0, Math.RandomFloat01() - 0.5);
					pos_rnd[1] = GetGame().SurfaceY(pos_rnd[0], pos_rnd[2]);
					Class.CastTo(added_item, GetGame().CreateObject("Bone", pos_rnd, false));
					added_item.PlaceOnSurface();
					added_item.SetQuantity(1); // 1 Bone always
					added_item.SetHealth(10); // Badly damaged always
					if (Math.RandomFloat01() < GetZenVirusConfig().ChanceOfBonesRuined) // 95% chance they're ruined
					{
						added_item.SetHealth(0);
					}
				}

				if (Math.RandomFloat01() < GetZenVirusConfig().ChanceOfWorm) // 50% chance of worm
				{
					pos_rnd = body.GetPosition() + Vector(Math.RandomFloat01() - 0.5, 0, Math.RandomFloat01() - 0.5);
					pos_rnd[1] = GetGame().SurfaceY(pos_rnd[0], pos_rnd[2]);
					Class.CastTo(added_item, GetGame().CreateObject("Worm", pos_rnd, false));
					added_item.PlaceOnSurface();
					added_item.SetHealth(1); // Badly damaged always
					if (Math.RandomFloat01() < GetZenVirusConfig().ChanceOfWormRuined) // 95% chance they're ruined
					{
						added_item.SetHealth(0);
					}
				}
			}
		}
	}
}