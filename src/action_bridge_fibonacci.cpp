// Copyright 2019 Fraunhofer IPA
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// Currently works with ros2 run action_tutorials fibonacci_action_server.py and rosrun actionlib_tutorials fibonacci_client
//run action bridge with ros2 run action_bridge action_bridge_fibonacci_node

//For dashing, git clone control_msgs crystal-devel

#include <action_bridge/action_bridge.hpp>

#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-parameter"
#endif
#include <actionlib_tutorials/FibonacciAction.h>
#ifdef __clang__
# pragma clang diagnostic pop
#endif

// include ROS 2
//#include <example_interfaces/action/fibonacci.hpp>
#include <action_tutorials/action/fibonacci.hpp>

using FibonacciActionBridge = ActionBridge<actionlib_tutorials::FibonacciAction,
    action_tutorials::action::Fibonacci>;

template<>
void FibonacciActionBridge::translate_goal_1_to_2(const ROS1Goal & goal1, ROS2Goal & goal2)
{
  goal2.order = goal1.order;
}

template<>
void FibonacciActionBridge::translate_result_2_to_1(
  ROS1Result & result1,
  const ROS2Result & result2)
{
  result1.sequence = result2.sequence;
}

template<>
void FibonacciActionBridge::translate_feedback_2_to_1(
  ROS1Feedback & feedback1,
  const ROS2Feedback & feedback2)
{
  feedback1.sequence = feedback2.partial_sequence;
}

int main(int argc, char * argv[])
{
  return FibonacciActionBridge::main("fibonacci", argc, argv);
}
