

#include <ph_Status.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PHBAL_REG_R_PI_SPI
#include "phbalReg_R_Pi_spi.h"

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


/*
 * piBoardRev:
 *	Return a number representing the hardware revision of the board.
 *	Revision is currently 1 or 2. -1 is returned on error.
 *
 *	Much confusion here )-:
 *	Seems there ar esome boards with 0000 in them (mistake in manufacture)
 *	and some board with 0005 in them (another mistake in manufacture).
 *	So the distinction between boards that I can see is:
 *	0000 - Error
 *	0001 - Not used
 *	0002 - Rev 1
 *	0003 - Rev 1
 *	0004 - Rev 2
 *	0005 - Rev 2
 *	0006 - Rev 2
 *	000f - Rev 2 + 512MB
 *
 *	A small thorn is the olde style overvolting - that will add in
 *		1000000
 *
 *this function was taken from https://github.com/WiringPi/WiringPi
 *********************************************************************************
 */

static int piBoardRev (void)
{
  FILE *cpuFd ;
  char line [120] ;
  char *c, lastChar ;
  static int  boardRev = -1 ;

// No point checking twice...

  if (boardRev != -1)
    return boardRev ;

  if ((cpuFd = fopen ("/proc/cpuinfo", "r")) == NULL)
    return -1 ;

  while (fgets (line, 120, cpuFd) != NULL)
    if (strncmp (line, "Revision", 8) == 0)
      break ;

  fclose (cpuFd) ;

  if (line == NULL)
  {
    errno = 0 ;
    return -1 ;
  }

  for (c = line ; *c ; ++c)
    if (isdigit (*c))
      break ;

  if (!isdigit (*c))
  {
    errno = 0 ;
    return -1 ;
  }

  lastChar = c [strlen (c) - 2] ;

  if ((lastChar == '2') || (lastChar == '3'))
    boardRev = 1 ;
  else
    boardRev = 2 ;

//  printf ("piboardRev: Revision string: %s, board revision: %d\n", c, boardRev) ;

  return boardRev ;
}

phStatus_t phbalReg_R_Pi_spi_Init(
                              phbalReg_R_Pi_spi_DataParams_t * pDataParams, /**< [In] Pointer to this layer's parameter structure. */
                              uint16_t wSizeOfDataParams                /**< [In] Specifies the size of the data parameter structure. */
                              )
{
    int ifsel_fd;
    uint8_t data[5];
    int boardRev;

    if (sizeof(phbalReg_R_Pi_spi_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
    }
	PH_ASSERT_NULL (pDataParams);

    pDataParams->wId = PH_COMP_BAL | PHBAL_REG_R_PI_SPI_ID;


    boardRev = piBoardRev();

    ifsel_fd = open("/sys/class/gpio/export",O_WRONLY);
    if (ifsel_fd == 0)
    	return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);

    if (boardRev == 1)
    {
    	sprintf(data,"0");	/* */
    }
    else
    {
    	sprintf(data,"2");	/* */
    }
    write(ifsel_fd,data,1);
    close(ifsel_fd);

    if (boardRev == 1)
    {
    	ifsel_fd = open("/sys/class/gpio/gpio0/direction",O_WRONLY);
    }
    else
    {
    	ifsel_fd = open("/sys/class/gpio/gpio2/direction",O_WRONLY);
    }
    if (ifsel_fd == 0)
    	return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
    sprintf(data,"in");
    write(ifsel_fd,data,3);
    close(ifsel_fd);


#ifdef NXPBUILD__PHHAL_HW_RC663
    ifsel_fd = open("/sys/class/gpio/export",O_WRONLY);
    if (ifsel_fd == 0)
    	return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
    if (boardRev == 1)
    {
    	sprintf(data,"21");	/* IFSEL0 */
    }
    else
    {
    	sprintf(data,"27");	/* IFSEL0 */
    }
    write(ifsel_fd,data,2);
    sprintf(data,"22");	/* IFSEL1 */
    write(ifsel_fd,data,2);

    sprintf(data,"7");	/* 512_NRSTPD */
    write(ifsel_fd,data,1);

    sprintf(data,"24");	/* 663_PDOWN */
    write(ifsel_fd,data,2);
    close(ifsel_fd);

    /* IFSEL0 - output */
    if (boardRev == 1)
    {
    	ifsel_fd = open("/sys/class/gpio/gpio21/direction",O_WRONLY);
    }
    else
    {
    	ifsel_fd = open("/sys/class/gpio/gpio27/direction",O_WRONLY);
    }
    if (ifsel_fd == 0)
    	return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
    sprintf(data,"out");
    write(ifsel_fd,data,3);
    close(ifsel_fd);

    /* IFSEL1 - output */
	ifsel_fd = open("/sys/class/gpio/gpio22/direction",O_WRONLY);
	if (ifsel_fd == 0)
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	sprintf(data,"out");
	write(ifsel_fd,data,3);
	close(ifsel_fd);

    /* 512_NRSTPD - output */
	ifsel_fd = open("/sys/class/gpio/gpio7/direction",O_WRONLY);
	if (ifsel_fd == 0)
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	sprintf(data,"out");
	write(ifsel_fd,data,3);
	close(ifsel_fd);

    /* 663_PDOWN - output */
	ifsel_fd = open("/sys/class/gpio/gpio24/direction",O_WRONLY);
	if (ifsel_fd == 0)
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	sprintf(data,"out");
	write(ifsel_fd,data,3);
	close(ifsel_fd);

    /* IFSEL0 - 0 */
	if (boardRev == 1)
	{
		ifsel_fd = open("/sys/class/gpio/gpio21/value",O_WRONLY);
	}
	else
	{
		ifsel_fd = open("/sys/class/gpio/gpio27/value",O_WRONLY);
	}
    if (ifsel_fd == 0)
    	return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
    sprintf(data,"0");
    write(ifsel_fd,data,1);
    close(ifsel_fd);

    /* IFSEL0 - 1 */
	ifsel_fd = open("/sys/class/gpio/gpio22/value",O_WRONLY);
	if (ifsel_fd == 0)
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	sprintf(data,"1");
	write(ifsel_fd,data,1);
	close(ifsel_fd);

	/* 512_NRSTPD - 1 */
	ifsel_fd = open("/sys/class/gpio/gpio7/value",O_WRONLY);
	if (ifsel_fd == 0)
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	sprintf(data,"1");
	write(ifsel_fd,data,1);
	close(ifsel_fd);

	/* 663_PDOWN - 0 */
	ifsel_fd = open("/sys/class/gpio/gpio24/value",O_WRONLY);
	if (ifsel_fd == 0)
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	sprintf(data,"0");
	write(ifsel_fd,data,1);
	close(ifsel_fd);

#endif /* NXPBUILD__PHHAL_HW_RC663 */

    pDataParams->spiMode	= 0 ;
    pDataParams->spiBPW		= 8 ;
    pDataParams->spiDelay	= 0;
    pDataParams->spiSpeed	= 2000000;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);

}

phStatus_t phbalReg_R_Pi_spi_GetPortList(
	phbalReg_R_Pi_spi_DataParams_t * pDataParams,
    uint16_t wPortBufSize,
    uint8_t * pPortNames,
    uint16_t * pNumOfPorts
    )
{

    wPortBufSize = 0;
    pPortNames = NULL;
    *pNumOfPorts = 0;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);

}

phStatus_t phbalReg_R_Pi_spi_SetPort(
							phbalReg_R_Pi_spi_DataParams_t * pDataParams,
                            uint8_t * pPortName
                            )
{

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);

}

phStatus_t phbalReg_R_Pi_spi_OpenPort(
								phbalReg_R_Pi_spi_DataParams_t * pDataParams
                                  )
{
	pDataParams->spiFD = open ("/dev/spidev0.0", O_RDWR);
	if (pDataParams->spiFD == 0)
	{
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	}

	if (ioctl (pDataParams->spiFD, SPI_IOC_WR_MODE, &pDataParams->spiMode)         < 0)
	{
		close(pDataParams->spiFD);
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	}
	if (ioctl (pDataParams->spiFD, SPI_IOC_WR_BITS_PER_WORD, &pDataParams->spiBPW) < 0)
	{
		close(pDataParams->spiFD);
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	}
	if (ioctl (pDataParams->spiFD, SPI_IOC_WR_MAX_SPEED_HZ, &pDataParams->spiSpeed)   < 0)
	{
		close(pDataParams->spiFD);
		return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
	}

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);

}

phStatus_t phbalReg_R_Pi_spi_ClosePort(
								phbalReg_R_Pi_spi_DataParams_t * pDataParams
                                   )
{
	close(pDataParams->spiFD);

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);

}

phStatus_t phbalReg_R_Pi_spi_Exchange(
								phbalReg_R_Pi_spi_DataParams_t * pDataParams,
                                uint16_t wOption,
                                uint8_t * pTxBuffer,
                                uint16_t wTxLength,
                                uint16_t wRxBufSize,
                                uint8_t * pRxBuffer,
                                uint16_t * pRxLength
                                  )
{
	  struct spi_ioc_transfer spi ;


	  spi.tx_buf        = (unsigned long)pTxBuffer ;
	  spi.rx_buf        = (unsigned long)pTxBuffer ;
	  spi.len           = wTxLength ;
	  spi.delay_usecs   = pDataParams->spiDelay ;
	  spi.speed_hz      = pDataParams->spiSpeed;
	  spi.bits_per_word = pDataParams->spiBPW ;

	  int i;

	  *pRxLength = ioctl (pDataParams->spiFD, SPI_IOC_MESSAGE(1), &spi) ;
	  if (*pRxLength <= 0 )
	  {
		  printf("read write error\n");
		  return PH_ADD_COMPCODE(PH_ERR_READ_WRITE_ERROR, PH_COMP_BAL);
	  }

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);

}

phStatus_t phbalReg_R_Pi_spi_SetConfig(
									phbalReg_R_Pi_spi_DataParams_t * pDataParams,
									uint16_t wConfig,
									uint16_t wValue
                                   )
{
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_R_Pi_spi_GetConfig(
									phbalReg_R_Pi_spi_DataParams_t * pDataParams,
									uint16_t wConfig,
									uint16_t * pValue
                                   )
{

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);

}

#endif	/* NXPBUILD__PHBAL_REG_R_PI_SPI */
