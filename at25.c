
#include "ch.h"
#include "hal.h"
#include "at25.h"
#include <string.h>

#define TRACE_LEVEL TRACE_LEVEL_DEBUG

#include "trace.h"

/// Number of dataflash which can be recognized.
#define NUMEEPROM    (sizeof(at25Devices) / sizeof(At25Desc))

static const At25Desc at25Devices[] = {
    {1024, { 0x3ff, 0x300, 0x200,0}, "AT25080"},
    {2048, { 0x7ff, 0x600, 0x400,0}, "AT25160"},
    {4096, { 0xfff, 0xc00, 0x800,0}, "AT25320"},
    {8192, {0x1fff,0x1800,0x1000,0}, "AT25640"},
};


static const SPIConfig At25DefSpiConfig = {
  /**
   * @brief Operation complete callback or @p NULL.
   */
  NULL,
  /**
   * @brief The chip select line port.
   */
  AT25_CS_PORT,
  /**
   * @brief The chip select line pad number.
   */
  AT25_CS_PAD,
  /**
   * @brief SPI initialization data.
   */
  SPI_CR1_BR_2 | SPI_CR1_BR_1
};

/***/
uint8_t AT25_Configure(At25Driver_t *pAt25, SPIDriver *pSpid, SPIConfig * spicfg, At25_id_t At25id) {
  chDbgAssert(pAt25,"AT25_Configure: pAt25 is NULL.\n\r");
//  chDbgAssert(pSpid,"AT25_Configure: pSpid is NULL.\n\r");
  chDbgAssert(At25id < NUMEEPROM,"AT25_Configure: Wrong At25id\n\r");

  memset(pAt25->pCmdBuffer, 0, AT25_CMD_BUFFER_SZ );

  if (pSpid) {
      pAt25->spidrv = pSpid;
  } else {
      pAt25->spidrv = &AT25_SPI_DRIVER;
  }
  pAt25->pDesc = &at25Devices[At25id];
  if (spicfg) {
    pAt25->spicfg = spicfg;
  } else {
    pAt25->spicfg = (SPIConfig *)&At25DefSpiConfig;
  }
  TRACE_DEBUG("%s: EEPROM %s\n\r",__FUNCTION__,pAt25->pDesc->name);
  
  return MSG_OK;
}

uint8_t AT25_SendCommand(
    At25Driver_t *pAt25,
    uint8_t cmd,
    uint8_t cmdSize,
    uint8_t *pData,
    uint16_t dataSize,
    uint16_t address)
{
    const At25Desc *pDesc = pAt25->pDesc;

    // Sanity checks
    chDbgAssert(pAt25, "AT25_SendCommand: pAt25 is 0.\n\r");
    chDbgAssert(pDesc,
           "AT25_SendCommand: Device has no descriptor, only STATUS_READ command allowed\n\r");
    spiAcquireBus(pAt25->spidrv);
    spiStart(pAt25->spidrv,pAt25->spicfg);
    // Compute command pattern
    pAt25->pCmdBuffer[0] = cmd;
    // Add address bytes if necessary
    if (cmdSize > 1) {
        chDbgAssert(pDesc, "AT25_SendCommand: No descriptor for dataflash.\n\r");
        // Write address bytes
        if ( !(address < pDesc->EepromSize) ) {
            TRACE_WARNING("%s: Address %#x exceeds size of EEPROM %s. Will be truncated!\n\r",__FUNCTION__,address,pDesc->name);
        }
        pAt25->pCmdBuffer[1] = ((address & 0x0000FF00) >> 8);
        pAt25->pCmdBuffer[2] = ((address & 0x000000FF) >> 0);
    }
    spiSelect(pAt25->spidrv);
    
    spiSend(pAt25->spidrv,cmdSize,pAt25->pCmdBuffer);
    if ( dataSize && 
         pData ) {
        spiExchange(pAt25->spidrv,dataSize,pData,pData);
    }

    spiUnselect(pAt25->spidrv);
    spiReleaseBus(pAt25->spidrv);
    return MSG_OK;
}

uint8_t AT25_StatusRead(At25Driver_t *pAt25)
{
    uint8_t status=0;
    uint8_t res;
    //Send STATUS REGISTER READ command
    do {
        res = AT25_SendCommand(pAt25,AT25CMD_STATUS_READ,1,&status,1,0);
    } while (res);
    return (uint8_t) status;
}

uint8_t AT25_IsEepromBusy(At25Driver_t *pAt25)
{
    uint8_t status;

    status = AT25_StatusRead(pAt25);
    if ( AT25_STATUS_READY(status) ) 
        return 0;
    else 
        return 1;
}

uint8_t AT25_Write_Enable(At25Driver_t *pAt25)
{
    return AT25_SendCommand(pAt25,AT25CMD_WRITE_ENABLE,1,0,0,0);
}

uint8_t AT25_Write_Disable(At25Driver_t *pAt25)
{
    return AT25_SendCommand(pAt25,AT25CMD_WRITE_DISABLE,1,0,0,0);
}

uint8_t AT25_StatusWrite(At25Driver_t *pAt25,uint8_t state)
{
    uint8_t Buf = state & 0x8C;
    uint8_t status;
    //wait ready
    while (AT25_IsEepromBusy(pAt25)) ;
    //Check is write enabled
    status = AT25_StatusRead(pAt25);
    if (! AT25_STATUS_WRITE_EN(status)) {
        AT25_Write_Enable(pAt25);
        do {
            status = AT25_StatusRead(pAt25);
        } while (! (AT25_STATUS_READY(status) && AT25_STATUS_WRITE_EN(status)) );
    }
    return AT25_SendCommand(pAt25,AT25CMD_STATUS_WRITE,1,&Buf,1,0);
}

uint16_t AT25_ee_write(At25Driver_t *pAt25,uint16_t address, uint8_t *data, uint16_t datasz)
{
    uint8_t pBuf[32];
    uint8_t i; 
	uint16_t k=0;

    /*The AT25080/160/320/640 is capable of a 32-byte PAGE WRITE operation. After each byte of
    data is received, the five low order address bits are internally incremented by one; the high
    order bits of the address will remain constant. If more than 32 bytes of data are transmitted,
    the address counter will roll over and the previously written data will be overwritten. The
    AT25080/160/320/640 is automatically returned to the write disable state at the completion of
    a WRITE cycle. (page 10)*/
    while (datasz) {
        uint8_t status;
        uint8_t n = 32;
        n = (address & ~0x1f ) + 0x20 - address; //вычисляем кол-во байт до следующего кратного 32-м байтам адреса
        for (i=0;(i<n)&&(datasz);i++) {
            //при достижении адреса кратного 32 байтам или достижения i==32 или окончания данных (datasz==0) выходим из цикла.
            pBuf[i]=data[k++];
            datasz--; 
        }
        while (AT25_IsEepromBusy(pAt25)) ;
        AT25_Write_Enable(pAt25);
        //Send STATUS REGISTER READ command
        do {
            status = AT25_StatusRead(pAt25);
        } while (! (AT25_STATUS_READY(status) && AT25_STATUS_WRITE_EN(status)) );
        AT25_SendCommand(pAt25,AT25CMD_WRITE, 3, pBuf, i,address);
        status = AT25_StatusRead(pAt25);
        address += i;
    }
    return k;
}

uint16_t AT25_ee_read(At25Driver_t *pAt25,uint16_t address, uint8_t *data, uint16_t datasz)
{
    uint8_t pBuf[32];
    uint8_t i, k;
    uint16_t	n=0;
    while (datasz) {
        uint8_t status;
        if (datasz<32) {
            i = datasz;
        }
        else  i = 32;
        do {
            status = AT25_StatusRead(pAt25);
        } while (! AT25_STATUS_READY(status));
        AT25_SendCommand(pAt25, AT25CMD_READ,3,pBuf,i,address);
        address += i;
        datasz -= i;
        for (k=0;k<i;k++) {
            data[n++] = (uint8_t)pBuf[k];
        }
    }
    return n;
}

