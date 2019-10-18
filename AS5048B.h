/**
 * @file AS5048B.h
 * @brief Class for interfacing with AS5048B 14-bit I2C encoder
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <I2CDevice.h>

class AS5048B
{
public:
	AS5048B(
		I2CDEVICE_I2C_CLASS* i2c,
		uint8_t i2c_addr = 0x40,
		float home_angle = 0.0f);
	AS5048B();
	void set_home();
	float get_angle();
protected:
	static const uint8_t reg_angle_addr = 0xFE;
	static const float rad_per_cnt;
	I2CDevice i2c;
	float home_angle;
};