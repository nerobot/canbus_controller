/////////////////////////////////////////////////////////////////////////////
// canbus controller test list
//
//  # Init
//  ## ID
//  * ID is stored correctly                        - Done
//  * if id is all good, then return true           - Done
//  * if id is out of bounds, then return false     - Done
//
//  ## Baudrate
//  * Baudrate is stored correctly                  - done
//  * if br is out of bounds, return false          - done
//  * br can be returned correctly                  - done
//
//  ## mcp init
//  * return true when mcp_init is all ok           - done
//  * return false when mcp_init fails              - done
//
//  # Sending commands over can
//  ## Sending switch pin command
//  * send_switch_on_command all ok                 - done
//  * send_switch_off_command all ok                - done
//  * sending to a device that isn't on the device 
//  list will cause a failure                       - done  
//  * if send_buffer returns false, return false    - done
//  
//  # Receiving data
//  ## Checking if data is available to read. 
//  * to check if there is data, has_receive_data 
//  will call mcp mcp2515_rx0_is_full               - done
//  * if rx0 buf has any data, then has_receive_data
//  will return true                                - done
//  * if rx0 buf is emtpy, then has_receive_data
//  will return false                               - done
//
// ## Reading data from buffers
// Note: read_buf doesn't check if there's acually any data in the rx buffer.
// However, it will return false if it tries to read data and fails.
//  * read_data-will_call_mcp_read_can_message      - done
//  * read_data_will_store_msg_its_id_and_length    - done
//  * the above can be read with get_can_message,
//  get_can_msg_id, and get_can_msg_len             - done
//  * if data has been read correctly, return true
//  * if data has not been read, return false
//  * read will clear rx0if after reading       

#include "unity.h"
#include "canbus_controller.h"
#include "mock_mcp2515_driver.h"

static uint16_t device_id = 1;
static baudrate_t baudrate = br_5kbpm; 

static void mcp2515_driver_read_can_message_expect(uint16_t* id, uint8_t* len, uint8_t* message)
{
    mcp2515_driver_read_can_message_Expect(id, len, message); 
    mcp2515_driver_read_can_message_IgnoreArg_id();
    mcp2515_driver_read_can_message_IgnoreArg_len();
    mcp2515_driver_read_can_message_IgnoreArg_read_buf();

    mcp2515_driver_read_can_message_ReturnThruPtr_id(id);
    mcp2515_driver_read_can_message_ReturnThruPtr_len(len);
    mcp2515_driver_read_can_message_ReturnArrayThruPtr_read_buf(message, *len);
}

void setUp(void)
{
    mcp2515_init_IgnoreAndReturn(true);
    canbus_controller_init(device_id, baudrate);
}

void tearDown(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// # Init
//

///////////////////////////////////////////////////////////////////////////////
// ## Device ID
//

void test_init_valid_id_return_true(void)
{
    bool success = false;
    success = canbus_controller_init(device_id, baudrate);
    TEST_ASSERT(success);
}

void test_init_id_out_of_bounds(void)
{
    bool success = canbus_controller_init(MAX_ID+1, baudrate);
    TEST_ASSERT_FALSE(success);
} 

void test_init_get_device_id_correct(void)
{
    canbus_controller_init(device_id, baudrate);
    uint16_t tmp_id = canbus_controller_get_device_id();
    TEST_ASSERT_EQUAL(device_id, tmp_id);
}

///////////////////////////////////////////////////////////////////////////////
// ## Baudrate
// 

void test_init_baudrate_correct(void)
{
    bool success = canbus_controller_init(device_id, baudrate);
    TEST_ASSERT(success);
}

void test_init_baudrate_out_of_bounds_returns_false(void)
{
    bool success = canbus_controller_init(device_id, br_num_types+1);
    TEST_ASSERT_FALSE(success);
}

void test_init_baudrate_get_baudrate_returns_correctly(void)
{
    bool success = canbus_controller_init(device_id, baudrate);
    baudrate_t tmp_br = canbus_controller_get_baudrate();
    TEST_ASSERT_EQUAL(baudrate, tmp_br);
}

///////////////////////////////////////////////////////////////////////////////
// ## mcp init
//

void test_init_will_call_mcp_init(void)
{
    mcp2515_init_ExpectAndReturn(true);
    
    canbus_controller_init(device_id, baudrate);
}

void test_init_will_return_false_if_mcp_init_fails(void)
{
    mcp2515_init_ExpectAndReturn(false);

    bool success = canbus_controller_init(device_id, baudrate);
    TEST_ASSERT_FALSE(success);
}

///////////////////////////////////////////////////////////////////////////////
// # Send commands
// 
 
///////////////////////////////////////////////////////////////////////////////
// ## Sending switch on commands
//

void test_send_switch_on_all_ok(void)
{
    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 1};
    mcp2515_driver_send_msg_buffer_ExpectAndReturn(device_id, 0, 6, message, true);
    canbus_controller_send_switch_on(id_boiler_switch);
}


void test_send_switch_off_all_ok(void)
{
    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 0};
    mcp2515_driver_send_msg_buffer_ExpectAndReturn(device_id, 0, 6, message, true);
    canbus_controller_send_switch_off(id_boiler_switch);
}

void test_send_switch_on_return_true_if_all_ok(void)
{
    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 1};
    mcp2515_driver_send_msg_buffer_ExpectAndReturn(device_id, 0, 6, message, true);
    bool success = canbus_controller_send_switch_on(id_boiler_switch);
    TEST_ASSERT(success);
}

void test_send_switch_off_return_true_if_all_ok(void)
{
    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 0};
    mcp2515_driver_send_msg_buffer_ExpectAndReturn(device_id, 0, 6, message, true);
    bool success = canbus_controller_send_switch_off(id_boiler_switch);
    TEST_ASSERT(success);
}

void test_send_switch_on_return_false_if_message_not_send_correctly(void)
{
    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 1};
    mcp2515_driver_send_msg_buffer_ExpectAndReturn(device_id, 0, 6, message, false);
    bool success = canbus_controller_send_switch_on(id_boiler_switch);
    TEST_ASSERT_FALSE(success);
}

void test_send_switch_off_return_false_if_message_not_send_correctly(void)
{
    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 0};
    mcp2515_driver_send_msg_buffer_ExpectAndReturn(device_id, 0, 6, message, false);
    bool success = canbus_controller_send_switch_off(id_boiler_switch);
    TEST_ASSERT_FALSE(success);
}

void test_send_switch_on_when_send_device_is_not_on_list_return_false(void)
{
//    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 0};
//    mcp2515_driver_send_msg_buffer_ExpectAndReturn(device_id, 0, 6, message, false);
    bool success = canbus_controller_send_switch_on(id_num_types);
    TEST_ASSERT_FALSE(success);
}

void test_send_switch_off_when_send_device_is_not_on_list_return_false(void)
{
//    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 0};
//    mcp2515_driver_send_msg_buffer_ExpectAndReturn(device_id, 0, 6, message, false);
    bool success = canbus_controller_send_switch_off(id_num_types);
    TEST_ASSERT_FALSE(success);
}

///////////////////////////////////////////////////////////////////////////////
// # Receiving data
//

///////////////////////////////////////////////////////////////////////////////
// ## Checking if data is available to read
//

void test_has_receive_data_will_call_mcp_rx0_is_full(void)
{
    mcp2515_rx0_is_full_ExpectAndReturn(true);
    canbus_controller_has_receive_data();
}

void test_when_there_is_data_in_rx0_buf__return_true(void)
{
    mcp2515_rx0_is_full_ExpectAndReturn(true);
    bool success = canbus_controller_has_receive_data();
    TEST_ASSERT(success); 
}

void test_when_there_is_no_data_in_rx0_buf__return_false(void)
{
    mcp2515_rx0_is_full_ExpectAndReturn(false);
    bool success = canbus_controller_has_receive_data();
    TEST_ASSERT_FALSE(success); 
}

///////////////////////////////////////////////////////////////////////////////
// ## Reading data from the buffer
//

void test_read_buf__will_call__mcp_read_message(void)
{
    uint16_t from_id = 0x0010;
    uint8_t len = 6;
    uint8_t receive_msg[] = {00, 00, 00, 01, 01, 01};
    uint16_t tmp_id = 0x0000;
    uint8_t tmp_len = 0;
    uint8_t tmp_receive_msg[] = {0, 0, 0, 0, 0, 0};

    mcp2515_driver_read_can_message_expect(&from_id, &len, receive_msg);
    mcp2515_driver_clear_rx0if_IgnoreAndReturn(true); 
    canbus_controller_read_buf();
}

void test_read_buf__will_store_id__read_id__will_return_value(void)
{
    uint16_t from_id = 0x0010;
    uint8_t len = 6;
    uint8_t receive_msg[] = {00, 00, 00, 01, 01, 01};
    uint16_t tmp_id = 0x0000;
    uint8_t tmp_len = 0;
    uint8_t tmp_receive_msg[] = {0, 0, 0, 0, 0, 0};

    mcp2515_driver_read_can_message_expect(&from_id, &len, receive_msg);
    mcp2515_driver_clear_rx0if_IgnoreAndReturn(true); 
    canbus_controller_read_buf();

    tmp_id = canbus_controller_get_buf_from_id();
    TEST_ASSERT_EQUAL(from_id, tmp_id);
}

void test_read_buf_will_store_msg_len__get_receive_msg_len__will_return_it(void)
{
    uint16_t from_id = 0x0010;
    uint8_t len = 6;
    uint8_t receive_msg[] = {00, 00, 00, 01, 01, 01};
    uint16_t tmp_id = 0x0000;
    uint8_t tmp_len = 0;
    uint8_t tmp_receive_msg[] = {0, 0, 0, 0, 0, 0};

    mcp2515_driver_read_can_message_expect(&from_id, &len, receive_msg);
    mcp2515_driver_clear_rx0if_IgnoreAndReturn(true); 
    canbus_controller_read_buf();

    tmp_len = canbus_controller_get_receive_msg_len();
    TEST_ASSERT_EQUAL(len, tmp_len);
} 

void test_read_buf_will_store_msg__get_receive_msg__will_return_it(void)

{
    uint16_t from_id = 0x0010;
    uint8_t len = 6;
    uint8_t receive_msg[] = {00, 00, 00, 01, 01, 01};
    uint16_t tmp_id = 0x0000;
    uint8_t tmp_len = 0;
    uint8_t tmp_receive_msg[] = {0, 0, 0, 0, 0, 0};

    mcp2515_driver_read_can_message_expect(&from_id, &len, receive_msg);
    mcp2515_driver_clear_rx0if_IgnoreAndReturn(true); 
    canbus_controller_read_buf();

    canbus_controller_get_receive_msg(tmp_receive_msg);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(receive_msg, tmp_receive_msg, len);
}

void test_read_buf_will_clear_rx0if_after_reading_message(void)
{
    uint16_t from_id = 0x0010;
    uint8_t len = 6;
    uint8_t receive_msg[] = {00, 00, 00, 01, 01, 01};
    uint16_t tmp_id = 0x0000;
    uint8_t tmp_len = 0;
    uint8_t tmp_receive_msg[] = {0, 0, 0, 0, 0, 0};

    mcp2515_driver_read_can_message_expect(&from_id, &len, receive_msg);
    mcp2515_driver_clear_rx0if_ExpectAndReturn(true);
    canbus_controller_read_buf();
}
