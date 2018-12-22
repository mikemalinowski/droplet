/*

This holds the node registration and deregistration
code.

Author : Mike Malinowski : www.twisted.space
*/
#pragma once

// Maya Includes
#include <maya/MFnPlugin.h>

// Droplet Includes
#include "Droplet.h"
#include "DropletNode.h"
#include "../Nodes/Stacks/FloatStackSum.h"
#include "../Nodes/Stacks/FloatStackMinus.h"

// Other Includes
#include <vector>

// -----------------------------------------------------------
// This is a shorthand function for registering a node against
// the typed plugin.
template<typename T>
void RegisterNode(MFnPlugin &plugin) {
    MString nodePrefix = "dp";
    MStatus status = plugin.registerNode(
            nodePrefix + T::NodeName(),
            T::Identifier,
            T::creator,
            T::initialize
    );
}

// ------------------------------------------------------------
// This is the plugin entry function which registers all nodes,
// commands and callbacks.
MStatus initializePlugin(MObject obj) {

	// -- Define our plugin details
	MFnPlugin plugin(obj, "Mike Malinowski", "1.0", "Any");

    MStatus status;
    RegisterNode<FloatStackSum>(plugin);
    RegisterNode<FloatStackMinus>(plugin);

    return MStatus::kSuccess;
}

// --------------------------------------------------------
// This is an entry point function to the plugin which unregisters
// and commands, nodes or callbacks
MStatus uninitializePlugin(MObject obj) {

    MFnPlugin plugin(obj);
    MStatus status;

    status = plugin.deregisterNode(FloatStackSum::Identifier);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    status = plugin.deregisterNode(FloatStackMinus::Identifier);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return MStatus::kSuccess;
}