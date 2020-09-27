const HAL_K_INVALID_HANDLE: i32 = 0;

#[no_mangle]
fn rust_create_port_handle(base_handle: i32, channel: u8, module: u8) -> i32 {
    let mut handle = base_handle;
    handle <<= 24;
    // shift module and add to 3rd set of 8 bits
    let mut temp: i32 = module.into();
    temp = (temp << 8) & 0xff00;
    handle += temp;
    // add channel to last 8 bits
    handle += channel as i32;
    return handle;
}

#[no_mangle]
pub fn rust_create_port_handle_for_spi(base_handle: i32, channel: u8) -> i32 {
    let mut handle = base_handle;
    handle <<= 16;
    // set second set up bits to 1
    let mut temp: i32 = 1;
    temp = (temp << 8) & 0xff00;
    handle += temp;
    // shift to last set of bits
    handle = handle << 8;
    // add channel to last 8 bits
    handle += channel as i32;
    return handle;
}

#[no_mangle]
pub fn rust_create_handle(index: i16, handle_type: u8, version: i16) -> i32 {
    if index < 0 {
        return HAL_K_INVALID_HANDLE;
    }
    if handle_type == 0 || handle_type > 127 {
        return HAL_K_INVALID_HANDLE;
    }
    // set last 8 bits, then shift to first 8 bits
    let mut handle: i32 = handle_type.into();
    handle = handle << 8;
    handle += version as i32;
    handle = handle << 16;
    // add index to set last 16 bits
    handle += index as i32;
    return handle;
}
