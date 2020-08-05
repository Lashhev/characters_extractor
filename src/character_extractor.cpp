#include "character_extractor.hpp"

using namespace cv;
using namespace std;

void CharacterSampleExtractor::process_image(const string& image_file, 
                                            const string& dataset_file)
{
    Mat large = imread(image_file);
    Mat small, bw, bw2;
    cvtColor(large, small, COLOR_BGR2GRAY);
    imshow("Origin", small);
    threshold(small, bw, 254, 255.0,THRESH_BINARY);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(bw, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    bw.copyTo(bw2);
    // filter contours
    for(int idx = 1; idx >= 0; idx = hierarchy[idx][0])
    {
        Rect rect = boundingRect(contours[idx]);
        Rect rect2 = Rect(rect.x-3, rect.y-3, rect.width+6, rect.height+6);
        Mat sample1 = bw2(rect);
        rect2 = check_if_Rect_fits(rect2, bw);
        Mat sample2 = bw2(rect2);
        if ((rect.height > 8 && rect.width > 8))
        {
            rectangle(bw, rect2, Scalar(0, 255, 0), 2);
            imshow("Rect", sample2);
            imshow("Image", bw);
            ask_what_is_it(dataset_file, sample1, sample2);
        }
    }
}

void CharacterSampleExtractor::save_sample(const string& dataset_file, 
                                            char character, 
                                            const Mat& sample)
{
    ofstream file;
    file.open(dataset_file, std::ios::app);
    vector<uchar> v;
    Mat image = sample/255;
    resize(image, image, sample_size);
    v.assign(image.data, image.data + image.size().width*image.size().height);
    file << int(character) << ", ";
    write_vector_to_file(file, v);
    file.close(); 
}

bool CharacterSampleExtractor::ask_what_is_it(const string& dataset_file, 
                                                const Mat& sample1,
                                                const Mat& sample2)
{
    cout << "Please input this symbol.\n";
    char key = waitKey(0);
    if(find(literals.begin(), literals.end(), key) != literals.end())
    {
        cout << "This symbol is recognized\nWriting it in file.\n";
        save_sample(dataset_file, key, sample1);
        save_sample(dataset_file, key, sample2);
        return true;
    }
    if(key=='27')
        cout << "Skipping...\n";
    cout << "This symbol wasn't recognized\n";
    return false;
}

void CharacterSampleExtractor::process_dir(const string& image_dir, 
                        const string& dataset_file)

{
    vector<string> image_files;
    glob_files_in_dir(image_dir, image_files);
    for(auto image_file:image_files)
    {
        process_image(image_file, dataset_file);
    }
}

Rect CharacterSampleExtractor::check_if_Rect_fits(Rect region, const Mat& image)
{
    auto size = image.size();
    if(region.x < 0)
        region.x = 0;

    if(region.x > size.width)
        region.x = size.width;

    if(region.y < 0)
        region.y = 0;
    
    if(region.y > size.height)
        region.y = size.height;

    if(region.x + region.width > size.width)
        region.width = size.width - region.x;

    if(region.y + region.height > size.height)
        region.height = size.height - region.y;
    return region;
}

void CharacterSampleExtractor::write_vector_to_file(ofstream& file, const vector<uchar> &v)
{
    for(size_t i=0; i < v.size(); i++)
    {
        file << int(v[i]);
        if(i < v.size() - 1)
            file << ", ";
        else
            file << "\n";
    }
}
