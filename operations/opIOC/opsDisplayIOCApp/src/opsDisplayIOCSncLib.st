/* test snc-seq program to make different lights on the modicon go blinky-blinky */
/* depending on what that analog setting is.                                     */
/*										 */
/*                                                    If the setting is over 10  */
/* go into the "Fault" state.							 */

program opsDisplayIOCSnc

double setting;
assign setting to "MOD1:VacuumPressure.VAL";
monitor setting;

short light;
assign light to "MOD1:bit16";

short fault;
assign fault to "MOD1:bit17";

string currentstate;
assign currentstate to "MOD1:CurrentVacuumState";

ss set_lights
{
	state light_on{
		when(setting >= 5.0){
 		strcpy(currentstate, "Light Off");
                pvPut(currentstate);
		/* turn light off */
		light=FALSE;
		pvPut(light);
		}state light_off

		when(setting > 10.0){
                strcpy(currentstate, "Fault");
                pvPut(currentstate);
                /* turn fault on */
                light=TRUE;
                pvPut(fault);
                }state fault 
	}

	state light_off{
		when(setting < 5.0){
                strcpy(currentstate, "Light On");
                pvPut(currentstate);
		/* turn light on */
		light=TRUE;
		pvPut(light);
		}state light_on

		when(setting > 10.0){
		strcpy(currentstate, "Fault");
                pvPut(currentstate);
                /* turn fault on */
                light=TRUE;
                pvPut(fault);
                }state fault
	}
	state fault{
		when(setting < 5.0){
		strcpy(currentstate, "Light On");
                pvPut(currentstate);
                /* turn light on */
                light=TRUE;
                pvPut(light);
                }state light_on

		 when(setting >= 5.0){
                strcpy(currentstate, "Light Off");
                pvPut(currentstate);
                /* turn light off */
                light=FALSE;
                pvPut(light);
                }state light_off
	}
}
