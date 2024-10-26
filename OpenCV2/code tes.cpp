// #include <opencv2/opencv.hpp>
// #include <iostream>

// using namespace cv;
// using namespace std;

// int main()
// {
//     VideoCapture cap("apt");

//     if (!cap.isOpened()) {
//         printf("Video tidak dapat dibuka.\n");
//         return -1;
//     }

//     Size ukuranBaru(1280, 720);
//     Mat vidResized, vidRobot, hsvVid, maskBola, maskRobot;

//     // Tentukan titik pusat frame sebagai titik pusat koordinat
//     Point2f titikPusat(ukuranBaru.width / 2, ukuranBaru.height / 2);

//     while (true) {
//         bool play = cap.read(vidRobot);
//         if (!play) {
//             printf("Selesai membaca video.\n");
//             break;
//         }

//         resize(vidRobot, vidResized, ukuranBaru);
//         cvtColor(vidResized, hsvVid, COLOR_BGR2HSV);

//         Scalar minColorBola(5, 100, 100);
//         Scalar maxColorBola(15, 255, 255);
//         inRange(hsvVid, minColorBola, maxColorBola, maskBola);

//         Scalar minColorRobot(0, 0, 0);
//         Scalar maxColorRobot(180, 255, 30);
//         inRange(hsvVid, minColorRobot, maxColorRobot, maskRobot);

//         erode(maskBola, maskBola, getStructuringElement(MORPH_RECT, Size(3, 3)));
//         dilate(maskBola, maskBola, getStructuringElement(MORPH_RECT, Size(3, 3)));

//         vector<vector<Point>> konturBola;
//         findContours(maskBola, konturBola, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

//         Rect boundingBoxBola;
//         double maxAreaBola = 0;
//         Point2f posisiBola;

//         for (size_t i = 0; i < konturBola.size(); i++) {
//             double area = contourArea(konturBola[i]);
//             if (area > 100 && area < 2350) {
//                 Rect tempBox = boundingRect(konturBola[i]);
//                 if (area > maxAreaBola) {
//                     maxAreaBola = area;
//                     boundingBoxBola = tempBox;
//                     posisiBola = (tempBox.br() + tempBox.tl()) * 0.5;
//                 }
//             }
//         }

//         vector<vector<Point>> konturRobot;
//         Point2f posisiRobot;
//         findContours(maskRobot, konturRobot, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

//         for (size_t i = 0; i < konturRobot.size(); i++) {
//             double area = contourArea(konturRobot[i]);
//             if (area > 500) {
//                 Moments m = moments(konturRobot[i]);
//                 posisiRobot = Point2f(m.m10 / m.m00, m.m01 / m.m00);
//                 break;
//             }
//         }

//         if (maxAreaBola > 100) {
//             rectangle(vidResized, boundingBoxBola, Scalar(0, 255, 0), 2);
//             circle(vidResized, Point(boundingBoxBola.x, boundingBoxBola.y), 5, Scalar(255, 0, 0), -1);
//             circle(vidResized, Point(boundingBoxBola.x + boundingBoxBola.width, boundingBoxBola.y), 5, Scalar(255, 0, 0), -1);
//             circle(vidResized, Point(boundingBoxBola.x, boundingBoxBola.y + boundingBoxBola.height), 5, Scalar(255, 0, 0), -1);
//             circle(vidResized, Point(boundingBoxBola.x + boundingBoxBola.width, boundingBoxBola.y + boundingBoxBola.height), 5, Scalar(255, 0, 0), -1);
//         }

//         // Hitung posisi relatif bola dan robot dari titik pusat
//         Point2f posisiBolaRelatif = posisiBola - titikPusat;
//         Point2f posisiRobotRelatif = posisiRobot - titikPusat;

//         // Konversi piksel ke cm berdasarkan skala 10 piksel = 1 cm
//         float bolaX = posisiBolaRelatif.x / 10;
//         float bolaY = posisiBolaRelatif.y / 10;
//         float robotX = posisiRobotRelatif.x / 10;
//         float robotY = posisiRobotRelatif.y / 10;

//         // Tampilkan posisi dalam cm
//         putText(vidResized, "Posisi Bola: (" + to_string(bolaX) + " cm, " + to_string(bolaY) + " cm)", 
//                 Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 0), 2);
//         putText(vidResized, "Posisi Robot: (" + to_string(robotX) + " cm, " + to_string(robotY) + " cm)", 
//                 Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 255), 2);
        
//         imshow("Video Robot", vidResized);

//         if (waitKey(30) == 'q') {
//             break;
//         }
//     }

//     return 0;
// }
