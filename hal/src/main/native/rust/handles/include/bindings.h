#pragma once

#include <stdint.h>

#if __cplusplus
extern "C" {
#endif
// HAL_Handle = int32_t
// HAL_PortHandle = HAL_Handle

int32_t rust_create_port_handle(int32_t base_handle, uint8_t channel,
                                uint8_t module);
int32_t rust_create_port_handle_for_spi(int32_t base_handle, uint8_t channel);
int32_t rust_create_handle(int16_t index, uint8_t handleType, int16_t version);

#if __cplusplus
}
#endif