#pragma once

#include "stdint.h"
#include "string.h"

#include "stm32f1xx_hal.h"

#include "gui/types.hpp"
#include "gui/idriver.hpp"

namespace qymos
{
    namespace driver
    {
        /**
         * @brief SSd1309 Commands
         *
         */
        enum Ssd1309Commands
        {
            SSD1309_ADDRESS = 0x3C,
            SSD1309_SET_CONTRAST = 0x81,
            SSD1309_RAM_ON = 0xA4,
            SSD1309_RAM_OFF = 0xA5,
            SSD1309_INVERT_OFF = 0xA6,
            SSD1309_INVERT_ON = 0xA7,
            SSD1309_DISPLAY_OFF = 0xAE,
            SSD1309_DISPLAY_ON = 0xAF,
            SSD1309_NOP = 0xE3,
            //			Команды прокрутки:
            SSD1309_SCROLL_HORIZONTAL_RIGHT = 0x26,
            SSD1309_SCROLL_HORIZONTAL_LEFT = 0x27,
            SSD1309_SCROLL_DIAGONAL_RIGHT = 0x29,
            SSD1309_SCROLL_DIAGONAL_LEFT = 0x2A,
            SSD1309_SCROLL_OFF = 0x2E,
            SSD1309_SCROLL_ON = 0x2F,
            SSD1309_SCROLL_VERTICAL = 0xA3,
            //			Команды адресации:
            SSD1309_ADDR_COLUMN_LBS = 0x00,
            SSD1309_ADDR_COLUMN_MBS = 0x10,
            SSD1309_ADDR_MODE = 0x20,
            SSD1309_ADDR_COLUMN = 0x21,
            SSD1309_ADDR_PAGE = 0x22,
            SSD1309_ADDR_ONE_PAGE = 0xB0,
            //			Команды аппаратной настройки:
            SSD1309_SET_START_LINE = 0x40,
            SSD1309_SET_REMAP_R_TO_L = 0xA0,
            SSD1309_SET_REMAP_L_TO_R = 0xA1,
            SSD1309_SET_MULTIPLEX_RATIO = 0xA8,
            SSD1309_SET_REMAP_D_TO_T = 0xC0,
            SSD1309_SET_REMAP_T_TO_D = 0xC8,
            SSD1309_SET_DISPLAY_OFFSET = 0xD3,
            SSD1309_SET_COM_PINS = 0xDA,
            //			Команды тайминга и схемы управления:
            SSD1309_SET_DISPLAY_CLOCK = 0xD5,
            SSD1309_SET_PRECHARGE_PERIOD = 0xD9,
            SSD1309_SET_VCOM_DESELECT = 0xDB,
            SSD1309_CHARGE_DCDC_PUMP = 0x8D,
            SSD1309_SHIFT_DC = 0x06,
            SSD1309_SHIFT_CO = 0x07,
        };

        class Ssd1309 : public qymos::gui::IDriver
        {
        private:
            uint8_t _address = 0x3C;
            I2C_HandleTypeDef *_i2cPort;
            GPIO_TypeDef *_resetPort;
            uint16_t _resetPin;

        public:
            /**
             * @brief Set the HAL handle i2c struct
             *
             * @param i2cPort HAL handle i2c struct
             */
            void SetPort(I2C_HandleTypeDef *i2cPort);
            /**
             * @brief Set the Reset Pin
             *
             * @param port Reset GPIO Port
             * @param pin Reset GPIO Pin
             */
            void SetResetPin(GPIO_TypeDef *port, uint16_t pin);
            /**
             * @brief Set the i2c Address m24cxx
             *
             * @param address i2c address
             */
            void SetAddress(uint8_t address);
            /**
             * @brief Clear display
             *
             * @param color Color false = black, true = white
             */
            void Clear(bool color = false);
            /**
             * @brief Invert display
             *
             * @param color Color false = black, true = white
             */
            void Invert(bool color);
            /**
             * @brief Initiailize driver
             *
             * @return true Done
             * @return false Error
             */
            bool Initialize();
            /**
             * @brief De initialize driver
             *
             * @return true Done
             * @return false Error
             */
            bool DeInitialize();
            /**
             * @brief Send command to display controller
             *
             * @param command Command
             * @param delayUs Delay time in Us
             * @return true Done
             * @return false Error
             */
            bool SendCommand(uint8_t command, uint16_t delayUs = 0);
            /**
             * @brief Send data to display controller
             *
             * @param buffer Data array
             * @param x Coord X
             * @param y Coord Y
             * @return true Done
             * @return false Error
             */
            bool SendFrame(qymos::gui::DisplayBuffer *buffer, uint16_t x = 0, uint16_t y = 0);
            /**
             * @brief Reset display
             *
             * @return true Done
             * @return false Error
             */
            bool Reset();
            /**
             * @brief Check display availability
             *
             * @return true Available
             * @return false Error
             */
            bool Check();
        };

    } // namespace driver

} // namespace qymos
