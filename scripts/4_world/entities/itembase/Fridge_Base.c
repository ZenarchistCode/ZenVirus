// This code is for adding compatability with MuchStuffPack's fridges
// (When a fridge is connected to power and a virus or brain is stored in it, it stops them from decaying.
/*modded class ItemBase
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
};*/