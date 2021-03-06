/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "mali_broadcast.h"
#include "mali_kernel_common.h"
#include "mali_osk.h"

static const int bcast_unit_reg_size = 0x1000;
static const int bcast_unit_addr_broadcast_mask = 0x0;
static const int bcast_unit_addr_irq_override_mask = 0x4;

struct mali_bcast_unit
{
	struct mali_hw_core hw_core;
	u32 current_mask;
};

struct mali_bcast_unit *mali_bcast_unit_create(const _mali_osk_resource_t *resource)
{
	struct mali_bcast_unit *bcast_unit = NULL;

	MALI_DEBUG_ASSERT_POINTER(resource);
	MALI_DEBUG_PRINT(2, ("Mali Broadcast unit: Creating Mali Broadcast unit: %s\n", resource->description));

	bcast_unit = _mali_osk_malloc(sizeof(struct mali_bcast_unit));
	if (NULL == bcast_unit)
	{
		return NULL;
	}

	if (_MALI_OSK_ERR_OK == mali_hw_core_create(&bcast_unit->hw_core, resource, bcast_unit_reg_size))
	{
		bcast_unit->current_mask = 0;
		mali_bcast_reset(bcast_unit);

		return bcast_unit;
	}
	else
	{
		MALI_PRINT_ERROR(("Mali Broadcast unit: Failed to allocate memory for Broadcast unit\n"));
	}

	return NULL;
}

void mali_bcast_unit_delete(struct mali_bcast_unit *bcast_unit)
{
	MALI_DEBUG_ASSERT_POINTER(bcast_unit);

	mali_hw_core_delete(&bcast_unit->hw_core);
	_mali_osk_free(bcast_unit);
}

void mali_bcast_add_group(struct mali_bcast_unit *bcast_unit, struct mali_group *group)
{
	u32 core_id;
	u32 broadcast_mask;

	MALI_DEBUG_ASSERT_POINTER(bcast_unit);
	MALI_DEBUG_ASSERT_POINTER(group);

	core_id = mali_pp_core_get_id(mali_group_get_pp_core(group));
	broadcast_mask = bcast_unit->current_mask;

	/* set the bit corresponding to the group's core's id to 1 */
	core_id = 1 << core_id;
	broadcast_mask |= (core_id); /* add PP core to broadcast */
	broadcast_mask |= (core_id << 16); /* add MMU to broadcast */

	/* store mask so we can restore on reset */
	bcast_unit->current_mask = broadcast_mask;

	mali_bcast_reset(bcast_unit);
}

void mali_bcast_remove_group(struct mali_bcast_unit *bcast_unit, struct mali_group *group)
{
	u32 core_id;
	u32 broadcast_mask;

	MALI_DEBUG_ASSERT_POINTER(bcast_unit);
	MALI_DEBUG_ASSERT_POINTER(group);

	core_id = mali_pp_core_get_id(mali_group_get_pp_core(group));
	broadcast_mask = bcast_unit->current_mask;

	/* set the bit corresponding to the group's core's id to 0 */
	core_id = 1 << core_id;
	broadcast_mask &= ~((core_id << 16) | core_id);

	/* store mask so we can restore on reset */
	bcast_unit->current_mask = broadcast_mask;

	mali_bcast_reset(bcast_unit);
}

void mali_bcast_reset(struct mali_bcast_unit *bcast_unit)
{
	MALI_DEBUG_ASSERT_POINTER(bcast_unit);

	/* set broadcast mask */
	mali_hw_core_register_write(&bcast_unit->hw_core,
	                            bcast_unit_addr_broadcast_mask,
	                            bcast_unit->current_mask);

	/* set IRQ override mask */
	mali_hw_core_register_write(&bcast_unit->hw_core,
	                            bcast_unit_addr_irq_override_mask,
	                            bcast_unit->current_mask & 0xFF);
}
