#include "Feature2D.h"
#include "Matrix.h"
#include "KeyPoint.h"

v8::Persistent<FunctionTemplate> Feature2D::constructor;

void
Feature2D::Init(Handle<Object> target) {
    HandleScope scope;

	// Constructor
	constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Feature2D::New));
	constructor->InstanceTemplate()->SetInternalFieldCount(1);
	constructor->SetClassName(String::NewSymbol("Feature2D"));

	NODE_SET_PROTOTYPE_METHOD(constructor, "get", Algorithm::Get);
	NODE_SET_PROTOTYPE_METHOD(constructor, "set", Algorithm::Set);

	NODE_SET_PROTOTYPE_METHOD(constructor, "detectAndCompute", DetectAndCompute);

	target->Set(String::NewSymbol("Feature2D"), constructor->GetFunction());
};    

Handle<Value>
Feature2D::New(const Arguments &args) {
	HandleScope scope;

  if (args.This()->InternalFieldCount() == 0)
		return v8::ThrowException(v8::Exception::TypeError(v8::String::New("Cannot Instantiate without new")));

	Feature2D *f2d;

	if (args[0]->IsString()){
		f2d = new Feature2D(std::string(*v8::String::AsciiValue(args[0]->ToString())));
	} else {
		return v8::ThrowException(v8::Exception::TypeError(v8::String::New("New gets one string parameter")));
	}

	f2d->Wrap(args.This());

	return args.This();
}

Feature2D::Feature2D(const std::string& detectorType) : Algorithm(){
	HandleScope scope;
	_algorithm = cv::Feature2D::create(detectorType);
}

Handle<Value> 
Feature2D::DetectAndCompute(const Arguments &args) {
	HandleScope scope;	
	Feature2D *f2d = ObjectWrap::Unwrap<Feature2D>(args.This());
	Matrix *image = ObjectWrap::Unwrap<Matrix>(args[0]->ToObject());	
	Local<Object> descriptorsMatrixObject = Matrix::NewInstance();
	Matrix *descriptorsMatrix = ObjectWrap::Unwrap<Matrix>(descriptorsMatrixObject);

	cv::InputArray imageArray(image->mat);	
	cv::OutputArray descriptors(descriptorsMatrix->mat);
	cv::vector<cv::KeyPoint> keypoints;
	f2d->GetFeature2D()->operator()(imageArray, cv::noArray(), keypoints, descriptors, false);

	return scope.Close(descriptorsMatrixObject);
}

cv::Ptr<cv::Feature2D> Feature2D::GetFeature2D(){
	return (cv::Ptr<cv::Feature2D>)_algorithm;
}
