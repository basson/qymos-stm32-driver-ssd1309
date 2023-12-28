# qymdrv-stm32-ssd1309

QymDrv STM32 SSD1309 display driver

#### Example

```cpp
// Display buffer structure
typedef struct
{
    uint8_t *data;   ///< byte array buffer
    uint16_t size;   ///< size array buffer
    uint16_t width;  ///< width pixels buffer
    uint16_t height; ///< height pixels buffer
} DisplayBuffer;

uint8_t buffer[1024] = {0x00,};

DisplayBuffer displayBuffer;

displayBuffer.data = buffer;
displayBuffer.size = 1024;
displayBuffer.width = 128;
displayBuffer.height = 64;

qymos::driver::Ssd1309 driver;

// Set HAL i2c handle struct
driver.SetPort(&hi2c2);
// Set i2c display address
driver.SetAddress(0x78);

driver.SetResetPin(DSP_RESET_GPIO_Port, DSP_RESET_Pin);
driver.Initialize();

// Send buffer to display
driver.SendFrame(&displayBuffer, 0, 0);

```
