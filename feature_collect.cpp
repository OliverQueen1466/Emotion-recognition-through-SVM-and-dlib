#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include<string>

using namespace dlib;
using namespace std;
void inputTXT(string name, string content, bool cover_flag);
int main()
{

	try
	{
		
		cv::VideoCapture cap(0);

		//image_window win;

		// Load face detection and pose estimation models.
		frontal_face_detector detector = get_frontal_face_detector();
		shape_predictor pose_model;
		deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
		std::vector<rectangle> faces2;
		// Grab and process frames until the main window is closed by the user.
		int file_name = 0;
		//	while (cv::waitKey(30) != 27)

	//	while (cv::waitKey(30) != 27){
		//	cv::VideoCapture cap("1.avi");
			if (!cap.isOpened())
		{
			cerr << "Unable to connect to camera" << endl;
			return 1;
		}

			int frames = cap.get(7);
		//	while (cv::waitKey(30) != 27 && --frames != 14)

			while (cv::waitKey(30) != 27)
			{
				// Grab a frame
				cv::Mat temp;
				cap >> temp;
				//	temp = cv::imread("1.bmp");
				cv_image<bgr_pixel> cimg(temp);
				// Detect faces 
				std::vector<rectangle> faces = detector(cimg);
				if (!faces.empty())faces2 = faces;
				// Find the pose of each face.
				std::vector<full_object_detection> shapes;
				if (faces.empty()) {

					//		for (unsigned long i = 0; i < faces2.size(); ++i)
							//	shapes.push_back(pose_model(cimg, faces2[i]));
				}
				else {
					for (unsigned long i = 0; i < faces.size(); ++i)
						shapes.push_back(pose_model(cimg, faces[i]));
				}
				if (!shapes.empty()) {
					cv::line(temp, cvPoint(faces[0].left(), faces[0].top()), cvPoint( faces[0].right(), faces[0].top()), cv::Scalar(255, 0, 0));
					cv::line(temp, cvPoint(faces[0].left(), faces[0].top()), cvPoint(faces[0].left(), faces[0].bottom()), cv::Scalar(255, 0, 0));

					
					file_name++;
					float cofficient =  -(faces[0].top() - faces[0].bottom()) / 300.0;
					cout << cofficient << endl;
					for (int i = 0; i < 68; i++) {
						circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
							putText(temp, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0), 1, 4);
					   //--------------Training data
							
					  	inputTXT((to_string(file_name)+".txt"), to_string((shapes[0].part(i).x()-faces[0].left())/ cofficient), 0);
					 	inputTXT((to_string(file_name) + ".txt"), to_string((shapes[0].part(i).y()- faces[0].top())/ cofficient), 0);
					//----------------------------------------------------------------------------
					}
			//		Drawarrow(temp, shapes[0].part(36).x(), shapes[0].part(48).x(), shapes[0].part(30).x(), shapes[0].part(45).x(), shapes[0].part(54).x(), shapes[0].part(36).y(), shapes[0].part(48).y(), shapes[0].part(30).y(), shapes[0].part(45).y(), shapes[0].part(54).y());
				}
				//Display it all on the screen
		//		cv::namedWindow("Dlibfeature_point", CV_WINDOW_NORMAL);
		//		cv::setWindowProperty("Dlibfeature_point", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
				imshow("Dlibfeature_point", temp);
				//	cv::waitKey(-1);
			}
		//}
		cv::destroyAllWindows();
	}
	catch (serialization_error& e)
	{
		cout << "You need dlib's default face landmarking model file to run this example." << endl;
		cout << "You can get it from the following URL: " << endl;
		cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
		cout << endl << e.what() << endl;
	}
	//catch (exception& e)
	//{
		//cout << e.what() << endl;
	//}
}
void inputTXT(string name, string content, bool cover_flag) {
	ofstream input(name, cover_flag ? ios::trunc : ios::app);

	if (input.is_open()) {//if success       
		input << content << endl;
		input.close();
	}
}