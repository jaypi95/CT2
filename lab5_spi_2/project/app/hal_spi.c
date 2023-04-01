/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur   -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences) -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Module      : SPI Library
 * --
 * -- $Id: hal_spi.c 4720 2019-03-04 10:11:31Z akdi $
 * ------------------------------------------------------------------
 */

#ifdef MOCKED_SPI_DISPLAY
#include "hal_spi.h"
#include "hal_mocked.h"
void hal_spi_init(void)
{
    hal_mocked_spi_init();
}
uint8_t hal_spi_read_write(uint8_t send_byte)
{
    return hal_mocked_spi_read_write(send_byte);
}
#else  // !MOCKED_SPI_DISPLAY
#include <reg_stm32f4xx.h>
#include "hal_spi.h"

#define BIT_TXE  (uint32_t)0x00000002
#define BIT_RXNE (uint32_t)0x00000001
#define BIT_BSY  (uint32_t)0x00000080

static void set_ss_pin_low(void);
static void set_ss_pin_high(void);
static void wait_10_us(void);

/*
 * according to description in header file
 */
void hal_spi_init(void)
{
    RCC->APB2ENR |= 0x00001000;     // enable SPI clock
    RCC->AHB1ENR |= 0x00000001;     // start clock on GPIO A
    GPIOA->OSPEEDR &= 0xFFFF00FF;     // clear P4 to P7
    GPIOA->OSPEEDR |= 0x0000FF00;     // set P4 to P7 to 100 MHz
    GPIOA->MODER &= 0xFFFF00FF;       // clear mode on P5 to P7
    // P5 to P7, P4 output mode
    GPIOA->MODER |= 0x0000A900;       // Set alternate function mode on
    // P5 to P7, P4 output mode
    GPIOA->AFRL &= 0x0000FFFF;      // clear alternate function
    GPIOA->AFRL |= 0x55550000;      // Set SPI1 alternate function

    SPI1->CR2 = 0x0000;               // set spi to default state
    SPI1->CR1 = 0x0000;               // set spi to default state

    /// STUDENTS: To be programmed


		// BIDIMODE = 0 //apparently has to be 0 because it's sending from MISO to MOSI or smth
		// BIDIOE = 0
		// CRCEN = 0
		// CRCNEXT = 0
		// DFF = 0 //only 8 bit is used
		// RXONLY = 0
		// SSM = 1
		// SSI = 1
		// LSBFIRST = 0 //wild assumption, maybe should be changed if tests are not successful
		// SPE = 0 //change to 1 once all settings are set to activate them
		// BR[2] = 1 //42'000'000 / x <= 200'000 --> x == 210 --> I assume baudrate should be set to 256 which is 111
		// BR[1] = 1
		// BR[0] = 1
		// MSTR = 1 //assumption that this is the master
		// CPOL = 0 //idk should probably be changed if tests fail
		// CPHA = 0 //idk should probably be changed if tests fail
		
		//complete setting = 0000 0011 0011 1100
		SPI1->CR1 = 0x033C;
		
		//activate setting by changing SPE to 1
		SPI1->CR1 |= (1 << 6); //changing bit 6 to one



    /// END: To be programmed
    set_ss_pin_high();
}

/*
 * according to description in header file
 */
uint8_t hal_spi_read_write(uint8_t send_byte)
{
    /// STUDENTS: To be programmed

		set_ss_pin_low();
		
		

    //write byte to data register
    SPI1->DR = send_byte;

    //wait until byte is sent
    while(!(SPI1->SR & BIT_TXE));

    //wait until byte is received
    while(!(SPI1->SR & BIT_RXNE));

    //read byte from data register
    uint8_t received_byte = SPI1->DR;

	
		//wait until SPI is not busy
    while(SPI1->SR & BIT_BSY);
	
    wait_10_us();

    set_ss_pin_high();

    return received_byte;


    /// END: To be programmed
}

/**
 * Set Slave-Select Pin (Port A, Pin 5) low
 *
 * No parameters
 *
 * No returns
 */
static void set_ss_pin_low(void)
{
    GPIOA->BSRR |= 0x0010 << 16;              // Set Port A, Pin 5 low
}

/**
 * Set Slave-Select Pin (Port A, Pin 5) high
 *
 * No parameters
 *
 * No returns
 */
static void set_ss_pin_high(void)
{
    GPIOA->BSRR |= 0x0010;             // Set Port A, Pin 5 high
}

/**
 * Wait for approximately 10us
 *
 * No parameters
 *
 * No returns
 */
static void wait_10_us(void)
{
    uint8_t counter = 0;
    while (counter < 160) {
        counter++;
    }
}
#endif // MOCKED_SPI_DISPLAY
