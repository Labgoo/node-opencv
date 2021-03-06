#include "OpenCV.h"
#include "Point.h"
#include "KeyPoint.h"
#include "Matrix.h"
#include "CascadeClassifierWrap.h"
#include "VideoCaptureWrap.h"
#include "Contours.h"
#include "CamShift.h"
#include "FeatureDetector.h"
#include "DescriptorExtractor.h"
#include "Feature2D.h"

extern "C" void
init(Handle<Object> target) {
    HandleScope scope;
    OpenCV::Init(target);
    Point::Init(target);
	KeyPoint::Init(target);
    Matrix::Init(target);
    CascadeClassifierWrap::Init(target);
    VideoCaptureWrap::Init(target);
    Contour::Init(target);
	TrackedObject::Init(target);
    Algorithm::Init(target);
	FeatureDetector::Init(target);
    DescriptorExtractor::Init(target);
    Feature2D::Init(target);
};

NODE_MODULE(opencv, init)
