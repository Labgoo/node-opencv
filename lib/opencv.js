var Stream = require('stream').Stream
  , Buffers = require('buffer')
  , util = require('util');

var bindings = require('./bindings')

var cv = module.exports = {};

cv.__proto__ = bindings;
/*

# Matrix #
The matrix is one of opencv's most core datatypes.

*/

module.exports.MatrixSerializer = MatrixSerializer;

var matrix = cv.Matrix.prototype;

matrix.detectObject = function(classifier, opts, cb){
	opts = opts || {}

  cv._detectObjectClassifiers = cv._detectObjectClassifiers || {}

  if (cv._detectObjectClassifiers[classifier]){
    var face_cascade = cv._detectObjectClassifiers[classifier];
  } else{
	  var face_cascade = new cv.CascadeClassifier(classifier);
    cv._detectObjectClassifiers[classifier] = face_cascade;
  }

	face_cascade.detectMultiScale(this, cb, opts.scale, opts.neighbors
		, opts.min && opts.min[0], opts.min && opts.min[1]);
}

matrix.inspect = function(){
	var size = this.size() ? (this.size()[0] + 'x' + this.size()[1]) : '';

	return "[Matrix " + size + " ]";
}

function MatrixSerializer(){	
}

MatrixSerializer.prototype.serialize = function (instance){
	var size = instance.size();
	var xSize = size[0];
	var ySize = size[1];
	var result = xSize + ' ' + ySize + ' ' + instance.type;
	for (var y=0; y<ySize; y++){
		for (var x=0; x<xSize; x++){
			result += ' ' + instance.get(x,y);
		}
	}
	return result;	
}

MatrixSerializer.prototype.deserialize = function (data){
	var array = data.split(' ');
	var xSize = array[0];
	var ySize = array[1];
	var type = array[2];
	var matrix = new cv.Matrix(xSize, ySize, type);

	var i = 3;
	for (var y=0; y<ySize; y++){
		for (var x=0; x<xSize; x++){
			matrix.set(x, y, array[i]);
			i++;
		}
	}
	return matrix;
}

cv.KeyPoint.prototype.inspect = function(){
	return "[" + this.x + "," + this.y + "]";
}

cv.ImageStream = function(){
	this.data = Buffers([])
	this.writable = true
}

util.inherits(cv.ImageStream, Stream);
var imagestream = cv.ImageStream.prototype;

imagestream.write = function(buf){
	this.data.push(buf)	
	return true;
}


imagestream.end = function(b){
	var self = this;
	
	if (b)
	  imagestream.write.call(this,b);

	var buf = this.data.toBuffer();

	cv.readImage(buf, function(err, im){
	  self.emit('load', im);
	});
}

