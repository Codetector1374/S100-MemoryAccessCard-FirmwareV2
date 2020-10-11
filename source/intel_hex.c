#include "intel_hex.h"

#include "ch.h"
#include "hal.h"

int8_t parseHex(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

uint8_t parseU8(char *stream, uint8_t *advancement)
{
    *advancement = 0;

    int8_t high = parseHex(*stream);
    if (high < 0) {
        return 0;
    }

    int8_t low = parseHex(*(stream + 1));
    if (low < 0) {
        return 0;
    }

    *advancement = 2;
    uint8_t value = ((uint8_t)low) | (high << 4);
    return value;
}

IHEX_STS parseiHex
(
    char       *stream,
    size_t      len,
    uint8_t    *buf,
    uint8_t    *filled,
    uint16_t   *baseAddr,
    IHEX_TYPE  *recordType
)
{
    *filled = 0;

    if (len == 0 || stream[0] != ':')
        return IHEX_STS_ERR;

    uint8_t advancement = 0;
    uint8_t checksum = 0;
    uint16_t index = 1; // Skips ':'

    uint8_t count = parseU8((stream + index), &advancement);
    if (advancement == 0)
        return IHEX_STS_ERR;
    index += advancement;
    checksum += count;

    // Parse Addr
    uint16_t addr = parseU8((stream + index), &advancement);
    checksum += addr;
    if (advancement == 0)
        return IHEX_STS_ERR;
    index += advancement;
    addr <<= 8;

    uint8_t thing = parseU8((stream + index), &advancement);
    if (advancement == 0)
        return IHEX_STS_ERR;
    index += advancement;

    checksum += thing;
    addr |= thing;
    *baseAddr = addr;

// Read Type
    *recordType = parseU8((stream + index), &advancement);
    if (advancement == 0)
        return IHEX_STS_ERR;
    index += advancement;
    checksum += *recordType;

    // Parse Data
    if (*recordType == IHEX_TYPE_DATA && count > 0)
    {
        for (int i = 0; i < count; ++i)
        {
            uint8_t byte = parseU8((stream + index), &advancement);
            if (advancement == 0)
                return IHEX_STS_ERR;
            index += advancement;
            *(buf + ((*filled)++)) = byte;
            checksum += byte;
        }
        uint8_t check = parseU8((stream + index), &advancement);
        if ((uint8_t)(check + checksum) == 0)
            return IHEX_STS_DATA_ACK;
        else
            return IHEX_STS_CHECKSUM;
    }
    else if (*recordType == IHEX_TYPE_EOF)
        return IHEX_STS_EOF_ACK;
    else if (*recordType == IHEX_TYPE_EXT_LADDR)
        return IHEX_STS_ADDR_ACK;
    else
    {
        return IHEX_STS_TYPE;
    }

}
