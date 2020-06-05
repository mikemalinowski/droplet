/*

This holds a bunch of math utility functions which are useful
across multiple nodes/commands.

Author : Mike Malinowski : www.twisted.space
*/
#pragma once

// Maya Includes
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MQuaternion.h>
#include <maya/MFloatVector.h>
#include <maya/MEulerRotation.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MTransformationMatrix.h>


namespace DropletMath
{
	/* ---------------------------------------------------------------------- */
	MVector RotationFromTransform(MTransformationMatrix transform, double x_offset = 0, double y_offset = 0, double z_offset = 0)
	{
		MEulerRotation rotation = transform.eulerRotation();

		// -- Roll is in degree's, so convert to degrees to add the roll in and then
		// -- convert it back to radians
		rotation.x = ((rotation.x * 57.2957795) + x_offset) * 0.0174532925;
		rotation.y = ((rotation.y * 57.2957795) + y_offset) * 0.0174532925;
		rotation.z = ((rotation.z * 57.2957795) + z_offset) * 0.0174532925;

		MVector vector(
			rotation.x,
			rotation.y,
			rotation.z
		);

		return vector;
	};

	/* ---------------------------------------------------------------------- */
	MMatrix RelativeMatrix(MMatrix matrix, MMatrix parentWorldSpaceMatrix)
	{
		MMatrix relativeMat4 = matrix * parentWorldSpaceMatrix.inverse();
		return relativeMat4;
	};

	/* ---------------------------------------------------------------------- */
	MTransformationMatrix FormTransform(MMatrix rotationMatrix, MVector translationVector)
	{
		MTransformationMatrix transform = MTransformationMatrix(rotationMatrix);
		transform.setTranslation(translationVector, MSpace::kWorld);
		return transform;
	}

	/* ---------------------------------------------------------------------- */
	/*
	Takes in two Transformation Matrices and extracts out the positions.
	We then return a relative position back.
	*/
	MVector LerpTransformPositions(MTransformationMatrix transformA, MTransformationMatrix transformB, double blend)
	{
		// -- Get the relative vector between the two
		// -- transforms
		MVector positionA = transformA.getTranslation(MSpace::kWorld);
		MVector positionB = transformB.getTranslation(MSpace::kWorld);
		MVector delta = positionA - positionB;

		// -- Factor in the blend and add in the 
		// -- first posisiton to make it relative
		delta = (delta * blend) + positionA;

		return delta;
	}

	/* ---------------------------------------------------------------------- */
	MVector CrossVectors(MVector vectorA, MVector vectorB)
	{
		MVector outVector = vectorA ^ vectorB;

		outVector.normalize();

		return outVector;
	}

	/* ---------------------------------------------------------------------- */
	/*
	Quaternion Slerp function. Implementation taken from:
	http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
	*/
	MQuaternion SlerpQuaternion(MQuaternion qa, MQuaternion qb, double t)
	{
		// quaternion to return
		MQuaternion qm = MQuaternion();

		// Calculate angle between them.
		double cosHalfTheta = qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z;

		// if qa=qb or qa=-qb then theta = 0 and we can return qa
		if (abs(cosHalfTheta) >= 1.0) {
			qm.w = qa.w; qm.x = qa.x; qm.y = qa.y; qm.z = qa.z;
			return qm;
		}

		// Calculate temporary values.
		double halfTheta = acos(cosHalfTheta);
		double sinHalfTheta = sqrt(1.0 - cosHalfTheta * cosHalfTheta);

		// if theta = 180 degrees then result is not fully defined
		// we could rotate around any axis normal to qa or qb
		if (fabs(sinHalfTheta) < 0.001) { // fabs is floating point absolute
			qm.w = (qa.w * 0.5 + qb.w * 0.5);
			qm.x = (qa.x * 0.5 + qb.x * 0.5);
			qm.y = (qa.y * 0.5 + qb.y * 0.5);
			qm.z = (qa.z * 0.5 + qb.z * 0.5);
			return qm;
		}

		double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
		double ratioB = sin(t * halfTheta) / sinHalfTheta;

		//calculate Quaternion.
		qm.w = (qa.w * ratioA + qb.w * ratioB);
		qm.x = (qa.x * ratioA + qb.x * ratioB);
		qm.y = (qa.y * ratioA + qb.y * ratioB);
		qm.z = (qa.z * ratioA + qb.z * ratioB);
		return qm;
	}
}