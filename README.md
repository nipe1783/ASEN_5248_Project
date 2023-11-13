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

### Creating Packages:
```
 ros2 pkg create --build-type ament_cmake 'pkg_name'


 cd ~/Desktop/ASEN_5248_Project
 colcon build
 source install/setup.bash
```

#### Running cpp nodes:
```
ros2 run <pkg_name> <node_name>
```

#### Running py nodes:
```
ros2 launch <pkg_name> <node_name>
```