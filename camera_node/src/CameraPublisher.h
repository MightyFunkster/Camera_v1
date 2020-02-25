/* 
 * File:   Camera.h
 * Author: Dr. Anthony J. Portelli
 * 
 * This class contains the main apparatus by which we can acquire images from
 * the camera. The data array is populated and a flag is set, this is done as
 * fast as possible and consuming classes process the data
 *
 * Created on 05 November 2016, 01:44
 */

#ifndef CAMERAPUBLISHER_H
#define CAMERAPUBLISHER_H

#include "Camera.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

using cv::Mat;
using cv::VideoCapture;

using namespace cv;

class CameraPublisher : public Camera
{
    public:
        /**
         * 
         * @author Dr. Anthony J. Portelli
         */
        CameraPublisher(std::string nodeName, ros::NodeHandle* nh, uint8_t camID, uint16_t frameWidth, uint16_t frameHeight);
        
        /**
         * 
         * @author Dr. Anthony J. Portelli
         */
        virtual ~CameraPublisher();
        
        /**
         * 
         * @author Dr. Anthony J. Portelli 
         * @return 
         */
        virtual bool Connect();
        
        /**
         * 
         * @author Dr. Anthony J. Portelli
         * @return 
         */
        virtual bool Execute();
        
    private:
        ros::NodeHandle* nh; 
        image_transport::Publisher pub;
        image_transport::ImageTransport* transporter;
        
        std::string nodeName;
        
};
#endif /* CAMERAPUBLISHER_H */

