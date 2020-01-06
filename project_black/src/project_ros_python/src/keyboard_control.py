#!/usr/bin/python3

import rospy
import time
from project_ros_python.msg import nano_control
import tty, termios, sys
import re

def getchar():

	fd = sys.stdin.fileno()
	old_settings = termios.tcgetattr(fd)
	try:
		tty.setraw(sys.stdin.fileno())
		ch = sys.stdin.read(1)
	finally:
		termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	return ch
   


def keyboard_order():

	while not rospy.is_shutdown():
		ch = getchar()
		temp_ch = ch
		if (re.findall('[\w]',temp_ch)):
			print ('You pressed : ',temp_ch,'. that is not arrow.')
			if ( temp_ch == 'o'):
				print ('Stop !!!')
				pub.publish(5)
			elif ( temp_ch == 'i'):
				print ('Spin !!!')
				pub.publish(6)
		elif (temp_ch == '\x03'):
			print ('Bye Bye, ByeBye ya')
			sys.exit(1)
		else:
			for i in range(2):
				ch = getchar()
				temp_ch = temp_ch + ch
			if (temp_ch == '\x1b[A'):
				print ('You pressed up arrow\n')
				pub.publish(1)
			elif (temp_ch == '\x1b[D'):
				print ('You pressed left arrow\n')
				pub.publish(2)
			elif (temp_ch == '\x1b[C'):
				print ('You pressed right arrow\n')
				pub.publish(3)
			elif (temp_ch == '\x1b[B'):
				print ('You pressed down arrow\n')
				pub.publish(4)


if __name__=='__main__':
	try:
		rospy.init_node('move_keyboard_node', anonymous=True)
		pub = rospy.Publisher('ros_move_topic', nano_control, queue_size=1)
		keyboard_order()

	except rospy.ROSInterruptException:
		pass
