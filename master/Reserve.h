// Pract.cpp : Defines the entry point for the application.
//

#include "Pract.h"

using namespace std;

struct collec
{
	std::string imagePath = "C:/Users/Temporary/Desktop/IoT_WT/Industrial Immersion/ImageDataset/";
	std::string readinfo = "C:/Users/Temporary/Desktop/IoT_WT/Industrial Immersion/info.txt";
	torch::Tensor s = torch::randn(3);
};

static collec nec;
using melaku = std::vector<std::pair<std::string, long>>;

std::vector<melaku> readData()
{
	std::cout << "The torch is " << nec.s << std::endl;
	melaku train;
	std::ifstream stream(nec.readinfo);
	assert(stream.is_open());

	long label;
	std::string path, type;

	while (true)
	{
		stream >> path >> label >> type;

		if (type == "train")
		{
			train.push_back(std::make_pair(path, label));
			std::cout << "Train print " << train;
		}
		else
			assert(false);
	}
	std::random_shuffle(train.begin(), train.end());
	//using std::shuffle;

	//return train;
}

using namespace cv;
int main()
{
	melaku train;
	long label;
	std::string path, type;
	std::ifstream stream(nec.readinfo);
	std::cout << "in" << endl;
	assert(stream.is_open());
	std::cout << "out successfully" << endl;
	stream >> path >> label >> type;
	//auto data = readInfo();
	//std::vector<melaku> data = train.push_back(std::make_pair(path, label));
	auto data = std::make_pair(path, label);
	std::string mainPath = nec.imagePath + data.first;
	auto mat = cv::imread(mainPath);
	//cv::imshow("window",mat);
	//cv::waitKey(0);
	assert(!mat.empty());
	std::cout << "path " << mainPath << std::endl;

	/*std::cout << "label " << label << " " << "type " << type << endl;
	std::cout << "Data " << data << endl;*/

	return 0;
}
#pragma once
