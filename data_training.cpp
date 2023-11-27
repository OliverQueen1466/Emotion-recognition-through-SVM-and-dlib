#include<opencv2\opencv.hpp> 
#include<string>
#include<fstream>    
using namespace std;
using namespace cv;
using namespace cv::ml;


void read_data(float array[150][136], int begin, string list);
int main()
{//use the feature collected to train the network

	float array[150][136];

	read_data(array, 0, "Calm");
	read_data(array, 50, "Delight");
	read_data(array, 100, "Disgust");
	int face_label[150];
	for (int i = 0; i < 50; i++) {
		face_label[i] = 170;
		face_label[i+50] = 250;
		face_label[i + 100] = 300;
	}

	//	int label[4] = { 1, 2, 3, 4 };
	//	float train_data[4][2] = { { 31, 12 },{ 65, 220 },{ 440, 350 },{ 400, 400 } };
	Mat train_Mat(150, 136, CV_32FC1, array);//
	Mat label(150, 1, CV_32SC1, face_label);
	//init
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	svm->train(train_Mat, ROW_SAMPLE, label);
	svm->save("SVM_DATA.xml");
}

void read_data(float [150][136], int begin, string list) {
	fstream read_file;


	for (int i = 0; i < 50; i++) {
		read_file.open(list +"\\"+ to_string(i+1) + ".txt");
		for (int j = 0; j < 136; j++) {
			string read_info;
			read_file >> read_info;		
			array[i+begin][j] = atof(read_info.c_str());

		}
		read_file.close();//close the  file
	}

}