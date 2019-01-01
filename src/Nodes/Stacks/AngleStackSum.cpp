/*

Droplet : AngleStackSum

This takes in a list of values and performs the operation
sequentially through them.

Author : Mike Malinowski : www.twisted.space

*/
// -- Maya Includes
#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MDataBlock.h>
#include <maya/MArrayDataHandle.h>

// -- Droplet Includes
#include "AngleStackSum.h"

// -- Declare our plugs
MObject AngleStackSum::values;
MObject AngleStackSum::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* AngleStackSum::creator()
{
    return new AngleStackSum;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus AngleStackSum::initialize()
{
    AngleStackSum n;
    dp::attributes::Create("values", MAngle(0), n, AngleStackSum::values, true, true);
    dp::attributes::Create("result", MAngle(0), n, AngleStackSum::result, false);

    attributeAffects(AngleStackSum::values, AngleStackSum::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus AngleStackSum::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(AngleStackSum::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    MGlobal::displayInfo(MString("Starting Evaluation..."));

    double result = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        result += inputData.inputValue().asAngle().asDegrees();
        MGlobal::displayInfo(MString("\tIndividual Angle : ") + inputData.inputValue().asAngle().asDegrees());
    }

    MGlobal::displayInfo(MString("\tFinal Evaluation : ") + result);

    dataBlock.outputValue(AngleStackSum::result).set(MAngle(result, MAngle::kDegrees));
    //dataBlock.setClean(AngleStackSum::result);

    return MStatus::kSuccess;
}


