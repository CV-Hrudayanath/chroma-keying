#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 3)
    {
     cout <<" Usage: ./chroma backimage chromavideo" << endl;
     return -1;
    }

//  VideoCapture capture1(argv[1]); // video on video
    VideoCapture capture(argv[2]);
    string window_name = "chroma keyed video";
    namedWindow(window_name, WINDOW_KEEPRATIO);
    Mat image;
    Mat backimage;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR); // video on image
	
    Mat src;
    capture >> src;
    bool isColor = (src.type() == CV_8UC3);
	
    VideoWriter writer;
    int codec = CV_FOURCC('M', 'J', 'P', 'G');  
    double fps = 10.0;                          
    string filename = "./live.avi";
    writer.open(filename, codec, fps, src.size(), isColor);


    for (;;)
    {
    	  //capture1 >> image;
            capture >> backimage;
            if (backimage.empty())
            {
                break;
            }
            for(int y=0;y<image.rows;y++)
    	    {
	       	 	for(int x=0;x<image.cols;x++)
	        	{
					Vec3b color = image.at<Vec3b>(Point(x,y));
					Vec3b bcolor = backimage.at<Vec3b>(Point(x,y));
					if(bcolor[1] > 150)
					{
						backimage.at<Vec3b>(Point(x,y)) = color;
		    			}
		    	}
	    }
            imshow(window_name, backimage);
            writer.write(backimage);
            char key = (char)waitKey(20); //delay N millis
	    if(key == 27)
	    {
		break;
	    }
    }
    return 0;
}
