#include "../include/ssd1309.hpp"

namespace qymos
{
    namespace driver
    {

        void Ssd1309::SetPort(I2C_HandleTypeDef *i2cPort)
        {
            _i2cPort = i2cPort;
        }
        void Ssd1309::SetResetPin(GPIO_TypeDef *port, uint16_t pin)
        {
            _resetPort = port;
            _resetPin = pin;
        }
        void Ssd1309::SetAddress(uint8_t address)
        {
            _address = address;
        }

        bool Ssd1309::Initialize()
        {
            Reset();
            HAL_Delay(100);
            SendCommand(SSD1309_DISPLAY_OFF); //	Выключаем дисплей.
            SendCommand(SSD1309_SET_DISPLAY_CLOCK);
            SendCommand(0x80);
            SendCommand(SSD1309_SET_MULTIPLEX_RATIO);
            SendCommand(0x3F);
            SendCommand(SSD1309_SET_DISPLAY_OFFSET);
            SendCommand(0x00);
            SendCommand(SSD1309_SET_START_LINE | 0);
            SendCommand(SSD1309_CHARGE_DCDC_PUMP);
            SendCommand(0x14);
            SendCommand(SSD1309_ADDR_MODE);
            SendCommand(0x00);
            SendCommand(SSD1309_SET_REMAP_L_TO_R);
            SendCommand(SSD1309_SET_REMAP_T_TO_D);
            SendCommand(SSD1309_SET_COM_PINS);
            SendCommand(0x12);
            SendCommand(SSD1309_SET_CONTRAST);
            SendCommand(0xCF); //	Устанавливаем контрастность в значение 0xCF
            SendCommand(SSD1309_SET_PRECHARGE_PERIOD);
            SendCommand(0xF1);
            SendCommand(SSD1309_SET_VCOM_DESELECT);
            SendCommand(0x30);               //	Устанавливаем питание светодиодов VcomH в значение выше чем по
                                             // умолчанию (0x30), что увеличит яркость дисплея (допустимые
                                             // значения: 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70).
            SendCommand(SSD1309_RAM_ON);     //	Разрешаем отображать содержимое RAM памяти.
            SendCommand(SSD1309_INVERT_OFF); //	Отключаем инверсию.
            SendCommand(SSD1309_DISPLAY_ON); //	Включаем дисплей.
            Clear();

            return true;
        }
        bool Ssd1309::DeInitialize()
        {
            return true;
        }
        void Ssd1309::Clear(bool color)
        {
            uint8_t i[128];
            for (uint8_t j = 0; j < 128; j++)
            {
                i[j] = color ? 0xFF : 0x00;
            }
            for (uint8_t j = 0; j < 8; j++)
            {
                SendCommand(SSD1309_ADDR_PAGE);
                SendCommand(j);
                SendCommand(j);
                SendCommand(SSD1309_ADDR_COLUMN);
                SendCommand(0);
                SendCommand(127);
                HAL_I2C_Mem_Write(_i2cPort, _address, (0 << SSD1309_SHIFT_CO) | (1 << SSD1309_SHIFT_DC), 1, i, 128, 100);
                // SendData(i, 128);
            }
        }
        void Ssd1309::Invert(bool color)
        {
            if (color)
                SendCommand(SSD1309_INVERT_ON);
            else
                SendCommand(SSD1309_INVERT_OFF);
        }
        bool Ssd1309::SendCommand(uint8_t command, uint16_t delayUs)
        {
            if (HAL_I2C_Mem_Write(_i2cPort, _address, (0 << SSD1309_SHIFT_CO) | (0 << SSD1309_SHIFT_DC), 1, &command, 1, 100) == HAL_OK)
                return true;
            return false;
        }

        bool Ssd1309::SendFrame(qymos::gui::DisplayBuffer *buffer, uint16_t x, uint16_t y)
        {
            // for (uint8_t i = 0; i < 8; i++)
            // {
            //     SendCommand(SSD1309_ADDR_PAGE);
            //     SendCommand(i);
            //     SendCommand(i);
            //     SendCommand(SSD1309_ADDR_COLUMN);
            //     SendCommand(0);
            //     SendCommand(127);
            //     if (HAL_I2C_Mem_Write(_i2cPort, _address, (0 << SSD1309_SHIFT_CO) | (1 << SSD1309_SHIFT_DC), 1, &buffer.data[i*128], 128, 100) != HAL_OK)
            //         return false;
            // }
            SendCommand(SSD1309_ADDR_PAGE);
            SendCommand(0);
            SendCommand(7);
            SendCommand(SSD1309_ADDR_COLUMN);
            SendCommand(0);
            SendCommand(127);
            if (HAL_I2C_Mem_Write(_i2cPort, _address, (0 << SSD1309_SHIFT_CO) | (1 << SSD1309_SHIFT_DC), 1, buffer->data, buffer->size, 100) != HAL_OK)
                return false;
            memset(buffer->data, 0, buffer->size);
            return true;
        }
        bool Ssd1309::Reset()
        {
            HAL_Delay(10);
            HAL_GPIO_WritePin(_resetPort, _resetPin, GPIO_PIN_RESET);
            HAL_Delay(10);
            HAL_GPIO_WritePin(_resetPort, _resetPin, GPIO_PIN_SET);
            return true;
        }
        bool Ssd1309::Check()
        {
            return true;
        }

    } // namespace driver

} // namespace qymos
