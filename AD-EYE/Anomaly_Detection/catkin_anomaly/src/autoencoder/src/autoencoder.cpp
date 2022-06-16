#include <iostream>
#include <fdeep/fdeep.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/core/>
#include "ssim.h"
#include <typeinfo>
#include <vector>
// #include <iterator>
#include <experimental/filesystem>
#include <exception>
// using namespace stdext;
// namespace fs = std::experimental::filesystem;
int main() {

    std::vector<cv::String> fn;
    
    std::string test_image_folder_path = "/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/dataset/anomaly_images/*.jpg";
    // std::string test_image_folder_path = "/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/dataset/images/*.jpg";
    
    cv::glob(test_image_folder_path, fn, false);
    // std::cout << fn[0] << std::endl;
    std::vector<cv::Mat> images_input;
    std::vector<cv::Mat> images_output;
    std::vector<float> losses;
    size_t count = fn.size();
    const auto model = fdeep::load_model("/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/models/autoencoder/autoencoder_sequential.json");
    std::cout << count<<std::endl;
    for (size_t i=0; i<count;i++)
        {
            
            std::cout << i <<std::endl;
            const cv::Mat image = cv::imread(fn[i], cv::IMREAD_GRAYSCALE);
            cv::Mat resizedImg;
            cv::resize(image, resizedImg, cv::Size(128, 128));
            // imshow("Display window", resi)
            
            const auto input = fdeep::tensor_from_bytes(resizedImg.ptr(), 
            static_cast <std::size_t>(resizedImg.rows), 
            static_cast <std::size_t>(resizedImg.cols), 
            static_cast <std::size_t>(resizedImg.channels()), 
            0.0f, 1.0f);
            
            // std::cout << "Before" <<std::endl;
            const auto output = model.predict ({input});


            assert(output.front().shape().depth_ == 1 || output.front().shape().depth_ == 3);
            const int mat_type = output.front().shape().depth_ == 1? CV_8UC1 : CV_8UC3;
            const cv::Mat image_reconstructed(cv::Size(output.front().shape().width_, output.front().shape().height_), mat_type);
            fdeep::tensor_into_bytes(output.front(), 
                image_reconstructed.data, 
                image_reconstructed.rows * image_reconstructed.cols * image_reconstructed.channels());

            images_input.push_back(resizedImg);
            images_output.push_back(image_reconstructed);
            losses.push_back(1 - calcSSIM(images_input[i], images_output[i]));

            // std::cout << calcSSIM(resizedImg, image_reconstructed)<<std::endl;

            

            imshow("image_input", images_input[i]);
            imshow("image_output", images_output[i]);
            std::cout <<"SSIM loss: "<<losses[i]<<std::endl;
            cv::waitKey();
            if (i == 0)
                break;
        }
    // int show_images = 5;
    // for (int i=0;i<=show_images;i++)
    //     {
    //         losses.push_back(1 - calcSSIM(images_input[i], images_output[i]));
    //         imshow("image_input", images_input[i]);
    //         imshow("image_output", images_output[i]);
    //         std::cout <<"SSIM loss: "<<losses[i]<<std::endl;
    //         cv::waitKey();
    //     }



    return 0;
}