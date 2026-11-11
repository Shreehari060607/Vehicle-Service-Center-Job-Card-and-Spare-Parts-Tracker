#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>

/* System Constraints */
#define MAX_JOBS           100
#define MAX_PARTS          100
#define MAX_PARTS_PER_JOB  10

/* String Length Constraints (including null terminator) */
#define MAX_REG_LEN        16
#define MAX_NAME_LEN       50
#define MAX_DESC_LEN       100
#define MAX_PATH_LEN       256

/* Billing Rate Constants */
#define GST_RATE_PERCENT   18.0f
#define LABOUR_PERIODIC    500.0f
#define LABOUR_REPAIR      1000.0f
#define LABOUR_ACCIDENT    2500.0f

/* Workflow Status */
typedef enum {
    STATUS_OPEN = 0,
    STATUS_IN_PROGRESS,
    STATUS_COMPLETED,
    STATUS_BILLED
} JobStatus_t;

/* Service Categories */
typedef enum {
    SERVICE_PERIODIC = 0,
    SERVICE_REPAIR,
    SERVICE_ACCIDENT
} ServiceType_t;

/* Global Function Status Codes */
typedef enum {
    STATUS_SUCCESS = 0,
    ERR_INVALID_INPUT,
    ERR_DUPLICATE_ID,
    ERR_JOB_NOT_FOUND,
    ERR_PART_NOT_FOUND,
    ERR_INSUFFICIENT_STOCK,
    ERR_INVALID_STATUS_TRANSITION,
    ERR_STORAGE_FULL,
    ERR_MAX_PARTS_EXCEEDED,
    ERR_INVALID_DISCOUNT,
    ERR_FILE_OPEN_FAILED,
    ERR_FILE_READ_FAILED,
    ERR_FILE_WRITE_FAILED
} Status_t;

#endif /* COMMON_H */