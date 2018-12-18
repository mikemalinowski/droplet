/*

This is a twist node that utilises quaternions to create the 
twist behaviour. Its a bit of a mish-mash of code utilising 
various techniques demonstrated over a variety of rigging 
and math websites.

Author : Mike Malinowski : www.twisted.space
*/

// Maya Includes
#include <maya/MPxNode.h>
#include <maya/MGlobal.h>
#include <maya/MFloatVector.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MMatrix.h>
#include <maya/MQuaternion.h>
#include <maya/MVector.h>
#include <maya/MEulerRotation.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixAttribute.h>

// Droplet Includes
#include "../../Utilities/Math.h"
#include "QuaternionTwist.h"


// Defining our input attributes
MObject QuaternionTwist::Root;
MObject QuaternionTwist::Target;
MObject QuaternionTwist::Twist;
MObject QuaternionTwist::Offset;
MObject QuaternionTwist::ParentMatrix;

// Defining our output attributes
MObject QuaternionTwist::rotation;
MObject QuaternionTwist::translation;


/* ---------------------------------------------------------------------- */
void* QuaternionTwist::creator()
{
	return new QuaternionTwist;
}


/* ---------------------------------------------------------------------- */
MStatus QuaternionTwist::initialize()
{
	// Declare the attribute types we will use
	MFnMatrixAttribute   matrixAttrFn;
	MFnNumericAttribute  numericAttrFn;
	MFnUnitAttribute     unitAttrFn;
	MFnCompoundAttribute compoundAttrFn;

	// Add the input attributes
	QuaternionTwist::Root = matrixAttrFn.create("root", "roo");
	CHECK_MSTATUS_AND_RETURN(addAttribute(QuaternionTwist::Root), MStatus::kFailure);

	QuaternionTwist::Target = matrixAttrFn.create("target", "trg");
	CHECK_MSTATUS_AND_RETURN(addAttribute(QuaternionTwist::Target), MStatus::kFailure);

	QuaternionTwist::Twist = numericAttrFn.create("twist", "tws", MFnNumericData::kDouble);
	numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(QuaternionTwist::Twist), MStatus::kFailure);

	QuaternionTwist::Offset = numericAttrFn.create("offset", "ofs", MFnNumericData::kDouble);
	numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(QuaternionTwist::Offset), MStatus::kFailure);

	QuaternionTwist::ParentMatrix = matrixAttrFn.create("parentWorldSpace", "prnt");
	CHECK_MSTATUS_AND_RETURN(addAttribute(QuaternionTwist::ParentMatrix), MStatus::kFailure);

	// Create the output attributes
	MObject rX = unitAttrFn.create("rotationX", "rx", MFnUnitAttribute::kAngle);
	MObject rY = unitAttrFn.create("rotationY", "ry", MFnUnitAttribute::kAngle);
	MObject rZ = unitAttrFn.create("rotationZ", "rz", MFnUnitAttribute::kAngle);

	QuaternionTwist::rotation = compoundAttrFn.create("rotation", "ro");
	compoundAttrFn.addChild(rX);
	compoundAttrFn.addChild(rY);
	compoundAttrFn.addChild(rZ);
	CHECK_MSTATUS_AND_RETURN(addAttribute(QuaternionTwist::rotation), MStatus::kFailure);

	QuaternionTwist::translation = numericAttrFn.createPoint("translation", "ot");
	CHECK_MSTATUS_AND_RETURN(addAttribute(QuaternionTwist::translation), MStatus::kFailure);

	// Setup the attribute dependencies
	attributeAffects(QuaternionTwist::Root, QuaternionTwist::rotation);
	attributeAffects(QuaternionTwist::Target, QuaternionTwist::rotation);
	attributeAffects(QuaternionTwist::Twist, QuaternionTwist::rotation);
	attributeAffects(QuaternionTwist::ParentMatrix, QuaternionTwist::rotation);
	attributeAffects(QuaternionTwist::Offset, QuaternionTwist::rotation);

	attributeAffects(QuaternionTwist::Root, QuaternionTwist::translation);
	attributeAffects(QuaternionTwist::Target, QuaternionTwist::translation);
	attributeAffects(QuaternionTwist::Twist, QuaternionTwist::translation);
	attributeAffects(QuaternionTwist::ParentMatrix, QuaternionTwist::translation);
	attributeAffects(QuaternionTwist::Offset, QuaternionTwist::translation);


	// Declare the attribute types we will 
	// be using
	return MS::kSuccess;
}


/* ---------------------------------------------------------------------- */
MStatus QuaternionTwist::compute(const MPlug& plug, MDataBlock& dataBlock)
{

	// Read out all the data we need to calculate
	// the twist
	MMatrix rootMatrix = dataBlock.inputValue(QuaternionTwist::Root).asMatrix();
	MMatrix targetMatrix = dataBlock.inputValue(QuaternionTwist::Target).asMatrix();
	MMatrix parentWorldMatrix = dataBlock.inputValue(QuaternionTwist::ParentMatrix).asMatrix();
	double twist = dataBlock.inputValue(QuaternionTwist::Twist).asDouble();
	double offset = dataBlock.inputValue(QuaternionTwist::Offset).asDouble();

	// Utilise transformation matrices during the compute
	MTransformationMatrix transformA(rootMatrix);
	MTransformationMatrix transformB(targetMatrix);

	// -- Split the rotation and the position and lerp/slerp them
	MMatrix rotation_matrix = QuaternionTwist::RotationMatrix(transformA, transformB, twist);
	MVector position_vector = DropletMath::LerpTransformPositions(transformA, transformB, twist);

	// -- Rebuild the 4x4 matrix
	MMatrix twistedWorldSpaceMatrix = DropletMath::FormTransform(rotation_matrix, position_vector).asMatrix();

	// Get the relative matrix between the twistMat4 and the parent global
	MMatrix twistedMatrix = DropletMath::RelativeMatrix(twistedWorldSpaceMatrix, parentWorldMatrix);

	// -- Extract the data we need
	MTransformationMatrix twistedTransform(twistedMatrix);
	MVector rotationVector = DropletMath::RotationFromTransform(twistedTransform, offset);
	MFloatVector translationVector(twistedTransform.getTranslation(MSpace::kWorld));

	// -- Set the output plugs
	dataBlock.outputValue(QuaternionTwist::rotation).set(rotationVector);
	dataBlock.outputValue(QuaternionTwist::translation).set(translationVector);

	// -- Mark the two attributes as being clean (solved)
	dataBlock.setClean(QuaternionTwist::rotation);
	dataBlock.setClean(QuaternionTwist::translation);
	return MStatus::kSuccess;
}


/* ---------------------------------------------------------------------- */
MMatrix QuaternionTwist::RotationMatrix(MTransformationMatrix transformA, MTransformationMatrix transformB, double twistFactor)
{
	MQuaternion slerpedQuaternion = QuaternionTwist::SlerpInterpolation(transformA, transformB, twistFactor);
	MVector     altAxis = QuaternionTwist::ExtractAxis(slerpedQuaternion, 2);

	MVector     axisX = QuaternionTwist::SubtractionVector(transformA, transformB);
	MVector     axisZ = DropletMath::CrossVectors(altAxis, axisX);
	MVector     axisY = DropletMath::CrossVectors(axisZ, axisX);

	MMatrix rotationMatrix = MMatrix();

	rotationMatrix[0][0] = axisX.x;
	rotationMatrix[0][1] = axisX.y;
	rotationMatrix[0][2] = axisX.z;

	rotationMatrix[1][0] = axisY.x;
	rotationMatrix[1][1] = axisY.y;
	rotationMatrix[1][2] = axisY.z;

	rotationMatrix[2][0] = axisZ.x;
	rotationMatrix[2][1] = axisZ.y;
	rotationMatrix[2][2] = axisZ.z;

	return rotationMatrix;
}


/* ---------------------------------------------------------------------- */
MQuaternion QuaternionTwist::SlerpInterpolation(MTransformationMatrix transformA, MTransformationMatrix transformB, double twistFactor)
{
	double xA, yA, zA, wA;
	double xB, yB, zB, wB;

	transformA.getRotationQuaternion(xA, yA, zA, wA);
	transformB.getRotationQuaternion(xB, yB, zB, wB);

	MQuaternion quatA(xA, yA, zA, wA);
	MQuaternion quatB(xB, yB, zB, wB);

	return DropletMath::SlerpQuaternion(quatA, quatB, twistFactor);
}


/* ---------------------------------------------------------------------- */
MVector QuaternionTwist::SubtractionVector(MTransformationMatrix transformA, MTransformationMatrix transformB)
{
	MVector vecA = transformA.getTranslation(MSpace::kWorld);
	MVector vecB = transformB.getTranslation(MSpace::kWorld);

	MVector sub = vecA - vecB;

	sub.normalize();

	return sub;
}


/* ---------------------------------------------------------------------- */
MVector QuaternionTwist::ExtractAxis(MQuaternion q, int row_id)
{
	MTransformationMatrix transform = MTransformationMatrix();
	transform.setRotationQuaternion(q.x, q.y, q.z, q.w);
	MMatrix rotationMat4 = transform.asRotateMatrix();

	MVector outVector = MVector();

	outVector.x = rotationMat4[row_id][0];
	outVector.y = rotationMat4[row_id][1];
	outVector.z = rotationMat4[row_id][2];

	return outVector;
}

