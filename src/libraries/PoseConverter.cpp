/**
 *
 * \file PoseConverter.cpp
 * \brief
 *
 * \author Andrew Price
 * \date May 30, 2013
 *
 * \copyright
 * Copyright (c) 2013, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Humanoid Robotics Lab Georgia Institute of Technology
 * Director: Mike Stilman http://www.golems.org
 *
 *
 * This file is provided under the following "BSD-style" License:
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided
 *   with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "hubo_motion_ros/PoseConverter.h"

namespace hubo_motion_ros
{
Eigen::Vector3f toEVector3(const urdf::Vector3 &vector)
{
	Eigen::Vector3f newVector;
	newVector.x() = vector.x;
	newVector.y() = vector.y;
	newVector.z() = vector.z;
	return newVector;
}

Eigen::Isometry3f toIsometry(geometry_msgs::Pose& pose)
{
	Eigen::Isometry3f result = Eigen::Isometry3f::Identity();
	Eigen::Vector3f trans(pose.position.x,pose.position.y,pose.position.z);
	Eigen::Quaternionf quat(pose.orientation.w,pose.orientation.x,pose.orientation.y,pose.orientation.z);

	result.translate(trans);
	result.rotate(quat);

	return result;
}
Eigen::Isometry3f toIsometry(tf::Transform& pose)
{
	Eigen::Isometry3f result = Eigen::Isometry3f::Identity();
	tf::Vector3 tVec = pose.getOrigin();
	tf::Quaternion tQuat = pose.getRotation();
	Eigen::Vector3f trans(tVec.x(),tVec.y(),tVec.z());
	Eigen::Quaternionf quat(tQuat.w(),tQuat.x(),tQuat.y(),tQuat.z());

	result.translate(trans);
	result.rotate(quat);

	return result;
}

tf::Transform toTF(geometry_msgs::Pose& pose)
{
	tf::Transform newTF;
	tf::poseMsgToTF(pose, newTF);
	return newTF;
}

geometry_msgs::Point toGMPoint3(const urdf::Vector3 &vector)
{
	geometry_msgs::Point newPoint;
	newPoint.x = vector.x;
	newPoint.y = vector.y;
	newPoint.z = vector.z;
	return newPoint;
}

geometry_msgs::Quaternion toGMQuaternion(const urdf::Rotation &rotation)
{
	geometry_msgs::Quaternion newQuaternion;
	rotation.getQuaternion(
				newQuaternion.x,
				newQuaternion.y,
				newQuaternion.z,
				newQuaternion.w);
	return newQuaternion;
}

geometry_msgs::Pose toPose(tf::Transform& pose)
{
	geometry_msgs::Pose newPose;
	tf::poseTFToMsg(pose, newPose);
	return newPose;
}

geometry_msgs::Pose toPose(const urdf::Pose &pose)
{
	geometry_msgs::Pose newPose;
	newPose.position = toGMPoint3(pose.position);
	newPose.orientation = toGMQuaternion(pose.rotation);
	return newPose;
}

} /* namespace hubo_manipulation_planner */
