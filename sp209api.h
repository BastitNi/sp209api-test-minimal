
#pragma once

#include <cstddef>
#include "sp209api_types.h"


#ifdef __cplusplus
extern "C"
{
#endif

    // library instance management

    /**
     * @brief sp209api_create_new_handle This functions creates a new handle that can be
     * later used to call the functions of this API.
     * @return the newly created handle.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_create_new_handle(sp209api_handle *h, sp209api_device_model_t model);

    /**
     * @brief sp209api_free is used to clear a handle (freeing all the memory used).
     * @param handle
     */
    SCANA_API
    ihwapi_err_code_t sp209api_free(sp209api_handle handle);

    // Device listing functions

    /**
     * @brief sp209api_create_device_list is used to create (or update the list
     * of SP209 devices that can be found on the USB).
     * @param handle
     */
    SCANA_API
    ihwapi_err_code_t sp209api_create_device_list(sp209api_handle handle);

    /**
     * @brief sp209api_free_device_list is used to free the memory used to
     * store the list of current devices.
     * @param handle
     */
    SCANA_API
    ihwapi_err_code_t sp209api_free_device_list(sp209api_handle handle);

    /**
     * @brief sp209api_get_devices_count is used to get the list of device
     * that was created using the sp209api_create_device_list function.
     * @param handle
     * @return the number of devices
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_devices_count(sp209api_handle handle, uint16_t *count);

    /**
     * @brief sp209api_get_device_descriptor is used to get the device descriptor
     * for a device on the bus. The funciton sp209api_create_device_list must be called
     * prior to calling this function. The device descriptor is needed to open an SP209
     * device.
     * @param handle
     * @param device_number, 0-based index.
     * @param where device descriptor will be written (no need to be allocated by the user)
     * @return error code
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_device_descriptor(sp209api_handle handle, uint8_t device_number, device_descriptor_t *d);

    // General Device Commands (common to all variants)

    /**
     * @brief sp209api_device_open Open SP209 device using a device descriptor.
     * @param handle
     * @param device: the device descriptor
     * @param variant: the device variant (or operation mode). Some devices ship with custom,
     * application speicifc firmware (like Nexus or TPIU) that are loaded next to the standard (Logic Analyzer)
     * firmware. The variant must be specified when openning a device.
     * @return error code, see ihwapi_err_code_t type.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_device_open(sp209api_handle handle, device_descriptor_t device, sp209api_variant_t variant);

    SCANA_API
    ihwapi_err_code_t sp209api_device_open_first(sp209api_handle handle, sp209api_variant_t variant);

    /**
     * @brief sp209api_device_power_off is used to switch off SP209 device (effectively
     * loosing any configuration made to the device).
     * @param handle
     * @return error code, see ihwapi_err_code_t type.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_device_power_off(sp209api_handle handle);

    /**
     * @brief sp209api_get_firmware_version_major returns the major version of the firmware
     * @param handle
     * @return
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_firmware_version_major(sp209api_handle handle, uint8_t *v);

    /**
     * @brief sp209api_get_firmware_version_minor returns the minor version of the firmware
     * @param handle
     * @return
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_firmware_version_minor(sp209api_handle handle, uint8_t *v);

    /**
     * @brief sp209api_get_bootloader_version_major return the major version of the bootloader
     * @param handle
     * @return
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_bootloader_version_major(sp209api_handle handle, uint8_t *v);

    /**
     * @brief sp209api_get_bootloader_version_minor returns the minor version of the bootloader
     * @param handle
     * @return
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_bootloader_version_minor(sp209api_handle handle, uint8_t *v);

    /**
     * @brief sp209api_get_device_open_flag returns TRUE if the device is open (connection is still active)
     * @param handle
     * @return
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_device_open_flag(sp209api_handle handle, bool* f);

    /**
     * @brief sp209api_launch_fw_update is used to launch a firmware update
     * @param handle
     * @param fw_data a pointer to the an array containing the firmware (loaded from *.bin file)
     * @param fw_size the size of the array (number of bytes).
     * @return error code, see ihwapi_err_code_t type.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_launch_fw_update(sp209api_handle handle, uint8_t *fw_data, size_t fw_size, sp209api_variant_t variant);

    /**
     * @brief sp209api_request_abort request any pending operation to abort.
     * This function returns without verifying if the operation was effectiely aborted
     * @param handle
     */
    SCANA_API
    ihwapi_err_code_t sp209api_request_abort(sp209api_handle handle);


    /**
     * @brief sp209api_launch_new_capture is used to start a new capture of samples.
     * @param handle
     * @param settings the SP209 device settings to be used for this capture
     * @return error code.
     * @details This function does not offer any trigger options, capture will start as soon as possible
     * after this function is called.
     * @see sp209api_launch_new_capture_complex_trigger
     */
    SCANA_API
    ihwapi_err_code_t sp209api_launch_new_capture_simple_trigger(sp209api_handle handle,
                                                                 sp209api_trigger_description_t trig,
                                                                 sp209api_settings_t settings);

    /**
     * @brief sp209api_get_config_done_flag is used to check if the device have finished its internal
     * configuration after a request to launch a new capture.
     * @details There is no any obligation to use this function, as the configuration of the device
     * usually takes a few milliseconds. This function is mainly here for feedback and monitoring purposes.
     * @param handle
     * @param f pointer to bool type varaible to hold the result
     * @return TRUE if configuration is done, FALSE if configuration is still in progress.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_config_done_flag(sp209api_handle handle, bool *f);


    /**
     * @brief Gets the device have triggered flag
     * 
     * @param handle 
     * @param f pointer to bool type varaible to hold the result which will be true if 
     * the device has triggered
     * @return error code.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_triggered_flag(sp209api_handle handle, bool *f);

    /**
     * @brief Gets the trigger position expressed in samples.
     * 
     * @param handle 
     * @param trig_pos Pointer to uint64_t variable where the result will be stored
     * @return error code.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_trigger_position(sp209api_handle handle, uint64_t *trig_pos);

    /**
     * @brief Gets the samples that have been read from device, that are buffered
     * and are ready for readout.
     * 
     * @param handle 
     * @param total_available_samples Pointer to int64_t to hold the total number of available samples
     * @param post_trig_samples Pointer to int64_t to hold the number of samples after the trigger condition
     * @return error code.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_available_samples(sp209api_handle handle, int64_t *total_available_samples, int64_t *post_trig_samples);

    /**
     * @brief Resets the transitions iterator for the channel with index `channel_index`
     * After calling this function, the next call to trs_get_next() will get the very first transition
     * 
     * @param handle 
     * @param channel_index 
     * @return error code.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_trs_reset(sp209api_handle handle, uint8_t channel_index);

    /**
     * @brief Resets the transitions iterator for the channel with index `channel_index` and 
     * make it point right before `target_sample`.
     * After calling this function, the next call to trs_get_next() will get the very first transition
     * after `target_sample`
     * 
     * @param handle 
     * @param channel_index 
     * @param target_sample 
     * @return error code.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_trs_before(sp209api_handle handle, uint8_t channel_index, uint64_t target_sample);

    /**
     * @brief Advances the transition iterator for `channel_index` to the next transition and writes the details of that
     * last transition in `transition_data`. Prior to calling this function, user must either call trs_reset() or 
     * trs_before().
     * 
     * @param handle 
     * @param channel_index 
     * @param transition_data Pointer to structure of type sp209api_trs_t to hold the transition description
     * @return error code.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_trs_get_next(sp209api_handle handle, uint8_t channel_index, sp209api_trs_t *transition_data);
    
    /**
     * @brief Same as trs_get_before() except that the transition iterator rewinds to the previous transition.
     * 
     * @param handle 
     * @param channel_index 
     * @param transition_data 
     * @return error code.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_trs_get_previous(sp209api_handle handle, uint8_t channel_index, sp209api_trs_t *transition_data);
    
    /**
     * @brief This functions determines if the transition pointed be the iterator for the channel `channel_index`
     * is pointing at the last transition.
     * 
     * @param handle 
     * @param channel_index 
     * @param is_not_last_trs Pointer to a bool variable that is writte;n to True if current transition is 
     * not that last one, and further calls to trs_get_next() are valid.
     * @return error code.
     */
    SCANA_API
    ihwapi_err_code_t sp209api_trs_is_not_last(sp209api_handle handle, uint8_t channel_index, bool *is_not_last_trs);

    /**
     * @brief This function is used to determin if the current capture is done and all data have been retrieved 
     * from the device. This function 
     * @note In case of an error or aborted capture, the flag will always return false.
     * 
     * @param handle 
     * @param f Pointer to bool variable to hold the state of the `capture done` flag.
     * @return SCANA_API 
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_capture_done_flag(sp209api_handle handle, bool *f);

    /**
     * @brief This function is used to check if the device is ready or if an operation is in
     * progress.
     * 
     * @param handle 
     * @param f pointer to bool type variable to hold the state of the `ready` flag
     * @return SCANA_API 
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_ready_flag(sp209api_handle handle, bool *f);

    /**
     * @brief Calling this function returns the last error that may have been thrown 
     * by API internal threads. it's wise to use this in case of unxpected behavior
     * or abnormal response times (e.g. config_done flag never equals true)
     * 
     * @param handle 
     * @return SCANA_API 
     */
    SCANA_API
    ihwapi_err_code_t sp209api_get_last_error(sp209api_handle handle);

#ifdef __cplusplus
}
#endif
