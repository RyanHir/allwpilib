// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <cameraserver/CameraServer.h>
#include <frc/TimedRobot.h>
#include <wpi/raw_ostream.h>

/**
 * Uses the CameraServer class to automatically capture video from a USB webcam
 * and send it to the FRC dashboard without doing any vision processing. This is
 * the easiest way to get camera images to the dashboard. Just add this to the
 * RobotInit() method in your program.
 */
class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override {
#if defined(__linux__)
    frc::CameraServer::GetInstance()->StartAutomaticCapture();
#else
    wpi::errs() << "Vision only available on Linux.\n";
    wpi::errs().flush();
#endif
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
