// groundfloor.c
// AutoMod 12.6.1 Generated File
// Build: 12.6.1.12
// Model name:	warehouse_simulation
// Model path:	C:\Users\Elaine\Documents\GitHub\Warehouse-Picking-Simulation\warehouse_simulation.dir\
// Generated:	Sat Oct 03 17:32:17 2015
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
P_groundbatch_arriving(load* this, int32 step, void* args)
{
	void* am_localargs = NULL;
	int32 retval = Continue;
	switch (step) { /* Make the step switcher */
	case Step 1: goto Label1;
	case Step 2: goto Label2;
	default: message("Bad step number %ld.", step);
	}
	retval = Error;
	goto LabelRet;
Label1: ;  /* Step1 */
	{
		{
			if (OrdGetCurConts(am2_OL_groundbatch) == 29) {
				this->nextproc = am2_P_groundfloor; /* send to ... */
				EntityChanged(W_LOAD);
				retval = Continue;
				goto LabelRet;
			}
			else {
				return waitorder(am2_OL_groundbatch, this, P_groundbatch_arriving, Step 2, am_localargs);
Label2: ; // Step 2
				if (!this->inLeaveProc && this->nextproc) {
					retval = Continue;
					goto LabelRet;
				}
			}
		}
	}
LabelRet: ;
	if (am_localargs)
		xfree(am_localargs);
	return retval;
} /* end of P_groundbatch_arriving */


typedef struct {
	double freq;
	int32 value;
} Oneof0;

static Oneof0 List0[] = {
	{ 70, 0},
	{ 110, 1},
	{ 130, 2},
	{ 140, 3},
	{ 145, 4}
};

static int32
oneofFunc0(load* this)
{
	int ind = 0;
	Oneof0* list = List0;
	double sample = getdrand(am2_stream0) * 145;

	tprintf(tfp, "In oneof\n");
	while (list->freq < sample) {
		ind++;
		list++;
	}
	return List0[ind].value;
}

static int32
P_groundfloor_arriving(load* this, int32 step, void* args)
{
	void* am_localargs = NULL;
	int32 retval = Continue;
	switch (step) { /* Make the step switcher */
	case Step 1: goto Label1;
	case Step 2: goto Label2;
	default: message("Bad step number %ld.", step);
	}
	retval = Error;
	goto LabelRet;
Label1: ;  /* Step1 */
	{
		{
			order(-1, am2_OL_groundbatch, am2_die, NULL);		// Place an order
		}
		{
			LdSetType(this, am2_L_groundbatch);
			EntityChanged(0x00000040);
		}
		{
			return usefor(am2_R_groundworker, 1, this, P_groundfloor_arriving, Step 2, am_localargs, ToModelTime(60, UNITMINUTES));
Label2: ; // Step 2
		}
		{
			this->attribute->am2_A_type = oneofFunc0(this);
			EntityChanged(0x00000040);
		}
		{
			if (this->attribute->am2_A_type == 0) {
				this->nextproc = am2_P_groundfinish; /* send to ... */
				EntityChanged(W_LOAD);
				retval = Continue;
				goto LabelRet;
			}
			else {
				if (this->attribute->am2_A_type == 1) {
					clone(this, 1, am2_P_groundTS, am2_L_TS);
				}
				else {
					if (this->attribute->am2_A_type == 2) {
						clone(this, 2, am2_P_groundTS, am2_L_TS);
					}
					else {
						if (this->attribute->am2_A_type == 3) {
							clone(this, 3, am2_P_groundTS, am2_L_TS);
						}
						else {
							if (this->attribute->am2_A_type == 4) {
								clone(this, 4, am2_P_groundTS, am2_L_TS);
							}
						}
					}
				}
			}
		}
	}
LabelRet: ;
	if (am_localargs)
		xfree(am_localargs);
	return retval;
} /* end of P_groundfloor_arriving */

static int32
P_groundTS_arriving(load* this, int32 step, void* args)
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
			pushppa(this, P_groundTS_arriving, Step 2, am_localargs);
			pushppa(this, inqueue, Step 1, am2_Q_groundTS_wait);
			return Continue; // go move into territory
Label2: ; // Step 2
		}
		{
			pushppa(this, P_groundTS_arriving, Step 3, am_localargs);
			pushppa(this, inqueue, Step 1, am2_Q_groundTS);
			return Continue; // go move into territory
Label3: ; // Step 3
		}
		{
			return usefor(am2_R_groundTS, 1, this, P_groundTS_arriving, Step 4, am_localargs, ToModelTime(exponential(am2_stream0, 5), UNITMINUTES));
Label4: ; // Step 4
		}
		{
			this->nextproc = am2_P_groundfinish; /* send to ... */
			EntityChanged(W_LOAD);
			retval = Continue;
			goto LabelRet;
		}
	}
LabelRet: ;
	if (am_localargs)
		xfree(am_localargs);
	return retval;
} /* end of P_groundTS_arriving */

static int32
P_groundfinish_arriving(load* this, int32 step, void* args)
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
} /* end of P_groundfinish_arriving */



/* init function for groundfloor.m */
void
model_groundfloor_init(struct model_struct* data)
{
	data->am_P_groundbatch->aprc = P_groundbatch_arriving;
	data->am_P_groundfloor->aprc = P_groundfloor_arriving;
	data->am_P_groundTS->aprc = P_groundTS_arriving;
	data->am_P_groundfinish->aprc = P_groundfinish_arriving;
}

