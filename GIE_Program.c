
#include "GIE_Config.h"
#include "GIE_Private.h"
#include "GIE_Interface.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"


void GIE_Enable(void)
{
	SET_BIT(GIE_REG, 7);
}

void GIE_Disable(void)
{
	CLR_BIT(GIE_REG, 7);
}