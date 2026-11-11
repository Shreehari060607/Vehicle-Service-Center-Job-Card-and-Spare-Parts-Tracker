#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

bool Utils_ValidateVehReg(const char *regNum) {
    if (!regNum) return false;
    
    size_t len = strlen(regNum);
    if (len < 8 || len > 13) return false;

    // Check standard Indian format prefix (2 uppercase letters + 2 digits)
    if (!isalpha((unsigned char)regNum[0]) || !isalpha((unsigned char)regNum[1])) return false;
    if (!isdigit((unsigned char)regNum[2]) || !isdigit((unsigned char)regNum[3])) return false;

    // Ensure all characters are alphanumeric
    for (size_t i = 0; i < len; i++) {
        if (!isalnum((unsigned char)regNum[i])) return false;
    }

    return true;
}

void Utils_TrimNewline(char *str) {
    if (!str) return;
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

bool Utils_ParseUInt(const char *str, uint32_t *outVal) {
    if (!str || !outVal) return false;
    char *endptr = NULL;
    long val = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0' || val < 0) {
        return false;
    }
    *outVal = (uint32_t)val;
    return true;
}

bool Utils_ParseFloat(const char *str, float *outVal) {
    if (!str || !outVal) return false;
    char *endptr = NULL;
    float val = strtof(str, &endptr);
    if (endptr == str || *endptr != '\0' || val < 0.0f) {
        return false;
    }
    *outVal = val;
    return true;
}

const char* Utils_StatusToString(JobStatus_t status) {
    switch (status) {
        case STATUS_OPEN:        return "OPEN";
        case STATUS_IN_PROGRESS: return "IN_PROGRESS";
        case STATUS_COMPLETED:   return "COMPLETED";
        case STATUS_BILLED:      return "BILLED";
        default:                 return "UNKNOWN";
    }
}

const char* Utils_ServiceTypeToString(ServiceType_t type) {
    switch (type) {
        case SERVICE_PERIODIC: return "PERIODIC";
        case SERVICE_REPAIR:   return "REPAIR";
        case SERVICE_ACCIDENT: return "ACCIDENT";
        default:               return "UNKNOWN";
    }
}

const char* Utils_ErrorToString(Status_t err) {
    switch (err) {
        case STATUS_SUCCESS:                return "Success";
        case ERR_INVALID_INPUT:             return "Invalid input format or out-of-range value";
        case ERR_DUPLICATE_ID:              return "Record ID already exists";
        case ERR_JOB_NOT_FOUND:             return "Job card not found";
        case ERR_PART_NOT_FOUND:            return "Spare part not found";
        case ERR_INSUFFICIENT_STOCK:        return "Insufficient stock available";
        case ERR_INVALID_STATUS_TRANSITION: return "Invalid status transition order";
        case ERR_STORAGE_FULL:              return "Storage capacity reached";
        case ERR_MAX_PARTS_EXCEEDED:        return "Maximum parts per job card reached";
        case ERR_INVALID_DISCOUNT:          return "Discount percentage must be between 0 and 50%";
        case ERR_FILE_OPEN_FAILED:          return "Failed to open persistent data file";
        case ERR_FILE_READ_FAILED:          return "Failed to read data from file";
        case ERR_FILE_WRITE_FAILED:         return "Failed to write data to file";
        default:                            return "Unknown error";
    }
}
