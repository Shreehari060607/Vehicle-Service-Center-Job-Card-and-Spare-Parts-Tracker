#ifndef SPARE_PARTS_H
#define SPARE_PARTS_H

#include "common.h"

typedef struct {
    uint32_t partId;
    char name[MAX_NAME_LEN];
    uint32_t quantity;
    float unitPrice;
    uint32_t reorderLevel;
} SparePart_t;

/* Inventory Public API */
void SpareParts_Init(void);
Status_t SpareParts_Add(const SparePart_t *part);
Status_t SpareParts_FindById(uint32_t partId, SparePart_t *outPart);
Status_t SpareParts_DeductStock(uint32_t partId, uint32_t qty);
Status_t SpareParts_AddStock(uint32_t partId, uint32_t qty);
Status_t SpareParts_GetLowStock(SparePart_t *outList, uint32_t *outCount);
uint32_t SpareParts_GetCount(void);
const SparePart_t* SpareParts_GetAll(void);

#endif /* SPARE_PARTS_H */