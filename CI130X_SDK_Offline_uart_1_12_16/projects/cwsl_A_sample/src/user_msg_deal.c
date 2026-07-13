#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "system_msg_deal.h"
#include "prompt_player.h"
#include "voice_module_uart_protocol.h"
#include "i2c_protocol_module.h"
#include "ci_nvdata_manage.h"
#include "ci_log.h"
#include "ci130x_gpio.h"
#include "baudrate_calibrate.h"
#include "user_msg_deal.h"
#include "user_control.h"
// #include "all_cmd_statement.h"

static send_cmd_pro_t welcome_pro[] = {
    ///tag-insert-send-welcome-protocol-pos-9
    //send_welcome_protocol_function
    {10001,"\xAA\x55\x01\x00\xFB",5,1},  //欢迎语

};

static send_cmd_pro_t bye_pro[] = {
    ///tag-insert-send-bye-protocol-pos-10
    //send_bye_protocol_function
    {10002,"\xAA\x55\x02\x00\xFB",5,1},  //休息语

};

static recv_cmd_pro_t recv_data[] = {
    ///tag-deal-uart-msg-by-play-id-after-recv-start
    //play_msg_deal_by_cmd_id
    {3,"\xAA\x55\x03\x00\xFB",5,0},  //HELLO-HI-WONDER
    {4,"\xAA\x55\x04\x00\xFB",5,3},  //TURN-UP-VOLUME
    {5,"\xAA\x55\x05\x00\xFB",5,4},  //TURN-DOWN-VOLUME
    {6,"\xAA\x55\x06\x00\xFB",5,1},  //MAXIMUM-VOLUME
    {7,"\xAA\x55\x07\x00\xFB",5,0},  //MEDIUM-VOLUME
    {8,"\xAA\x55\x08\x00\xFB",5,2},  //MINIMUM-VOLUME
    {9,"\xAA\x55\x09\x00\xFB",5,0},  //START-BROADCASTING
    {10,"\xAA\x55\x0A\x00\xFB",5,0},  //STOP-BROADCASTING
    {11,"\xAA\x55\x00\x01\xFB",5,0},  //GO-STRAIGHT
    {12,"\xAA\x55\x00\x02\xFB",5,0},  //GO-BACKWARD
    {13,"\xAA\x55\x00\x03\xFB",5,0},  //TURN-LEFT
    {14,"\xAA\x55\x00\x04\xFB",5,0},  //TURN-RIGHT
    {15,"\xAA\x55\x00\x05\xFB",5,0},  //LEAN-FORWARD
    {16,"\xAA\x55\x00\x06\xFB",5,0},  //LEAN-BACK
    {17,"\xAA\x55\x00\x07\xFB",5,0},  //LEAN-LEFT
    {18,"\xAA\x55\x00\x08\xFB",5,0},  //LEAN-RIGHT
    {19,"\xAA\x55\x00\x09\xFB",5,0},  //STOP
    {20,"\xAA\x55\x00\x0A\xFB",5,0},  //ATTENTION
    {21,"\xAA\x55\x00\x0B\xFB",5,0},  //GET-DOWN
    {22,"\xAA\x55\x00\x0C\xFB",5,0},  //SIT-DOWN
    {23,"\xAA\x55\x00\x0D\xFB",5,0},  //SPEED-UP
    {24,"\xAA\x55\x00\x0E\xFB",5,0},  //SLOW-DOWN
    {25,"\xAA\x55\x00\x0F\xFB",5,0},  //RAISE-THE-BODY
    {26,"\xAA\x55\x00\x10\xFB",5,0},  //LOWER-THE-BODY
    {27,"\xAA\x55\x00\x11\xFB",5,0},  //MAKE-A-SOUND
    {28,"\xAA\x55\x00\x12\xFB",5,0},  //TURN-ON-THE-LIGHT
    {29,"\xAA\x55\x00\x13\xFB",5,0},  //TURN-OFF-THE-LIGHT
    {30,"\xAA\x55\x00\x14\xFB",5,0},  //OPEN-THE-DOOR
    {31,"\xAA\x55\x00\x15\xFB",5,0},  //CLOSE-THE-DOOR
    {32,"\xAA\x55\x00\x16\xFB",5,0},  //TURN-ON-THE-WATER-PUMP
    {33,"\xAA\x55\x00\x17\xFB",5,0},  //TURN-OFF-THE-WATER-PUMP
    {34,"\xAA\x55\x00\x18\xFB",5,0},  //UNFOLD-THE-AIRING-RACK
    {35,"\xAA\x55\x00\x19\xFB",5,0},  //FOLD-THE-ARING-RACK
    {36,"\xAA\x55\x00\x1A\xFB",5,0},  //HELLO
    {37,"\xAA\x55\x00\x1B\xFB",5,0},  //INTRODUCE-YOURSELF
    {38,"\xAA\x55\x00\x1C\xFB",5,0},  //SHOW-A-SKIII
    {39,"\xAA\x55\x00\x1D\xFB",5,0},  //MARCH
    {40,"\xAA\x55\x00\x1E\xFB",5,0},  //SHAKE-HEAD
    {41,"\xAA\x55\x00\x1F\xFB",5,0},  //DIVE-FORWARD
    {42,"\xAA\x55\x00\x20\xFB",5,0},  //DIVE-BACKWARD
    {43,"\xAA\x55\x00\x21\xFB",5,0},  //COMBATMODE
    {44,"\xAA\x55\x00\x22\xFB",5,0},  //SQUAT-DOWN
    {45,"\xAA\x55\x00\x23\xFB",5,0},  //SHAKE-IT-OFF
    {46,"\xAA\x55\x00\x24\xFB",5,0},  //TURN-ON-THE-FAN
    {47,"\xAA\x55\x00\x25\xFB",5,0},  //TURN-OFF-THE-FAN
    {48,"\xAA\x55\x00\x26\xFB",5,0},  //ROTATING-STEERING-GEAR
    {49,"\xAA\x55\x00\x27\xFB",5,0},  //GIVE-A-RED-LIGHT
    {50,"\xAA\x55\x00\x28\xFB",5,0},  //GIVE-A-GREEN-LIGHT
    {51,"\xAA\x55\x00\x29\xFB",5,0},  //GIVE-A-BLUE-LIGHT
    {52,"\xAA\x55\x00\x2A\xFB",5,0},  //SHOW-SMILEY-FACE
    {53,"\xAA\x55\x00\x2B\xFB",5,0},  //SHOW-CRYING-FACE
    {54,"\xAA\x55\x00\x62\xFB",5,0},  //START-FACE-RECOGNITION
    {55,"\xAA\x55\x00\x63\xFB",5,0},  //START-LABEL-RECOGNITION
    {56,"\xAA\x55\x00\x64\xFB",5,0},  //START-WASTE-SORTING
    {57,"\xAA\x55\x00\x65\xFB",5,0},  //START-COLOR-RECOGNITION
    {58,"\xAA\x55\x00\x66\xFB",5,0},  //START-LINE-FOLLOWING
    {59,"\xAA\x55\x00\x67\xFB",5,0},  //START-COLOR-TRACKING
    {60,"\xAA\x55\x00\x68\xFB",5,0},  //START-OBSTACLE-AVOIDANCE
    {61,"\xAA\x55\x00\x69\xFB",5,0},  //SORT-RED
    {62,"\xAA\x55\x00\x6A\xFB",5,0},  //SORT-GREEN
    {63,"\xAA\x55\x00\x6B\xFB",5,0},  //SORT-BLUE
    {64,"\xAA\x55\x00\x6C\xFB",5,0},  //DANCE
    {65,"\xAA\x55\x00\x6D\xFB",5,0},  //PUSH-UP
    {66,"\xAA\x55\x00\x6E\xFB",5,0},  //LEFT-FOOT-SHOOT
    {67,"\xAA\x55\x00\x6F\xFB",5,0},  //RIGHT-FOOT-SHOOT
    {68,"\xAA\x55\x00\x71\xFB",5,0},  //TWIST
    {69,"\xAA\x55\x00\x72\xFB",5,0},  //SIT-UP
    {70,"\xAA\x55\x00\x73\xFB",5,0},  //BOW
    {71,"\xAA\x55\x00\x74\xFB",5,0},  //SPREAD-THE-HANDS
    {72,"\xAA\x55\x00\x75\xFB",5,0},  //WAVE-HAND
    {73,"\xAA\x55\x00\x76\xFB",5,0},  //MARCH-IN-PLACE
    {74,"\xAA\x55\x00\x77\xFB",5,0},  //FALL-AND-STAND-UP
    {75,"\xAA\x55\x00\x78\xFB",5,0},  //STRUT
    {76,"\xAA\x55\x00\x79\xFB",5,0},  //LEFT-HOOK
    {77,"\xAA\x55\x00\x7A\xFB",5,0},  //RIGHT-HOOK
    {78,"\xAA\x55\x00\x7B\xFB",5,0},  //CLOSEGAMEPLAY
    {91,"\xAA\x55\x00\x80\xFB",5,0},  //EXECUTE-ACTION-ONE
    {92,"\xAA\x55\x00\x81\xFB",5,0},  //EXECUTE-ACTION-TWO
    {93,"\xAA\x55\x00\x82\xFB",5,0},  //EXECUTE-ACTION-THREE
    {94,"\xAA\x55\x00\x83\xFB",5,0},  //EXECUTE-ACTION-FOUR
    {95,"\xAA\x55\x00\x84\xFB",5,0},  //EXECUTE-ACTION-FIVE
    {96,"\xAA\x55\x00\x85\xFB",5,0},  //EXECUTE-ACTION-SIX
    {97,"\xAA\x55\x00\x86\xFB",5,0},  //EXECUTE-ACTION-SEVEN
    {98,"\xAA\x55\x00\x87\xFB",5,0},  //EXECUTE-ACTION-EIGHT
    {99,"\xAA\x55\x00\x88\xFB",5,0},  //EXECUTE-ACTION-NINE
    {100,"\xAA\x55\x00\x89\xFB",5,0},  //EXECUTE-ACTION-TEN
    {101,"\xAA\x55\x00\xA1\xFB",5,0},  //EXECUTE-ACTION-ELEVENT
    {102,"\xAA\x55\x00\xA2\xFB",5,0},  //EXECUTE-ACTION-TWELVE
    {103,"\xAA\x55\x00\xA3\xFB",5,0},  //EXECUTE-ACTION-THIRTEEN
    {104,"\xAA\x55\x00\xA4\xFB",5,0},  //EXECUTE-ACTION-FOURTEEN
    {105,"\xAA\x55\x00\xA5\xFB",5,0},  //EXECUTE-ACTION-FIFTEEN
    {106,"\xAA\x55\x00\xA6\xFB",5,0},  //EXECUTE-ACTION-SIXTEEN
    {107,"\xAA\x55\x00\xA7\xFB",5,0},  //EXECUTE-ACTION-SEVENTEEN
    {108,"\xAA\x55\x00\xA8\xFB",5,0},  //EXECUTE-ACTION-EIGHTEEN
    {109,"\xAA\x55\x00\xA9\xFB",5,0},  //EXECUTE-ACTION-NINETEEN
    {110,"\xAA\x55\x00\xAA\xFB",5,0},  //EXECUTE-ACTION-TWENTY
    {111,"\xAA\x55\x00\xAB\xFB",5,0},  //EXECUTE-ACTION-TWENTY-ONE
    {112,"\xAA\x55\x00\xAC\xFB",5,0},  //EXECUTE-ACTION-TWENTY-TWO
    {113,"\xAA\x55\x00\xAD\xFB",5,0},  //EXECUTE-ACTION-TWENTY-THREE
    {114,"\xAA\x55\x00\xAE\xFB",5,0},  //EXECUTE-ACTION-TWENTY-FOUR
    {115,"\xAA\x55\x00\xAF\xFB",5,0},  //EXECUTE-ACTION-TWENTY-FIVE
    {116,"\xAA\x55\x00\xB0\xFB",5,0},  //EXECUTE-ACTION-TWENTY-SIX
    {117,"\xAA\x55\x00\xB1\xFB",5,0},  //EXECUTE-ACTION-TWENTY-SEVEN
    {118,"\xAA\x55\x00\xB2\xFB",5,0},  //EXECUTE-ACTION-TWENTY-EIGHT
    {119,"\xAA\x55\x00\xB3\xFB",5,0},  //EXECUTE-ACTION-TWENTY-NINE
    {120,"\xAA\x55\x00\xB4\xFB",5,0},  //EXECUTE-ACTION-THIRTY
    {10001,"\xAA\x55\x01\x00\xFB",5,0},  //欢迎语
    {10002,"\xAA\x55\x02\x00\xFB",5,0},  //休息语
    {150,"\xAA\x55\xFF\x01\xFB",5,0},  //RECYCLABLE-WASTE
    {151,"\xAA\x55\xFF\x02\xFB",5,0},  //KITCHEN-WASTE
    {152,"\xAA\x55\xFF\x03\xFB",5,0},  //HAZARDOUS-WASTE
    {153,"\xAA\x55\xFF\x04\xFB",5,0},  //OTHER-WASTE
    {154,"\xAA\x55\xFF\x05\xFB",5,0},  //ABSTACLE-AHEAD
    {155,"\xAA\x55\xFF\x06\xFB",5,0},  //PARKING
    {156,"\xAA\x55\xFF\x07\xFB",5,0},  //RESTART-DEPARTURE
    {157,"\xAA\x55\xFF\x08\xFB",5,0},  //DETECT-LEFT-TURN
    {158,"\xAA\x55\xFF\x09\xFB",5,0},  //DETECT-RIGHT-TURN
    {159,"\xAA\x55\xFF\x0A\xFB",5,0},  //DETECT-PARKING
    {160,"\xAA\x55\xFF\x0B\xFB",5,0},  //DETECT-RED-LIGHT
    {161,"\xAA\x55\xFF\x0C\xFB",5,0},  //DETECT-GREEN-LIGHT
    {162,"\xAA\x55\xFF\x0D\xFB",5,0},  //DETECT-U-TURN
    {163,"\xAA\x55\xFF\x0E\xFB",5,0},  //DETECT-TURN
    {164,"\xAA\x55\xFF\x0F\xFB",5,0},  //WELCOME-YOU
    {167,"\xAA\x55\xFF\x12\xFB",5,0},  //FIND-SOMETHING-AHEAD
    {181,"\xAA\x55\xFF\x20\xFB",5,0},  //RECOGNIZED-ZERO
    {182,"\xAA\x55\xFF\x21\xFB",5,0},  //RECOGNIZED-ONE
    {183,"\xAA\x55\xFF\x22\xFB",5,0},  //RECOGNIZED-TWO
    {184,"\xAA\x55\xFF\x23\xFB",5,0},  //RECOGNIZED-THREE
    {185,"\xAA\x55\xFF\x24\xFB",5,0},  //RECOGNIZED-FOUR
    {186,"\xAA\x55\xFF\x25\xFB",5,0},  //RECOGNIZED-FIVE
    {187,"\xAA\x55\xFF\x26\xFB",5,0},  //RECOGNIZED-SIX
    {188,"\xAA\x55\xFF\x27\xFB",5,0},  //RECOGNIZED-SEVEN
    {189,"\xAA\x55\xFF\x28\xFB",5,0},  //RECOGNIZED-EIGHT
    {190,"\xAA\x55\xFF\x29\xFB",5,0},  //RECOGNIZED-NINE
    {191,"\xAA\x55\xFF\x2A\xFB",5,0},  //RECOGNIZED-RED
    {192,"\xAA\x55\xFF\x2B\xFB",5,0},  //RECOGNIZED-GREEN
    {193,"\xAA\x55\xFF\x2C\xFB",5,0},  //RECOGNIZED-BLUE
    {194,"\xAA\x55\xFF\x2D\xFB",5,0},  //RECOGNIZED-YELLOW
    {195,"\xAA\x55\xFF\x2E\xFB",5,0},  //RECOGNIZED-PURPLE

};

static send_cmd_pro_t send_data[] = {
    ///tag-send-uart-msg-by-cmd-id-after-has-asr-result-start
    //asr_msg_deal_by_cmd_id
    {3,"\xAA\x55\x03\x00\xFB",5,1},  //HELLO-HI-WONDER
    {4,"\xAA\x55\x04\x00\xFB",5,0},  //TURN-UP-VOLUME
    {5,"\xAA\x55\x05\x00\xFB",5,0},  //TURN-DOWN-VOLUME
    {6,"\xAA\x55\x06\x00\xFB",5,0},  //MAXIMUM-VOLUME
    {7,"\xAA\x55\x07\x00\xFB",5,0},  //MEDIUM-VOLUME
    {8,"\xAA\x55\x08\x00\xFB",5,0},  //MINIMUM-VOLUME
    {9,"\xAA\x55\x09\x00\xFB",5,0},  //START-BROADCASTING
    {10,"\xAA\x55\x0A\x00\xFB",5,0},  //STOP-BROADCASTING
    {11,"\xAA\x55\x00\x01\xFB",5,1},  //GO-STRAIGHT
    {12,"\xAA\x55\x00\x02\xFB",5,1},  //GO-BACKWARD
    {13,"\xAA\x55\x00\x03\xFB",5,1},  //TURN-LEFT
    {14,"\xAA\x55\x00\x04\xFB",5,1},  //TURN-RIGHT
    {15,"\xAA\x55\x00\x05\xFB",5,1},  //LEAN-FORWARD
    {16,"\xAA\x55\x00\x06\xFB",5,1},  //LEAN-BACK
    {17,"\xAA\x55\x00\x07\xFB",5,1},  //LEAN-LEFT
    {18,"\xAA\x55\x00\x08\xFB",5,1},  //LEAN-RIGHT
    {19,"\xAA\x55\x00\x09\xFB",5,1},  //STOP
    {20,"\xAA\x55\x00\x0A\xFB",5,1},  //ATTENTION
    {21,"\xAA\x55\x00\x0B\xFB",5,1},  //GET-DOWN
    {22,"\xAA\x55\x00\x0C\xFB",5,1},  //SIT-DOWN
    {23,"\xAA\x55\x00\x0D\xFB",5,1},  //SPEED-UP
    {24,"\xAA\x55\x00\x0E\xFB",5,1},  //SLOW-DOWN
    {25,"\xAA\x55\x00\x0F\xFB",5,1},  //RAISE-THE-BODY
    {26,"\xAA\x55\x00\x10\xFB",5,1},  //LOWER-THE-BODY
    {27,"\xAA\x55\x00\x11\xFB",5,1},  //MAKE-A-SOUND
    {28,"\xAA\x55\x00\x12\xFB",5,1},  //TURN-ON-THE-LIGHT
    {29,"\xAA\x55\x00\x13\xFB",5,1},  //TURN-OFF-THE-LIGHT
    {30,"\xAA\x55\x00\x14\xFB",5,1},  //OPEN-THE-DOOR
    {31,"\xAA\x55\x00\x15\xFB",5,1},  //CLOSE-THE-DOOR
    {32,"\xAA\x55\x00\x16\xFB",5,1},  //TURN-ON-THE-WATER-PUMP
    {33,"\xAA\x55\x00\x17\xFB",5,1},  //TURN-OFF-THE-WATER-PUMP
    {34,"\xAA\x55\x00\x18\xFB",5,1},  //UNFOLD-THE-AIRING-RACK
    {35,"\xAA\x55\x00\x19\xFB",5,1},  //FOLD-THE-ARING-RACK
    {36,"\xAA\x55\x00\x1A\xFB",5,1},  //HELLO
    {37,"\xAA\x55\x00\x1B\xFB",5,1},  //INTRODUCE-YOURSELF
    {38,"\xAA\x55\x00\x1C\xFB",5,1},  //SHOW-A-SKIII
    {39,"\xAA\x55\x00\x1D\xFB",5,1},  //MARCH
    {40,"\xAA\x55\x00\x1E\xFB",5,1},  //SHAKE-HEAD
    {41,"\xAA\x55\x00\x1F\xFB",5,1},  //DIVE-FORWARD
    {42,"\xAA\x55\x00\x20\xFB",5,1},  //DIVE-BACKWARD
    {43,"\xAA\x55\x00\x21\xFB",5,1},  //COMBATMODE
    {44,"\xAA\x55\x00\x22\xFB",5,1},  //SQUAT-DOWN
    {45,"\xAA\x55\x00\x23\xFB",5,1},  //SHAKE-IT-OFF
    {46,"\xAA\x55\x00\x24\xFB",5,1},  //TURN-ON-THE-FAN
    {47,"\xAA\x55\x00\x25\xFB",5,1},  //TURN-OFF-THE-FAN
    {48,"\xAA\x55\x00\x26\xFB",5,1},  //ROTATING-STEERING-GEAR
    {49,"\xAA\x55\x00\x27\xFB",5,1},  //GIVE-A-RED-LIGHT
    {50,"\xAA\x55\x00\x28\xFB",5,1},  //GIVE-A-GREEN-LIGHT
    {51,"\xAA\x55\x00\x29\xFB",5,1},  //GIVE-A-BLUE-LIGHT
    {52,"\xAA\x55\x00\x2A\xFB",5,1},  //SHOW-SMILEY-FACE
    {53,"\xAA\x55\x00\x2B\xFB",5,1},  //SHOW-CRYING-FACE
    {54,"\xAA\x55\x00\x62\xFB",5,1},  //START-FACE-RECOGNITION
    {55,"\xAA\x55\x00\x63\xFB",5,1},  //START-LABEL-RECOGNITION
    {56,"\xAA\x55\x00\x64\xFB",5,1},  //START-WASTE-SORTING
    {57,"\xAA\x55\x00\x65\xFB",5,1},  //START-COLOR-RECOGNITION
    {58,"\xAA\x55\x00\x66\xFB",5,1},  //START-LINE-FOLLOWING
    {59,"\xAA\x55\x00\x67\xFB",5,1},  //START-COLOR-TRACKING
    {60,"\xAA\x55\x00\x68\xFB",5,1},  //START-OBSTACLE-AVOIDANCE
    {61,"\xAA\x55\x00\x69\xFB",5,1},  //SORT-RED
    {62,"\xAA\x55\x00\x6A\xFB",5,1},  //SORT-GREEN
    {63,"\xAA\x55\x00\x6B\xFB",5,1},  //SORT-BLUE
    {64,"\xAA\x55\x00\x6C\xFB",5,1},  //DANCE
    {65,"\xAA\x55\x00\x6D\xFB",5,1},  //PUSH-UP
    {66,"\xAA\x55\x00\x6E\xFB",5,1},  //LEFT-FOOT-SHOOT
    {67,"\xAA\x55\x00\x6F\xFB",5,1},  //RIGHT-FOOT-SHOOT
    {68,"\xAA\x55\x00\x71\xFB",5,1},  //TWIST
    {69,"\xAA\x55\x00\x72\xFB",5,1},  //SIT-UP
    {70,"\xAA\x55\x00\x73\xFB",5,1},  //BOW
    {71,"\xAA\x55\x00\x74\xFB",5,1},  //SPREAD-THE-HANDS
    {72,"\xAA\x55\x00\x75\xFB",5,1},  //WAVE-HAND
    {73,"\xAA\x55\x00\x76\xFB",5,1},  //MARCH-IN-PLACE
    {74,"\xAA\x55\x00\x77\xFB",5,1},  //FALL-AND-STAND-UP
    {75,"\xAA\x55\x00\x78\xFB",5,1},  //STRUT
    {76,"\xAA\x55\x00\x79\xFB",5,1},  //LEFT-HOOK
    {77,"\xAA\x55\x00\x7A\xFB",5,1},  //RIGHT-HOOK
    {78,"\xAA\x55\x00\x7B\xFB",5,1},  //CLOSEGAMEPLAY
    {91,"\xAA\x55\x00\x80\xFB",5,1},  //EXECUTE-ACTION-ONE
    {92,"\xAA\x55\x00\x81\xFB",5,1},  //EXECUTE-ACTION-TWO
    {93,"\xAA\x55\x00\x82\xFB",5,1},  //EXECUTE-ACTION-THREE
    {94,"\xAA\x55\x00\x83\xFB",5,1},  //EXECUTE-ACTION-FOUR
    {95,"\xAA\x55\x00\x84\xFB",5,1},  //EXECUTE-ACTION-FIVE
    {96,"\xAA\x55\x00\x85\xFB",5,1},  //EXECUTE-ACTION-SIX
    {97,"\xAA\x55\x00\x86\xFB",5,1},  //EXECUTE-ACTION-SEVEN
    {98,"\xAA\x55\x00\x87\xFB",5,1},  //EXECUTE-ACTION-EIGHT
    {99,"\xAA\x55\x00\x88\xFB",5,1},  //EXECUTE-ACTION-NINE
    {100,"\xAA\x55\x00\x89\xFB",5,1},  //EXECUTE-ACTION-TEN
    {101,"\xAA\x55\x00\xA1\xFB",5,1},  //EXECUTE-ACTION-ELEVENT
    {102,"\xAA\x55\x00\xA2\xFB",5,1},  //EXECUTE-ACTION-TWELVE
    {103,"\xAA\x55\x00\xA3\xFB",5,1},  //EXECUTE-ACTION-THIRTEEN
    {104,"\xAA\x55\x00\xA4\xFB",5,1},  //EXECUTE-ACTION-FOURTEEN
    {105,"\xAA\x55\x00\xA5\xFB",5,1},  //EXECUTE-ACTION-FIFTEEN
    {106,"\xAA\x55\x00\xA6\xFB",5,1},  //EXECUTE-ACTION-SIXTEEN
    {107,"\xAA\x55\x00\xA7\xFB",5,1},  //EXECUTE-ACTION-SEVENTEEN
    {108,"\xAA\x55\x00\xA8\xFB",5,1},  //EXECUTE-ACTION-EIGHTEEN
    {109,"\xAA\x55\x00\xA9\xFB",5,1},  //EXECUTE-ACTION-NINETEEN
    {110,"\xAA\x55\x00\xAA\xFB",5,1},  //EXECUTE-ACTION-TWENTY
    {111,"\xAA\x55\x00\xAB\xFB",5,1},  //EXECUTE-ACTION-TWENTY-ONE
    {112,"\xAA\x55\x00\xAC\xFB",5,1},  //EXECUTE-ACTION-TWENTY-TWO
    {113,"\xAA\x55\x00\xAD\xFB",5,1},  //EXECUTE-ACTION-TWENTY-THREE
    {114,"\xAA\x55\x00\xAE\xFB",5,1},  //EXECUTE-ACTION-TWENTY-FOUR
    {115,"\xAA\x55\x00\xAF\xFB",5,1},  //EXECUTE-ACTION-TWENTY-FIVE
    {116,"\xAA\x55\x00\xB0\xFB",5,1},  //EXECUTE-ACTION-TWENTY-SIX
    {117,"\xAA\x55\x00\xB1\xFB",5,1},  //EXECUTE-ACTION-TWENTY-SEVEN
    {118,"\xAA\x55\x00\xB2\xFB",5,1},  //EXECUTE-ACTION-TWENTY-EIGHT
    {119,"\xAA\x55\x00\xB3\xFB",5,1},  //EXECUTE-ACTION-TWENTY-NINE
    {120,"\xAA\x55\x00\xB4\xFB",5,1},  //EXECUTE-ACTION-THIRTY

};

// {"cmd_id","wakeup_net"},
wakeup_data wakeup_lst[] = {
///tag-insert-multi-wake-up-net-switch-wakeup-lst-pos-13
//multi_wake_up_net_switch_wakeup_lst_function
    {3,1}, //HELLO-HI-WONDER


};

static wakeup_net_pro_t wakeup_net_recv_prot[] = {
    ///tag-insert-multi-wake-up-net-switch-by-recv-protocol-pos-14
};

///tag-insert-uart-send-data-function-code-pos-1
//uart_send_data_function
void uart_send_bytes(char *buffer,int length)
{
	for(int index = 0; index < length; index++)
	{
		UartPollingSenddata((UART_TypeDef*)UART_PROTOCOL_NUMBER, buffer[index]);
	}
}


///tag-insert-uart-recv-function-code-pos-2
//uart_recv_data_function
void send_packet_rev_msg(void *msg, int msg_lenght)
{
	sys_msg_t send_msg;
	BaseType_t xResult;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	send_msg.msg_type = SYS_MSG_TYPE_COM;
	if(msg_lenght <= sizeof(send_msg.msg_data.com_data))
	{
		memcpy((uint8_t *)(&send_msg.msg_data.com_data), msg, msg_lenght);
		xResult = send_msg_to_sys_task(&send_msg,&xHigherPriorityTaskWoken);
		if((xResult != pdFAIL)&&(pdTRUE == xHigherPriorityTaskWoken))
		{
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
}

static char rx_buffer[24];
void uart_irq_handler(void)
{
	if (((UART_TypeDef*)UART_PROTOCOL_NUMBER)->UARTMIS & (1UL << UART_RXTimeoutInt))
	{
		rx_buffer[0] = 1;
		while(0 == (((UART_TypeDef*)UART_PROTOCOL_NUMBER)->UARTFlag & (0x1 << UART_RXFE)))
		{
			if (rx_buffer[0] >= 20)
			{
				memmove(rx_buffer+1, rx_buffer+2, 19);
				rx_buffer[0] = 20;
			}
			rx_buffer[rx_buffer[0]++] = UART_RXDATA((UART_TypeDef*)UART_PROTOCOL_NUMBER);
		}
		send_packet_rev_msg(&rx_buffer, rx_buffer[0]);
	}
	UART_IntClear((UART_TypeDef*)UART_PROTOCOL_NUMBER,UART_AllInt);
}



///tag-insert-insert-baudrate-calibrate-send-function-code-pos-3




// 接收到协议后的播报
void deal_voice_by_recv_protocol(char *p_data,char length, int* max_vol_id,int* min_vol_id)
{
    int vol_id = 0;
    int recv_pro_len = sizeof(recv_data)/sizeof(recv_cmd_pro_t);
    for(int i=0;i<recv_pro_len;i++)
    {
        vol_id = recv_data[i].paly_type;
        if(vol_id == PLAY_MAXIMUM_VOLUME)
        {
            *max_vol_id = recv_data[i].cmd_id;
        }
        if(vol_id == PLAY_MINIMUM_VOLUME)
        {
            *min_vol_id = recv_data[i].cmd_id;
        }
        if(memcmp(p_data,recv_data[i].pro_buf,recv_data[i].pro_len) == 0)
        {
            if(vol_id == PLAY_MAXIMUM_VOLUME)
            {
                vol_set(VOLUME_MAX);
            }
            else if(vol_id == PLAY_MINIMUM_VOLUME)
            {
                vol_set(VOLUME_MIN);
            }
            else if(vol_id == PLAY_TURN_UP_VOLUME)
            {
                vol_set(vol_get() + 1);
            }
            else if(vol_id == PLAY_TURN_DOWN_VOLUME)
            {
                vol_set(vol_get() - 1);
            }
        }
    }
}


void change_wakeup_net_by_recv_protocol(char *p_data,char length)
{
    uint8_t wakeup_net;
    uint16_t play_id = 0;
    int i = 0;

    int net_len = sizeof(wakeup_net_recv_prot)/sizeof(wakeup_net_pro_t);
    for(;i<net_len;i++)
    {
        if (memcmp(p_data, wakeup_net_recv_prot[i].pro_buf, wakeup_net_recv_prot[i].pro_len) == 0)
        {
            wakeup_net = wakeup_net_recv_prot[i].net_num;
            play_id = wakeup_net + PLAY_ID_OFFSET_SWITCH;
            set_wakeup_net(wakeup_net);
            #if (UART_PROTOCOL_VER == 255)
                pause_voice_in();
                prompt_play_by_cmd_id(play_id, -1, default_play_done_callback,true);
            #endif
            break;
        }
    }
}


//
extern void set_state_enter_wakeup(uint32_t exit_wakup_ms);      /* 设置退出唤醒时间 */
void com_msg_process(char * msg)
{
    int i = 0;
    int cmd_id = -1;
    int vol_id = -1;
    char length  = msg[0] - 1;
    char *p_data = msg + 1;
    int max_vol_id = -1;
    int min_vol_id = -1;
    
    deal_voice_by_recv_protocol(p_data,length,&max_vol_id,&min_vol_id);
    change_wakeup_net_by_recv_protocol(p_data,length);
    // 接收到协议后的播报
    int recv_pro_len = sizeof(recv_data)/sizeof(recv_cmd_pro_t);
    for(;i<recv_pro_len;i++)
    {
        if(memcmp(p_data,recv_data[i].pro_buf,recv_data[i].pro_len) == 0)
        {
            cmd_id = recv_data[i].cmd_id;
            vol_id = recv_data[i].paly_type;
            // 如果协议是唤醒词的，则需要切换到命令词网络s
            if(check_cmd_id_is_wake_up(cmd_id))
            {
                change_asr_normal_word();
                set_state_enter_wakeup(EXIT_WAKEUP_TIME);
            }
            // 播报
            if((vol_id == PLAY_TURN_UP_VOLUME) && (vol_get() == VOLUME_MAX))
            {
                cmd_id = max_vol_id;
            }
            if((vol_id == PLAY_TURN_DOWN_VOLUME) && (vol_get() == VOLUME_MIN))
            {
                cmd_id = min_vol_id;
            }
        }
    }

    ///tag-insert-baudrate-calibrate-recv-functioncode-pos-4

    //播报
    pause_voice_in();
    prompt_play_by_cmd_id(cmd_id, -1, default_play_done_callback,true);
}

uint8_t check_cmd_id_is_wake_up(uint16_t cmd_id)
{
    int i = 0;
    int net_num = 0;
    int wakeup_num = sizeof(wakeup_lst) / sizeof(wakeup_data);
    for(; i < wakeup_num; i++)
    {
        if(wakeup_lst[i].wakeup_cmd_id == cmd_id)
        {
            net_num = 1;
            break;
        }
    }
    return net_num;
}

uint8_t get_wakeup_net_by_cmd_id(uint16_t cmd_id)
{
    int i = 0;
    int net_num = 1;
    int wakeup_num = sizeof(wakeup_lst) / sizeof(wakeup_data);
    for(; i < wakeup_num; i++)
    {
        if(wakeup_lst[i].wakeup_cmd_id == cmd_id)
        {
            net_num = wakeup_lst[i].wakeup_net;
            break;
        }
    }
    return net_num;
}


uint32_t deal_welcome_for_usr(void)
{
    int i = 0;
    for(;i<sizeof(welcome_pro)/sizeof(send_cmd_pro_t);i++)
    {
        uart_send_bytes(welcome_pro[i].pro_buf,welcome_pro[i].pro_len);
    }
}


uint32_t deal_exit_wakeup_for_usr(void)
{
    if(power_on_flag)
    {
        power_on_flag = 0;
    }
    else
    {
        int i = 0;
        for(;i<sizeof(bye_pro)/sizeof(send_cmd_pro_t);i++)
        {
            uart_send_bytes(bye_pro[i].pro_buf,bye_pro[i].pro_len);
        }
    }
}


int check_change_cmd_id(uint16_t cmd_id)
{
    int ret = 0;
    int i = 0;
    for(;i<sizeof(wakeup_net_recv_prot)/sizeof(wakeup_net_pro_t);i++)
    {
        if(cmd_id == wakeup_net_recv_prot[i].cmd_id)
        {
            ret = 1;
            break;
        }
    }
    return ret;
}


void set_wake_up_net_by_asr(uint16_t cmd_id)
{
    uint8_t wakeup_net;
    uint16_t real_len;
    //
    if((cmd_id != SWITCH_WAKEWORD_ID) && (!check_change_cmd_id(cmd_id)))
    {
        return;
    }
    if (CINV_OPER_SUCCESS != cinv_item_read(NVDATA_ID_USER_WAKEUP_NET, sizeof(wakeup_net), &wakeup_net, &real_len))
    {
        wakeup_net = 1;
        cinv_item_init(NVDATA_ID_USER_WAKEUP_NET, sizeof(wakeup_net), &wakeup_net);
    }
    else
    {
        if(cmd_id == SWITCH_WAKEWORD_ID)
        {
            wakeup_net += 1;
            if(wakeup_net > WAKE_UP_NET_TOTAL)
            {
                wakeup_net = 1;
            }
        }
        else
        {
            wakeup_net = get_wakeup_net_by_cmd_id(cmd_id);
        }
    }
    set_wakeup_net(wakeup_net);
    // 
    int play_id = wakeup_net + PLAY_ID_OFFSET_SWITCH;
    pause_voice_in();
    prompt_play_by_cmd_id(play_id, -1, default_play_done_callback,true);
}

/**
 * @brief 用户初始化
 *
 */
void userapp_initial(void)
{
    #if CPU_RATE_PRINT
    init_timer3_getresource();
    #endif

    #if MSG_COM_USE_UART_EN
    #if (UART_PROTOCOL_VER == 1)
    uart_communicate_init();
    #elif (UART_PROTOCOL_VER == 2)
    vmup_communicate_init();
    #elif (UART_PROTOCOL_VER == 255)
    
    #if HAL_UART0_BASE == UART_PROTOCOL_NUMBER
    __eclic_irq_set_vector(UART0_IRQn, (int32_t)uart_irq_handler);
    #elif (HAL_UART1_BASE == UART_PROTOCOL_NUMBER)
    __eclic_irq_set_vector(UART1_IRQn, (int32_t)uart_irq_handler);
    #else
    __eclic_irq_set_vector(UART2_IRQn, (int32_t)uart_irq_handler);
    #endif

    UARTInterruptConfig((UART_TypeDef *)UART_PROTOCOL_NUMBER, UART_PROTOCOL_BAUDRATE);
    UART_IntMaskConfig((UART_TypeDef *)UART_PROTOCOL_NUMBER, UART_RXTimeoutInt, DISABLE);
    UART_IntMaskConfig((UART_TypeDef *)UART_PROTOCOL_NUMBER, UART_RXInt, ENABLE);
    #if UART_BAUDRATE_CALIBRATE
    baudrate_calibrate_init(UART_PROTOCOL_NUMBER, UART_PROTOCOL_BAUDRATE, defined_send_baudrate_sync_req);          // 初始化波特率校准
    baudrate_calibrate_start();         // 启动一次波特率校准
    #endif
    #endif
    #endif

    #if MSG_USE_I2C_EN
    i2c_communicate_init();
    #endif

    ///tag-gpio-init
    user_pin_control_init();
}

/**
 * @brief 处理按键消息（目前未实现该demo）
 *
 * @param key_msg 按键消息
 */
void userapp_deal_key_msg(sys_msg_key_data_t  *key_msg)
{
    (void)(key_msg);
}



/**
 * @brief 按语义ID响应asr消息处理
 *
 * @param asr_msg
 * @param cmd_handle
 * @param semantic_id
 * @return uint32_t
 */
uint32_t deal_asr_msg_by_semantic_id(sys_msg_asr_data_t *asr_msg, cmd_handle_t cmd_handle, uint32_t semantic_id)
{
    uint32_t ret = 1;
    if (PRODUCT_GENERAL == get_product_id_from_semantic_id(semantic_id))
    {
        uint8_t vol;
        int select_index = -1;
        switch(get_function_id_from_semantic_id(semantic_id))
        {
        case VOLUME_UP:        //增大音量
            vol = vol_set(vol_get() + 1);
            select_index = (vol == VOLUME_MAX) ? 1:0;
            break;
        case VOLUME_DOWN:      //减小音量
            vol = vol_set(vol_get() - 1);
            select_index = (vol == VOLUME_MIN) ? 1:0;
            break;
        case MAXIMUM_VOLUME:   //最大音量
            vol_set(VOLUME_MAX);
            break;
        case MEDIUM_VOLUME:  //中等音量
            vol_set(VOLUME_MID);
            break;
        case MINIMUM_VOLUME:   //最小音量
            vol_set(VOLUME_MIN);
            break;
        case TURN_ON_VOICE_BROADCAST:    //开启语音播报
            prompt_player_enable(ENABLE);
            break;
        case TURN_OFF_VOICE_BROADCAST:    //关闭语音播报
            prompt_player_enable(DISABLE);
            break;
        default:
            ret = 0;
            break;
        }
        if (ret)
        {
            #if PLAY_OTHER_CMD_EN
            pause_voice_in();
            prompt_play_by_cmd_handle(cmd_handle, select_index, default_play_done_callback,true);
            #endif
        }
    }
    else
    {
        ret = 0;
    }
    return ret;
}


/**
 * @brief 按命令词id响应asr消息处理
 *
 * @param asr_msg
 * @param cmd_handle
 * @param cmd_id
 * @return uint32_t
 */
uint32_t deal_asr_msg_by_cmd_id(sys_msg_asr_data_t *asr_msg, cmd_handle_t cmd_handle, uint16_t cmd_id)
{
    uint32_t ret = 1;
    int select_index = -1;
    int play_id = 0;
    play_id = cmd_id;
    switch(cmd_id)
    {   
        case -1:
            ret = 0;
        break;
        ///tag-insert-control-volume-code-pos-6
        //voice_contrl_by_cmd_id_function
        case 4: //TURN-UP-VOLUME
		vol_set(vol_get() + 1);
        if(vol_get() == VOLUME_MAX)
        {
            play_id = 6;
        }
		break;

        case 5: //TURN-DOWN-VOLUME
		vol_set(vol_get() - 1);
        if(vol_get() == VOLUME_MIN)
        {
            play_id = 8;
        }
		break;

        case 6: //MAXIMUM-VOLUME
		vol_set(VOLUME_MAX);
		break;

        case 7: //MEDIUM-VOLUME
		vol_set(VOLUME_MID);
		break;

        case 8: //MINIMUM-VOLUME
		vol_set(VOLUME_MIN);
		break;

        case 9: //START-BROADCASTING
		prompt_player_enable(ENABLE);
		break;

        case 10: //STOP-BROADCASTING
		prompt_player_enable(DISABLE);
		break;



        default:
            ret = 0;
        break;
    }
    if (ret && select_index >= -1)
    {
        #if 1
        pause_voice_in();
        prompt_play_by_cmd_id(play_id, -1, default_play_done_callback,true);
        #endif
    }
    return ret;
}


/**
 * @brief 用户自定义消息处理
 *
 * @param msg
 * @return uint32_t
 */
uint32_t deal_userdef_msg(sys_msg_t *msg)
{
    uint32_t ret = 1;
    switch(msg->msg_type)
    {
    /* 按键消息 */
    case SYS_MSG_TYPE_KEY:
    {
        sys_msg_key_data_t *key_rev_data;
        key_rev_data = &msg->msg_data.key_data;
        userapp_deal_key_msg(key_rev_data);
        break;
    }
    #if MSG_COM_USE_UART_EN
    /* CI串口协议消息 */
    case SYS_MSG_TYPE_COM:
    {
		#if ((UART_PROTOCOL_VER == 1) || (UART_PROTOCOL_VER == 2))
    	sys_msg_com_data_t *com_rev_data;
        com_rev_data = &(msg->msg_data.com_data);
        userapp_deal_com_msg(com_rev_data);
        #elif (UART_PROTOCOL_VER == 255)
        com_msg_process(&msg->msg_data.com_data); //串口数据接收时,rx_buffer[0]存放的是接收的数据长度信息，串口数据从rx_buffer[1]开始存放
        #endif
        break;
    }
    #endif
    /* CI IIC 协议消息 */
    #if MSG_USE_I2C_EN
    case SYS_MSG_TYPE_I2C:
    {
        sys_msg_i2c_data_t *i2c_rev_data;
        i2c_rev_data = &msg->msg_data.i2c_data;
        userapp_deal_i2c_msg(i2c_rev_data);
        break;
    }
    #endif
    default:
        break;
    }
    return ret;
}


/**
 * @brief 按命令词id响应asr消息处理
 *
 * @param asr_msg
 * @param cmd_handle
 * @param cmd_id
 * @return uint32_t
 */
uint32_t deal_asr_msg_by_cmd_id_for_usr(cmd_handle_t cmd_handle)
{
    uint32_t ret = 1;
    int select_index = -1;
    uint16_t cmd_id = cmd_info_get_command_id(cmd_handle);
    #if (UART_PROTOCOL_VER == 255)
    if(MULTI_WAKE_UP_NET_SWITCH)
    {
        set_wake_up_net_by_asr(cmd_id);
        if(cmd_info_is_wakeup_word(cmd_handle))
        {
            if(get_wakeup_net_by_cmd_id(cmd_id) != get_wakeup_net())
            {
                return ret;
            }
            else
            {
                cmd_info_change_cur_model_group(0);
            }
        }
    }
    #endif
    // 识别到命令词后的发送协议
    int send_pro_len = sizeof(send_data)/sizeof(send_cmd_pro_t);
    int i=0;
    for(;i<send_pro_len;i++)
    {
        if(cmd_id == send_data[i].cmd_id)
        {
            uart_send_bytes(send_data[i].pro_buf,send_data[i].pro_len);
            ret = send_data[i].paly_type;
        }
    }
    if (ret && select_index >= -1)
    {
        #if (UART_PROTOCOL_VER == 255)
        pause_voice_in();
        prompt_play_by_cmd_handle(cmd_handle, select_index, default_play_done_callback,true);
        #else
        #if PLAY_OTHER_CMD_EN
        pause_voice_in();
        prompt_play_by_cmd_handle(cmd_handle, select_index, default_play_done_callback,true);
        #endif
        #endif
    }

    return ret;
}
