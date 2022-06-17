
#ifndef _AS_STRUCTS_H_
#define _AS_STRUCTS_H_
/**
 * Describes Temperature object
 */
typedef struct
{
    float temperatureC;
    char *label;
    uint8_t index;
} ASTempSensor;

#endif