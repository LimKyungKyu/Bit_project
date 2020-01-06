#include <unistd.h>
#include <fstream>
#include <iostream>
#include <chrono>

#include <ros/ros.h>

#include "std_msgs/Int32.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"

#include "project_ros_cpp/nano_control.h"
#include "project_ros_cpp/get_degree.h"
#include "project_ros_cpp/clean_point.h"

#include "tf/transform_listener.h"



// ros msg define //
project_ros_cpp::nano_control step_one_order;
project_ros_cpp::nano_control step_two_order;
std_msgs::Int32MultiArray point_data;
std_msgs::Int32 move_ready_flag;


// find_direction //
double target_x = 0.0, target_y = 0.0;
int xy_count = 0;
int map_origin_x = 0, map_origin_y = 0;

// step_one_func //
bool step_one_rotation_flag = true;
bool make_target_yaw_flag = true;
double get_mpu_yaw = 0.0;
double destination_yaw = 0.0;
double target_yaw = 0.0;

// step_two_func //
bool step_two_rotation_flag = true;
bool shutdown_flag = true;

#define grid_interval_pixel 4 // 픽셀 단위 //
#define grid_interval_cm 4 // cm 단위 //
#define degree_range 10 // 각도 범위 // 

// Flags //
std::string file_path_mode("/home/jetbot/web/mode");
std::string file_path_pause("/home/jetbot/mode110");
std::string file_path_map_move("/home/jetbot/map_move_flag");

std::chrono::system_clock::time_point time_start;
std::chrono::duration<double> limit_sec;


double in_180_func(double original_degree)
{

	if ( original_degree < -180.0 )
	{
		original_degree = original_degree + 360.0;
	}
	else if ( original_degree > 180.0 )
	{
		original_degree = original_degree - 360.0;
	}

	return original_degree;
}

void find_direction(int point_data_set[][2])
{
	double yaw=0.0, pitch=0.0, roll=0.0;
	double nano_x=0.0, nano_y=0.0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 7_1. 현재 xy_count가 마지막 포인트인지 확인한다. //
	if (xy_count < (point_data.data.size()/2) )
	{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 8. xy_count에 해당하는 포인트를 불러온다. //
		target_x = point_data_set[xy_count][0];
		target_y = point_data_set[xy_count][1];
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 9_1. 다음 포인트를 준비한다. //
		++xy_count;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// google cartographer tf setting //
		tf::TransformListener tfl;
		tf::StampedTransform my_test_transform;

		std::string start = std::string("/map"); 
		std::string move = std::string("/base_footprint");
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		try
		{
			///////////////////////////////////////////////////////////////////////////////
			// 10. 나노의 현재위치 (i,j) 를 계산한다. //
			tfl.waitForTransform(start, move, ros::Time(), ros::Duration(1.0));
			tfl.lookupTransform(start, move, ros::Time(), my_test_transform);
			tf::Vector3 Coordinate_3D = my_test_transform.getOrigin();

			// Map의(0,0)에 해당하는 Mat의(i,j)는 (map_origin_x, map_origin_y)이다. //
			nano_x = map_origin_x + Coordinate_3D.getX()*100.0/2.0;
			nano_y = map_origin_y - Coordinate_3D.getY()*100.0/2.0;
			my_test_transform.getBasis().getRPY(roll, pitch, yaw);

			std::cout << "나노의 현재위치 (i,j) : " << nano_x << ", " << nano_y << std::endl;
			///////////////////////////////////////////////////////////////////////////////


			///////////////////////////////////////////////////////////////////////////////
			// 11. 현재위치가 목표지점과 몇 픽셀 떨어져있는지 확인하고 범위안에 도착하면 종료 //
			double distance = sqrt(pow(nano_x-target_x,2)+pow(nano_y-target_y,2));
			if ( distance < grid_interval_pixel )
			{
				std::cout << "reached !!! : " << std::endl;
				step_two_rotation_flag= false;
				return;
			}
			///////////////////////////////////////////////////////////////////////////////


			///////////////////////////////////////////////////////////////////////////////
			// 12. nano의 yaw를 0으로 만들 yaw값을 구한다. //
			// map(0,0)의 좌표축과 동일위치에 있다고 가정한 yaw값이 나온다. //
			// 동일한 위치에 있다고 가정하고 x축이 Y가 0보다 작은 방향을 보는 경우 yaw는 반드시 0 ~ -180 사이의 값을 반환한다.
			// 동일한 위치에 있다고 가정하고 x축이 Y가 0보다 큰 방향을 보는 경우 yaw는 반드시 0 ~ +180 사이의 값을 반환한다.
			double nano_zero_yaw = -yaw*180.0/M_PI;
			//std::cout << "nano_zero_yaw : " << nano_zero_yaw << std::endl;
			///////////////////////////////////////////////////////////////////////////////


			///////////////////////////////////////////////////////////////////////////////	
			// 13. nano의 yaw가 map의 좌표계와 같은 방향을 본다고 가정하고 목표지점까지의 yaw를 구한다.
			// nano의 현재 위치보다 목표지점의 Y가 0보다 작은 위치에 있는 경우 yaw는 반드시 0 ~ -180 사이의 값을 반환한다.
			// nano의 현재 위치보다 목표지점의 Y가 0보다 큰 위치에 있는 경우 yaw는 반드시 0 ~ -180 사이의 값을 반환한다.

			double zero_to_target = (atan2(-(target_y-nano_y), (target_x-nano_x))*180.0/M_PI);
			//std::cout << "zero_to_target : " << zero_to_target << std::endl;
			///////////////////////////////////////////////////////////////////////////////	


			///////////////////////////////////////////////////////////////////////////////
			// 14. 현재 yaw에서 회전할 yaw를 구한다.
			// 180도 이상의 회전을 방지하기 위해 아래와 같이 정의한다.
			destination_yaw = nano_zero_yaw + zero_to_target;
			destination_yaw = in_180_func(destination_yaw);
			//std::cout << "destination_yaw : " << destination_yaw << std::endl;
			///////////////////////////////////////////////////////////////////////////////
		}
		catch(tf2::LookupException& e)
		{
			///////////////////////////////////////////////////////////////////////////////
			// 9_2. tf에 실패한 경우 이전 점으로 되돌린다. //
			printf("fail tf \n");
			step_two_rotation_flag= false;
			xy_count = xy_count - 1;
			return;
			///////////////////////////////////////////////////////////////////////////////
		}

	}
	else
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 7_2. 마지막 포인트면 종료한다. //	
		step_two_rotation_flag = false;
		shutdown_flag = false;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

}

void step_one_func(const project_ros_cpp::get_degree::ConstPtr& data)
{

	/////////////////////////////////////////////////////////////
	// 18. mpu_6050에서 현재 상태의 yaw값을 추출한다. //
	// 이때의 yaw값은 cartographer의 yaw값과 별개의 정보이다. //

	//std::cout << "step one start !!!" << std::endl;
	get_mpu_yaw = data->yaw;
	/////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////
	// 19. step_one_rotation_flag를 확인한다. //
	if ( step_one_rotation_flag )
	{
	/////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////
		// 20_1. make_target_yaw_flag를 확인한다. //
		// 20_2. make_target_yaw_flag가 true인 경우 //
		// 현재 mpu_6050의 yaw값을 기준으로 총 회전해야될 각도를 계산한다. //
		if ( make_target_yaw_flag )
		{
			get_mpu_yaw = in_180_func(get_mpu_yaw);	
			target_yaw = destination_yaw + get_mpu_yaw;
			target_yaw = in_180_func(target_yaw);
			make_target_yaw_flag = false;
		}
		///////////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////
		// 21_1. 현재 mpu_6050의 yaw값과 target_yaw의 차이를 구한다. //
		// gap이 degree_range 이하가 될때까지 반복한다. //
		double gap = target_yaw - get_mpu_yaw;
		gap = in_180_func(gap);

		if ( (gap<degree_range) && (gap>-degree_range) )
		{
			///////////////////////////////////////////////////////////////////////////
			// 21_2. 범위안에 들어오면 멈추고 step_one_rotation_flag 를 false 로 바꾼다. //
			std::cout << "gap : " << gap << " 회전 정지" <<std::endl;
			step_one_order.move_message = 5;
			step_one_rotation_flag = false;
			///////////////////////////////////////////////////////////////////////////	
		}
		else if ( gap>degree_range )
		{
			std::cout << "gap : " << gap << " 제자리 좌회전" <<std::endl;
			step_one_order.move_message = 7;
		}
		else if ( gap<-degree_range )
		{
			std::cout << "gap : " << gap << " 제자리 우회전" <<std::endl;
			step_one_order.move_message = 6;
		}
		///////////////////////////////////////////////////////////////////////////
	}
}

void get_grid_point(const std_msgs::Int32MultiArray::ConstPtr& msg)
{
	
	if ( msg->data.size() > 0 )
	{
		point_data.data = msg->data;
	}
}

int main(int argc, char **argv)
{

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// ROS init //
	ros::init(argc, argv, "rotation_move_node");
	ros::NodeHandle nh;

	// subscriber, publisher //
	ros::Subscriber step_one = nh.subscribe("mpu_6050_degree", 1, step_one_func);

	ros::Publisher move_ready = nh.advertise<std_msgs::Int32>("move_ready_topic", 1);
	ros::Publisher step_one_pub = nh.advertise<project_ros_cpp::nano_control>("ros_move_topic", 1);
	ros::Publisher step_two_pub = nh.advertise<project_ros_cpp::nano_control>("ros_move_topic", 1);
	///////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// google cartographer tf setting //
	tf::TransformListener tfl;
	tf::StampedTransform my_test_transform;

	std::string start = std::string("/map"); 
	std::string move = std::string("/base_footprint");
	///////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// map move setting //
	// 1 : 진행중, 0 : grid point 순회 완료 //
	std::ofstream file_map_move(file_path_map_move);
	while ( ros::ok() )
	{
		if( file_map_move.is_open() )
		{
            std::cout << "move setting : move" << std::endl;
			file_map_move << 1 << std::endl;
			file_map_move.close();
			break;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////


	int mode_value = 0;
	while ( ros::ok() )
	{
		std::cout << "mode check" << std::endl;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 1. control_tower.cpp에서 보내는 mode를 수신한다. //
		// 참고 : control_tower.cpp에서는 일반모드를 누른 순간 //
		// /home/nvidia/mode.txt에 100을 기록하고, 100이라는 메세지를 발송하고 //
		// /home/nvidia/mode.txt에 0을 다시 기록한다. //
		std_msgs::Int32::ConstPtr control_mode = ros::topic::waitForMessage<std_msgs::Int32>("control_tower_topic",nh,ros::Duration(1.0));\
		if (control_mode)
		{
			mode_value = control_mode->data;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 2. mode가 반드시 100, 110번일때만 코드를 실행한다. //
			if ( mode_value == 100 )
			{
				std::cout << "mode is : " << mode_value << std::endl;
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 3_1. grid 포인트를 받을때까지 clean_map.cpp에 100을 발송한다. //
				// 3_2. clean_map.cpp는 100을 받으면 맵 그리기를 시작한다. //
				// 3_3. 이때 clean_map.cpp는 /home/nvidia/map_load_flag를 읽고 새로 그릴지, 기존맵을 사용할지 판단한다. //
				// 3_4. clean_map.cpp로부터 순회할 grid point 를 받는다.
				// 3_3. get_grid_point 함수를 호출한다.
				while ( ros::ok() )
				{
					move_ready_flag.data = 100;
					move_ready.publish(move_ready_flag);

					std_msgs::Int32MultiArray::ConstPtr msg = ros::topic::waitForMessage<std_msgs::Int32MultiArray>("clean_point_topic",nh,ros::Duration(1.0));
					if (msg)
					{
						get_grid_point(msg);
                        std::cout << "get grid point success !!!" << std::endl;
						break; 
					}
                    else
                    {
                        std::cout << "not yet receive !!!" << std::endl;
                    }
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				

				///////////////////////////////////////////////////////////////////////////////////
				// 4. clean_map.cpp로부터 map(0,0)의 (i,j)를 추출한다.
				map_origin_y = point_data.data.back();
				point_data.data.pop_back();
				map_origin_x = point_data.data.back();
				point_data.data.pop_back();
				std::cout << "map (0,0) : " << map_origin_x << ", " << map_origin_y << std::endl;
				///////////////////////////////////////////////////////////////////////////////////


				///////////////////////////////////////////////////////////////////////////////////
				// 5. grid 포인트 데이터를 저장한다. //
				int point_data_set[point_data.data.size()/2][2];
				int j = 0;
				for ( int i=0; i<(point_data.data.size()/2); i++ )
				{
					point_data_set[i][0] = point_data.data[j];
					point_data_set[i][1] = point_data.data[j+1];
					std::cout << point_data_set[i][0] << ", " << point_data_set[i][1] << std::endl;
					j+=2;
				}
				///////////////////////////////////////////////////////////////////////////////////


				///////////////////////////////////
				// 6. 방향 찾기 초기화 //
				step_one_rotation_flag = true;
				make_target_yaw_flag = true;

				step_two_rotation_flag = true;

				shutdown_flag = true;

				find_direction(point_data_set);
				///////////////////////////////////


				while ( ros::ok() )
				{
					///////////////////////////////////////////////////////////////////////////////////
					// 15. step_two_rotation_flag를 확인한다. //
					// 7_2번, 9_2번, 11번의 경우 step_two_rotation_flag = false이다. //
					if ( step_two_rotation_flag )
					{
						///////////////////////////////////////////////////////////////////////////////////
						// 16. step_one_rotation_flag를 확인한다. //
						if ( step_one_rotation_flag )
						{
							///////////////////////////////////////////////////////////////////////////////////
							// 17. 목표 지점 향하게 만들기 //
							// spinOnce가 실행되면 step_one_func이 1번 실행된다. //
							// 21_1번, 21_2로 결과를 반환한다. //
							// 21_2번의 경우 step_one_rotation_flag = false이다. //
							ros::spinOnce();
							step_one_pub.publish(step_one_order);
							///////////////////////////////////////////////////////////////////////////////////


							///////////////////////////////////////////////////////////////////////////////////
							// 22. 모든 21번의 명령을 0.5초동안 지속하고 멈춘다. //
			    			time_start = std::chrono::system_clock::now();
							limit_sec = std::chrono::system_clock::now() - time_start;
							while ( limit_sec.count() < 0.05 )
							{
								limit_sec = std::chrono::system_clock::now() - time_start;
							}
							step_one_order.move_message = 5;
							step_one_pub.publish(step_one_order);
							///////////////////////////////////////////////////////////////////////////////////
						}
						else
						{
							///////////////////////////////////////////////////////////////////////////////////
							// 23. 21_2번의 결과로 else에 도착한다. //
							// 직진을 0.01초씩 10번 한다. //
							std::cout <<"target point : "<< target_x <<", " << target_y <<std::endl;
							std::cout << "직진" <<std::endl;
							int step_count = 0;
							while ( step_count < 10)
							{
								step_two_order.move_message = 1;
								step_two_pub.publish(step_two_order);

				    				time_start = std::chrono::system_clock::now();
								limit_sec = std::chrono::system_clock::now() - time_start;
								while ( limit_sec.count() < 0.01 )
								{
									limit_sec = std::chrono::system_clock::now() - time_start;
								}

								step_two_order.move_message = 5;
								step_two_pub.publish(step_two_order);

								++step_count;
							}
							///////////////////////////////////////////////////////////////////////////////////

							step_two_order.move_message = 5;
							step_two_pub.publish(step_two_order);

							///////////////////////////////////////////////////////////////////////////////////
							// 24. 7_1번으로 돌아간다. //
							xy_count = xy_count - 1;

							step_one_rotation_flag = true;
							make_target_yaw_flag = true;

							step_two_rotation_flag = true;

							find_direction(point_data_set);
							///////////////////////////////////////////////////////////////////////////////////
						
						}
					}
					else
					{
						///////////////////////////////////////////////////////////////////////////////////
						// 25_1. 24번에서 7_1번을 거쳐 11번으로 들어가서 여기에 도착한 경우 //
							// 다음 진행되는 7_1에서 point를 다 돌지 않았으면 15번으로 진행된다. //
							// 다음 진행되는 7_1에서 point를 다 돌았으면 7_2번에 의해 shutdown_flag = false가 된다. //
						// 25_2. 24번에서 7_1번을 거쳐 9_2번으로 들어가서 여기에 도착한 경우 //
							// 다음 진행되는 7_1에서 15번으로 진행된다. //
						step_one_rotation_flag = true;
						make_target_yaw_flag = true;

						step_two_rotation_flag = true;

						find_direction(point_data_set);
						///////////////////////////////////////////////////////////////////////////////////


						///////////////////////////////////////////////////////////////////////////////////
						// 26. 모드 확인 //
						std::ifstream file_mode(file_path_mode);
						std::string temp_file_mode;
						while ( ros::ok() )
						{
							if( file_mode.is_open() )
							{
								file_mode >> temp_file_mode;
								mode_value = atoi(temp_file_mode.c_str());
								file_mode.close();

								///////////////////////////////////////////////////////////////////////////////////
								// 27_1. 일시정지 ( 900 모드 ) 모드가 풀리기 전까지 정지한다. //
								while ( ros::ok )
								{
									if ( mode_value == 900 )
									{
										file_mode.open(file_path_mode);
										file_mode >> temp_file_mode;
										mode_value = atoi(temp_file_mode.c_str());
										file_mode.close();

						    			time_start = std::chrono::system_clock::now();
										limit_sec = std::chrono::system_clock::now() - time_start;
										while ( limit_sec.count() < 0.01 )
										{
											limit_sec = std::chrono::system_clock::now() - time_start;
										}
									}
									else
									{
										break;
									}
								}
								///////////////////////////////////////////////////////////////////////////////////

								///////////////////////////////////////////////////////////////////////////////////
								// 27_2. 모드가 변했기 때문에 1번으로 되돌아간다. //
								if ( mode_value == 300 || mode_value == 310 || mode_value == 990 )
								{

									step_two_order.move_message = 5;
									step_two_pub.publish(step_two_order);
                                    
                                    shutdown_flag = false;

									std::cout << "mode is : " << mode_value << std::endl;
									std::cout << "mode changed" << std::endl;
									break;
								}
								///////////////////////////////////////////////////////////////////////////////////

								///////////////////////////////////////////////////////////////////////////////////
								// 28. 일시정지 ( 110 모드 ) 3초동안 정지한다.  //
                                std::ifstream file_pause(file_path_pause);
                                std::string temp_file_pause;
                                int pause_flag = 0;
                                
                                while ( ros::ok )
								{
                                    if( file_pause.is_open() )
                                    {
                                        file_pause >> temp_file_pause;
                                        pause_flag = atoi(temp_file_pause.c_str());
                                        file_pause.close();
                                        
                                        if ( pause_flag == 5 )
                                        {
                                            time_start = std::chrono::system_clock::now();
                                            limit_sec = std::chrono::system_clock::now() - time_start;
                                            while ( limit_sec.count() < 3.0 )
                                            {
                                                 limit_sec = std::chrono::system_clock::now() - time_start;
                                            }
                                        }
                                        
                                        break;
                                    }
                                    else
                                    {
                                        std::cout << "pause file open fail" << std::endl;
                                    }
                                }

                                ///////////////////////////////////////////////////////////////////////////////////
                                
                                ///////////////////////////////////////////////////////////////////////////////////
                                // 어느것도 해당하지 않으면 모드를 검색하는 while 탈출
                                std::cout << "mode is not changed" << std::endl;
                                break;
                                ///////////////////////////////////////////////////////////////////////////////////

							}
							else
							{
								std::cout << "mode check fail" << std::endl;
							}
                            
						}
						/////////////////////////////////////////////////////////////////////////////////////////////////////////

						///////////////////////////////////////////////////////////////////////////////////
						// 29. 포인트를 모두 돌았으면 shutdown_flag = false이다. //
						// file_path_map_move를 0으로 바꾼다. //
						// 1번으로 돌아간다. //
						if ( !shutdown_flag )
						{
                            if ( mode_value == 300 || mode_value == 310 || mode_value == 990 )
							{
                                break;
                            }
                            else
                            {
                                std::cout << "clean done" << std::endl;
                                
                                step_two_order.move_message = 5;
                                step_two_pub.publish(step_two_order);
                                
                                // move setting //
                                file_map_move.open(file_path_map_move);
                                while ( ros::ok() )
                                {
                                    if( file_map_move.is_open() )
                                    {
                                        file_map_move << 0 << std::endl;
                                        file_map_move.close();
                                        break;
                                    }
                                }
                                
                                break;   
                            }
						}
						///////////////////////////////////////////////////////////////////////////////////
                        
					}
	
				}
			}
			else
			{
				std::cout << "mode is : " << mode_value << std::endl;
				std::cout << "this mode is not used in here" << mode_value << std::endl;
			}
		}
		else
		{
			std::cout << "mode is not set" << std::endl;
		}

	}

	return 0;
}