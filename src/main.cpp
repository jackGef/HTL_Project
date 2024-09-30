#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void displayVideo(const string &videoFile)
{
    // Open the AVI file
    cv::VideoCapture cap(videoFile);

    // Check if the file opened successfully
    if (!cap.isOpened())
    {
        cerr << "Error: Cannot open AVI file: " << videoFile << endl;
        return;
    }

    cout << "Successfully opened AVI file: " << videoFile << endl;

    // Display the AVI file
    cv::Mat frame;
    while (true)
    {
        cap >> frame; // Capture frame
        if (frame.empty())
        {
            cout << "End of video." << endl;
            break; // End of video
        }

        cv::imshow("AVI Video", frame); // Display the frame

        // Press 'q' to exit
        if (cv::waitKey(25) == 'q')
        {
            cout << "Video stopped by user." << endl;
            break;
        }
    }

    cap.release();           // Release the video capture object
    cv::destroyAllWindows(); // Close the video window
}

string convertVideoToAVI(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <input_mp4> <output_avi>" << endl;
        return "Failed";
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    // Open input MP4 file directly using OpenCV
    cv::VideoCapture cap(inputFile);

    // Check if the file opened successfully
    if (!cap.isOpened())
    {
        cerr << "Error: Cannot open video file: " << inputFile << endl;
        return "Failed";
    }

    cout << "Successfully opened video file: " << inputFile << endl;

    // Get video properties
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);

    // Define the codec and create VideoWriter object to output in AVI format
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(width, height));

    if (!writer.isOpened())
    {
        cerr << "Error: Cannot open output file for writing: " << outputFile << endl;
        return "Failed";
    }

    // Process frames and write to AVI
    cv::Mat frame;
    while (true)
    {
        cap >> frame; // Capture frame
        if (frame.empty())
        {
            break; // End of video
        }

        writer.write(frame); // Write frame to AVI file
    }

    cout << "Video converted successfully to: " << outputFile << endl;
    return outputFile;
}

string trimVideo(const string &videoFile)
{

    cv::VideoCapture cap(videoFile);

    if (!cap.isOpened())
    {
        cerr << "Error: Cannot open video file: " << videoFile << endl;
        return "";
    }

    cout << "Enter the time you want to trim video" << endl;
    int startingTime = -1;
    cin >> startingTime;

    while (startingTime == -1)
    {
        cout << "you must enter a valid start time to trim the video(bigger than or equal to 0)" << endl;
        cout << "Enter the time: ";
        cin >> startingTime;
    }

    cout << "Enter the time you want the video to end.\n Enter -1 for the whole video" << endl;
    int endingTime = -1;
    cin >> endingTime;

    double fps = cap.get(cv::CAP_PROP_FPS);
    int totalFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));

    if (endingTime == -1)
    {
        // endingFrame = static_cast<int>(endingTime * fps);

        // endingTime = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT)) / cap.get(cv::CAP_PROP_FPS);

        endingTime = totalFrames / fps;
    }

    int startingFrame = static_cast<int>(startingTime * fps);
    int endingFrame = static_cast<int>(endingTime * fps);

    if (endingFrame > totalFrames)
    {
        endingFrame = totalFrames;
    }

    cout << "Enter the name of the trimed video" << endl;
    string videoFileName = "";
    cin >> videoFileName;

    while (videoFileName == "")
    {
        cout << "You must enter the name of the video file" << endl;
        cout << "Enter the name of the video file: ";
        cin >> videoFileName;
    }

    videoFileName += ".avi";

    string videoFilePath = "C:/Users/jack/Desktop/HTLProject/videos/trimedVIdeos/" + videoFileName;

    cv::Mat frame;
    cv::VideoWriter trimmedVideo(videoFilePath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cap.set(cv::CAP_PROP_POS_FRAMES, startingFrame);

    while (cap.get(cv::CAP_PROP_POS_FRAMES) < endingFrame)
    {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty())
        {
            break;
        }

        trimmedVideo.write(frame);
    }

    return videoFilePath;
}

string resizeVideo(const string &videoFilePath) {
    cv::VideoCapture cap(videoFilePath);

    if (!cap.isOpened()) {
        cerr << "Error: Cannot open video file: " << videoFilePath << endl;
        return "";
    }

    cout << "Enter the width of the video file:" << endl;
    double width = 0;
    cin >> width;

    while(width <= 0) {
        cout << "You must enter a valid widht(greater  than zero): " << endl;
        cin >> width;
    }

    cout << "Enter the width of the video file:" << endl;
    double height = 0;
    cin >> height;

    while(height <= 0) {
        cout << "You must enter a valid widht(greater  than zero): " << endl;
        cin >> height;
    }

    cout << "Enter the name of the video file:" << endl;
    string videoFileName = "";
    cin >> videoFileName;

    while (videoFileName == "") {
        cout << "You must enter the name of the video file:" << endl;
        cin >> videoFileName;
    }

    videoFileName += ".avi";
    string resizedFilePath = "C:/Users/jack/Desktop/HTLProject/videos/resizedVideos" + videoFileName;

    double fps = cap.get(cv::CAP_PROP_FPS);

    cv::VideoWriter resizedVideo(resizedFilePath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size((int)width, (int)height));

    cv::Mat frame;
    while(true) {
        cap >> frame;

        if (frame.empty()) {
            break;
        }

        cv::Mat resizedFrame;
        cv::resize(frame, resizedFrame, cv::Size(width, height));

        resizedVideo.write(resizedFrame);
    }

    return resizedFilePath;
}

int main(int argc, char **argv)
{

    // string video = convertVideoToAVI(argc, argv);

    // if (video == "Failed") {
    //     cout << "Failed" << endl;
    //     return 1;
    // }

    // video = trimVideo("C:/Users/jack/Desktop/HTLProject/videos/AVI/conv.avi");

    //!: you made the fucntion to trim but you entered 10 seconds and it gave you 18 seconds      Fix this!!!

    string video = resizeVideo("C:/Users/jack/Desktop/HTLProject/videos/AVI/idf.avi");

    displayVideo(video);

    return 0;
}