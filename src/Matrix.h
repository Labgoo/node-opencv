#include "OpenCV.h"

class Matrix: public node::ObjectWrap {
  public:
  	
  	cv::Mat mat;
    static Persistent<FunctionTemplate> constructor;
    static void Init(Handle<Object> target);
    static Handle<Value> New(const Arguments &args);
    static Local<Object> NewInstance();
    
    Matrix();      
    Matrix(cv::Mat other, cv::Rect roi);
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int type);

    static double DblGet(cv::Mat mat, int i, int j);
    static Handle<Value> GetType(Local<String> prop, const AccessorInfo &info);
    static void RaiseImmutable(Local<String> property, Local<Value> value, const AccessorInfo& info);


    JSFUNC(Eye) // factory

    JSFUNC(Get) // at
    JSFUNC(Set)

    JSFUNC(Row)
    JSFUNC(PixelRow)
    JSFUNC(Col)
    JSFUNC(PixelCol)

    JSFUNC(Size)
    JSFUNC(Width)
    JSFUNC(Height)
    JSFUNC(Channels)

    JSFUNC(Ellipse)
    JSFUNC(Rectangle)
    JSFUNC(Line)
    JSFUNC(Empty)

    JSFUNC(Save)
    JSFUNC(ToBuffer)
	  
    JSFUNC(ToBufferAsync)

    JSFUNC(Resize)

    JSFUNC(ConvertGrayscale)
    JSFUNC(ConvertHSVscale)
    JSFUNC(Copy)
    JSFUNC(Ptr)
    JSFUNC(AddWeighted)
    JSFUNC(Split)
    JSFUNC(Canny)
    JSFUNC(Dilate)

    JSFUNC(FindContours)
    JSFUNC(DrawContour)
    JSFUNC(DrawAllContours)

    // Feature Detection
    JSFUNC(GoodFeaturesToTrack)
    JSFUNC(HoughLinesP)

/*
	static Handle<Value> Val(const Arguments& args);
	static Handle<Value> RowRange(const Arguments& args);
	static Handle<Value> ColRange(const Arguments& args);
	static Handle<Value> Diag(const Arguments& args);
	static Handle<Value> Clone(const Arguments& args);
	static Handle<Value> CopyTo(const Arguments& args);
	static Handle<Value> ConvertTo(const Arguments& args);
    static Handle<Value> AssignTo(const Arguments& args);
    static Handle<Value> SetTo(const Arguments& args);
    static Handle<Value> Reshape(const Arguments& args);
    static Handle<Value> Transpose(const Arguments& args);
    static Handle<Value> Invert(const Arguments& args);
    static Handle<Value> Multiply(const Arguments& args);
    static Handle<Value> Cross(const Arguments& args);
    static Handle<Value> Dot(const Arguments& args);
    static Handle<Value> Zeroes(const Arguments& args);
    static Handle<Value> Ones(const Arguments& args);
// create, increment, release
    static Handle<Value> PushBack(const Arguments& args);
    static Handle<Value> PopBack(const Arguments& args);
    static Handle<Value> LocateROI(const Arguments& args);
    static Handle<Value> AdjustROI(const Arguments& args);
    static Handle<Value> Total(const Arguments& args);
    static Handle<Value> IsContinous(const Arguments& args);
    static Handle<Value> Type(const Arguments& args);
    static Handle<Value> Depth(const Arguments& args);
    static Handle<Value> Channels(const Arguments& args);
    static Handle<Value> StepOne(const Arguments& args);
    
    
*/

};

