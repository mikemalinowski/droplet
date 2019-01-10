/*

Droplet : FootPivot

This is an implementation of a foot pivot node

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
#include "FootPivot.h"

// Attribute Inputs
MObject FootPivot::BaseMatrix;
MObject FootPivot::RightMatrix;
MObject FootPivot::LeftMatrix;
MObject FootPivot::RearMatrix;
MObject FootPivot::FrontMatrix;
MObject FootPivot::BridgeMatrix;
MObject FootPivot::AnchorMatrix;

// These are our main animatable attributes
MObject FootPivot::Roll;
MObject FootPivot::Bank;
MObject FootPivot::Ball;

// These are our setup attributes
MObject FootPivot::MaxRoll;
MObject FootPivot::MaxBridge;
MObject FootPivot::MaxBank;
MObject FootPivot::MaxBall;

// Output attributes
MObject FootPivot::Demo;


/* ---------------------------------------------------------------------- */
void* FootPivot::creator()
{
    return new FootPivot;
}


/* ---------------------------------------------------------------------- */
MStatus FootPivot::initialize()
{
    // Grab the function sets for the attribute
    // types we will need
    MFnNumericAttribute numericAttrFn;
    MFnMatrixAttribute  matrixAttrFn;

    FootPivot n;
    dp::attributes::Create("baseMatrix", MMatrix(), n, FootPivot::BaseMatrix, true);
    dp::attributes::Create("rightMatrix", MMatrix(), n, FootPivot::RightMatrix, true);
    dp::attributes::Create("leftMatrix", MMatrix(), n, FootPivot::LeftMatrix, true);
    dp::attributes::Create("rearMatrix", MMatrix(), n, FootPivot::RearMatrix, true);
    dp::attributes::Create("frontMatrix", MMatrix(), n, FootPivot::FrontMatrix, true);
    dp::attributes::Create("bridgeMatrix", MMatrix(), n, FootPivot::BridgeMatrix, true);
    dp::attributes::Create("anchorMatrix", MMatrix(), n, FootPivot::AnchorMatrix, true);

    dp::attributes::Create("roll", float(0), n, FootPivot::Roll, true);
    dp::attributes::Create("bank", float(0), n, FootPivot::Bank, true);
    dp::attributes::Create("ball", float(0), n, FootPivot::Ball, true);

    dp::attributes::Create("maxRoll", float(0), n, FootPivot::MaxRoll, true);
    dp::attributes::Create("maxBridge", float(0), n, FootPivot::MaxBridge, true);
    dp::attributes::Create("maxBank", float(0), n, FootPivot::MaxBank, true);
    dp::attributes::Create("maxBall", float(0), n, FootPivot::MaxBall, true);

    // Define our output attributes
    dp::attributes::Create("demoMatrix", MMatrix(), n, FootPivot::Demo, false);

    attributeAffects(FootPivot::BaseMatrix, FootPivot::Demo);
    attributeAffects(FootPivot::RightMatrix, FootPivot::Demo);
    attributeAffects(FootPivot::LeftMatrix, FootPivot::Demo);
    attributeAffects(FootPivot::RearMatrix, FootPivot::Demo);
    attributeAffects(FootPivot::FrontMatrix, FootPivot::Demo);
    attributeAffects(FootPivot::BridgeMatrix, FootPivot::Demo);
    attributeAffects(FootPivot::AnchorMatrix, FootPivot::Demo);

    attributeAffects(FootPivot::Roll, FootPivot::Demo);
    attributeAffects(FootPivot::Bank, FootPivot::Demo);
    attributeAffects(FootPivot::Ball, FootPivot::Demo);

    attributeAffects(FootPivot::MaxRoll, FootPivot::Demo);
    attributeAffects(FootPivot::MaxBridge, FootPivot::Demo);
    attributeAffects(FootPivot::MaxBank, FootPivot::Demo);
    attributeAffects(FootPivot::MaxBall, FootPivot::Demo);

    return MS::kSuccess;
}


/* ---------------------------------------------------------------------- */
MStatus FootPivot::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get our matrix inputs
    MMatrix baseMatrix = dataBlock.inputValue(FootPivot::BaseMatrix).asMatrix();
    MMatrix rightMatrix = dataBlock.inputValue(FootPivot::RightMatrix).asMatrix();
    MMatrix leftMatrix = dataBlock.inputValue(FootPivot::LeftMatrix).asMatrix();
    MMatrix rearMatrix = dataBlock.inputValue(FootPivot::RearMatrix).asMatrix();
    MMatrix frontMatrix = dataBlock.inputValue(FootPivot::FrontMatrix).asMatrix();
    MMatrix bridgeMatrix = dataBlock.inputValue(FootPivot::BridgeMatrix).asMatrix();
    MMatrix anchorMatrix = dataBlock.inputValue(FootPivot::AnchorMatrix).asMatrix();

    // -- Get our setup values
    double maxRoll = dataBlock.inputValue(FootPivot::MaxRoll).asDouble();
    double maxBridge = dataBlock.inputValue(FootPivot::MaxBridge).asDouble();
    double maxBank = dataBlock.inputValue(FootPivot::MaxBank).asDouble();
    double maxBall = dataBlock.inputValue(FootPivot::MaxBall).asDouble();

    // -- Get our animated input values
    double roll = dataBlock.inputValue(FootPivot::Roll).asDouble();
    double bank = dataBlock.inputValue(FootPivot::Bank).asDouble();
    double ball = dataBlock.inputValue(FootPivot::Ball).asDouble();

    // -- Construct our transformation matrix
    MTransformationMatrix transform(baseMatrix);

    return MStatus::kSuccess;
}
