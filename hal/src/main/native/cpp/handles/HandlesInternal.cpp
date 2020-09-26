/*----------------------------------------------------------------------------*/
/* Copyright (c) 2016-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "hal/handles/HandlesInternal.h"

#include <algorithm>

#include <wpi/SmallVector.h>
#include <wpi/mutex.h>

extern "C" {
HAL_PortHandle rust_create_port_handle(HAL_PortHandle base_handle,
                                       uint8_t channel, uint8_t module);
HAL_PortHandle rust_create_port_handle_for_spi(HAL_PortHandle base_handle,
                                               uint8_t channel);
HAL_Handle rust_create_handle(int16_t index, uint8_t handleType,
                              int16_t version);
}

namespace hal {
static wpi::SmallVector<HandleBase*, 32>* globalHandles = nullptr;
static wpi::mutex globalHandleMutex;
HandleBase::HandleBase() {
  static wpi::SmallVector<HandleBase*, 32> gH;
  std::scoped_lock lock(globalHandleMutex);
  if (!globalHandles) {
    globalHandles = &gH;
  }

  auto index = std::find(globalHandles->begin(), globalHandles->end(), this);
  if (index == globalHandles->end()) {
    globalHandles->push_back(this);
  } else {
    *index = this;
  }
}
HandleBase::~HandleBase() {
  std::scoped_lock lock(globalHandleMutex);
  auto index = std::find(globalHandles->begin(), globalHandles->end(), this);
  if (index != globalHandles->end()) {
    *index = nullptr;
  }
}
void HandleBase::ResetHandles() {
  m_version++;
  if (m_version > 255) {
    m_version = 0;
  }
}
void HandleBase::ResetGlobalHandles() {
  std::unique_lock lock(globalHandleMutex);
  for (auto&& i : *globalHandles) {
    if (i != nullptr) {
      lock.unlock();
      i->ResetHandles();
      lock.lock();
    }
  }
}
HAL_PortHandle createPortHandle(uint8_t channel, uint8_t module) {
  // set last 8 bits, then shift to first 8 bits
  HAL_PortHandle handle = static_cast<HAL_PortHandle>(HAL_HandleEnum::Port);
  handle = handle << 24;
  return rust_create_port_handle(handle, channel, module);
}
HAL_PortHandle createPortHandleForSPI(uint8_t channel) {
  // set last 8 bits, then shift to first 8 bits
  HAL_PortHandle handle = static_cast<HAL_PortHandle>(HAL_HandleEnum::Port);
  handle = handle << 16;
  return rust_create_port_handle_for_spi(handle, channel);
}
HAL_Handle createHandle(int16_t index, HAL_HandleEnum handleType,
                        int16_t version) {
  return rust_create_handle(index, static_cast<uint8_t>(handleType), version);
}
}  // namespace hal
