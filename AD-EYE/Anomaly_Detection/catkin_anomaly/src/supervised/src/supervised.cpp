#include <iostream>
#include <cmath>
#include <fdeep/fdeep.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/core/>
// #include "ssim.h"
#include <typeinfo>
#include <vector>
// #include <iterator>
#include <experimental/filesystem>
#include <exception>
// using namespace stdext;
namespace fs = std::experimental::filesystem;
int main() {

    std::vector<cv::String> fa;
    std::vector<cv::String> fc;
    
    std::string test_image_folder_path_anomalous = "/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/dataset/anomaly_images/*.jpg";
    std::string test_image_folder_path_clean = "/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/dataset/images/*.jpg";
    
    cv::glob(test_image_folder_path_anomalous, fa, false);
    cv::glob(test_image_folder_path_clean, fc, false);
    // std::cout << fn[0] << std::endl;
    std::vector<cv::Mat> images_input;
    std::vector<cv::Mat> images_output;
    std::vector<cv::String> random_clean_array;
    std::vector<cv::String> random_anomalous_array;
    int no_test_images = 5;
    for (int i=0;i<=no_test_images;i++)
    {
        int random_clean = rand() % fc.size();
        int random_anomalous = rand() % fa.size();

        // std::cout <<  fc[random_clean] <<std::endl;
        random_clean_array.push_back(fc[random_clean]);
        random_anomalous_array.push_back(fa[random_anomalous]);
    }
    // std::cout<<random_clean_array[0]<<std::endl;
    // std::cout<<random_anomalous_array[0]<<std::endl;
    // std::vector<float> losses;
    size_t count = random_clean_array.size();
    const auto model = fdeep::load_model("/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/models/supervised_model/supervised_model.json");
    // std::cout << count<<std::endl;
    for (size_t i=0; i<count;i++)
        {
            
            // std::cout << i <<std::endl;
            const cv::Mat image_clean = cv::imread(fc[i]);
            const cv::Mat image_anomalous = cv::imread(fa[i]);
            cv::Mat resizedImg_clean;
            cv::resize(image_clean, resizedImg_clean, cv::Size(128, 128));
            // imshow("Display window", resi)
            
            const auto input_clean = fdeep::tensor_from_bytes(resizedImg_clean.ptr(), 
            static_cast <std::size_t>(resizedImg_clean.rows), 
            static_cast <std::size_t>(resizedImg_clean.cols), 
            static_cast <std::size_t>(resizedImg_clean.channels()), 
            0.0f, 1.0f);
            
            
            const auto output_clean = model.predict ({input_clean});


            cv::Mat resizedImg_anomalous;
            cv::resize(image_anomalous, resizedImg_anomalous, cv::Size(128, 128));
            // imshow("Display window", resi)
            
            const auto input_anomalous = fdeep::tensor_from_bytes(resizedImg_anomalous.ptr(), 
            static_cast <std::size_t>(resizedImg_anomalous.rows), 
            static_cast <std::size_t>(resizedImg_anomalous.cols), 
            static_cast <std::size_t>(resizedImg_anomalous.channels()), 
            0.0f, 1.0f);
            
            
            const auto output_anomalous = model.predict ({input_anomalous});
            // std::cout << "Predicted clean: "<<fdeep::show_tensors(output_clean)<<std::endl;
            // std::cout << "Predicted anomalous: "<<fdeep::show_tensors(output_anomalous)<<std::endl;


            std::vector<float> clean = output_clean.front().to_vector();
            std::vector<float> anomalous = output_anomalous.front().to_vector();
            std::cout << std::endl<<"Predicted clean: "<<round(clean[0])<<std::endl;
            std::cout << "Predicted anomalous: "<<round(anomalous[0])<<std::endl;
            
            // const auto output_tensor = fdeep::tensor_from_bytes(output)
            // std::cout << output.front().shape().depth_ <<std::endl;
            // std::cout << fdeep::show_tensor_shape(output.front().shape());
            // assert(output_clean.front().shape().depth_ == 1 || output_clean.front().shape().depth_ == 3);
            // const int mat_type = output_clean.front().shape().depth_ == 1? CV_8UC1 : CV_8UC3;
            // const cv::Mat image_reconstructed(cv::Size(output_clean.front().shape().width_, output_clean.front().shape().height_), mat_type);
            // fdeep::tensor_into_bytes(output_clean.front(), 
            //     image_reconstructed.data, 
            //     image_reconstructed.rows * image_reconstructed.cols * image_reconstructed.channels());

            // images_input.push_back(resizedImg);
            // images_output.push_back(image_reconstructed);


            // std::cout << calcSSIM(resizedImg, image_reconstructed)<<std::endl;

            // losses.push_back(1 - calcSSIM(resizedImg, image_reconstructed));

            // imshow("image_input", images_input[i]);
            // imshow("image_output", images_output[i]);
            // std::cout <<"SSIM loss: "<<losses[i]<<std::endl;
            // cv::waitKey();
            // if (i == 5)
            //     break;
        }
    // int show_images = 5;
    // for (int i=0;i<=show_images;i++)
    //     {
    //         imshow("image_input", images_input[i]);
    //         imshow("image_output", images_output[i]);
    //         std::cout <<"SSIM loss: "<<losses[i]<<std::endl;
    //         cv::waitKey();
    //     }



    return 0;
}