begin P_mainTS arriving
	move into Q_mainTS_wait
	move into Q_mainTS
	use R_mainTS for e 5 min /*assume dont care if item can be found or not, after a reasonable period of time, will give up*/
	send to P_mainfinish
end 

begin P_mainfinish arriving /*this process should also be used as last step in the main flow*/
	dec V_insystem by 1
	set A_timestamp to (ac-A_timestamp) /*someone has to code for the start of timestamp at the beginning of entire process)*/
	print "picklist had time in system of", (A_timestamp/60), "min" to message
	send to die
end

