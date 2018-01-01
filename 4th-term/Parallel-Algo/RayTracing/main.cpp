#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

#include "sceneprocessor.hpp"

#define INPUT "input_data.txt"
#define GNOME "gnomeASCI.stl"
#define LIGHT "light.txt"
#define CAMERA "camera.txt"
#define OUTPUT "output.ppm"
#define CUSTOM "nudegirl.stl"
#define TEXTURE_MAP "texturemap.txt"

//"brick","brown_wood","sand","grey_wood","chess_field"

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    SceneProcessor sceneProcessor(BACKGROUND_INTENSITY, 4);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    sceneProcessor
                .scanDataFromMy(INPUT)
//                .loadTextureFromPPMWithKey("brick.ppm", "brick")
//                .loadTextureFromPPMWithKey("brown_wood.ppm", "brown_wood")
//                .loadTextureFromPPMWithKey("sand.ppm", "sand")
//                .loadTextureFromPPMWithKey("grey_wood.ppm", "grey_wood")
//                .loadTextureFromPPMWithKey("chess_field.ppm", "chess_field")
//                .addTextureMap(TEXTURE_MAP)
//                .scanDataFromASCISTL(GNOME)
                .scanLightData(LIGHT)
//                .scanCameraData(CAMERA)
                .run()
                .printDataWithFormatPPM(OUTPUT)
    ;
    
    end = std::chrono::system_clock::now();
    int64_t elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    cout << "elapsed seconds: " << elapsed_milliseconds/1000 << endl;
//    FILE* outtime = freopen("time.txt", "w", stdout);
//    cout << "elapsed seconds1: " << elapsed_milliseconds/1000 << endl;
//    fclose(stdout);
//    cout << "elapsed seconds2: " << elapsed_milliseconds/1000 << endl;
    return 0;
}
