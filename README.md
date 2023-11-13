# ASEN_5248_Project

## Running instructions:

1. Gazebo simulation:
    
    ```
    cd ~/Desktop/ASEN_5248_Project
    colcon build --packages-select gazebo_pkg
    source install/setup.bash
    ```

    ```
    ros2 launch gazebo_pkg launch_gazebo.py
    ```