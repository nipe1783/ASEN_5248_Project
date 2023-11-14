from launch import LaunchDescription
from launch.actions import ExecuteProcess, SetEnvironmentVariable, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    package_dir = get_package_share_directory('gazebo_pkg')
    world_file = os.path.join(package_dir, 'worlds', 'my_world.world')
    models_path = os.path.join(package_dir, 'models')
    controllers_config = os.path.join(package_dir, 'models', 'rs_robot', 'config', 'controllers.yaml')
    print(controllers_config)
    
    # Set the GAZEBO_MODEL_PATH environment variable
    set_model_path = SetEnvironmentVariable(
        name='GAZEBO_MODEL_PATH',
        value=[models_path, os.pathsep, os.environ.get('GAZEBO_MODEL_PATH', '')]
    )

    # Node for controller manager
    controller_manager_node = Node(
        package='controller_manager',
        executable='ros2_control_node',
        parameters=[controllers_config],
        output='screen'
    )

    # RobotController node
    robot_controller_node = Node(
        package='navigation_pkg',
        executable='RobotController',
        name='robot_controller',
        output='screen'
    )

    return LaunchDescription([
        set_model_path,
        ExecuteProcess(
            cmd=['gazebo', '--verbose', world_file, '-s', 'libgazebo_ros_factory.so'],
            output='screen'
        ),
        controller_manager_node,
        robot_controller_node,
    ])