#pragma once
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "functions_impl.hpp"

class CharacterSampleExtractor
{
public:
    CharacterSampleExtractor(size_t sample_weight=10, size_t sample_height=10):sample_size(sample_weight, sample_height)
    {

    }
    void process_image(const std::string& image_file, 
                        const std::string& dataset_file);
    void process_dir(const std::string& image_dir, 
                        const std::string& dataset_file);
    void save_sample(const std::string& dataset_file, 
                        char character, 
                        const cv::Mat& sample);
                    
    bool ask_what_is_it(const std::string& dataset_file, 
                        const cv::Mat& sample1,
                        const cv::Mat& sample2);
private:
    cv::Rect check_if_Rect_fits(cv::Rect region, const cv::Mat& image);
    void write_vector_to_file(std::ofstream& file, const std::vector<uchar> &v);
    const std::vector<char> literals = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                                   'I', 'J', 'K', 'L', 'M', 'N', 'O', 
                                   'P', 'Q', 'R', 'S', 'T', 'U', 'V', 
                                   'W', 'X', 'Y', 'Z', '0', '1', '2', 
                                   '3', '4', '5', '6', '7', '8', '9'};
    cv::Size sample_size;
};