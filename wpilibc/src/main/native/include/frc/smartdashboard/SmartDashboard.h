// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableValue.h>

#include "frc/smartdashboard/ListenerExecutor.h"
#include "frc/smartdashboard/Sendable.h"
#include "frc/smartdashboard/SendableHelper.h"

namespace frc {

class SmartDashboard : public Sendable, public SendableHelper<SmartDashboard> {
 public:
  static void init();

  /**
   * Determines whether the given key is in this table.
   *
   * @param key the key to search for
   * @return true if the table as a value assigned to the given key
   */
  static bool ContainsKey(wpi::StringRef key);

  /**
   * @param types bitmask of types; 0 is treated as a "don't care".
   * @return keys currently in the table
   */
  static std::vector<std::string> GetKeys(int types = 0);

  /**
   * Makes a key's value persistent through program restarts.
   *
   * @param key the key to make persistent
   */
  static void SetPersistent(wpi::StringRef key);

  /**
   * Stop making a key's value persistent through program restarts.
   * The key cannot be null.
   *
   * @param key the key name
   */
  static void ClearPersistent(wpi::StringRef key);

  /**
   * Returns whether the value is persistent through program restarts.
   * The key cannot be null.
   *
   * @param key the key name
   */
  static bool IsPersistent(wpi::StringRef key);

  /**
   * Sets flags on the specified key in this table. The key can
   * not be null.
   *
   * @param key the key name
   * @param flags the flags to set (bitmask)
   */
  static void SetFlags(wpi::StringRef key, unsigned int flags);

  /**
   * Clears flags on the specified key in this table. The key can
   * not be null.
   *
   * @param key the key name
   * @param flags the flags to clear (bitmask)
   */
  static void ClearFlags(wpi::StringRef key, unsigned int flags);

  /**
   * Returns the flags for the specified key.
   *
   * @param key the key name
   * @return the flags, or 0 if the key is not defined
   */
  static unsigned int GetFlags(wpi::StringRef key);

  /**
   * Deletes the specified key in this table.
   *
   * @param key the key name
   */
  static void Delete(wpi::StringRef key);

  /**
   * Returns an NT Entry mapping to the specified key
   *
   * This is useful if an entry is used often, or is read and then modified.
   *
   * @param key the key
   * @return    the entry for the key
   */
  static nt::NetworkTableEntry GetEntry(wpi::StringRef key);

  /**
   * Maps the specified key to the specified value in this table.
   *
   * The value can be retrieved by calling the get method with a key that is
   * equal to the original key.
   *
   * In order for the value to appear in the dashboard, it must be registered
   * with SendableRegistry.  WPILib components do this automatically.
   *
   * @param keyName the key
   * @param value   the value
   */
  static void PutData(wpi::StringRef key, Sendable* data);

  /**
   * Maps the specified key (where the key is the name of the Sendable)
   * to the specified value in this table.
   *
   * The value can be retrieved by calling the get method with a key that is
   * equal to the original key.
   *
   * In order for the value to appear in the dashboard, it must be registered
   * with SendableRegistry.  WPILib components do this automatically.
   *
   * @param value the value
   */
  static void PutData(Sendable* value);

  /**
   * Returns the value at the specified key.
   *
   * @param keyName the key
   * @return the value
   */
  static Sendable* GetData(wpi::StringRef keyName);

  /**
   * Maps the specified key to the specified value in this table.
   *
   * The value can be retrieved by calling the get method with a key that is
   * equal to the original key.
   *
   * @param keyName the key
   * @param value   the value
   * @return        False if the table key already exists with a different type
   */
  static bool PutBoolean(wpi::StringRef keyName, bool value);

  /**
   * Gets the current value in the table, setting it if it does not exist.
   * @param key the key
   * @param defaultValue the default value to set if key doesn't exist.
   * @returns False if the table key exists with a different type
   */
  static bool SetDefaultBoolean(wpi::StringRef key, bool defaultValue);

  /**
   * Returns the value at the specified key.
   *
   * If the key is not found, returns the default value.
   *
   * @param keyName the key
   * @return the value
   */
  static bool GetBoolean(wpi::StringRef keyName, bool defaultValue);

  /**
   * Maps the specified key to the specified value in this table.
   *
   * The value can be retrieved by calling the get method with a key that is
   * equal to the original key.
   *
   * @param keyName the key
   * @param value   the value
   * @return        False if the table key already exists with a different type
   */
  static bool PutNumber(wpi::StringRef keyName, double value);

  /**
   * Gets the current value in the table, setting it if it does not exist.
   *
   * @param key          The key.
   * @param defaultValue The default value to set if key doesn't exist.
   * @returns False if the table key exists with a different type
   */
  static bool SetDefaultNumber(wpi::StringRef key, double defaultValue);

  /**
   * Returns the value at the specified key.
   *
   * If the key is not found, returns the default value.
   *
   * @param keyName the key
   * @return the value
   */
  static double GetNumber(wpi::StringRef keyName, double defaultValue);

  /**
   * Maps the specified key to the specified value in this table.
   *
   * The value can be retrieved by calling the get method with a key that is
   * equal to the original key.
   *
   * @param keyName the key
   * @param value   the value
   * @return        False if the table key already exists with a different type
   */
  static bool PutString(wpi::StringRef keyName, wpi::StringRef value);

  /**
   * Gets the current value in the table, setting it if it does not exist.
   *
   * @param key the key
   * @param defaultValue the default value to set if key doesn't exist.
   * @returns False if the table key exists with a different type
   */
  static bool SetDefaultString(wpi::StringRef key, wpi::StringRef defaultValue);

  /**
   * Returns the value at the specified key.
   *
   * If the key is not found, returns the default value.
   *
   * @param keyName the key
   * @return the value
   */
  static std::string GetString(wpi::StringRef keyName,
                               wpi::StringRef defaultValue);

  /**
   * Put a boolean array in the table.
   *
   * @param key the key to be assigned to
   * @param value the value that will be assigned
   * @return False if the table key already exists with a different type
   *
   * @note The array must be of int's rather than of bool's because
   *       std::vector<bool> is special-cased in C++. 0 is false, any
   *       non-zero value is true.
   */
  static bool PutBooleanArray(wpi::StringRef key, wpi::ArrayRef<int> value);

  /**
   * Gets the current value in the table, setting it if it does not exist.
   *
   * @param key the key
   * @param defaultValue the default value to set if key doesn't exist.
   * @returns False if the table key exists with a different type
   */
  static bool SetDefaultBooleanArray(wpi::StringRef key,
                                     wpi::ArrayRef<int> defaultValue);

  /**
   * Returns the boolean array the key maps to.
   *
   * If the key does not exist or is of different type, it will return the
   * default value.
   *
   * @param key          The key to look up.
   * @param defaultValue The value to be returned if no value is found.
   * @return the value associated with the given key or the given default value
   *         if there is no value associated with the key
   *
   * @note This makes a copy of the array. If the overhead of this is a concern,
   *       use GetValue() instead.
   *
   * @note The returned array is std::vector<int> instead of std::vector<bool>
   *       because std::vector<bool> is special-cased in C++. 0 is false, any
   *       non-zero value is true.
   */
  static std::vector<int> GetBooleanArray(wpi::StringRef key,
                                          wpi::ArrayRef<int> defaultValue);

  /**
   * Put a number array in the table.
   *
   * @param key   The key to be assigned to.
   * @param value The value that will be assigned.
   * @return False if the table key already exists with a different type
   */
  static bool PutNumberArray(wpi::StringRef key, wpi::ArrayRef<double> value);

  /**
   * Gets the current value in the table, setting it if it does not exist.
   *
   * @param key          The key.
   * @param defaultValue The default value to set if key doesn't exist.
   * @returns False if the table key exists with a different type
   */
  static bool SetDefaultNumberArray(wpi::StringRef key,
                                    wpi::ArrayRef<double> defaultValue);

  /**
   * Returns the number array the key maps to.
   *
   * If the key does not exist or is of different type, it will return the
   * default value.
   *
   * @param key The key to look up.
   * @param defaultValue The value to be returned if no value is found.
   * @return the value associated with the given key or the given default value
   * if there is no value associated with the key
   *
   * @note This makes a copy of the array. If the overhead of this is a concern,
   *       use GetValue() instead.
   */
  static std::vector<double> GetNumberArray(wpi::StringRef key,
                                            wpi::ArrayRef<double> defaultValue);

  /**
   * Put a string array in the table.
   *
   * @param key   The key to be assigned to.
   * @param value The value that will be assigned.
   * @return False if the table key already exists with a different type
   */
  static bool PutStringArray(wpi::StringRef key,
                             wpi::ArrayRef<std::string> value);

  /**
   * Gets the current value in the table, setting it if it does not exist.
   *
   * @param key          The key.
   * @param defaultValue The default value to set if key doesn't exist.
   * @returns False if the table key exists with a different type
   */
  static bool SetDefaultStringArray(wpi::StringRef key,
                                    wpi::ArrayRef<std::string> defaultValue);

  /**
   * Returns the string array the key maps to.
   *
   * If the key does not exist or is of different type, it will return the
   * default value.
   *
   * @param key          The key to look up.
   * @param defaultValue The value to be returned if no value is found.
   * @return the value associated with the given key or the given default value
   * if there is no value associated with the key
   *
   * @note This makes a copy of the array. If the overhead of this is a concern,
   *       use GetValue() instead.
   */
  static std::vector<std::string> GetStringArray(
      wpi::StringRef key, wpi::ArrayRef<std::string> defaultValue);

  /**
   * Put a raw value (byte array) in the table.
   *
   * @param key   The key to be assigned to.
   * @param value The value that will be assigned.
   * @return False if the table key already exists with a different type
   */
  static bool PutRaw(wpi::StringRef key, wpi::StringRef value);

  /**
   * Gets the current value in the table, setting it if it does not exist.
   *
   * @param key          The key.
   * @param defaultValue The default value to set if key doesn't exist.
   * @returns False if the table key exists with a different type
   */
  static bool SetDefaultRaw(wpi::StringRef key, wpi::StringRef defaultValue);

  /**
   * Returns the raw value (byte array) the key maps to.
   *
   * If the key does not exist or is of different type, it will return the
   * default value.
   *
   * @param key          The key to look up.
   * @param defaultValue The value to be returned if no value is found.
   * @return the value associated with the given key or the given default value
   *         if there is no value associated with the key
   *
   * @note This makes a copy of the raw contents. If the overhead of this is a
   *       concern, use GetValue() instead.
   */
  static std::string GetRaw(wpi::StringRef key, wpi::StringRef defaultValue);

  /**
   * Maps the specified key to the specified complex value (such as an array) in
   * this table.
   *
   * The value can be retrieved by calling the RetrieveValue method with a key
   * that is equal to the original key.
   *
   * @param keyName the key
   * @param value   the value
   * @return        False if the table key already exists with a different type
   */
  static bool PutValue(wpi::StringRef keyName,
                       std::shared_ptr<nt::Value> value);

  /**
   * Gets the current value in the table, setting it if it does not exist.
   *
   * @param key the key
   * @param defaultValue The default value to set if key doesn't exist.
   * @returns False if the table key exists with a different type
   */
  static bool SetDefaultValue(wpi::StringRef key,
                              std::shared_ptr<nt::Value> defaultValue);

  /**
   * Retrieves the complex value (such as an array) in this table into the
   * complex data object.
   *
   * @param keyName the key
   * @param value   the object to retrieve the value into
   */
  static std::shared_ptr<nt::Value> GetValue(wpi::StringRef keyName);

  /**
   * Posts a task from a listener to the ListenerExecutor, so that it can be run
   * synchronously from the main loop on the next call to {@link
   * SmartDashboard#updateValues()}.
   *
   * @param task The task to run synchronously from the main thread.
   */
  static void PostListenerTask(std::function<void()> task);

  /**
   * Puts all sendable data to the dashboard.
   */
  static void UpdateValues();

 private:
  ~SmartDashboard() override = default;

  static detail::ListenerExecutor listenerExecutor;
};

}  // namespace frc
