/**
 * @file AS5048B.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "AS5048B.h"
#include <CppUtil.h>

/**
 * Static Constants
 */
const float AS5048B::rad_per_cnt = 2.0f * M_PI / 16384.0f;

/**
 * @brief Constructor for AS5048B encoder interface
 * @param i2c Platform-specific I2C interface
 * @param i2c_addr I2C address (default 0x40)
 * @param home_angle Zero angle (default 0)
 */
AS5048B::AS5048B(I2CDevice::i2c_t* i2c, uint8_t i2c_addr, float home_angle) :
	i2c(i2c, i2c_addr, Struct::msb_first)
{
	set_home(home_angle);
}

/**
 * @brief Sets home angle to current angle.
 */
void AS5048B::set_home()
{
	set_home(0.0f);
	set_home(get_angle());
}

/**
 * @brief Sets home angle to given angle
 */
void AS5048B::set_home(float home_angle)
{
	this->home_angle = home_angle;
}

/**
 * @brief Returns angle relative to home in radians [-pi, pi].
 */
float AS5048B::get_angle()
{
	// Get MSB and LSB from device
	i2c.get_seq(reg_angle_addr, 2);
	uint16_t msb = (uint8_t)i2c;
	uint16_t lsb = (uint8_t)i2c;
	uint16_t angle_raw = (msb << 6) | lsb;

	// Convert to float and wrap to [-pi, pi]
	float angle = angle_raw * rad_per_cnt;
	angle = CppUtil::wrap(angle - home_angle, -M_PI, +M_PI);
	return angle;
}
