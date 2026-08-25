#include "TrumaCpPlusBinarySensor.h"
#include "esphome/core/log.h"
#include "esphome/components/truma_inetbox/helpers.h"

namespace esphome {
namespace truma_inetbox {

static const char *const TAG = "truma_inetbox.cpplus_binary_sensor";

void TrumaCpPlusBinarySensor::update() {
  if (this->parent_->get_lin_bus_fault() || (this->parent_->get_last_cp_plus_request() == 0)) {
    this->publish_state(false);
    return;
  }
  const uint32_t now = micros();
    const uint32_t last_request = static_cast<uint32_t>(this->parent_->get_last_cp_plus_request());
    const uint32_t elapsed = now - last_request;  // overflow-safe: wraps correctly across the ~71min micros() rollover
    this->publish_state(elapsed < (90u * 1000u * 1000u) /* 90 seconds*/);
}

void TrumaCpPlusBinarySensor::dump_config() { LOG_BINARY_SENSOR("", "Truma CP Plus Binary Sensor", this); }
}  // namespace truma_inetbox
}  // namespace esphome
