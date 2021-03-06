/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2011-2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include "mali_mem_validation.h"
#include "mali_osk.h"
#include "mali_kernel_common.h"

#include <linux/string.h>
#include <linux/kernel.h>
extern int  mtk_fb_get_property(unsigned int* addr, unsigned int* size);
#define MALI_INVALID_MEM_ADDR 0xFFFFFFFF

typedef struct
{
	u32 phys_base;        /**< Mali physical base of the memory, page aligned */
	u32 size;             /**< size in bytes of the memory, multiple of page size */
} _mali_mem_validation_t;

static _mali_mem_validation_t mali_mem_validator = { MALI_INVALID_MEM_ADDR, MALI_INVALID_MEM_ADDR };

_mali_osk_errcode_t mali_mem_validation_add_range(u32 start, u32 size)
{
	/* Check that no other MEM_VALIDATION resources exist */
	#if 0
	if (MALI_INVALID_MEM_ADDR != mali_mem_validator.phys_base)
	{
		MALI_PRINT_ERROR(("Failed to add frame buffer memory; another range is already specified\n"));
		return _MALI_OSK_ERR_FAULT;
	}

	/* Check restrictions on page alignment */
	if ((0 != (start & (~_MALI_OSK_CPU_PAGE_MASK))) ||
	    (0 != (size & (~_MALI_OSK_CPU_PAGE_MASK))))
	{
		MALI_PRINT_ERROR(("Failed to add frame buffer memory; incorrect alignment\n"));
		return _MALI_OSK_ERR_FAULT;
	}

	mali_mem_validator.phys_base = start;
	mali_mem_validator.size = size;
   #else

	unsigned int fb_base, fb_size;

   if(mtk_fb_get_property(&fb_base, &fb_size) == 0)
    {
     mali_mem_validator.phys_base = fb_base;
     mali_mem_validator.size = fb_size;
     MALI_PRINT(("MEM_VALIDATION - phys: 0x%8x, size 0x%8x\n",  fb_base, fb_size));                             
    }
   else
    {
      MALI_PRINT(("FB not yet init, use default!!\n"));
    }
	#endif
	MALI_DEBUG_PRINT(2, ("Memory Validator installed for Mali physical address base=0x%08X, size=0x%08X\n",
	                 mali_mem_validator.phys_base, mali_mem_validator.size));

	return _MALI_OSK_ERR_OK;
}

_mali_osk_errcode_t mali_mem_validation_check(u32 phys_addr, u32 size)
{
	if (phys_addr < (phys_addr + size)) /* Don't allow overflow (or zero size) */
	{
		if ((0 == ( phys_addr & (~_MALI_OSK_CPU_PAGE_MASK))) &&
			(0 == ( size & (~_MALI_OSK_CPU_PAGE_MASK))))
		{
			if ((phys_addr          >= mali_mem_validator.phys_base) &&
				((phys_addr + (size - 1)) >= mali_mem_validator.phys_base) &&
				(phys_addr          <= (mali_mem_validator.phys_base + (mali_mem_validator.size - 1))) &&
				((phys_addr + (size - 1)) <= (mali_mem_validator.phys_base + (mali_mem_validator.size - 1))) )
			{
				MALI_DEBUG_PRINT(3, ("Accepted range 0x%08X + size 0x%08X (= 0x%08X)\n", phys_addr, size, (phys_addr + size - 1)));
				return _MALI_OSK_ERR_OK;
			}
		}
	}

	MALI_PRINT_ERROR(("MALI PHYSICAL RANGE VALIDATION ERROR: The range supplied was: phys_base=0x%08X, size=0x%08X\n", phys_addr, size));

	return _MALI_OSK_ERR_FAULT;
}
