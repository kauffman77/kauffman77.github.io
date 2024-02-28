// thermo_main.c: DO NOT MODIFY (bug fix on Wed Feb 28 04:47:43 PM EST 2024)
//
// Thermometer simulator main program and supporting functions. Read
// temperatuer sensor value and mode (C / F) from the command line and
// show the results of running functions from thermo_update.c on the
// screen. 


#include "thermo.h"

#define CELSIUS_FLAG    0b000000
#define FAHRENHEIT_FLAG 0b100000

int main(int argc, char **argv){
  if(argc < 3){
    printf("usage: %s {sensor_val} {C | F}\n",argv[0]);
    printf("  sensor_val: integer\n");
    return 0;
  }
  THERMO_SENSOR_PORT = atoi(argv[1]);
  printf("THERMO_SENSOR_PORT set to: %hd\n", THERMO_SENSOR_PORT);

  THERMO_STATUS_PORT = 0b10001000;
  if(argv[2][0]=='C' || argv[2][0]=='c'){
    THERMO_STATUS_PORT |= CELSIUS_FLAG;
  }
  else if(argv[2][0]=='F' || argv[2][0]=='f'){
    THERMO_STATUS_PORT |= FAHRENHEIT_FLAG;
  }
  else{
    printf("Unknown display mode: '%s'\n",argv[2]);
    printf("Should be 'C' or 'F'\n");
    return 1;
  }
  printf("THERMO_STAUS_PORT set to: %s\n",bitstr(THERMO_STATUS_PORT, &statspec));
  printf("index:                    %s\n",bitstr_index(&statspec));

  temp_t temp = {};
  int result;


  printf("result = set_temp_from_ports(&temp);\n");
  result = set_temp_from_ports(&temp);
  printf("result: %d\n",result);
  printf("%s", (result == 0) ? "" : "WARNING: Non-zero value returned\n");

  printf("temp = {\n"); 
  printf("  .tenths_degrees = %d\n",temp.tenths_degrees);
  printf("  .temp_mode      = %d\n",temp.temp_mode);
  printf("}\n");

  int quo = temp.tenths_degrees / 10;
  int rem = temp.tenths_degrees % 10;
  if(rem < 0){
    rem *= -1;
  }
  char *sym = "ERROR";
  // if(temp.temp_mode == 1){ sym = "deg F"; } // TYPO
  // if(temp.temp_mode == 2){ sym = "deg C"; }
  if(temp.temp_mode == 1){ sym = "deg C"; }
  if(temp.temp_mode == 2){ sym = "deg F"; }
  printf("Simulated temp is: %d.%d %s\n",quo,rem,sym);

  int display = 0;
  printf("result = set_display_from_temp(temp, &display);\n");
  result = set_display_from_temp(temp, &display);
  printf("result: %d\n", result);
  printf("%s", (result == 0) ? "" : "WARNING: Non-zero value returned\n");

  printf("display is\n");
  printf("bits:  %s\n",bitstr(display, &dispspec));
  printf("index: %s\n",bitstr_index(&dispspec));
  // printf("showing display graphically\n");
  // THERMO_DISPLAY_PORT = display;
  // print_thermo_display();
  printf("\n");

  // printf("Resetting display port\n");
  // THERMO_DISPLAY_PORT = 0;
  printf("result = thermo_update();\n");
  result = thermo_update();
  printf("result: %d\n", result);
  printf("%s", (result == 0) ? "" : "WARNING: Non-zero value returned\n");

  printf("THERMO_DISPLAY_PORT is\n");
  printf("bits:  %s\n",bitstr(THERMO_DISPLAY_PORT, &dispspec));
  printf("index: %s\n",bitstr_index(&dispspec));

  printf("\n");

  printf("Thermometer Display:\n");
  print_thermo_display();

  return 0;
}
