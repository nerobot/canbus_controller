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
