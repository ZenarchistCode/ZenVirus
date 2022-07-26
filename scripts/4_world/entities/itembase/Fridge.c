// UNCOMMENT ALL OF THIS CODE AND RE-PACK IF YOU WANT TO MAKE IT SO VIRUS CURES "ROT" AND YOU NEED TO PUT THEM IN A MUCHSTUFFPACK FRIDGE TO PRESERVE THEM
// MSP FRIDGE MOD LINK: https://steamcommunity.com/sharedfiles/filedetails/?id=1991570984
// Don't forget to add this to the config.cpp: requiredAddons[] = { "DZ_Data", "DZ_Scripts", "DZ_Gear_Books", "ZenVirus", "MSP_Storage", };

/*

modded class ItemBase
{
	bool m_StoredInFridge = false;
	Msp_Fridge_Base m_Fridge = null;

	override void ProcessDecay(float delta, bool hasRootAsPlayer)
	{
		if (m_StoredInFridge)
		{
			if (m_Fridge)
			{
				if (m_Fridge.GetCompEM().IsSwitchedOn())
				{
					return;
				}
			}
		}

		super.ProcessDecay(delta, hasRootAsPlayer);
	}

	override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
	{
		super.EEItemLocationChanged(oldLoc, newLoc);

		if (oldLoc.GetParent())
		{
			if (oldLoc.GetParent().GetType().Contains("Fridge") && (!newLoc.GetParent() || !newLoc.GetParent().GetType().Contains("Fridge")))
			{
				m_StoredInFridge = false; // Item was taken out of the fridge
				m_Fridge = null;
			}
		}
	}
};

modded class Edible_Base
{
	override void ProcessDecay(float delta, bool hasRootAsPlayer)
	{
		if (m_StoredInFridge)
		{
			if (m_Fridge)
			{
				if (m_Fridge.GetCompEM().IsSwitchedOn())
				{
					return;
				}
			}
		}

		super.ProcessDecay(delta, hasRootAsPlayer);
	}
};

modded class Msp_Fridge_Base
{
	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if (super.CanReceiveItemIntoCargo(item))
		{
			return true;
		}

		return item.GetType() == "Zen_Virus_Brain" || item.GetType() == "Zen_Virus_Cure_Injector";
	}

	override bool CanSwapItemInCargo(EntityAI child_entity, EntityAI new_entity)
	{
		if (super.CanSwapItemInCargo(child_entity, new_entity))
		{
			return true;
		}

		return new_entity.GetType() == "Zen_Virus_Brain" || new_entity.GetType() == "Zen_Virus_Cure_Injector" || child_entity.GetType() == "Zen_Virus_Brain" || child_entity.GetType() == "Zen_Virus_Cure_Injector";
	}

	override void EECargoIn(EntityAI item)
	{
		super.EECargoIn(item);

		ItemBase ib = ItemBase.Cast(item);
		if (ib)
		{
			ib.m_StoredInFridge = true;
			ib.m_Fridge = this;
		}
	}
};

class Zen_VirusBrain extends ItemBase
{
	// This code is used for adding MuchStuffPack Fridge compatability
	protected float m_DecayTimer = 0.0;
	protected float m_DecayDelta = 0.0;

	void Zen_VirusBrain()
	{
		m_DecayTimer = (GameConstants.DECAY_FOOD_DRIED_MEAT + (Math.RandomFloat01() * (GameConstants.DECAY_FOOD_DRIED_MEAT * (GameConstants.DECAY_TIMER_RANDOM_PERCENTAGE / 100.0))));
	}

	override bool CanDecay() // Virus cure can decay
	{
		return true;
	}

	override protected bool CanProcessDecay() // Virus cure can decay
	{
		return true;
	}

	override void ProcessDecay(float delta, bool hasRootAsPlayer)
	{
		if (IsRuined() || m_StoredInFridge)
		{
			return;
		}

		super.ProcessDecay(delta, hasRootAsPlayer);

		delta *= DayZGame.Cast(GetGame()).GetFoodDecayModifier();
		m_DecayDelta += (1 + (1 - GetHealth01("", "")));
		if (hasRootAsPlayer)
			m_DecayDelta += GameConstants.DECAY_RATE_ON_PLAYER;

		m_DecayTimer -= (delta * m_DecayDelta);

		if (m_DecayTimer <= 0)
		{
			SetHealth(0);
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_DecayTimer);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_DecayTimer))
		{
			m_DecayTimer = 0.0;
			return false;
		}

		return true;
	}
}

modded class Zen_Virus_Cure_Injector
{
	protected float m_DecayTimer = 0.0;
	protected float m_DecayDelta = 0.0;

	void Zen_Virus_Cure_Injector()
	{
		m_DecayTimer = (GameConstants.DECAY_FOOD_DRIED_MEAT + (Math.RandomFloat01() * (GameConstants.DECAY_FOOD_DRIED_MEAT * (GameConstants.DECAY_TIMER_RANDOM_PERCENTAGE / 100.0))));
	}

	override bool CanDecay() // Virus cure can decay
	{
		return true;
	}

	override protected bool CanProcessDecay() // Virus cure can decay
	{
		return true;
	}

	override void ProcessDecay(float delta, bool hasRootAsPlayer)
	{
		if (IsRuined() || m_StoredInFridge)
		{
			return;
		}

		super.ProcessDecay(delta, hasRootAsPlayer);
		delta *= DayZGame.Cast(GetGame()).GetFoodDecayModifier();
		m_DecayDelta += (1 + (1 - GetHealth01("", "")));
		if (hasRootAsPlayer)
			m_DecayDelta += GameConstants.DECAY_RATE_ON_PLAYER;

		m_DecayTimer -= (delta * m_DecayDelta);

		//if (Math.RandomFloat01() < 0.01)
		//	ZenModLogger.Log("m_DecayTimer = " + m_DecayTimer);

		if (m_DecayTimer <= 0)
		{
			SetHealth(0);
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_DecayTimer);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_DecayTimer))
		{
			m_DecayTimer = 0.0;
			return false;
		}

		return true;
	}
}

*/