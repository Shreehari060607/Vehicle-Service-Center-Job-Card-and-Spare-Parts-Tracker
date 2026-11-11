#ifndef FILE_IO_H
#define FILE_IO_H

#include "common.h"
#include "job_card.h"
#include "spare_parts.h"

Status_t FileIO_LoadJobs(const char *filename, JobCard_t *jobs, uint32_t *count);
Status_t FileIO_SaveJobs(const char *filename, const JobCard_t *jobs, uint32_t count);
Status_t FileIO_LoadParts(const char *filename, SparePart_t *parts, uint32_t *count);
Status_t FileIO_SaveParts(const char *filename, const SparePart_t *parts, uint32_t count);
Status_t FileIO_ExportBill(const char *filename, const JobCard_t *job, const Bill_t *bill);

#endif /* FILE_IO_H */