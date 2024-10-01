#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

//?: a structure representing the returned values in functions
struct return_values {
    string pathFileName;
    string fileName;
};


//?: The funciton "displayVideo" get a path to a video file and the name of the video file and dispay the video file
void displayVideo(const string &videoFile, string fileNameDisplay)
{
    // Open the video file
    cv::VideoCapture cap(videoFile);

    // Check if the file opened successfully
    if (!cap.isOpened())
    {
        cerr << "Error: Cannot open AVI file: " << videoFile << endl;
        return;
    }

    std::cout << "Successfully opened AVI file: " << videoFile << endl;

    // Display the AVI file. The frame variable gets wach frame of the video in a loop
    cv::Mat frame;

    // loop to display the video
    while (true)
    {
        cap >> frame; // Capture frame the next frame 

        // check if the frame is empty if it is empty than its stop displaying the video
        if (frame.empty())
        {
            std::cout << "End of video." << endl;
            break; // End of video
        }

        // display the current frame with the video file name
        cv::imshow(fileNameDisplay, frame); // Display the frame

        // waites 15 ms for the user to press 'q' (video display speed)
        if (cv::waitKey(15) == 'q')
        {
            std::cout << "Video stopped by user." << endl;
            break;
        }
    }

    cap.release(); // Release the video capture object
    cv::destroyAllWindows(); // Close the video window
}

//?: The function "convertVideoToAVI" get input video path and output video path and convert to given video file(mp4) to avi format
return_values convertVideoToAVI(int argc, char *argv[])
{

    // Check if the input arguments correct (command line arguments)
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <input_mp4> <output_avi>" << endl;
        return {"Fialed", "Failed"};
    }

    // save the input path in a variable
    string inputFile = argv[1];

    // save the output path in a variable
    string outputFile = argv[2];

    // Open input MP4 file 
    cv::VideoCapture cap(inputFile);

    // Check if the file opened
    if (!cap.isOpened())
    {
        cerr << "Error: Cannot open video file: " << inputFile << endl;
        return {"Fialed", "Failed"};
    }

    // print a message to show the succes of the 'videoCapture'
    std::cout << "Successfully opened video file: " << inputFile << endl;

    // Get video properties
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);

    // Define the codec and create VideoWriter object to output in AVI format
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(width, height));

    // check if the video capture was successfully opened
    if (!writer.isOpened())
    {
        cerr << "Error: Cannot open output file for writing: " << outputFile << endl;
        return {"Fialed", "Failed"};
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

    std::cout << "Video converted successfully to: " << outputFile << endl; // a message of video converted seccessfuly

    cap.release(); // releas the 'videoCapture'
    return {outputFile, "AVI_File"}; //return the return_values structure
}


//! chatGPT's code
// return_values trimVideo(const std::string& inputFilePath) {
//     // Open the input video file
//     cv::VideoCapture inputVideo(inputFilePath);

//     if (!inputVideo.isOpened()) {
//         std::cerr << "Error: Could not open the input video file!" << std::endl;
//         return {};
//     }

//     std::cout << "Enter the starting time: " << endl;
//     double startTime = -1;
//     std::cin >> startTime;

//     while (startTime == -1) {
//         std::cerr << "Error: Invalid starting time! Please enter a positive number." << std::endl;
//         std::cin >> startTime;
//     }

//     std::cout << "Enter the ending time: " << endl;
//     double endTime = -1;
//     std::cin >> endTime;

//     while (endTime == -1) {
//         std::cerr << "Error: Invalid ending time! Please enter a positive number." << std::endl;
//         std::cin >> endTime;
//     }

//     std::cout << "Enter the name of the trimmed video: " << std::endl;
//     std::string fileName = "";
//     std::cin >> fileName;

//     while (fileName == "") {
//         std::cerr << "Error: You must enter the name of the trimmed video!" << std::endl;
//         std::cin >> fileName;
//     }

//     std::string outputFilePath = "C:/Users/jack/Desktop/HTL_project_ort/videos/trimmed/" + fileName + ".avi";

//     // Get video properties
//     double fps = inputVideo.get(cv::CAP_PROP_FPS);
//     int codec = static_cast<int>(inputVideo.get(cv::CAP_PROP_FOURCC));
//     int totalFrames = static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_COUNT));

//     // Calculate the frame range for trimming
//     int startFrame = static_cast<int>(startTime * fps);
//     int endFrame = static_cast<int>(endTime * fps);

//     if (startFrame < 0 || endFrame >= totalFrames || startFrame >= endFrame) {
//         std::cerr << "Error: Invalid start or end time!" << std::endl;
//         return {};
//     }

//     // Set the starting point of the input video
//     inputVideo.set(cv::CAP_PROP_POS_FRAMES, startFrame);

//     // Open the output video writer
//     cv::VideoWriter outputVideo(outputFilePath, codec, fps, cv::Size(inputVideo.get(cv::CAP_PROP_FRAME_WIDTH), cv::CAP_PROP_FRAME_HEIGHT));
//     if (!outputVideo.isOpened()) {
//         std::cerr << "Error: Could not open the output video file!" << std::endl;
//         return {};
//     }

//     // Read frames from the input and write them to the output
//     cv::Mat frame;
//     for (int currentFrame = startFrame; currentFrame < endFrame; ++currentFrame) {
//         if (!inputVideo.read(frame)) {
//             std::cerr << "Error: Could not read a frame from the input video!" << std::endl;
//             break;
//         }
//         outputVideo.write(frame);
//     }

//     // Release resources
//     inputVideo.release();
//     outputVideo.release();

//     std::cout << "Video trimming completed successfully!" << std::endl;
//     return {outputFilePath, fileName};
// }


//! my code:
// return_values trimVideo(const string &videoFile)
// {

//     cv::VideoCapture cap(videoFile);

//     if (!cap.isOpened())
//     {
//         cerr << "Error: Cannot open video file: " << videoFile << endl;
//         return {"Fialed", "Failed"};
//     }

//     std::cout << "Enter the start time for trimming(in seconds)" << endl;
//     int startingTime = -1;
//     std::cin >> startingTime;

//     while (startingTime == -1)
//     {
//         std::cout << "you must enter a valid start time to trim the video(bigger than or equal to 0)" << endl;
//         std::cout << "Enter the time: ";
//         std::cin >> startingTime;
//     }

//     std::cout << "Enter the time you want the trimmed video to end(int seconds).\n Enter -1 for the whole video" << endl;
//     int endingTime = -1;
//     std::cin >> endingTime;

//     double fps = cap.get(cv::CAP_PROP_FPS);
//     int totalFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
//     double videoDuration = totalFrames / fps;

//     // if (endingTime == -1 || endingTime > videoDuration)
//     // {
//     //     endingTime = static_cast<int>(videoDuration);
//     // }

//     int startingFrame = static_cast<int>(startingTime * fps);
//     int endingFrame = static_cast<int>(endingTime * fps);

//     if (startingFrame >= endingFrame)
//     {
//         std::cout << "Error: starting time must be less than ending time" << endl;
//         return {"Fialed", "Failed"};
//     }

//     std::cout << "Enter the name of the trimed video" << endl;
//     string videoFileName = "";
//     std::cin >> videoFileName;

//     while (videoFileName == "")
//     {
//         std::cout << "You must enter the name of the video file" << endl;
//         std::cout << "Enter the name of the video file: ";
//         std::cin >> videoFileName;
//     }

//     string videoFilePath = "C:/Users/jack/Desktop/HTL_project_ort/videos/trimmed/" + videoFileName + ".avi";

//     cv::VideoWriter trimmedVideo(videoFilePath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

//     cap.set(cv::CAP_PROP_POS_FRAMES, startingFrame);

//     cv::Mat frame;
//     while (cap.get(cv::CAP_PROP_POS_FRAMES) < endingFrame)
//     {
//         cap >> frame;
//         if (frame.empty())
//         {
//             break;
//         }

//         trimmedVideo.write(frame);
//     }
//     std::cout << "success" << endl;

//     cap.release();
//     return {videoFilePath, videoFileName};
// }

//? a function to resize the video file
return_values resizeVideo(const string &videoFilePath) {
    cv::VideoCapture cap(videoFilePath); // capture the video file

    // check if the video file was opned seccessfuly
    if (!cap.isOpened()) {
        cerr << "Error: Cannot open video file: " << videoFilePath << endl;
        return {"failed", "failed"};
    }


    std::cout << "Enter the width of the video file:" << endl;
    int width = 0; // a variable to save the user's input
    std::cin >> width;

    // check if the user's input is valid
    while(width <= 0) {
        std::cout << "You must enter a valid width(greater  than zero): " << endl;
        std::cin >> width;
    }

    std::cout << "Enter the height of the video file:" << endl;
    int height = 0; // a variable to save the user's input
    std::cin >> height;

    // check if the user's input is valid
    while(height <= 0) {
        std::cout << "You must enter a valid height(greater  than zero): " << endl;
        std::cin >> height;
    }

    std::cout << "Enter the name of the video file:" << endl;
    string videoFileName = "";// a variable to save the user's input
    std::cin >> videoFileName;

    // check if the user's input is valid
    while (videoFileName == "") {
        std::cout << "You must enter the name of the video file:" << endl;
        std::cin >> videoFileName;
    }

    // create the new video file path with the user's input file name
    string resizedFilePath = "C:/Users/jack/Desktop/HTL_project_ort/videos/resize/" + videoFileName + ".avi";

    double fps = cap.get(cv::CAP_PROP_FPS); // get the video fps

    // create a new object to create the resized video
    cv::VideoWriter resizedVideo(resizedFilePath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(width, height));

    // read each frame from the video file and resize it in the loop
    cv::Mat frame;
    while(true) {
        cap >> frame;

        if (frame.empty()) {
            break;
        }

        cv::Mat resizedFrame;

        // resize the frame using OpenCV's resize function
        cv::resize(frame, resizedFrame, cv::Size(width, height));

        resizedVideo.write(resizedFrame);
    }

    cap.release();// release the video capture
    return {resizedFilePath, videoFileName};
}

//? a function to rotate the video file
return_values rotateVideo(const string& videoFilePath) {
    cv::VideoCapture cap(videoFilePath); // captrue the video file

    // check if the video file was successfluy opened
    if (!cap.isOpened()) {
        std::cout << "Error: video path is incorrect!" << endl;
        return {"Fialed", "Failed"};
    }

    // show the user the option to rotate the video
    std::cout << "Choose an angle:" << endl;
    std::cout << "1. 90 degrees clockwise" << endl;
    std::cout << "2. 180 degrees" << endl;
    std::cout << "3. 270 degrees clockwise" << endl;

    int userResponse = 0; // save the user's input
    std::cin >> userResponse;
    int angle = 0;

    // declare the angle according to the user's input
    switch (userResponse) {
        case 1:
            angle = 90;
            break;
        case 2:
            angle = 180;
            break;
        case 3:
            angle = 270;
            break;
        default:
            std::cout << "Invalid input. Please choose 1, 2, or 3." << endl;
            return {};
    }

    // user name of choise
    std::cout << "Enter name of the video file:" << endl;
    string videoFileName = "";
    std::cin >> videoFileName;

    // the new video will be save in this path
    string rotatedVideoPath = "C:/Users/jack/Desktop/HTL_project_ort/videos/rotateed/" + videoFileName + ".avi";

    // get the original video fps
    double fps = cap.get(cv::CAP_PROP_FPS);

    // declare a new video object
    cv::VideoWriter roatatedVideo(rotatedVideoPath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cv::Mat frame;// will save each frame

    // while loop to write frame to the new video object 
    while(true) {
        cap >> frame; // save the current frame

        // check if the frame is empty if it is than close the break out of the loop
        if (frame.empty()) {
            break;
        }

        cv::Mat videoAngle; // the destination frame will save the awanted angle

        // check wich angle the user chose to rotate the video file
        switch (angle) {
            case 90:
                cv::rotate(frame, videoAngle, cv::ROTATE_90_CLOCKWISE);
                break;
            case 180:
                cv::rotate(frame, videoAngle, cv::ROTATE_180);
                break;
            case 270:
                cv::rotate(frame, videoAngle, cv::ROTATE_90_COUNTERCLOCKWISE);
                break;
        }

        // write the rotated frame to the new video object
        roatatedVideo.write(videoAngle);
    }
    
    std::cout << "Video rotated seccesfully" << endl;

    // release the video capture
    cap.release();
    return {rotatedVideoPath, videoFileName};
}

//? a function to add text overlay to the video file
return_values addOverlayText(const string& videoFilePath) {
    cv::VideoCapture cap(videoFilePath); // capture the video file

    // check if the video file was opened successfully
    if (!cap.isOpened()) {
        std::cout << "Error: file path is incorrect!" << endl;
        std::cout << videoFilePath << endl;
        return {};
    }

    // user's text choise
    std::cout << "Enter the text you want to display: " << endl;
    string text; // keep the user text choise
    std::getline(std::cin, text); // a f=built in function to escape the buffer

    // user's font size choise
    std::cout << "Enter the font size(Must be bigger than 0): " << endl;
    double fontSize = 0; // save teh user input
    std::cin >> fontSize;

    // check if the user's input is valid
    if (fontSize <= 0) {
        std::cout << "You entered invalid font size\n setting to the default: 1" << endl;
        fontSize = 1;
    }

    // show the user the text color options
    std::cout << "Choose the font color: " << endl;
    std::cout << "1. red" << endl;
    std::cout << "2. green" << endl;
    std::cout << "3. blue" << endl;
    std::cout << "4. yellow" << endl;
    std::cout << "5. purple" << endl;
    std::cout << "6. cyan" << endl;
    std::cout << "7. white" << endl;

    int userChoiceColor = 0; // save the user's input
    std::cin >> userChoiceColor;

    cv::Scalar fontColor;// will save the font colot value
    
    // save the "fontColor" value according to the user's input
    switch (userChoiceColor) {
        case 1:
            fontColor = cv::Scalar(0, 0, 255);
            break;
        case 2:
            fontColor = cv::Scalar(0, 255, 0);
            break;
        case 3:
            fontColor = cv::Scalar(255, 0, 0);
            break;
        case 4:
            fontColor = cv::Scalar(0, 255, 255);
            break;
        case 5:
            fontColor = cv::Scalar(255, 0, 255);
            break;
        case 6:
            fontColor = cv::Scalar(255, 255, 0);
            break;
        case 7:
            fontColor = cv::Scalar(255, 255, 255);
            break;
        default:
            std::cout << "You chose the default color(black)" << endl;
    }
    
    // show the user the option for the font type
    std::cout << "Choose the font type: " << endl;
    std::cout << "1. FONT_HERSHEY_TRIPLEX" << endl;
    std::cout << "2. FONT_HERSHEY_PLAIN" << endl;
    std::cout << "3. FONT_HERSHEY_DUPLEX" << endl;
    std::cout << "4. FONT_HERSHEY_COMPLEX" << endl;
    
    int userChoiseFontType = 0; // will save teh user input
    std::cin >> userChoiseFontType;

    int fontType;
    
    // save the 'fontType' value according to the user's input
    switch (userChoiseFontType) {
        case 1:
            fontType = cv::FONT_HERSHEY_TRIPLEX;
            break;
        case 2:
            fontType = cv::FONT_HERSHEY_PLAIN;
            break;
        case 3:
            fontType = cv::FONT_HERSHEY_DUPLEX;
            break;
        case 4:
            fontType = cv::FONT_HERSHEY_COMPLEX;
            break;
        default:
            std::cout << "You chose the default font type" << endl;
            fontType = cv::FONT_HERSHEY_SIMPLEX;
    }
    
    int thickness = 2; // the thickness of the text 

    int baseline = 0; // the baseline of the text

    // user's choise of the file's name
    std::cout << "Enter the video file name: " << endl;
    string videoFileName = "";
    std::getline(std::cin, videoFileName);

    // check if the user's input is valid
    while(videoFileName == "") {
        std::cout << "You must enter the name of the video file:" << endl;
        std::getline(std::cin, videoFileName);
    }

    // the path to the new video file
    string overlayedVideoPath = "C:/Users/jack/Desktop/HTL_project_ort/videos/overlayText/" + videoFileName + ".avi";

    double fps = cap.get(cv::CAP_PROP_FPS); // save the capture video fps

    // declare a new video object for the new video file with the overlayed text
    cv::VideoWriter overlayVIdeo(overlayedVideoPath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cv::Mat frame; // will save each frame
    while (true) {
        cap >> frame; // save the current frame

        // cheack if the frame is empty if it is than the loop will stop
        if (frame.empty()) {
            break;
        }

        // use the OpenCV's Size function to declare the font's size
        cv::Size textSize = cv::getTextSize(text, fontType, fontSize, thickness, &baseline);
        // calculate the center of the frame and place the text there
        cv::Point textOrg((frame.cols - textSize.width) / 2, frame.rows - 30);

        cv::putText(frame, text, textOrg, fontType, fontSize, fontColor, thickness);// declare the text vlaues

        overlayVIdeo.write(frame); // write the frames in the new file
    }
    
    std::cout << "Text overlay loaded" << endl;

    cap.release();
    return { overlayedVideoPath, videoFileName};
}

return_values applyFilter(const string& videoFilePath) {

    cv::VideoCapture cap(videoFilePath); // capture the video file

    // check if the video file was opened successfully
    if (!cap.isOpened()) {
        std::cout << "Error: file path is incorrect!" << endl;
        std::cout << videoFilePath << endl;
        return {};
    }

    // show the user the filter options
    std::cout << "Choose the filter: " << endl;
    std::cout << "1. Invert" << endl;
    std::cout << "2. GaussianBlur" << endl;
    std::cout << "3. MedianBlur" << endl;
    std::cout << "4. BilateralFilter" << endl;

    int userChoiceFilter = 0; // save the user's input
    std::cin >> userChoiceFilter;

    // check if the user's input is valid
    if (userChoiceFilter <= 0 || userChoiceFilter   >= 6) {
        std::cout << "Invalid choice";
        return {};
    }

    // clear the buffer after std::cin
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // let the user put the new file's name
    std::cout << "Enter the video file name: " << endl;
    string videoFileName = ""; // will save the bew file's name
    std::getline(std::cin, videoFileName);

    // check if the user's input is valid
    while (videoFileName == "") { 
        std::cout << "You must enter the name of the video file:" << endl;
        std::getline(std::cin, videoFileName);
    }

    // declare the path to the new video file
    string filterVideoPath = "C:/Users/jack/Desktop/HTL_project_ort/videos/filter/" + videoFileName + ".avi";

    double fps = cap.get(cv::CAP_PROP_FPS); // save the capture video's fps

    // create a new video object 
    cv::VideoWriter filteredVideo(filterVideoPath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cv::Mat frame;
    while (true) {
        cap >> frame; // save teh current frame

        // check if the frame is empty
        if (frame.empty()) {
            break;
        }

        cv::Mat filteredFrame; // this will be the filtered frame

        // apply the selected filter to the frame
        switch (userChoiceFilter) {
            case 1:
                cv::bitwise_not(frame, filteredFrame);
                break;
            case 2:
                cv::GaussianBlur(frame, filteredFrame, cv::Size(7, 7), 0);
                break;
            case 3:
                cv::medianBlur(frame, filteredFrame, 5);
                break;
            case 4:
                cv::bilateralFilter(frame, filteredFrame, 15, 75, 75);
                break;
        }
        
        filteredVideo.write(filteredFrame); // write the new frame 
    }

    cap.release();
    return { filterVideoPath, videoFileName };
}

int main(int argc, char **argv)
{

    cout << "First it will convert the file video.mp4 to an AVI format" << endl;
    return_values video = convertVideoToAVI(argc, argv);

    return_values newVideo = {};

    while (true) {
        std::cout << "Choose an operation:" << endl;
        std::cout << "1. Convert video to AVI" << endl;
        std::cout << "2. Resize video" << endl;
        std::cout << "3. Rotate video" << endl;
        std::cout << "4. Add overlay text" << endl;
        std::cout << "5. Apply filter" << endl;
        std::cout << "6. Exit" << endl;

        int choice = 0;
        std::cin >> choice;

        switch (choice) {
            case 1:
                newVideo = convertVideoToAVI(argc, argv);
                displayVideo(newVideo.pathFileName, newVideo.fileName);
                break;
            case 2:
                newVideo = resizeVideo(video.pathFileName);
                displayVideo(newVideo.pathFileName, newVideo.fileName);
                break;
            case 3:
                newVideo = rotateVideo(video.pathFileName);
                displayVideo(newVideo.pathFileName, newVideo.fileName);
                break;
            case 4:
                newVideo = addOverlayText(video.pathFileName);
                displayVideo(newVideo.pathFileName, newVideo.fileName);
                break;
            case 5:
                newVideo = applyFilter(video.pathFileName);
                displayVideo(newVideo.pathFileName, newVideo.fileName);
                break;
            case 6:
                return 0;
            default:
                std::cout << "Invalid choice" << endl;
        }
    }

    return 0;
}