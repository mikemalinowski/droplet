/*

This holds the node registration and deregistration
code.

Author : Mike Malinowski : www.twisted.space
*/
#include "droplet.h"
#include "Soft2BoneIk.h"
#include "QuaternionTwist.h"
#include "FloatOpCompound.h"
#include <maya/MFnPlugin.h>


// -- List of all the id's. These are placed here rather than
// -- on the class itself to make it easier to track which 
// -- id's are being used to register.
int idFloatOpCompound = 0x00117fc0;
int idQuaternionTwist = 0x00117fc1;
int idSoft2BoneIk = 0x00117fc2;


MStatus initializePlugin(MObject obj) {

	// -- Define our plugin details
	MFnPlugin plugin(obj, "Mike Malinowski", "1.0", "Any");

	// -- All the nodes registered by this plugin should
	// -- be prefixed with this
	MString nodePrefix = "dp";

	// -- Register our nodes
	MStatus status = plugin.registerNode(
		nodePrefix + "FloatOpCompound",
		MTypeId(idFloatOpCompound),
		FloatOpCompound::creator,
		FloatOpCompound::initialize
	);
	CHECK_MSTATUS_AND_RETURN_IT(status, MStatus::kFailure);

	// -- Register our nodes
	status = plugin.registerNode(
		nodePrefix + "QuaternionTwist",
		MTypeId(idQuaternionTwist),
		QuaternionTwist::creator,
		QuaternionTwist::initialize
	);
	CHECK_MSTATUS_AND_RETURN_IT(status, MStatus::kFailure);

	// -- Register our nodes
	status = plugin.registerNode(
		nodePrefix + "Soft2BoneIk",
		MTypeId(idSoft2BoneIk),
		Soft2BoneIk::creator,
		Soft2BoneIk::initialize
	);
	CHECK_MSTATUS_AND_RETURN_IT(status, MStatus::kFailure);
	return status;
}

MStatus uninitializePlugin(MObject obj) {
	MFnPlugin plugin(obj);

	MStatus status = plugin.deregisterNode(MTypeId(idFloatOpCompound));
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(MTypeId(idQuaternionTwist));
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(MTypeId(idSoft2BoneIk));
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return status;
}
