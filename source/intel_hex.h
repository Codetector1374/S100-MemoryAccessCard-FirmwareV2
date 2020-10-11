#pragma once

#include <stdint.h>
#include <strings.h>

typedef char IHEX_STS;
typedef uint8_t IHEX_TYPE;

#define IHEX_STS_DATA_ACK   'K'
#define IHEX_STS_EOF_ACK    'R'
#define IHEX_STS_ADDR_ACK   'S'
#define IHEX_STS_ERR        'E'
#define IHEX_STS_TYPE       'T'
#define IHEX_STS_CHECKSUM   'X'

#define IHEX_TYPE_DATA          0
#define IHEX_TYPE_EOF           1
#define IHEX_TYPE_EXT_SEG       2
#define IHEX_TYPE_START_SEG     3
#define IHEX_TYPE_EXT_LADDR     4
#define IHEX_TYPE_START_LADDR   5

// NOTE: This iHex parser will simply respond OK to any set addr 0
// and err to set anything non-zero

/**
 * @brief Parses a iHex stream
 *
 * @param(in)   stream
 *      a Pointer to the stream of iHex to be interperted.
 * @param(in)   len
 *      length of the stream.
 * @param(out)  buf
 *      Pointer to the output buffer.
 * @param(out)  filled
 *      Pointer to a u8 that will hold the size filled into the buffer.
 *
 */
IHEX_STS parseiHex
(
    char       *stream,
    size_t      len,
    uint8_t    *buf,
    uint8_t    *filled,
    uint16_t   *baseAddr,
    IHEX_TYPE  *recordType
);
