#ifndef PHBALREG_R_PI_SPI_H_
#define PHBALREG_R_PI_SPI_H_
#include <ph_Status.h>

phStatus_t phbalReg_R_Pi_spi_GetPortList(
	phbalReg_R_Pi_spi_DataParams_t * pDataParams,
    uint16_t wPortBufSize,
    uint8_t * pPortNames,
    uint16_t * pNumOfPorts
    );

phStatus_t phbalReg_R_Pi_spi_SetPort(
							phbalReg_R_Pi_spi_DataParams_t * pDataParams,
                            uint8_t * pPortName
                            );

phStatus_t phbalReg_R_Pi_spi_OpenPort(
								phbalReg_R_Pi_spi_DataParams_t * pDataParams
                                  );

phStatus_t phbalReg_R_Pi_spi_ClosePort(
								phbalReg_R_Pi_spi_DataParams_t * pDataParams
                                   );

phStatus_t phbalReg_R_Pi_spi_Exchange(
								phbalReg_R_Pi_spi_DataParams_t * pDataParams,
                                uint16_t wOption,
                                uint8_t * pTxBuffer,
                                uint16_t wTxLength,
                                uint16_t wRxBufSize,
                                uint8_t * pRxBuffer,
                                uint16_t * pRxLength
                                  );

phStatus_t phbalReg_R_Pi_spi_SetConfig(
									phbalReg_R_Pi_spi_DataParams_t * pDataParams,
									uint16_t wConfig,
									uint16_t wValue
                                   );

phStatus_t phbalReg_R_Pi_spi_GetConfig(
									phbalReg_R_Pi_spi_DataParams_t * pDataParams,
									uint16_t wConfig,
									uint16_t * pValue
                                   );

#endif /* PHBALREG_R_PI_SPI_H_ */
