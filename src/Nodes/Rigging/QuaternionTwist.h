/*

This is a twist node that utilises quaternions to create the
twist behaviour. Its a bit of a mish-mash of code utilising
various techniques demonstrated over a variety of rigging
and math websites.

Author : Mike Malinowski : www.twisted.space
*/
#include <maya/MPxNode.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MGlobal.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MQuaternion.h>
#include <maya/MVector.h>


/* ---------------------------------------------------------------------- */
class QuaternionTwist : public MPxNode
{
public:

	static void* creator();
	static MStatus initialize();
	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

	// Define our input plugs
	static MObject Root;
	static MObject Target;
	static MObject Twist;
	static MObject Offset;
	static MObject ParentMatrix;

	// Define our output plugs
	static MObject rotation;
	static MObject translation;

private:

	// -- Set of private calculation functions
	static MMatrix     RotationMatrix(MTransformationMatrix transformA, MTransformationMatrix transformB, double twistFactor);
	static MQuaternion SlerpInterpolation(MTransformationMatrix transformA, MTransformationMatrix transformB, double twistFactor);
	static MVector     SubtractionVector(MTransformationMatrix transformA, MTransformationMatrix transformB);
	static MVector     ExtractAxis(MQuaternion quaternion, int row_id);

};


