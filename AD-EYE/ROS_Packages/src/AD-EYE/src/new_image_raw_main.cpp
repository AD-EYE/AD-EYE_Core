#include "new_image_raw.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "visualize_raw");
  VisualizeRaw app;
  ros::spin();

  return 0;
}