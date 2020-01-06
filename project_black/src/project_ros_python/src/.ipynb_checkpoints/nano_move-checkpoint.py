#!/usr/bin/env python3

import sys
sys.path.append("/home/jetbot/project_black/src/project_ros_python/include")

import time
import rospy
from robot import Robot
from project_ros_python.msg import nano_control

robot = Robot()
robot.set_motors(0.0, 0.0)

left_now = 0.0
right_now = 0.0
left_now_2 = 0.0
right_now_2 = 0.0

max_speed = 0.15

change_speed = 0.01
forward_change_speed = 0.1
rotation_speed = 0.15
# 최대 1.0
# 1.0 이상으로 올라가므로 주의한다.

def callback(data):
	global left_now
	global right_now 
	move_value = data.move_message
	rospy.loginfo("I heard from keyboard %d", move_value)

	if ( move_value == 1 ):
		# 직진
		robot.set_motors(max_speed, max_speed-0.015)
		left_now = max_speed
		right_now = max_speed-0.015

	elif ( move_value == 2 ):
		# 좌회전
		if((left_now==0) and (right_now==0)):
			robot.set_motors(max_speed-change_speed, max_speed)	
			left_now = max_speed
			right_now = max_speed-change_speed
		else:
			if (left_now >= max_speed):
				robot.left_motor.value = max_speed - change_speed
				left_now = max_speed - change_speed
			elif (left_now <= 0.0):
				robot.left_motor.value = 0.0
				left_now = 0.0
			else:
				robot.left_motor.value = left_now - change_speed
				left_now = left_now - change_speed

			if (right_now >= max_speed):
				robot.right_motor.value = max_speed
				right_now = max_speed
			elif (right_now <= 0.0):
				robot.right_motor.value = 0.0
				right_now = 0.0
				robot.right_motor.value = right_now + change_speed
				right_now = right_now + change_speed
			else :
				robot.right_motor.value = right_now + change_speed
				right_now = right_now + change_speed

	elif ( move_value == 3 ):
		# 우회전
		if((left_now==0) and (right_now==0)):
			robot.set_motors(max_speed, max_speed-change_speed)	
			left_now = max_speed-change_speed
			right_now = max_speed
		else:
			if (left_now >= max_speed):
				robot.left_motor.value = max_speed
				left_now = max_speed
			elif (left_now <= 0.0):
				robot.left_motor.value = 0.0
				left_now = 0.0
				robot.left_motor.value = left_now + change_speed
				left_now = left_now + change_speed
			else:
				robot.left_motor.value = left_now + change_speed
				left_now = left_now + change_speed

			if (right_now >= max_speed):
				robot.right_motor.value = max_speed - change_speed
				right_now = max_speed - change_speed
			elif (right_now <= 0.0):
				robot.right_motor.value = 0.0
				right_now = 0.0
			else:
				robot.right_motor.value = right_now - change_speed
				right_now = right_now - change_speed

	elif ( move_value == 4 ):
		# 후진
		robot.set_motors(-max_speed, -max_speed)
		left_now = -max_speed
		right_now = -max_speed

	elif ( move_value == 5 ):
		# 정지
		robot.set_motors(0.0, 0.0)		
		left_now = 0.0
		right_now = 0.0

	elif ( move_value == 6 ):
		# 제자리 우회전	
		robot.set_motors(rotation_speed, -rotation_speed)		
		left_now = rotation_speed
		right_now = -rotation_speed
	elif ( move_value == 7 ):
		# 제자리 좌회전
		robot.set_motors(-rotation_speed, rotation_speed)		
		left_now = -rotation_speed
		right_now = rotation_speed
        
	elif ( move_value == 8 ):
        # 직진(점진적 증가)
		if (left_now >= max_speed):
			robot.left_motor.value = max_speed
			left_now = max_speed
		elif (left_now <= 0.0):
			robot.left_motor.value = 0.0 + forward_change_speed
			left_now = 0.0 + forward_change_speed
		else:
			robot.left_motor.value = left_now + forward_change_speed
			left_now = left_now + forward_change_speed

		if (right_now >= max_speed):
			robot.right_motor.value = max_speed
			right_now = max_speed
		elif (right_now <= 0.0):
			robot.right_motor.value = 0.0 + forward_change_speed
			right_now = 0.0 + forward_change_speed
		else:
			robot.right_motor.value = right_now + forward_change_speed
			right_now = right_now + forward_change_speed



def wait_listen():
    
	rospy.init_node('move_subscriber_node', anonymous=True)
	rospy.Subscriber('ros_move_topic', nano_control, callback, queue_size=1)
	rospy.spin()   


if __name__=='__main__':
	wait_listen()
