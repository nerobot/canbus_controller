/////////////////////////////////////////////////////////////////////////////
// canbus controller test list
//
//  # Init
//  ## ID
//  * ID is stored correctly                        - 
//  * if id is all good, then return true           - 
//  * if id is out of bounds, then return false
  
#include "unity.h"
#include "canbus_controller.h"
#include "mock_mcp2515_driver.h"

static uint16_t device_id = 1;

void setUp(void)
{
    canbus_controller_init(device_id);
}

void tearDown(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// # Init
//

void test_init_valid_id_return_true(void)
{
    bool success = false;
    success = canbus_controller_init(device_id);
    TEST_ASSERT(success);
}

void test_init_id_out_of_bounds(void)
{
    bool success = canbus_controller_init(MAX_ID+1);
    TEST_ASSERT_FALSE(success);
} 

void test_init_get_device_id_correct(void)
{
    canbus_controller_init(device_id);
    uint16_t tmp_id = canbus_controller_get_device_id();
    TEST_ASSERT_EQUAL(device_id, tmp_id);
}


