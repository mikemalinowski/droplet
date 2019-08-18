/*

Droplet : TransformMixer

Takes in a list of matrices and for each one the

Author : Mike Malinowski : www.twisted.space

*/

#include <maya/MMatrix.h>
#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MDataBlock.h>
#include <maya/MArrayDataHandle.h>

// -- Droplet Includes
#include "TransformMixer.h"

// -- Declare our plugs
MObject TransformMixer::weights;
MObject TransformMixer::poses;
MObject TransformMixer::tracks;
MObject TransformMixer::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* TransformMixer::creator()
{
	return new TransformMixer;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus TransformMixer::initialize()
{
	MMatrix m;
	TransformMixer n;
	dp::attributes::Create("weights", float(0), n, TransformMixer::weights, true, true);

	// -- Create the tracks attribute, this is where we store
	// -- all the matrix poses
	MFnMatrixAttribute matrixFn;

	MStatus status;
	TransformMixer::tracks = matrixFn.create("tracks", "tracks", matrixFn.kDouble, &status);
	matrixFn.setArray(true);
	matrixFn.setKeyable(true);
	matrixFn.setWritable(true);
	matrixFn.setStorable(true);

	// -- Create the compound
	MFnCompoundAttribute compoundFn;

	TransformMixer::poses = compoundFn.create("poses", "poses", &status);
	compoundFn.addChild(TransformMixer::tracks);
	compoundFn.setArray(true);

	// -- Add the track attribute
	addAttribute(TransformMixer::poses);

	// -- Add our output attribute
	dp::attributes::Create("result", m, n, TransformMixer::result, true, false);
	// setUsesArrayDataBuilder

	// -- Setup our attribute dependencies
	attributeAffects(TransformMixer::weights, TransformMixer::result);
	attributeAffects(TransformMixer::tracks, TransformMixer::result);
	attributeAffects(TransformMixer::poses, TransformMixer::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus TransformMixer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MGlobal::displayInfo("Beep");
	return MStatus::kSuccess;
}