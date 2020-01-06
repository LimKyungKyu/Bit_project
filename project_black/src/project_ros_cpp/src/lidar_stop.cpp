#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "tf/transform_listener.h"
#include <math.h>
#include <opencv2/opencv.hpp>

void lidar_stop(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int m_a_count = 0;
    int count = scan->ranges.size();
    for(int i=0; i < count; i++)
	{
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
        if( degree<180.0 && degree>-180.0 )
		{
            if( isinf(scan->ranges[i]) || scan->ranges[i]>8.0 || scan->ranges[i]<0.1 )
			{
                std::cout << "range out" << control_mode << std::endl;
            }
			else
			{
				map_point_data[m_a_count][0] = (scan->ranges[i])*cos(degree*M_PI/180.0)*assist_enlarge;
				map_point_data[m_a_count][1] = -(scan->ranges[i])*sin(degree*M_PI/180.0)*assist_enlarge;
				++m_a_count;
			}
        }
    }
}


int main(int argc, char **argv)
{
    // ROS init //
	ros::init(argc, argv, "lidar_stop");
    // 노드 핸들러 선언
	ros::NodeHandle n;
	// 카토그래퍼에서 보내지는 /scan 토픽을 읽어서 scanCallback함수를 실행한다.
	ros::Subscriber ydlidar_sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1, lidar_stop);  
	
    ros::spin();
    
	return 0;
}