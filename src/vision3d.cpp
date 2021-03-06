#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <triclops/triclops.h>

#include "usma_triclops/typedefs.h"
#include "usma_triclops/vision3d.h"

Vision3d::Vision3d()
{
}

int Vision3d::producePointCloud(cv::Mat const& disparityImage,
    cv::Mat const& maskImage,
    TriclopsContext const& triclops,
    PointCloud& returnedPoints)
{
    float x, y, z;
    int i = 0, j = 0;
    unsigned short disparity;
    unsigned char mask;

    // printf("[!] Searching through image at %p for obstacles..mask
    // %d,%d,%d,%d,%d and dispar %d,%d,%d,%d,%d\n",
    // &maskImage,maskImage.cols,maskImage.rows,int(maskImage.step),maskImage.channels(),int(maskImage.elemSize()),disparityImage.cols,disparityImage.rows,int(disparityImage.step),disparityImage.channels(),int(disparityImage.elemSize())
    // );
    for (i = 0; i < disparityImage.rows; i++) {
        for (j = 0; j < disparityImage.cols; j++) {
            disparity = disparityImage.at<unsigned short>(i, j);
            mask = maskImage.at<unsigned char>(i, j);

            // do not run invalid points
            if (disparity < 0xFF00) {
                // look at points within a range
                PointT point;

                // only fil out for points that are cyan
                if (mask != 0) {
                    triclopsRCD16ToXYZ(triclops, i, j, disparity, &x, &y, &z);
                    point.x = z;
                    point.y = -x;
                    point.z = -y;
                    point.r = 255;
                    point.g = 255;
                    point.b = 255;
                    returnedPoints.push_back(point);
                }
            }
        }
    }

    return 0;
}
