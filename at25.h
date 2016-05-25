#ifndef AT52_H_
#define AT25_H_

#include "at25_conf.h"

//! WRITE ENABLE (WREN) command
#define AT25CMD_WRITE_ENABLE   0x6
//! WRITE DISABLE (WRDI) command
#define AT25CMD_WRITE_DISABLE  0x4
//! READ STATUS REGISTER (RDSR) command
#define AT25CMD_STATUS_READ    0x5
//! WRITE STATUS REGISTER (WRSR) command
#define AT25CMD_STATUS_WRITE   0x1
//! Read Data from Memory Array
#define AT25CMD_READ            0x3
//! Write Data to Memory Array
#define AT25CMD_WRITE           0x2
/*! Bit 0 = 0 (RDY) indicates the device is READY. Bit 0 = 1 indicates the write cycle is 
in progress.*/
#define AT25_STATUS_RDY_BIT      (1<<0)
/*!Bit 1= 0 indicates the device is not WRITE ENABLED. Bit 1 = 1 indicates the 
device is WRITE ENABLED.*/
#define AT25_STATUS_WEN_BIT      (1<<1)
/*!Block protection bit 0 
  see http://www.atmel.com/Images/doc0675.pdf page 9*/
#define AT25_STATUS_BP0_BIT      (1<<2)
/*!Block protection bit 1
  see http://www.atmel.com/Images/doc0675.pdf page 9*/
#define AT25_STATUS_BP1_BIT      (1<<3)
/*! Write Protect Enable (WPEN) bit.
  Allows the user to enable or disable the write protect (/WP) pin
  Hardware write protection is enabled when the /WP pin is low and the WPEN bit is ?1?.
  Hardware write protection is disabled when either the /WP pin is high or the WPEN bit is ?0?.
  When the device is hardware write protected, writes to the Status Register, including the Block
  Protect bits and the WPEN bit, and the block-protected sections in the memory array are disabled.
  Writes are only allowed to sections of the memory which are not block-protected.*/
#define AT25_STATUS_WPEN_BIT     (1<<7)

/// Returns 1 if the device is ready; otherwise 0. 
/// Status Register: Bit 0 (/RDY): Bit 0 = 0 (/RDY) indicates the device is READY. Bit 0 = 1 indicates the write cycle is in progress.
#define AT25_STATUS_READY(status)       ((status & AT25_STATUS_RDY_BIT)==0)
#define AT25_STATUS_WRITE_EN(status)    (status & AT25_STATUS_WEN_BIT)

typedef enum {
    idAt25080,
    idAt25160,
    idAt25320,
    idAt25640
} At25_id_t;

typedef struct {
    /// Size of EEPROM 
    uint16_t  EepromSize;
    /// The block write protection levels and
    uint16_t  BlockWPaddr[4];
    /// Identifier.
    const char *name;
} At25Desc;

#define AT25_CMD_BUFFER_SZ  8

typedef struct {
  SPIDriver * spidrv;
  SPIConfig * spicfg;
  /// Pointer to the dataflash description.
	const At25Desc *pDesc;
  /// Buffer to store the current command (opcode + dataflash address.
	uint8_t pCmdBuffer[AT25_CMD_BUFFER_SZ];
} At25Driver_t;

extern uint8_t AT25_Configure(At25Driver_t *pAt25, SPIDriver *pSpid, SPIConfig * spicfg, At25_id_t At25id);

extern uint8_t AT25_Write_Enable(At25Driver_t *pAt25);

extern uint8_t AT25_Write_Disable(At25Driver_t *pAt25);

extern uint8_t AT25_StatusWrite(At25Driver_t *pAt25,uint8_t state);

extern uint8_t AT25_StatusRead(At25Driver_t *pAt25);

extern uint16_t AT25_ee_write(At25Driver_t *pAt25,uint16_t address, uint8_t *data, uint16_t datasz);

extern uint16_t AT25_ee_read(At25Driver_t *pAt25,uint16_t address, uint8_t *data, uint16_t datasz);

#endif