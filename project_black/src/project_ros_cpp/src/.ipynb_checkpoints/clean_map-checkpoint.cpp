#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui/highgui.hpp"

#include "tf/transform_listener.h"

#include <ros/ros.h>

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Int32.h"
#include <std_msgs/Header.h>
#include <nav_msgs/MapMetaData.h>
#include <nav_msgs/OccupancyGrid.h>
#include "project_ros_cpp/nano_control.h"

#include "pathFinder.h" // pathFinder 헤더 추가
#include "MJPEGWriter.h"

///////////////////////////////////////////
// user define //
#define _USE_MATH_DEFINES
#define map_square_padding 10
#define wall_padding 14
#define move_fill_area 6
///////////////////////////////////////////

cv::Mat i_want_to_see;
std_msgs::Int32MultiArray clean_point;

int map_origin_x = 0;
int map_origin_y = 0;

std::string file_path_mode("/home/jetbot/web/mode");
std::string file_path_map_load("/home/jetbot/map_load_flag");
std::string file_path_map_move("/home/jetbot/map_move_flag");

int int_port_num = 0;




void flag_change( std::string file_path, int flag_value );
int mode_or_flag_read( std::string file_path );
int add_padding(cv::Mat resizing_mat);
void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg);
void wait_control_tower();
void wait_cartographer_map_data();
void draw_func();

int main(int argc, char **argv)
{
   
	// 1. ROS init //
	ros::init(argc, argv, "map_reader");
    std::string port_number = argv[1];
    int_port_num = atoi(port_number.c_str());
    
    //static std::unique_ptr<ros::NodeHandle> map_handler;
    //static std::unique_ptr<ros::NodeHandle> mode_handler;
    

	// 2. map load setting //
	flag_change(file_path_map_load, 0); // 1 : 맵을 로드한다, 0 : 새로 그린다. //

	while ( true )
	{
		// 3. rotation_and_move.cpp 에서 보내는 100 메세지를 수신할때까지 대기한다. //
		wait_control_tower();

		// 4. google cartographer에서 map 데이터를 수신한다. //
		wait_cartographer_map_data();

		// 12. 드로잉을 시작한다. //
		draw_func();
	}
	return 0;
}




// 플래그를 변환하는 함수 //
void flag_change( std::string file_path, int flag_value )
{
        std::ofstream file_open(file_path);
        while ( ros::ok() )
        {
                if( file_open.is_open() )
                {
                        file_open << flag_value << std::endl;
                        file_open.close();
                        break;
                }
        }
}

// 플래그를 불러오는 함수 //
int mode_or_flag_read( std::string file_path )
{
        std::ifstream file_open(file_path);
        std::string temp_string;
        int map_load_flag = 0;
        while ( ros::ok() )
        {
                if( file_open.is_open() )
                {
                        file_open >> temp_string;
                        map_load_flag = atoi(temp_string.c_str());
                        file_open.close();
                        break;
                }
        }
        return map_load_flag;
}

// 전체 사이즈를 정사각형으로 바꾸고 //
// map_square_padding에 2를 곱해서 전체 사이즈에 더했기 때문에 //
// map_square_padding만큼 상하좌우로 패딩을 된다. //
int add_padding(cv::Mat resizing_mat)
{
	if ( resizing_mat.rows >= resizing_mat.cols )
	{
		return int(resizing_mat.rows)+map_square_padding*2;
	}
	else
	{
		return int(resizing_mat.cols)+map_square_padding*2;
	}
}


void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 6. mat을 불러올지, 새로 그릴지 판단한다. 1이면 불러오고 0이면 새로 그린다.//
	int map_load_flag = mode_or_flag_read(file_path_map_load);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cv::Mat for_gird_mat;

	if ( map_load_flag == 1 )
	{
		std::cout << "map load" << std::endl;

	}
	else if ( map_load_flag == 0 )
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_1. Cartographer에서 보낸 맵정보 확인 //
		std_msgs::Header header = msg->header;
		nav_msgs::MapMetaData info = msg->info;
		// rviz의 좌측 하단이 (0,0)이다. //
		ROS_INFO("Got map %d %d", info.width, info.height);
		ROS_INFO("Map Origin x %f", info.origin.position.x);
		ROS_INFO("Map Origin y %f", info.origin.position.y);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_2. 맵의 metadata 데이터 획득 //
		std::vector<signed char> data = msg->data;
		// rows,cols으로 변환 //
		cv::Mat meta_data_resize = cv::Mat(data).reshape(1,info.height);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_3. opencv에서 활용가능한 데이터로 변환 //
		cv::Mat meta_to_opencv;
		meta_data_resize.convertTo(meta_to_opencv,CV_8UC1);

		// 원본 맵을 정사각형으로 만들고 상하좌우 map_square_padding만큼 추가하기 위한 함수. //
		int resize_square_value = add_padding(meta_to_opencv);
		cv::Mat original(resize_square_value, resize_square_value, CV_8UC1, cv::Scalar(0));

		// 원본의 자료를 패딩했기때문에 i+map_square_padding, j+map_square_padding 위치에서부터 복사한다. //
		for (int i=0; i<meta_to_opencv.rows; i++) // 행
			for (int j=0; j<meta_to_opencv.cols; j++) // 열
				original.at<unsigned char>(i+map_square_padding,j+map_square_padding) = meta_to_opencv.at<unsigned char>(i,j);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_4. 벽으로 가정한 데이터를 상하좌우 5px씩 확장 //
		cv::Mat wall_padding_mat(original.size(),original.type(),cv::Scalar(0));
		for (int i=0; i<original.rows; i++) // 행
			for (int j=0; j<original.cols; j++) // 열
				if ( int(original.at<unsigned char>(i,j)) > 80 )
					for ( int k=(-wall_padding/2); k<=(wall_padding/2); k++ )
						for ( int l=(-wall_padding/2); l<=(wall_padding/2); l++ )
						{
							//std::cout << "here 2" << std::endl;
							if ( (i+k)<0 || (i+k)>=original.rows || (j+l)<0 || (j+l)>=original.cols ) {}
							else { wall_padding_mat.at<unsigned char>((i+k),(j+l))=255; }
						}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_5. 외부는 하얀색 내부는 검은색으로 만들기 위하여 최외곽 경계를 찾아낸다. //
		cv::Mat canny_temp;
		cv::Canny(wall_padding_mat, canny_temp, 100, 100*3, 3);
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(canny_temp, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

		/*
		cv::Mat show_contour;
		cv::cvtColor(wall_padding_mat, show_contour, cv::COLOR_GRAY2BGR);
		for ( int i=0; i<int(contours.size()); i++)
		{
			cv::drawContours(show_contour, contours, i, cv::Scalar(255,0,0),2,8,hierarchy,0,cv::Point());
		}
		cv::imshow("show_contour", show_contour);
		//std::cout << contours[0] << std::endl;
		//std::cout << contours[0][0] << std::endl;
		//std::cout << contours[0][0].x << std::endl;
		//std::cout << contours[0][0].y << std::endl;
		//std::cout << int(contours.size()) << std::endl;
		//std::cout << int(contours[0].size()) << std::endl;
		*/
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_6. 최외곽으로부터 내부를 검은색으로 만든다. //
		cv::Mat back_ground_white(wall_padding_mat.size(), wall_padding_mat.type(), cv::Scalar(255));
		cv::fillPoly(back_ground_white, contours, cv::Scalar(0));
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_7. 기존 매트릭스와 합친다. //
		wall_padding_mat = wall_padding_mat + back_ground_white;
		// 최외곽이였던 부분도 채워야 하므로 그려준다. //
		for ( int i=0; i<int(contours.size()); i++)
		{
			cv::drawContours(wall_padding_mat, contours, i, cv::Scalar(255),2,8,hierarchy,0,cv::Point());
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_8. metadata의 값은 y가 반전되어 있으므로 Mat을 x축에 대하여 회전시킨다.
		cv::flip(wall_padding_mat, wall_padding_mat, 0);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_9. metadata에서 넘어오는 map(0,0)의 정보는 //
		// rviz의 좌측 하단을 -x,-y로 표시한다. //
		// m단위이므로 100을 곱하고 2cm당 1px 이므로 2로 나눠준다. //
		// 패딩한만큼 위치를 옮겨준다. //

		// 현재 flip된 상태를 고려해서 map(0,0)을 Mat(i,j)로 표현한다. //
		map_origin_x = (-info.origin.position.x*100.0/2.0) + map_square_padding ;
		map_origin_y = wall_padding_mat.rows - (-info.origin.position.y*100.0/2.0+map_square_padding) ;
		std::cout << "map x(i) : " << map_origin_x << std::endl;
		std::cout << "map y(j) : " << map_origin_y << std::endl;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 6_10. 색상 표현을 위해 3채널 Mat을 만든다. //

		/*
		// try 1 : 실패 //
		cv::Mat in[] = {wall_padding_mat, wall_padding_mat, wall_padding_mat};
		merge(in, 3, color_map);
		i_want_to_see = color_map.clone();
		*/

		/*
		// try 2 : 실패 //
		wall_padding_mat.convertTo(color_map,CV_8UC3);
		i_want_to_see = color_map.clone();
		*/

		// try 3 : 성공 //
		cv::Mat color_map(wall_padding_mat.rows, wall_padding_mat.cols, CV_8UC3, cv::Scalar(0));
		int color_value = 0;
		for (int i=0; i<wall_padding_mat.rows; i++) // 행
			for (int j=0; j<wall_padding_mat.cols; j++) // 열
				{
					color_value = wall_padding_mat.at<unsigned char>(i,j);
					color_map.at<cv::Vec3b>(i,j) = cv::Vec3b(color_value,color_value,color_value);
				}

		i_want_to_see = color_map.clone();
        for_gird_mat = wall_padding_mat.clone();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////
		// 6_11. 다음 진행부터 맵을 새로 그리지 않도록 세팅한다. //
		flag_change( file_path_map_load, 1 );
		/////////////////////////////////////////////////

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 7. google cartographer tf setting //
	tf::TransformListener tfl;
	tf::StampedTransform my_test_transform;

	std::string start = std::string("/map"); 
	std::string move = std::string("/base_footprint");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	while ( ros::ok() )
	{
		try
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 8. google cartographer에서 tf 데이터를 수신한다. //
			tfl.waitForTransform(start, move, ros::Time(), ros::Duration(1.0));
			tfl.lookupTransform(start, move, ros::Time(), my_test_transform);
			tf::Vector3 Coordinate_3D = my_test_transform.getOrigin();
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 9. nano위치를 Mat(i,j)로 표현한다. //
			// Coordinate_3D는 map의(0,0)으로부터의 거리를 알려준다. //
			int nano_origin_x = map_origin_x + Coordinate_3D.getX()*100.0/2.0;
			int nano_origin_y = map_origin_y - Coordinate_3D.getY()*100.0/2.0;
			std::cout << "nano x(i) : " << nano_origin_x <<std::endl;
			std::cout << "nano y(j) : " << nano_origin_y <<std::endl;
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 10. 경로 탐색 init //
			PathFinder path;

			// Mat에서 현재 nano의 위치(i,j) 설정 //
			Position start(nano_origin_x,nano_origin_y);

			// grid좌표를 담을 공간 선언 //
			std::list<Position> pathList;

			// grid 간격 선언 (px단위) //
			//path.setMoveInterval(5); // default : 5px = 10cm

			// grid 포인트 작성 //
			pathList = path.findCoveragePath(start, for_gird_mat, 0); // 1 : 그림표시, 0 : 표시안함 //

			clean_point.data.clear();
			for (auto it = pathList.begin(); it != pathList.end(); ++it)
			{
				printf("[%d, %d]\n", (*it).x, (*it).y);
				clean_point.data.push_back( (*it).x );
				clean_point.data.push_back( (*it).y );
			}
			// map의 (0,0) 데이터 저장 //
			clean_point.data.push_back(map_origin_x);
			clean_point.data.push_back(map_origin_y);


			for ( int i=0; i< clean_point.data.size(); i+=2 )
			{
				std::cout << "pub [" << clean_point.data[i] << ", "
				<< clean_point.data[i+1] << "]" <<std::endl;
			}
            
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            //cv::circle(i_want_to_see, cv::Point(nano_origin_x, nano_origin_y), 10, cv::Scalar(255, 0, 0), -1);
			//cv::imshow("check_window", i_want_to_see);
			//cv::waitKey(0);
			break;
		}
		catch(tf2::LookupException& e)
		{
			printf("get grid point fail\n");
			return;
		}
	}

}

// control_tower의 명령을 대기하는 함수 //
void wait_control_tower()
{
	ros::NodeHandle mode_handler;
	while ( ros::ok() )
	{
		std_msgs::Int32::ConstPtr move_ready_flag = ros::topic::waitForMessage<std_msgs::Int32>("move_ready_topic", mode_handler, ros::Duration(1.0));
		if(move_ready_flag)
		{
			int move_ready = move_ready_flag->data;
			if ( move_ready == 100 || move_ready == 110 )
			{
                std::cout << "[clean map] mode is : " << move_ready << std::endl;
				break;
			}
		}
        else
        {
			std::cout << "wait drawing map" <<std::endl;
        }
	}
}

// cartographer의 map 데이터를 대기하는 함수 //
void wait_cartographer_map_data()
{
    ros::NodeHandle map_handler;
	ros::Publisher point_pub = map_handler.advertise<std_msgs::Int32MultiArray>("clean_point_topic", 1);
	while ( ros::ok() )
	{
		nav_msgs::OccupancyGrid::ConstPtr grid = ros::topic::waitForMessage<nav_msgs::OccupancyGrid>("/map", map_handler, ros::Duration(1.0));
		if ( grid )
		{

			// 5. mapCallback 함수를 호출한다. //
			mapCallback(grid);
            
            // 11. 청소할 point를 Mat의 (i,j)형태로 publish한다. //
            std::chrono::system_clock::time_point time_start;
            std::chrono::duration<double> limit_sec;
            time_start = std::chrono::system_clock::now();
            limit_sec = std::chrono::system_clock::now() - time_start;
            while ( limit_sec.count() < 3.0 )
            {
                point_pub.publish(clean_point);
                limit_sec = std::chrono::system_clock::now() - time_start;
            }

            std::cout << "[clean map] grid point send ok" << std::endl;
			break;
		}
		else
		{
			std::cout << "wait drawing map data" <<std::endl;
		}
	}
}

void draw_func()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 13. delay에 사용될 변수 선언 //
	std::chrono::system_clock::time_point time_start;
	std::chrono::duration<double> limit_sec;
	time_start = std::chrono::system_clock::now();
	limit_sec = std::chrono::system_clock::now() - time_start;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 14. google cartographer tf setting //
	tf::TransformListener tfl;
	tf::StampedTransform my_test_transform;

	std::string start = std::string("/map"); 
	std::string move = std::string("/base_footprint");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 15. 드로잉 영역 변수 선언 //
	// old_and_new_xy[0] = old_x //
	// old_and_new_xy[1] = old_y //
	// old_and_new_xy[2] = new_x //
	// old_and_new_xy[3] = new_y //
	int old_and_new_xy[4] = {0, };
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //MJPEGWriter test(7779);
    MJPEGWriter test(int_port_num);
    test.start();
    
	while ( ros::ok() )
	{
		try
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 16. map의 모든 포인트를 돌았는지 file_path_map_move로 확인한다. //
			// 모든 포인트를 돌았으면 맵을 새로그릴 준비를 하고 드로잉 while을 break로 벗어나고 //
			// rotation_and_move.cpp 에서 보내는 100 메세지를 기다린다. //

			int map_move_flag = mode_or_flag_read(file_path_map_move);
			if ( map_move_flag == 1 )
			{
				std::cout << "not yet done, nano will move" << std::endl;
			}
			else if ( map_move_flag == 0 )
			{
				std::cout << "map move done" << std::endl;
				flag_change(file_path_map_load, 0);
				break;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 17. 모드를 확인한다. //
			// 모드가 변경되었으면 드로잉 영역을 break로 벗어나고 //
			// rotation_and_move.cpp 에서 보내는 100 메세지를 기다린다. //
			int mode_value = mode_or_flag_read( file_path_mode );

			if ( mode_value == 300 || mode_value == 310 )
			{
				std::cout << "mode is : " << mode_value << std::endl;
				std::cout << "mode change" << std::endl;
				break;
			}
			else if ( mode_value == 990 )
			{
				std::cout << "초기화" << std::endl;
				flag_change(file_path_map_load, 0);
				break;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 18. Mat에서 nano의 현재위치(i,j) 기록 //
			tfl.waitForTransform(start, move, ros::Time(), ros::Duration(1.0));
			tfl.lookupTransform(start, move, ros::Time(), my_test_transform);
			tf::Vector3 Coordinate_3D = my_test_transform.getOrigin();
			old_and_new_xy[2] = map_origin_x + Coordinate_3D.getX()*100.0/2.0;
			old_and_new_xy[3] = map_origin_y - Coordinate_3D.getY()*100.0/2.0;
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 19. nano의 현재위치를 중심으로 7x7 채우기
			// 7x7 = 중심으로부터 위로 3칸, 아래로 3칸
			// move_fill_area = 6 입력하면 된다.
			// cols = 열 = x, rows = 행 = y
			// 검은색(0,0,0)일때만 색칠한다. 
			for ( int k = (old_and_new_xy[2]-move_fill_area/2); k <= (old_and_new_xy[2]+move_fill_area/2); k++ ) // 열 = x
			{
				for ( int l = (old_and_new_xy[3]-move_fill_area/2); l <= (old_and_new_xy[3]+move_fill_area/2); l++ ) // 행 = y
				{
					if ( k<0 || k>=i_want_to_see.rows || l<0 || l>=i_want_to_see.cols ) {}
					else
					{
						if (i_want_to_see.at<cv::Vec3b>(l,k) != cv::Vec3b(0, 0, 0)) {}
						else { i_want_to_see.at<cv::Vec3b>(l,k) = cv::Vec3b(128,128,128); }
					}
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 20. 2초 마다 라인을 그린다. //
			if ( limit_sec.count() > 2.0 )
			{
				if ( old_and_new_xy[0] == 0 && old_and_new_xy[1] == 0 )
				{
					old_and_new_xy[0] = old_and_new_xy[2];
					old_and_new_xy[1] = old_and_new_xy[3];
				}

				cv::line(i_want_to_see,
					cv::Point( old_and_new_xy[0], old_and_new_xy[1] ),
					cv::Point( old_and_new_xy[2], old_and_new_xy[3] ),
					cv::Scalar(0,0,255), 2);

				old_and_new_xy[0] = old_and_new_xy[2];
				old_and_new_xy[1] = old_and_new_xy[3];

				time_start = std::chrono::system_clock::now();
				limit_sec = std::chrono::system_clock::now() - time_start;
			}
			else
			{
				limit_sec = std::chrono::system_clock::now() - time_start;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            test.write(i_want_to_see);
            
			//cv::imshow("i_want_to_see", i_want_to_see);
			//cv::waitKey(100);

		}
		catch(tf2::LookupException& e)
		{
			time_start = std::chrono::system_clock::now();
			limit_sec = std::chrono::system_clock::now() - time_start;
			printf("tf fail\n");
		}
	}
    
    test.stop();

}



