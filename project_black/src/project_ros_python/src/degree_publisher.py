#!/usr/bin/python3

import rospy
import math
import time
import board
import busio
import adafruit_lsm303dlh_mag
import adafruit_lsm303_accel

from project_ros_python.msg import get_degree
MY_PI = 3.14159265358979323846

i2c = busio.I2C(board.SCL_1, board.SDA_1)
mag_sensor = adafruit_lsm303dlh_mag.LSM303DLH_Mag(i2c)
acc_sensor = adafruit_lsm303_accel.LSM303_Accel(i2c)

def get_from_raw():

	for_pub = get_degree()

	while not rospy.is_shutdown():

		roll = 0.0
		pitch = 0.0
		yaw = 0.0
		#print('yaw : %f' % yaw)

		mean_count = 0
		do_number = 1
		while ( mean_count < do_number ):
			mag_x, mag_y, mag_z = mag_sensor.magnetic
			acc_x, acc_y, acc_z = acc_sensor.acceleration
			#print('Magnetometer (gauss): ({0:10.3f}, {1:10.3f}, {2:10.3f})'.format(mag_x, mag_y, mag_z))
			#print('Acceleration (m/s^2): ({0:10.3f}, {1:10.3f}, {2:10.3f})'.format(acc_x, acc_y, acc_z))

			roll = roll + math.atan2(-acc_x, math.sqrt(acc_y*acc_y + acc_z*acc_z))
			pitch = pitch + math.atan2(acc_y, math.sqrt(acc_x*acc_x + acc_z*acc_z))
			#new_mag_x = mag_x*math.cos(pitch) + mag_y*math.sin(roll)*math.sin(pitch) + mag_z*math.cos(roll)*math.sin(pitch)
			#new_mag_y = mag_y*math.cos(roll) - mag_z*math.sin(roll)
			yaw = yaw + math.atan2(mag_y, mag_x)
			#print('yaw : %f' % yaw)
			mean_count += 1

		yaw = yaw*180.0/MY_PI/do_number
		roll = roll*180.0/MY_PI/do_number
		pitch = pitch*180.0/MY_PI/do_number
		


		for_pub.roll = float(roll)
		for_pub.pitch = float(pitch)
		for_pub.yaw = float(yaw)
		for_pub.acc_x = float(acc_x)
		for_pub.acc_y = float(acc_y)
		for_pub.acc_z = float(acc_z)
		for_pub.imu_time_stamp = float(time.clock_gettime(time.CLOCK_MONOTONIC)) # mean : 0.2sec
		pub.publish(for_pub)
		print('yaw : %f' % yaw)
		#print('roll : %f' % roll)
		#print('pitch : %f' % pitch)
		time.sleep(0.01)


if __name__=='__main__':
	try:
		rospy.init_node('project_degree_node', anonymous=True)
		pub = rospy.Publisher('project_degree', get_degree, queue_size=1)
		get_from_raw()

	except rospy.ROSInterruptException:
		pass
