#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap("apt");

    if (!cap.isOpened()) {
        cout << "Video tidak dapat dibuka." << endl;
        return -1;
    }
    Size ukuranFrame(1280, 720);
    Mat video, frameResized, hsvFrame, maskBola;

    // Titik pusat vid (0, 0)
    Point2f titikPusat(ukuranFrame.width / 2, ukuranFrame.height / 2);
    cout << "Titik Pusat Frame: (" << titikPusat.x << ", " << titikPusat.y << ")" << endl;

    // pixel ke cm, 10x = 1cm
    const float pixelKeCM = 1.0 / 10.0;

    while (true) {
        // Baca video
        bool berhasil = cap.read(video);
        if (!berhasil) {
            cout << "Selesai membaca video." << endl;
            break;
        }

        // konversi HSV
        resize(video, frameResized, ukuranFrame);
        cvtColor(frameResized, hsvFrame, COLOR_BGR2HSV);

        // Range warna bola 
        Scalar minWarnaBola(0, 144, 153);
        Scalar maxWarnaBola(15, 255, 255);
        inRange(hsvFrame, minWarnaBola, maxWarnaBola, maskBola);

        // Operasi morfologi untuk mengurangi noise
        erode(maskBola, maskBola, getStructuringElement(MORPH_RECT, Size(3, 3)));
        dilate(maskBola, maskBola, getStructuringElement(MORPH_RECT, Size(3, 3)));

        // kontur bola
        vector<vector<Point>> konturBola;
        findContours(maskBola, konturBola, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        Point2f posisiBola;
        bool bolaTerdeteksi = false;

        for (const auto& kontur : konturBola) {
            double area = contourArea(kontur);
            if (area > 100 && area < 2350) {
                Rect detectionBox = boundingRect(kontur);
                posisiBola = (detectionBox.br() + detectionBox.tl()) * 0.5;
                bolaTerdeteksi = true;
                break;
            }
        }

        if (bolaTerdeteksi) {
            // posisi bola ke titik pusat
            Point2f posisiRelatif = posisiBola - titikPusat;

            // perhitungan jarak
            float jarakX = (posisiRelatif.x * pixelKeCM)-32.4;
            float jarakY = posisiRelatif.y * pixelKeCM;

            // bounding box bola
            rectangle(frameResized, Rect(posisiBola.x - 10, posisiBola.y - 10, 20, 20), Scalar(0, 255, 0), 2);
            circle(frameResized, posisiBola, 5, Scalar(255, 0, 0), -1);

            // posisi bola teks di vidnya
            putText(frameResized, "Posisi Robot: (" + to_string(jarakX) + " cm, " + to_string(jarakY) + " cm)", 
                    Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 255), 2);

            // cout << "Posisi Piksel: (" << posisiRelatif.x << ", " << posisiRelatif.y << ")" << endl;
            // cout << "Posisi Bola cm: (" << jarakX << " cm, " << jarakY << " cm)" << endl;
        }

        // hasil vid
        imshow("Deteksi Bola", frameResized);

        if (waitKey(30) == 'q') {
            break;
        }
    }

    return 0;
}
