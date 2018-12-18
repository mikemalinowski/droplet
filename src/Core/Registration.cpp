/*

This holds the node registration and deregistration
code.

Author : Mike Malinowski : www.twisted.space
*/
#include "Registration.h"
#include "../Nodes/Rigging/Soft2BoneIk.h"
#include "../Nodes/Rigging/QuaternionTwist.h"
#include "../Nodes/Utility/FloatOpCompound.h"
#include "../Nodes/Stacks/FloatStackSum.h"
#include <maya/MFnPlugin.h>
#include <vector>


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
	CHECK_MSTATUS_AND_RETURN_IT(status);

	// -- Register our nodes
	status = plugin.registerNode(
			nodePrefix + "QuaternionTwist",
			MTypeId(idQuaternionTwist),
			QuaternionTwist::creator,
			QuaternionTwist::initialize
	);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	// -- Register our nodes
	status = plugin.registerNode(
			nodePrefix + "Soft2BoneIk",
			MTypeId(idSoft2BoneIk),
			Soft2BoneIk::creator,
			Soft2BoneIk::initialize
	);
	CHECK_MSTATUS_AND_RETURN_IT(status);


	// -- Register our nodes
	status = plugin.registerNode(
			nodePrefix + FloatStackSum::NodeName(),
			MTypeId(FloatStackSum::TypeId),
			FloatStackSum::creator,
			FloatStackSum::initialize
	);
	CHECK_MSTATUS_AND_RETURN_IT(status);
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

	status = plugin.deregisterNode(MTypeId(FloatStackSum::TypeId));
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}