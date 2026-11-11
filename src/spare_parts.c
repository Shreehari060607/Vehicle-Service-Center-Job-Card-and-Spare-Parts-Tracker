#include <stdio.h>
#include <string.h>
#include "spare_parts.h"

static SparePart_t s_parts[MAX_PARTS];
static uint32_t s_partCount = 0;

void SpareParts_Init(void) {
    memset(s_parts, 0, sizeof(s_parts));
    s_partCount = 0;
}

Status_t SpareParts_Add(const SparePart_t *part) {
    if (!part || part->partId == 0 || strlen(part->name) == 0) {
        return ERR_INVALID_INPUT;
    }
    if (s_partCount >= MAX_PARTS) {
        return ERR_STORAGE_FULL;
    }

    // Check duplicate ID
    for (uint32_t i = 0; i < s_partCount; i++) {
        if (s_parts[i].partId == part->partId) {
            return ERR_DUPLICATE_ID;
        }
    }

    s_parts[s_partCount] = *part;
    s_partCount++;
    return STATUS_SUCCESS;
}

Status_t SpareParts_FindById(uint32_t partId, SparePart_t *outPart) {
    if (partId == 0 || !outPart) return ERR_INVALID_INPUT;

    for (uint32_t i = 0; i < s_partCount; i++) {
        if (s_parts[i].partId == partId) {
            *outPart = s_parts[i];
            return STATUS_SUCCESS;
        }
    }
    return ERR_PART_NOT_FOUND;
}

Status_t SpareParts_DeductStock(uint32_t partId, uint32_t qty) {
    if (partId == 0 || qty == 0) return ERR_INVALID_INPUT;

    for (uint32_t i = 0; i < s_partCount; i++) {
        if (s_parts[i].partId == partId) {
            if (s_parts[i].quantity < qty) {
                return ERR_INSUFFICIENT_STOCK;
            }
            s_parts[i].quantity -= qty;
            return STATUS_SUCCESS;
        }
    }
    return ERR_PART_NOT_FOUND;
}

Status_t SpareParts_AddStock(uint32_t partId, uint32_t qty) {
    if (partId == 0 || qty == 0) return ERR_INVALID_INPUT;

    for (uint32_t i = 0; i < s_partCount; i++) {
        if (s_parts[i].partId == partId) {
            s_parts[i].quantity += qty;
            return STATUS_SUCCESS;
        }
    }
    return ERR_PART_NOT_FOUND;
}

Status_t SpareParts_GetLowStock(SparePart_t *outList, uint32_t *outCount) {
    if (!outList || !outCount) return ERR_INVALID_INPUT;

    uint32_t count = 0;
    for (uint32_t i = 0; i < s_partCount; i++) {
        if (s_parts[i].quantity <= s_parts[i].reorderLevel) {
            outList[count++] = s_parts[i];
        }
    }
    *outCount = count;
    return STATUS_SUCCESS;
}

uint32_t SpareParts_GetCount(void) {
    return s_partCount;
}

const SparePart_t* SpareParts_GetAll(void) {
    return s_parts;
}
