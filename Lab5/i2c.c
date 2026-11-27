#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "i2c.h"
#include "uart.h"

// Evita perder dados do UART enquanto espera o I2C terminar
static void I2C_Aguarda(uint32_t base)
{
  while (I2CMasterBusy(base))
  {
    UART0_Drena();
  }
}

void I2C0_Init(void)
{
  // Configure I2C0 for pins PB2 and PB3
  SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0) || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));  
  
  //Configuracao da PORTB PIN2 e PIN3 - B.M.
  GPIOPinConfigure(GPIO_PB2_I2C0SCL);
  GPIOPinConfigure(GPIO_PB3_I2C0SDA);
  GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
  GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
  I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
}

void I2C7_Init(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C7);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C7) || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));  

  //Configuracao da PORTD PIN0 e PIN1 - B.M.
  GPIOPinConfigure(GPIO_PD0_I2C7SCL);
  GPIOPinConfigure(GPIO_PD1_I2C7SDA);
  GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
  GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);

  I2CMasterInitExpClk(I2C7_BASE, SysCtlClockGet(), false);
}

void I2C0_sendSingleByte(uint8_t slave_addr, char data)
{
  I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);
  I2CMasterDataPut(I2C0_BASE, data);
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
  I2C_Aguarda(I2C0_BASE);
}

void I2C0_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[])
{
  uint8_t i;

  I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

  I2CMasterDataPut(I2C0_BASE, by[0]);
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
  I2C_Aguarda(I2C0_BASE);

  for (i = 1; i < numOfBytes - 1; i++)
  {
    I2CMasterDataPut(I2C0_BASE, by[i]);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
    I2C_Aguarda(I2C0_BASE);
  }

  I2CMasterDataPut(I2C0_BASE, by[numOfBytes - 1]);
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
  I2C_Aguarda(I2C0_BASE);
}

void I2C7_sendSingleByte(uint8_t slave_addr, char data)
{
  I2CMasterSlaveAddrSet(I2C7_BASE, slave_addr, false);
  I2CMasterDataPut(I2C7_BASE, data);
  I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_SINGLE_SEND);
  I2C_Aguarda(I2C7_BASE);
}

void I2C7_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[])
{
  uint8_t i;

  I2CMasterSlaveAddrSet(I2C7_BASE, slave_addr, false);

  I2CMasterDataPut(I2C7_BASE, by[0]);
  I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_START);
  I2C_Aguarda(I2C7_BASE);

  for (i = 1; i < numOfBytes - 1; i++)
  {
    I2CMasterDataPut(I2C7_BASE, by[i]);
    I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
    I2C_Aguarda(I2C7_BASE);
  }

  I2CMasterDataPut(I2C7_BASE, by[numOfBytes - 1]);
  I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
  I2C_Aguarda(I2C7_BASE);
}
