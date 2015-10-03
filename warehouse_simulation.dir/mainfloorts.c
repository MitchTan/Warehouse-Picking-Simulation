// mainfloorTS.c
// AutoMod 12.6.1 Generated File
// Build: 12.6.1.12
// Model name:	warehouse_simulation
// Model path:	C:\Users\Elaine\Documents\GitHub\Warehouse-Picking-Simulation\warehouse_simulation.dir\
// Generated:	Sat Oct 03 17:33:47 2015
// Applied/AutoMod Licensee Confidential
// NO DISTRIBUTION OR REPRODUCTION RIGHTS GRANTED!
// Copyright (c) 1988-2015 Applied Materials All rights reserved.
//
// All Rights Reserved.  Reproduction or transmission in whole or
// in part, in any form or by any means, electronic, mechanical or
// otherwise, is prohibited without the prior written consent of
// copyright owner.
//
// Licensed Material - Property of Applied Materials, Inc.
//
// Applied Materials, Inc.
// 3050 Bowers Drive
// P.O. Box 58039
// Santa Clara, CA 95054-3299
// U.S.A.
//


#include "cdecls.h"


static int32
P_mainTS_arriving(load* this, int32 step, void* args)
{
	void* am_localargs = NULL;
	int32 retval = Continue;
	switch (step) { /* Make the step switcher */
	case Step 1: goto Label1;
	case Step 2: goto Label2;
	case Step 3: goto Label3;
	case Step 4: goto Label4;
	default: message("Bad step number %ld.", step);
	}
	retval = Error;
	goto LabelRet;
Label1: ;  /* Step1 */
	{
		{
			pushppa(this, P_mainTS_arriving, Step 2, am_localargs);
			pushppa(this, inqueue, Step 1, am2_Q_mainTS_wait);
			return Continue; // go move into territory
Label2: ; // Step 2
		}
		{
			pushppa(this, P_mainTS_arriving, Step 3, am_localargs);
			pushppa(this, inqueue, Step 1, am2_Q_mainTS);
			return Continue; // go move into territory
Label3: ; // Step 3
		}
		{
			return usefor(am2_R_mainTS, 1, this, P_mainTS_arriving, Step 4, am_localargs, ToModelTime(exponential(am2_stream0, 5), UNITMINUTES));
Label4: ; // Step 4
		}
		{
			this->nextproc = am2_P_mainfinish; /* send to ... */
			EntityChanged(W_LOAD);
			retval = Continue;
			goto LabelRet;
		}
	}
LabelRet: ;
	if (am_localargs)
		xfree(am_localargs);
	return retval;
} /* end of P_mainTS_arriving */

static int32
P_mainfinish_arriving(load* this, int32 step, void* args)
{
	void* am_localargs = NULL;
	int32 retval = Continue;
	{
		{
			am2_V_insystem -= 1;
			EntityChanged(0x01000000);
		}
		{
			this->attribute->am2_A_timestamp = (FromModelTime(ASIclock, UNITSECONDS) - this->attribute->am2_A_timestamp);
			EntityChanged(0x00000040);
		}
		{
			{
				char* pArg1 = "picklist had time in system of";
				char* pArg2 = " ";
				int32 pArg3 = (this->attribute->am2_A_timestamp / 60);
				char* pArg4 = " ";
				char* pArg5 = "min";

				message("%s%s%d%s%s", pArg1, pArg2, pArg3, pArg4, pArg5);
			}
		}
		{
			this->nextproc = am2_die; /* send to ... */
			EntityChanged(W_LOAD);
			retval = Continue;
			goto LabelRet;
		}
	}
LabelRet: ;
	if (am_localargs)
		xfree(am_localargs);
	return retval;
} /* end of P_mainfinish_arriving */



/* init function for mainfloorTS.m */
void
model_mainfloorTS_init(struct model_struct* data)
{
	data->am_P_mainTS->aprc = P_mainTS_arriving;
	data->am_P_mainfinish->aprc = P_mainfinish_arriving;
}

