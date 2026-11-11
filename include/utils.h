#ifndef UTILS_H
#define UTILS_H

#include "common.h"

bool Utils_ValidateVehReg(const char *regNum);
void Utils_TrimNewline(char *str);
bool Utils_ParseUInt(const char *str, uint32_t *outVal);
bool Utils_ParseFloat(const char *str, float *outVal);
const char* Utils_StatusToString(JobStatus_t status);
const char* Utils_ServiceTypeToString(ServiceType_t type);
const char* Utils_ErrorToString(Status_t err);

#endif /* UTILS_H */