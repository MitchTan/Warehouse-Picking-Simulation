begin P_groundbatch arriving
	if OL_groundbatch current loads is 29 then
		send to P_groundfloor
	else 
		wait to be ordered on OL_groundbatch
end

begin P_groundfloor arriving /*treated as a black box*/
	order all from OL_groundbatch to die
	set load type to L_groundbatch /*30th load becomes a full batch load*/
	use R_groundworker for 60min /*numbers are arbitrary for now*/
	set A_type to oneof (70:0,40:1,20:2,10:3,5:4) /* 70/145% chance that all items found, 40/145% chance that 1 picklist going into TS,etc --> assume other events probability is near 0)*/
	if A_type = 0 then send to P_groundfinish
	else if A_type = 1 then clone 1 load to P_groundTS nlt L_TS
	else if A_type = 2 then clone 2 loads to P_groundTS nlt L_TS
	else if A_type = 3 then clone 3 loads to P_groundTS nlt L_TS
	else if A_type = 4 then clone 4 loads to P_groundTS nlt L_TS
end

begin P_groundTS arriving
	move into Q_groundTS_wait
	move into Q_groundTS
	use R_groundTS for e 5 min /*dont care if can find or cannot find, assume will give up after a reasonable time period*/
	send to P_groundfinish
end 

begin P_groundfinish arriving
	dec V_insystem by 1
	set A_timestamp to (ac-A_timestamp) /*someone has to code for the start of timestamp at the beginning of entire process)*/
	print "picklist had time in system of", (A_timestamp/60), "min" to message
	send to die
end

