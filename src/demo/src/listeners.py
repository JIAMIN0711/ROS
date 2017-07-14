#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def callback(data):
    print("data is %s"%data)

def listener():
    rospy.init_node('mysubscr',anonymous=True)
    rospy.Subscriber('gohome',String,callback)
    rospy.spin()

if __name__ == "__main__":
    listener()
