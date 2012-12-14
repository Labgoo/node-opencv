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

var BYTE_OFFSET 	= 1;
var INT_OFFSET 		= BYTE_OFFSET * 4;
var DOUBLE_OFFSET 	= BYTE_OFFSET * 8;

MatrixSerializer.prototype.serialize = function (instance){
	var size = instance.size();
	var xSize = size[0];
	var ySize = size[1];
	var buffer = new Buffer(xSize * ySize * DOUBLE_OFFSET + 3 * INT_OFFSET); 
	console.log('buffer length ' + buffer.length + ' x,y ' + xSize + ',' + ySize);
	var offset = 0;
	buffer.writeUInt32BE(xSize, offset);
	offset += INT_OFFSET;
	buffer.writeUInt32BE(ySize, offset);
	offset += INT_OFFSET;
	buffer.writeUInt32BE(instance.type, offset);
	offset += INT_OFFSET;
	for (var y=0; y<ySize; y++){
		for (var x=0; x<xSize; x++){
			buffer.writeDoubleBE(instance.get(x,y), offset);
			offset += DOUBLE_OFFSET;
		}
	}
	console.log('offset ' + offset);
	return buffer.toString('base64');	
}

MatrixSerializer.prototype.deserialize = function (data){
	var buffer = new Buffer(data, 'base64');
	var offset = 0;
	var xSize = buffer.readUInt32BE(offset);
	offset += INT_OFFSET;
	var ySize = buffer.readUInt32BE(offset);
	offset += INT_OFFSET;
	var type = buffer.readUInt32BE(offset);
	var matrix = new cv.Matrix(xSize, ySize, type);

	var i = 3;
	for (var y=0; y<ySize; y++){
		for (var x=0; x<xSize; x++){			
			matrix.set(x, y, buffer.readDoubleBE(offset));
			offset += DOUBLE_OFFSET;
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

