#pragma once

#include "mpark/variant.hpp"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

using GroupDevice = std::map<std::string, std::string>;
using SubscribeTopic = std::string; // use GetTopic to identify in std::map faster
template<class GroupDeviceType>
using GroupDevices = std::vector<std::pair<SubscribeTopic, GroupDeviceType>>;
namespace mqtt { struct MQTTSwitchGroup; struct MQTTGroup; struct MQTTSensorGroup; }
using MQTTSwitchGroupPtr = std::shared_ptr<mqtt::MQTTSwitchGroup>;
using MQTTSensorGroupPtr = std::shared_ptr<mqtt::MQTTSensorGroup>;
using MQTTGroupBasePtr = std::shared_ptr<mqtt::MQTTGroup>;
using MQTTVariants = mpark::variant<MQTTSwitchGroupPtr, MQTTSensorGroupPtr, MQTTGroupBasePtr>;
using MQTTGroupsPtr = std::shared_ptr<std::vector<MQTTSwitchGroupPtr>>;

namespace mqtt
{
  struct MQTTSwitchDevice
  {
    std::string name;
    std::string getTopic;
    std::string setTopic;

    std::string onValue;
    std::string offValue;

    uint16_t deviceId = 0;
    bool active = false;
    std::function<void()> mSetNeedsUpdateCB;
  };

  struct MQTTGroup
  {
    std::string sceneName;
    std::string sceneType;
    std::string iconName;

    uint16_t groupId;
    std::function<void()> mSetNeedsUpdateCB;
  };

  struct MQTTSwitchGroup : public MQTTGroup
  {
    bool active = false;
    bool isActive()
    {
      for (auto& device : mDevices)
      {
        if (device.second.active == false)
        {
          return false;
        }
      }
      return true;
    }

    GroupDevices<MQTTSwitchDevice> mDevices;
  };
} // namespce mqtt
