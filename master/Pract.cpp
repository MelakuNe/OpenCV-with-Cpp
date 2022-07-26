#include "Pract.h"
using namespace std;
using namespace cv;


struct things
{
	std::string imagePath = "../TestImage/8.jpg";
	std::string imagePath2 = "../TestIMage/flower.jpg";
	std::string newImage = "../TestImage/ima/";
};

static things thing;

void screenSize(int &width, int &height)
{
	RECT desktop;
	const HWND hdesktop = GetDesktopWindow();
	GetWindowRect(hdesktop, &desktop);
	width = desktop.right;
	height = desktop.bottom;
}

int main()
{
	auto image = cv::imread(thing.imagePath2);
	assert(!image.empty());

	cv::imshow("Original",image);
	int img_width = 0, img_height = 0;
	screenSize(img_width, img_height);
	//cv::resize(image, image, Size(img_width,img_height), INTER_CUBIC);
	//cv::imshow("Resized", image);
	/*std::cout << "width " << image.size().width << endl;
	std::cout << "height " << image.size().height << endl;
	std::cout << "Channels " << image.channels() << endl;*/
	
	// Image filtering using convolution in OpenCV
	
	//Identity, which has no effect on the original image
	Mat kernel = (Mat_<int>(3, 3) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	Mat identity;
	cv::filter2D(image, identity, -1, kernel, Point(-1, -1), 0, 4);
	cv::imshow("Identity", identity);

	// Blurring an image
	Mat kernel1 = Mat::ones(5, 5, CV_64F); //matrix with all ones
	kernel1 = kernel1 / 25; //normalizing each element

	Mat blur;
	//cv::filter2D(image, blur, -1, kernel1, Point(-1, 1), 0, 4);
	cv::blur(image, blur, Size(10, 10));  // blurring using built in function
	cv::imshow("Blurr", blur);
	// Gaussian blur
	Mat gauBlur;
	cv::GaussianBlur(image, gauBlur, Size(11, 11), 0, 0,1);
	//cv::imshow("Gaussian blurr", gauBlur);
	
	// sharpening an image using custom 2D-convolution kernels
	Mat sharpImg;
	Mat kernel3 = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(image, sharpImg, -1, kernel3, Point(-1, -1), 0, BORDER_DEFAULT);
	cv::imshow("Sharpenned", sharpImg);

	// bilateral filtering 
	Mat bilterImg;
	cv::bilateralFilter(image, bilterImg, 20, 100, 100);
	cv::imshow("Bilateral filtered", bilterImg);

	std::string resize = "resize3.jpg";
	std::string path = thing.newImage + resize;
	cv::imwrite(path, image);
	cv::waitKey();
	cv::destroyAllWindows();
}
