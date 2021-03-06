#ifndef BUMBLEBEECAMERA_H
#define BUMBLEBEECAMERA_H

#include <stdlib.h>
#include <flycapture/FlyCapture2.h>
#include <triclops/triclops.h>
#include <triclops/fc2triclops.h>
#include "usma_triclops/common.h"

class BumbleBeeCamera {

private:
    FC2::Camera camera;
    TriclopsContext triclops;
    TriclopsImage16 disparityImage;
    TriclopsColorImage rectifiedColorImage;

    TriclopsInput triclopsColorInput;
    TriclopsInput triclopsMonoInput;
    ImageContainer imageContainer;

    int stereo_mask;
    int disp_max;
    int disp_min;
    int disp_map_on;
    u_char disp_map_max;
    u_char disp_map_min;
    int retreiveImageFormat(FC2::Format7ImageSettings formatSettings);
    int preProcessing(const FC2::Image& grabbedImage);
    int convertToBGR(FC2::Image& image, FC2::Image& convertedImage);
    int convertToBGRU(FC2::Image& image, FC2::Image& convertedImage);
    int doStereo();

public:
    BumbleBeeCamera();
    int startCamera();
    int shutdown();
    TriclopsImage16 getDisparityImage() { return disparityImage; }
    TriclopsColorImage getRectifiedColorImage() { return rectifiedColorImage; }
    TriclopsContext getTriclopsContext() { return triclops; }
    int retrieveImages();
};

#endif // BUMBLEBEECAMERA_H
