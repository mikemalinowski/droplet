/*

Droplet : FacialMatrixBlender

This is used to operate on matrix transforms much like how we're
used to operating on blendshapes. Each pose is additively applied
based on a given weighting.

*/

// -- Droplet Includes
#include "FacialMatrixBlender.h"

#include <maya/MIOStream.h>

#include <maya/MPxNode.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MQuaternion.h>
#include <maya/MTransformationMatrix.h>

#include <maya/MDataBlock.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MArrayDataBuilder.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnMessageAttribute.h>

#include "../../Utilities/MathLib.h"
#include <unordered_map>

using namespace std;
// -- Declare our plugs
MObject FacialMatrixBlender::neutralTracks;
MObject FacialMatrixBlender::poseList;
MObject FacialMatrixBlender::posedTracks;
MObject FacialMatrixBlender::weight;
MObject FacialMatrixBlender::results;
MObject FacialMatrixBlender::label;
MObject FacialMatrixBlender::targets;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FacialMatrixBlender::creator()
{
	return new FacialMatrixBlender;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FacialMatrixBlender::initialize()
{
	// -- We use the droplet convenience function for adding
	// -- attributes to our node, to do that we need to pass
	// -- it as an object
	FacialMatrixBlender n;

	// -- To utilize the droplet functions, we need to give an 
	// -- instance of the variable type we want to add. As we
	// -- use matrices a lot in this node, lets create a single
	// -- matrix to pass through.
	MMatrix m;
	MStatus status;

	// -- All the poses in the pose list may have a label to help 
	// -- identify them. This is not used in any calculation, and 
	// -- does not invoke an evaluation but it is useful for tooling
	// -- and to allow the user to identify their poses
	dp::attributes::Create("label", "", n, FacialMatrixBlender::label, true, false);

	// -- Add the list of target nodes, these allow us to keep track
	// -- of the targets and their order even after they are disconnected
	// -- from the matrices
	MMessage message;
	dp::attributes::Create("targets", message, n, FacialMatrixBlender::targets, true, true);

	// -- This attribute allows the user to specify how much
	// -- of the matrix should come through
	dp::attributes::Create("weight", float(0), n, FacialMatrixBlender::weight, true, false);

	// -- This defines the 'default' pose of all the objects
	// -- that make up the pose. 
	dp::attributes::Create("neutralTracks", m, n, FacialMatrixBlender::neutralTracks, true, true);

	// -- This is a list of all the transform tracks which go
	// -- into each pose
	dp::attributes::Create("tracks", m, n, FacialMatrixBlender::posedTracks, true, true);

	// -- Each pose is made up of a weight and a set of matrix
	// -- tracks. We compound them together
	MFnCompoundAttribute compoundFn;
	FacialMatrixBlender::poseList = compoundFn.create("poses", "poses", &status);

	compoundFn.addChild(FacialMatrixBlender::weight);
	compoundFn.addChild(FacialMatrixBlender::posedTracks);
	compoundFn.addChild(FacialMatrixBlender::label);
	compoundFn.setArray(true);
	compoundFn.setWritable(true);
	compoundFn.setStorable(true);

	addAttribute(FacialMatrixBlender::poseList);

	// -- Finally we add our output plug, this will hold all the fully
	// -- resolved attributes
	dp::attributes::Create("results", m, n, FacialMatrixBlender::results, false, true, true);

	// -- Now we have all our attributes in place we need to define
	// -- which input attributes of the node affect which outputs
	attributeAffects(weight, results);
	attributeAffects(neutralTracks, results);
	attributeAffects(posedTracks, results);
	attributeAffects(poseList, results);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FacialMatrixBlender::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	// -- We only want to process if we're being asked for the values of
	// -- our output plug (results)
	if (plug == FacialMatrixBlender::results)
	{

		// -- Firstly, we need to get the data for our neutral
		// -- poses, as this serves as the base, as well as the 
		// -- weights handle
		MArrayDataHandle neutralTracksHandle = dataBlock.inputArrayValue(FacialMatrixBlender::neutralTracks);
		MDataHandle weightsHandle = dataBlock.inputValue(FacialMatrixBlender::weight);

		// -- Vectors are nice and simple to work with, so we create
		// -- a couple to start collating our data in
		std::vector<MTransformationMatrix> neutralTrackList;
		//std::vector<MVector> neutralTranslation;
		//std::vector<MQuaternion> neutralRotation;

		std::vector<MTransformationMatrix> resultsList;

		// -- We start by populating our neutral track vector, but we
		// -- also want to get the count so we can compare when it comes
		// -- to posed tracks
		int neutralTracksCount = neutralTracksHandle.elementCount();

		for (int trackIdx = 0; trackIdx < neutralTracksCount; trackIdx++)
		{
			// Get the matrix from the list
			neutralTracksHandle.jumpToArrayElement(trackIdx);
			MMatrix m = neutralTracksHandle.inputValue().asMatrix();

			// -- We store this neutral matrix, but we also initiate a blank matrix
			// -- for the output. This guarantees that our results will always be of 
			// -- the same length as the neutral tracks
			neutralTrackList.push_back(MTransformationMatrix(m));
			resultsList.push_back(MTransformationMatrix(m));
		}

		// -- Now we can cycle our pose list
		MArrayDataHandle poseListHandle = dataBlock.inputArrayValue(FacialMatrixBlender::poseList);
		int poseCount = poseListHandle.elementCount();

		for (int poseIdx = 0; poseIdx < poseCount; poseIdx++)
		{
			poseListHandle.jumpToElement(poseIdx);

			// -- Get the weight of this individual pose
			float weight = poseListHandle.inputValue().child(FacialMatrixBlender::weight).asFloat();

			// -- If there is no weighting, we don't need to process it
			if (weight == 0.0)
			{
				continue;
			}

			// -- We now need to get the pose tracks
			MArrayDataHandle posedTracksHandle = poseListHandle.inputValue().child(FacialMatrixBlender::posedTracks);

			int posedTracksCount = posedTracksHandle.elementCount();

			// -- If this does not have parity with our neutral tracks, we do not process it
			if (posedTracksCount != neutralTracksCount)
			{
				MString pose_name = poseListHandle.inputValue().child(FacialMatrixBlender::label).asString();
				MGlobal::displayInfo(MString("Pose ") + pose_name + MString("has track count miss match. Pose Track Count: ") + posedTracksCount + MString(", Neutral Track Count: ") + neutralTracksCount);
				continue;
			}

			// -- We can now cycle the posed track count, and do the matrix operations
			// -- required of the node
			for (int posedTrackIdx = 0; posedTrackIdx < posedTracksCount; posedTrackIdx++)
			{
				posedTracksHandle.jumpToElement(posedTrackIdx);

				MMatrix trackMatrix = posedTracksHandle.inputValue().asMatrix();
				MTransformationMatrix trackTransform = MTransformationMatrix(trackMatrix);

				// -- We need to get the trackMatrix variable relative to the neutral pose for the
				// -- same track
				MMatrix relativeMatrix = trackMatrix * neutralTrackList[posedTrackIdx].asMatrix().inverse();
				MTransformationMatrix relativeTransformMatrix = MTransformationMatrix(relativeMatrix);

				// -- Rotation
				double rx, ry, rz, rw;
				relativeTransformMatrix.getRotationQuaternion(rx, ry, rz, rw, MSpace::kWorld);

				MQuaternion relativeQuaternion = MQuaternion(rx, ry, rz, rw);
				MQuaternion identityQuaternion = MQuaternion();

				MQuaternion weightedQuaternion = DropletMath::SlerpQuaternion(identityQuaternion, relativeQuaternion, weight);
				//resultsList[posedTrackIdx].addRotationQuaternion(rx, ry, rz, rw, MSpace::kWorld);
				resultsList[posedTrackIdx].addRotationQuaternion(weightedQuaternion.x, weightedQuaternion.y, weightedQuaternion.z, weightedQuaternion.w, MSpace::kWorld);

				// -- Scale
				double scale[3];
				trackTransform.getScale(scale, MSpace::kTransform);
				resultsList[posedTrackIdx].addScale(scale, MSpace::kTransform);

				// -- Translation
				MVector posedTranslation = trackTransform.getTranslation(MSpace::kTransform);
				MVector neutralTranslation = neutralTrackList[posedTrackIdx].getTranslation(MSpace::kTransform);
				MVector translationDelta = (posedTranslation - neutralTranslation) * weight;
				resultsList[posedTrackIdx].addTranslation(translationDelta, MSpace::kTransform);

			}
		}

		// -- Now all our calculations are complete we can start to 
		// -- apply our output data. We get the data handle for the 
		// -- output plug
		MStatus status;
		MArrayDataHandle resultsHandle = dataBlock.outputArrayValue(FacialMatrixBlender::results, &status);
		CHECK_MSTATUS_AND_RETURN(status, MStatus::kFailure);

		// -- We now need to create a data builder to populate 
		MArrayDataBuilder dataBuilder = resultsHandle.builder(&status);
		CHECK_MSTATUS_AND_RETURN(status, MStatus::kFailure);

		// -- Cycle our results, and add them to the data builder	
		for (float idx = 0; idx < resultsList.size(); idx++)
		{
			MDataHandle dataHandle = dataBuilder.addElement(idx);
			dataHandle.setMMatrix(resultsList[idx].asMatrix());
		}

		// -- Finally set the data of the plug
		resultsHandle.set(dataBuilder);

		// -- Mark this plug as clean, this ensures it will not re-calculate until
		// -- its inputs become dirty again
		dataBlock.setClean(FacialMatrixBlender::results);

	}
	return MStatus::kSuccess;
}