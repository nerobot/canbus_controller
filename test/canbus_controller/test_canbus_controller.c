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
// * 
  
#include "unity.h"
#include "canbus_controller.h"
#include "mock_mcp2515_driver.h"

static uint16_t device_id = 1;
static baudrate_t baudrate = br_5kbpm; 

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
