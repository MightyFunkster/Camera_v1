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

#ifndef CAMERA_H
#define CAMERA_H

#include "Thread.h"

#include <stdio.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <deque>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types_c.h>

using cv::Mat;
using cv::VideoCapture;

class Camera : public Thread
{
    public:
        /**
         * 
         * @author Dr. Anthony J. Portelli
         */
        Camera(uint8_t camID, uint16_t frameWidth, uint16_t frameHeight);
        
        /**
         * 
         * @author Dr. Anthony J. Portelli
         */
        virtual ~Camera();
        
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
        
    public:
    
        bool IsCameraOpen();
        bool NewDataAvailable(){ return (newDataAvailable); }

        int ImageWidth(){ return (imageWidth); }
        int ImageHeight(){ return (imageHeight); }
        
        int MemoryAllocationSize(){ return imageWidth * imageHeight * imageChannels; }
        
        Mat* GetImageData(long int* length);
        Mat GetImageData();
        
    protected:
        pthread_mutex_t dataLock;
                
        VideoCapture* camera;
        
        uint16_t imageWidth;
        uint16_t imageHeight;
        uint8_t imageChannels;
        uint8_t camID;
        
        bool newDataAvailable;
        
        double frameFormat;
        
        Mat* imageData;        
        
        uint16_t frameWidth;
        uint16_t frameHeight;
};

#endif /* CAMERA_H */

