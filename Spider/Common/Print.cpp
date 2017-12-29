#include <iostream>
#include "AData.hpp"
#include "Header.hpp"
#include "LogInput.hpp"
#include "Command.hpp"
#include "LogMouse.hpp"

void spider::Header::print()
{
  std::cout << "[HEADER]" << " Magic number: " << magicNumber_ << "\n"
            << "Packet size: " << dataSize_ << " of type: " << type_ << "\n"
            << std::endl;
}

void spider::AData::print()
{
  std::cout << "[" << getTimeStamp() << "] Client Id: " << getId()
            << "Packet type: " << getType() << std::endl;
}

void spider::LogMouse::print()
{
  std::cout << "[" << getTimeStamp() << "] Client Id: " << getId() << "\n"
            << "Packet type: " << getType() << "\n"
            << "Window name: " << getWindowName() << " of size: ["
            << getWindowSizeX() << ", " << getWindowSizeY() << "] and mouse coordinates: ["
            << getMouseCoordX() << ", " << getMouseCoordY() << "]" << std::endl;
}

void spider::Command::print() {
  std::cout << "[" << getTimeStamp() << "] Client Id: " << getId() << "\n"
            << "Packet type: " << getType() << "\n"
            << "Message :" << getMessage() << std::endl;
}

void spider::LogInput::print()
{
  std::cout << "[" << getTimeStamp() << "] Client Id: " << getId() << "\n"
            << "Packet type: " << getType() << "\n"
            << "Window name: " << getWindowName() << " keyboard input: '" << getInput() << "'"
            << std::endl;
}