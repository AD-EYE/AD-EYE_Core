//
// (c)Copyright 2019 by Siemens Industry Software and Services B.V.
// All rights reserved.
//
// Simcenter Prescan(r) has been developed at Siemens Industry Software and
// Services B.V.
//
// This document contains proprietary and confidential information of Siemens.
// The contents of this document may not be disclosed to third parties, copied
// or duplicated in any form, in whole or in part, without prior written
// permission of Siemens.
//
// The terms and conditions governing the license of Simcenter Prescan(r)
// software consist solely of those set forth in the written contracts between
// Siemens or Siemens authorized third parties and its customers. The software
// may only be used or copied in accordance with the terms of these contracts.
//

#ifndef PROXIMITY_DEMO_UTILS_H
#define PROXIMITY_DEMO_UTILS_H


#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void writeTextMessage(cv::Mat* image, const std::string& string, const cv::Point& point)
{
  cv::putText(*image, string, point, cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 0, 0), 1, cv::LineTypes::LINE_AA);
}

cv::Mat convertToOpenCVImage(prescan::sim::CameraSensorUnit::Image img)
{
  assert(img.format() == prescan_enum_camerasensor_image_format_t::CameraSensorImageFormatSimulinkColorbuffersU8);
  std::vector<prescan::sim::Buffer> buffers = img.buffers();

  prescan::sim::Buffer redBuffer = buffers[0];
  prescan::sim::Buffer greenBuffer = buffers[1];
  prescan::sim::Buffer blueBuffer = buffers[2];

  auto resolution = img.resolution();
  cv::Mat image = cv::Mat::zeros(resolution.y, resolution.x, CV_8UC3);

  for (unsigned int x = 0, k = 0; x < resolution.x; x++)
  {
    for (unsigned int y = 0; y < resolution.y; y++)
    {
      image.at<cv::Vec3b>(y, x) = cv::Vec3b(
        blueBuffer.data<uint8_t>()[k],
        greenBuffer.data<uint8_t>()[k],
        redBuffer.data<uint8_t>()[k]);
      ++k;
    }
  }

  return image;
}

# endif
