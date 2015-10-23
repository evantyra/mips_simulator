	//output code 2: the following code will output the register 
        //value to screen at every cycle and wait for the ENTER key
        //to be pressed; this will make it proceed to the next cycle 
	printf("cycle: %d ",sim_cycle);
	if(sim_mode==1){
		for (i=1;i<REG_NUM;i++){
			printf("%d  ",mips_reg[i]);
		}
	}
	printf("%d\n",pgm_c);
	pgm_c+=4;
	sim_cycle+=1;
	test_counter++;
	printf("press ENTER to continue\n");
	while(getchar() != '\n');