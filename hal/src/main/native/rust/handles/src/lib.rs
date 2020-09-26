#[allow(non_camel_case_types)]
type HAL_Handle = i32;
#[allow(non_camel_case_types)]
type HAL_PortHandle = HAL_Handle;

const HAL_K_INVALID_HANDLE: HAL_Handle = 0;

#[no_mangle]
pub fn rust_create_port_handle(base_handle: HAL_PortHandle, channel: u8, module: u8) -> HAL_PortHandle{
    let mut handle = base_handle;
    // shift module and add to 3rd set of 8 bits
    let mut temp: i32 = module.into();
    temp = (temp << 8) & 0xff00;
    handle += temp;
    // add channel to last 8 bits
    handle += channel as HAL_PortHandle;
    return handle;
}

#[no_mangle]
pub fn rust_create_port_handle_for_spi(base_handle: HAL_PortHandle, channel: u8) -> HAL_PortHandle {
    let mut handle = base_handle;
    // set second set up bits to 1
    let mut temp: i32 = 1;
    temp = (temp << 8) & 0xff00;
    handle += temp;
    // shift to last set of bits
    handle = handle << 8;
    // add channel to last 8 bits
    handle += channel as HAL_PortHandle;
    return handle;
}

#[no_mangle]
pub fn rust_create_handle(index: i16, handle_type: u8, version: i16) -> HAL_Handle {
    if index < 0 {
        return HAL_K_INVALID_HANDLE;
    }
    if handle_type == 0 || handle_type > 127 {
        return HAL_K_INVALID_HANDLE;
    }
    // set last 8 bits, then shift to first 8 bits
    let mut handle: HAL_Handle = handle_type.into();
    handle = handle << 8;
    handle += version as HAL_Handle;
    handle = handle << 16;
    // add index to set last 16 bits
    handle += index as HAL_Handle;
    return handle;
}
