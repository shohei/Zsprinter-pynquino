// Tonokip RepRap firmware rewrite based off of Hydra-mmm firmware.
// Licence: GPL

//Check Version of Arduino and then include the right libraries
//#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
//#else
  //#include <WProgram.h>
//#endif

#include "fastio.h"
#include "xil_types.h"
extern "C" {
  #include "uart.h"
}

extern "C" void __cxa_pure_virtual();

#define  FORCE_INLINE __attribute__((always_inline)) inline
// #define  FORCE_INLINE inline


//#if X_ENABLE_PIN > -1
//#define  enable_x() WRITE(X_ENABLE_PIN, X_ENABLE_ON)
//#define disable_x() WRITE(X_ENABLE_PIN,!X_ENABLE_ON)
//#else
//#define enable_x() ;
//#define disable_x() ;
//#endif
//#if Y_ENABLE_PIN > -1
//#define  enable_y() WRITE(Y_ENABLE_PIN, Y_ENABLE_ON)
//#define disable_y() WRITE(Y_ENABLE_PIN,!Y_ENABLE_ON)
//#else
//#define enable_y() ;
//#define disable_y() ;
//#endif
//#if Z_ENABLE_PIN > -1
//#define  enable_z() WRITE(Z_ENABLE_PIN, Z_ENABLE_ON)
//#define disable_z() WRITE(Z_ENABLE_PIN,!Z_ENABLE_ON)
//#else
//#define enable_z() ;
//#define disable_z() ;
//#endif
//#if E_ENABLE_PIN > -1
//#define  enable_e() WRITE(E_ENABLE_PIN, E_ENABLE_ON)
//#define disable_e() WRITE(E_ENABLE_PIN,!E_ENABLE_ON)
//#else
//#define enable_e() ;
//#define disable_e() ;
//#endif
void enable_x();
void disable_x();
void enable_y();
void disable_y();
void enable_z();
void disable_z();
void enable_e();
void disable_e();


#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define E_AXIS 3


//Extracted from Marlin
#define MMM_TO_MMS(MM_M) ((MM_M)/60.0)
#define MMS_TO_MMM(MM_S) ((MM_S)*60.0)
//#define MMM_SCALED(MM_M) ((MM_M)*feedrate_percentage*0.01)
//#define MMS_SCALED(MM_S) MMM_SCALED(MM_S)
//#define MMM_TO_MMS_SCALED(MM_M) (MMS_SCALED(MMM_TO_MMS(MM_M)))
//#define LOGICAL_POSITION(POS, AXIS) (POS + home_offset[AXIS] + position_shift[AXIS])
//#define RAW_POSITION(POS, AXIS)     (POS - home_offset[AXIS] - position_shift[AXIS])
//#define LOGICAL_X_POSITION(POS)     LOGICAL_POSITION(POS, X_AXIS)
//#define LOGICAL_Y_POSITION(POS)     LOGICAL_POSITION(POS, Y_AXIS)
//#define LOGICAL_Z_POSITION(POS)     LOGICAL_POSITION(POS, Z_AXIS)
//#define RAW_X_POSITION(POS)         RAW_POSITION(POS, X_AXIS)
//#define RAW_Y_POSITION(POS)         RAW_POSITION(POS, Y_AXIS)
//#define RAW_Z_POSITION(POS)         RAW_POSITION(POS, Z_AXIS)
//#define RAW_CURRENT_POSITION(AXIS)  RAW_POSITION(current_position[AXIS], AXIS)


// This struct is used when buffering the setup for each linear movement "nominal" values are as specified in 
// the source g-code and may never actually be reached if acceleration management is active.
typedef struct {
  // Fields used by the bresenham algorithm for tracing the line
  long steps_x, steps_y, steps_z, steps_e;  // Step count along each axis

  unsigned long step_event_count;                    // The number of step events required to complete this block
  long accelerate_until;           // The index of the step event on which to stop acceleration
  long decelerate_after;           // The index of the step event on which to start decelerating
  long acceleration_rate;          // The acceleration rate used for acceleration calculation
  volatile unsigned char direction_bits;             // The direction bit set for this block (refers to *_DIRECTION_BIT in config.h)

  #ifdef ADVANCE
    long advance_rate;
    volatile long initial_advance;
    volatile long final_advance;
    float advance;
  #endif

  // Fields used by the motion planner to manage acceleration
//  float speed_x, speed_y, speed_z, speed_e;          // Nominal mm/minute for each axis
  float nominal_speed;                               // The nominal speed for this block in mm/min  
  float entry_speed;                                 // Entry speed at previous-current junction in mm/min
  float max_entry_speed;                             // Maximum allowable junction entry speed in mm/min
  float millimeters;                                 // The total travel of this block in mm
  float acceleration;                                // acceleration mm/sec^2
  unsigned char recalculate_flag;                    // Planner flag to recalculate trapezoids on entry junction
  unsigned char nominal_length_flag;                 // Planner flag for nominal speed always reached


  // Settings for the trapezoid generator
  long nominal_rate;                                 // The nominal step rate for this block in step_events/sec 
  long initial_rate;                        // The jerk-adjusted step rate at start of block  
  long final_rate;                          // The minimal rate at exit
  long acceleration_st;                              // acceleration steps/sec^2
  volatile char busy;
  float dispenser_multiplier;
  float dispenser_pressure_gain;
  char *next_command;
  uint8_t current_tool_number;
} block_t;


void FlushSerialRequestResend();
void ClearToSend();

void analogWrite_check(uint8_t check_pin, int val);
//void showString (PGM_P s);

void manage_inactivity(byte debug);

void get_command();
void get_coordinates();
void prepare_move();
void prepare_arc_move(char isclockwise);
FORCE_INLINE void process_commands();
#ifdef USE_ARC_FUNCTION
  FORCE_INLINE void get_arc_coordinates();
#endif

void kill(byte debug);

void check_axes_activity();
void plan_init();
void st_init();
void tp_init();
void plan_buffer_line(float x, float y, float z, float e, float feed_rate);
void plan_set_position(float x, float y, float z, float e);
void st_wake_up();
void st_synchronize();
void st_set_position(const long &x, const long &y, const long &z, const long &e);

//function prototypes
void initializeGPIO();
void initializeGPIO_ChipKit();
void initializeAxiTimer();

void check_buffer_while_arc();

#ifdef SDSUPPORT
void print_disk_info(void);
#endif //SDSUPPORT

#if (MINIMUM_FAN_START_SPEED > 0)
void manage_fan_start_speed(void);
#endif

#ifdef DEBUG
void log_message(char*   message);
void log_bool(char* message, bool value);
void log_int(char* message, int value);
void log_long(char* message, long value);
void log_float(char* message, float value);
void log_uint(char* message, unsigned int value);
void log_ulong(char* message, unsigned long value);
#endif

void inverse_kinematics(const float cartesian[3]);
// void inverse_kinematics(volatile float cartesian[3]);
void initializeXADC();

u32 millis();

void print_string();
//void parse_command(char serial_char);
void parse_command(char serial_char, int idx);
void get_command_mailbox();
void initializeOLED();
void mydelay(int factor);

void update_dispenser_pressure(int channel, int target_pressure);
void initializeUART0();
void initializeUART1();

void uart_print(char *msg);

void uv_led_on();
void uv_led_off();
void dispenser_on();
void dispenser_off();

inline void gcode_T(uint8_t tmp_extruder);

