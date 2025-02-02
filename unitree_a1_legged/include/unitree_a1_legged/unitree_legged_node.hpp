// Copyright 2023 Mobile Robots Laboratory at Poznan University of Technology
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "unitree_a1_legged/unitree_legged_converter.hpp"

#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/joint_state.hpp>

using namespace UNITREE_LEGGED_SDK;

namespace unitree_a1_legged

{
    /**
     * @brief Node for communication with the robot.
     */
    class UnitreeLeggedNode : public rclcpp::Node
    {
    public:
        /**
         * @brief Constructor for the UnitreeLeggedNode class.
         */
        explicit UnitreeLeggedNode(const rclcpp::NodeOptions &options);
        ~UnitreeLeggedNode();

    private:
        int safety_factor_;
        std::thread state_thread_;
        UnitreeLegged unitree_;
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Subscription<unitree_a1_legged_msgs::msg::LowCmd>::SharedPtr low_command_subscriber_;
        rclcpp::Subscription<unitree_a1_legged_msgs::msg::QuadrupedState>::SharedPtr quadruped_command__subscriber_;
        rclcpp::Publisher<unitree_a1_legged_msgs::msg::LowState>::SharedPtr state_publisher_;
        rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_publisher_;
        rclcpp::Publisher<sensor_msgs::msg::Joy>::SharedPtr joystick_publisher_;
        rclcpp::Subscription<unitree_a1_legged_msgs::msg::JointCommand>::SharedPtr joint_state_subscriber_;
        void updateLoop();
        void receiveCommandCallback(const unitree_a1_legged_msgs::msg::LowCmd::SharedPtr msg);
        void receiveJointCommandCallback(const unitree_a1_legged_msgs::msg::JointCommand::SharedPtr msg);
        void updateStateCallback();
    };
} // namespace unitree_a1_legged