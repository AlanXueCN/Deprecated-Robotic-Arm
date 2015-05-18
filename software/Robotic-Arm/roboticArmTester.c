// roboticArmTester.c 2015

//TESTER TASK:

#include "roveIncludes/roveWareHeaders/roboticArm.h"

// BIOS_start in main inits this as the roboticArmTesterTask Thread

//this is a roboticArm.cfg object::roboticArmTask::priority 1,
//768 persistent private stack, vital_flag = t,

//roveWare.h :: #define TEST_STRUCT ((speed_struct*)(&buffer_struct))

typedef struct gps_telem
{
    uint8_t struct_id;
    bool fix;
    uint8_t fix_quality;
    uint8_t satellites;
    int32_t latitude_fixed;
    int32_t longitude_fixed;
    float altitude;
    float speed;
    float angle;
}__attribute__((packed)) gps_telem;


typedef struct bms_power_board_telem
{
    uint8_t struct_id;
    float value;
} bms_power_board_telem;

typedef struct science_board_telem
{
    uint8_t struct_id;
    float value;
} science_board_telem;

#define gps_board_telem_id                              140
#define bms_power_board_telem_id                        141
#define science_board_telem_id                          142

//Send Tester for Mob Telem Threading

#define GPS_STRUCT            ((gps_telem*)(&write_buffer))
#define BMS_POWER_STRUCT      ((bms_power_board_telem*)(&write_buffer))
#define SCIENCE_STRUCT        ((science_board_telem*)(&write_buffer))

void roboticArmTester(UArg arg0, UArg arg1)
{
	System_printf("roboticArmTesterTask init \n\n\n");
	System_flush();

	//      UART 3:   TX PC7, RX PC6  END_EFFECTOR_UART
	//      UART 4:   TX PC5, RX PC4  DYNAMIXEL_UART
	//      UART 7:   TX PE1, RX PE0  LINEAR_ACTUATOR_UART

	char write_buffer[BUFFER_SIZE];

	int i;
	int bytes_wrote;
	int test_ms_delay = 10;

	//hack for unreachable statement warnings
	//const uint8_t FOREVER = 1;
	while(1){

        BMS_POWER_STRUCT->struct_id = bms_power_board_telem_id;
        BMS_POWER_STRUCT->value = 9.0909;

	    bytes_wrote = deviceWrite(DYNAMIXEL_UART, write_buffer, sizeof(struct bms_power_board_telem));

		ms_delay(test_ms_delay);
/*
            System_printf("\DYNAMIXEL_UART bms_power_board_telem just wrote: \n");
            System_flush();
            i = 0;
            while( i <( bytes_wrote ) )
            {
                System_printf(" : %d", write_buffer[i]);
                i++;
            }//end while
            System_printf("\n\n");
            System_flush();
*/
		SCIENCE_STRUCT->struct_id = science_board_telem_id;
		SCIENCE_STRUCT->value = 3.0303;

		bytes_wrote = deviceWrite(LINEAR_ACTUATOR_UART, write_buffer, sizeof(struct science_board_telem));

		ms_delay(test_ms_delay);
/*
            System_printf("\nLINEAR_ACTUATOR_UART science_board_telem just wrote: \n");
            System_flush();
            i = 0;
            while( i <( bytes_wrote ) )
            {
                System_printf(" : %d", write_buffer[i]);
                i++;
            }//end while
            System_printf("\n\n");
            System_flush();
*/
        GPS_STRUCT->struct_id = gps_board_telem_id;
        GPS_STRUCT->fix = true;
        GPS_STRUCT->fix_quality = 2;
        GPS_STRUCT->satellites = 3;
        GPS_STRUCT->latitude_fixed = 123456789;
        GPS_STRUCT->longitude_fixed = 987654321;
        GPS_STRUCT->altitude = 0.1;
        GPS_STRUCT->speed = 0.22;
        GPS_STRUCT->angle = 0.333;

		bytes_wrote = deviceWrite(END_EFFECTOR_UART, write_buffer, sizeof(struct gps_telem));

		ms_delay(test_ms_delay);
/*
            System_printf("\nEND_EFFECTOR_UART gps_telem just wrote: \n");
            System_flush();
            i = 0;
            while( i <( bytes_wrote ) )
            {
                System_printf(" : %d", write_buffer[i]);
                i++;
            }//end while
            System_printf("\n\n");
            System_flush();
*/
        test_ms_delay = test_ms_delay + 50;

    }//endwhile FOREVER

}//endfnct task roboticArmTester

//COMMENT* HERE FOR RECIEVE TESTER

/*

    while(FOREVER)
    {
        while( recvSerialStructMessage(MOTHERBOARD_UART, (void*)&buffer_struct) )
        {
            System_printf("recvSerialStructMessage struct_id: %d", buffer_struct.struct_id);
            System_printf("speed: %d\n", SPEED_STRUCT->speed);
            System_flush();
        }//endwhile

//COMMENT* HERE FOR RECIEVE TESTER
 *
 * #define bms_emergency_stop_command_id                   150
#define bms_cell1_voltage_telem_id                      151
#define bms_cell2_voltage_telem_id                      152
#define bms_cell3_voltage_telem_id                      153
#define bms_cell4_voltage_telem_id                      154
#define bms_cell5_voltage_telem_id                      155
#define bms_cell6_voltage_telem_id                      156
#define bms_cell7_voltage_telem_id                      157
#define bms_cell8_voltage_telem_id                      158
#define bms_pack_voltage_telem_id                       159
#define bms_total_amperage_telem_id                     160

#define power_board_command_id                          170
#define power_board_telem_motor1_current_id             180
#define power_board_telem_motor2_current_id             181
#define power_board_telem_motor3_current_id             182
#define power_board_telem_motor4_current_id             183
#define power_board_telem_motor5_current_id             184
#define power_board_telem_motor6_current_id             185
#define power_board_telem_aux_current_id                186
#define power_board_telem_5V_bus_current_id             187
#define power_board_telem_12v_critical_bus_current_id   188
#define power_board_telem_12v_highpower_bus_current_id  189
#define power_board_telem_robotarm_bus_current_id       190
#define power_board_telem_main_battery_voltage_id       191

*/

