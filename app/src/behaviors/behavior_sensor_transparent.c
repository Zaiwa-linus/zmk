/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_sensor_transparent

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int on_sensor_binding_accept_data(struct zmk_behavior_binding *binding,
                                         struct zmk_behavior_binding_event event,
                                         const struct zmk_sensor_config *sensor_config,
                                         size_t channel_data_size,
                                         const struct zmk_sensor_channel_data *channel_data) {
    return 0;
}

static int on_sensor_binding_process(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event,
                                     enum behavior_sensor_binding_process_mode mode) {
    // Returning TRANSPARENT (not OPAQUE) leaves the sensor event unconsumed so that
    // zmk_keymap_sensor_event keeps walking down to the next active layer's binding.
    return ZMK_BEHAVIOR_TRANSPARENT;
}

static const struct behavior_driver_api behavior_sensor_transparent_driver_api = {
    .sensor_binding_accept_data = on_sensor_binding_accept_data,
    .sensor_binding_process = on_sensor_binding_process,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .get_parameter_metadata = zmk_behavior_get_empty_param_metadata,
#endif // IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
};

BEHAVIOR_DT_INST_DEFINE(0, NULL, NULL, NULL, NULL, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                        &behavior_sensor_transparent_driver_api);

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
