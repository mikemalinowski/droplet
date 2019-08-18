/*

Droplet : Soft2BoneIk

This is an implementation of the Soft IK solver described in
Andy Nicholas' blog here:
	http://www.softimageblog.com/archives/108

This is not an IK solver, but a node which can be utilised
and hooked into the chain being solved to increase the translation
of the joints to soften the IK snap.

Author : Mike Malinowski : www.twisted.space
*/

// High level includes
#include <maya/MPxNode.h>
#include <maya/MGlobal.h>
#include <maya/MFnStringData.h>
#include <maya/MVector.h>
#include <maya/MDataBlock.h>
#include <maya/MMatrix.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnTypedAttribute.h>

// Droplet Includes
#include "Soft2BoneIk.h"

// Attribute Inputs
MObject Soft2BoneIk::FirstBoneLength;
MObject Soft2BoneIk::SecondBoneLength;

MObject Soft2BoneIk::AdditionalFirstBoneStretch;
MObject Soft2BoneIk::AdditionalSecondBoneStretch;

MObject Soft2BoneIk::RootTarget;
MObject Soft2BoneIk::EffectorTarget;
MObject Soft2BoneIk::PinTarget;

MObject Soft2BoneIk::Stretch;
MObject Soft2BoneIk::SoftDistance;
MObject Soft2BoneIk::Pin;

// Attribute Outputs
MObject Soft2BoneIk::FirstBoneResult;
MObject Soft2BoneIk::SecondBoneResult;


/* ---------------------------------------------------------------------- */
void* Soft2BoneIk::creator()
{
	return new Soft2BoneIk;
}


/* ---------------------------------------------------------------------- */
MStatus Soft2BoneIk::initialize()
{
	// Grab the function sets for the attribute
	// types we will need
	MFnNumericAttribute numericAttrFn;
	MFnMatrixAttribute  matrixAttrFn;

	// Add the default length attributes
	Soft2BoneIk::FirstBoneLength = numericAttrFn.create("firstBoneLength", "fbl", MFnNumericData::kDouble);
	//numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::FirstBoneLength), MStatus::kFailure);


	Soft2BoneIk::SecondBoneLength = numericAttrFn.create("secondBoneLength", "sbl", MFnNumericData::kDouble);
	//numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::SecondBoneLength), MStatus::kFailure);

	// Add the default length attributes
	Soft2BoneIk::AdditionalFirstBoneStretch = numericAttrFn.create("additionalFirstBoneStretch", "afs", MFnNumericData::kDouble);
	//numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::AdditionalFirstBoneStretch), MStatus::kFailure);

	Soft2BoneIk::AdditionalSecondBoneStretch = numericAttrFn.create("additionalSecondBoneStretch", "ass", MFnNumericData::kDouble);
	//numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::AdditionalSecondBoneStretch), MStatus::kFailure);

	// Now add the Matrix Parameters
	Soft2BoneIk::RootTarget = matrixAttrFn.create("rootTarget", "wub");
	matrixAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::RootTarget), MStatus::kFailure);

	Soft2BoneIk::EffectorTarget = matrixAttrFn.create("effectorTarget", "wta");
	matrixAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::EffectorTarget), MStatus::kFailure);

	Soft2BoneIk::PinTarget = matrixAttrFn.create("pinTarget", "pta");
	matrixAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::PinTarget), MStatus::kFailure);

	// Add the animation sliders
	Soft2BoneIk::Stretch = numericAttrFn.create("stretch", "str", MFnNumericData::kDouble);
	numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::Stretch), MStatus::kFailure);

	// Add the soft IK atttributes
	Soft2BoneIk::SoftDistance = numericAttrFn.create("softDistance", "sdt", MFnNumericData::kDouble);
	numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::SoftDistance), MStatus::kFailure);

	// Add the soft IK atttributes
	Soft2BoneIk::Pin = numericAttrFn.create("pin", "pin", MFnNumericData::kDouble);
	numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::Pin), MStatus::kFailure);

	// Now add the output attributes
	Soft2BoneIk::FirstBoneResult = numericAttrFn.create("firstBoneResult", "fbr", MFnNumericData::kDouble);
	numericAttrFn.setWritable(false);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::FirstBoneResult), MStatus::kFailure);

	Soft2BoneIk::SecondBoneResult = numericAttrFn.create("secondBoneResult", "sbrx", MFnNumericData::kDouble);
	numericAttrFn.setWritable(false);
	CHECK_MSTATUS_AND_RETURN(addAttribute(Soft2BoneIk::SecondBoneResult), MStatus::kFailure);


	// Define the attribute dependency
	attributeAffects(Soft2BoneIk::FirstBoneLength, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::SecondBoneLength, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::AdditionalFirstBoneStretch, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::AdditionalSecondBoneStretch, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::RootTarget, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::EffectorTarget, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::Stretch, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::SoftDistance, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::Pin, Soft2BoneIk::FirstBoneResult);
	attributeAffects(Soft2BoneIk::PinTarget, Soft2BoneIk::FirstBoneResult);

	attributeAffects(Soft2BoneIk::FirstBoneLength, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::SecondBoneLength, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::AdditionalFirstBoneStretch, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::AdditionalSecondBoneStretch, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::RootTarget, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::EffectorTarget, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::Stretch, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::SoftDistance, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::Pin, Soft2BoneIk::SecondBoneResult);
	attributeAffects(Soft2BoneIk::PinTarget, Soft2BoneIk::SecondBoneResult);

	return MS::kSuccess;
}


/* ---------------------------------------------------------------------- */
MStatus Soft2BoneIk::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	// -- These values are addative overrides. They allow the 
	// -- user to extend the amount of stretch arbitrarily of
	// -- distance
	double upperAddition = dataBlock.inputValue(Soft2BoneIk::AdditionalFirstBoneStretch).asDouble();
	double lowerAddition = dataBlock.inputValue(Soft2BoneIk::AdditionalSecondBoneStretch).asDouble();

	// -- Get the normal bone lengths to allow us to determine
	// -- how much (if any) stretch should occur. We then add
	// -- the static additions onto it
	double firstBoneValue = (dataBlock.inputValue(Soft2BoneIk::FirstBoneLength).asDouble()) + upperAddition;
	double secondBoneValue = (dataBlock.inputValue(Soft2BoneIk::SecondBoneLength).asDouble()) + lowerAddition;
	double firstBoneLength = abs(firstBoneValue);
	double secondBoneLength = abs(secondBoneValue);

	// -- Check how far this two bone chain should actually be
	// -- able to stretch to
	double maximumLength = firstBoneLength + secondBoneLength;

	// -- Using the expected lengths we work out what factor
	// -- each bone needs to take when stretching
	double upperFactor = firstBoneLength / maximumLength;
	double lowerFactor = secondBoneLength / maximumLength;

	// -- Get the value which determines how much we should allow
	// -- for stretching. A factor of zero is no stretch whilst
	// -- a factor of 1 is full stretch.
	double stretchFactor = dataBlock.inputValue(Soft2BoneIk::Stretch).asDouble();

	// -- Get the matrices of the two nodes we need to measure. These
	// -- are expected to be worldspace matrices.
	MMatrix rootMatrix = dataBlock.inputValue(Soft2BoneIk::RootTarget).asMatrix();
	MMatrix effectorMatrix = dataBlock.inputValue(Soft2BoneIk::EffectorTarget).asMatrix();

	// -- Extract out the positions from the two matrices
	MVector rootPosition(rootMatrix[3][0], rootMatrix[3][1], rootMatrix[3][2]);
	MVector effectorPosition(effectorMatrix[3][0], effectorMatrix[3][1], effectorMatrix[3][2]);

	// -- Find the distance between the root and the effector
	MVector delta = rootPosition - effectorPosition;
	double distance = delta.length();

	// -- Get the distance from which we should start applying
	// -- softening
	double margin = dataBlock.inputValue(Soft2BoneIk::SoftDistance).asDouble();
	double beginSoftening = maximumLength - margin;

	// -- Only calculate the soft ik if we're within the softening range
	if (distance > beginSoftening)
	{
		// -- Calculate the softening
		double shortd = margin * (1.0 - exp(-(distance - beginSoftening) / margin)) + beginSoftening;
		double scale = distance / shortd;

		// -- Add the softening to the additions
		upperAddition += ((firstBoneLength * scale) - firstBoneLength) * stretchFactor;
		lowerAddition += ((secondBoneLength * scale) - secondBoneLength) * stretchFactor;

	}

	// -- Now we check for pinning
	double upperPinAddition = 0;
	double lowerPinAddition = 0;
	double pinning = dataBlock.inputValue(Soft2BoneIk::Pin).asDouble();

	if (pinning != 0)
	{
		// -- Get the worldspace position of the pin object
		MMatrix pinMatrix = dataBlock.inputValue(Soft2BoneIk::PinTarget).asMatrix();
		MVector pinPosition(pinMatrix[3][0], pinMatrix[3][1], pinMatrix[3][2]);

		upperPinAddition = MVector(rootPosition - pinPosition).length() - firstBoneLength;
		lowerPinAddition = MVector(effectorPosition - pinPosition).length() - secondBoneLength;

		// -- Determine what the additive difference is to apply
		// -- the pinning
		upperPinAddition *= pinning;
		lowerPinAddition *= pinning;

		// -- Share the pinning and the stretch to ensure we
		// -- do not get a doubling of the result
		upperAddition *= 1.0 - pinning;
		lowerAddition *= 1.0 - pinning;
	}

	// -- Resolve the final values and ensure we use the
	// -- correct inversion values based on the expected
	// -- default lengths
	double resolvedFirstBone = firstBoneLength + upperAddition + upperPinAddition;
	double resolvedSecondBone = secondBoneLength + lowerAddition + lowerPinAddition;

		if (firstBoneValue < 0.0) {
			resolvedFirstBone *= -1;
		}

		if (secondBoneValue < 0.0) {
			resolvedSecondBone *= -1;
		}

	// -- Assign the output values
	dataBlock.outputValue(Soft2BoneIk::FirstBoneResult).set(resolvedFirstBone);
	dataBlock.outputValue(Soft2BoneIk::SecondBoneResult).set(resolvedSecondBone);
	
	// -- Mark the two attributes as being clean (solved)
	dataBlock.setClean(Soft2BoneIk::FirstBoneResult);
	dataBlock.setClean(Soft2BoneIk::SecondBoneResult);
	
	return MStatus::kSuccess;
}
