## Cameras
There are 3 different camera controllers provided in raylib-extras. Each one is intended to show an example of a different way to move the camera around a scene.

### rlFPCamera
This is a first person camera. It uses the traditional mouse and WASD keys for movement. It provides position and view angle data back to the calling application.
See cameras/rlFPCamera/samples/example.c for a simple use case.

![fpCamera](https://user-images.githubusercontent.com/322174/136627569-64e0b660-d846-4b1c-9239-5e09b030b2aa.gif)

### rlTPCamera
This is a third person camera. It uses the traditional mouse and WASD keys for movement. It follows a target position and lets the user rotate around that as it moves.
See cameras/rlTPCamera/samples/example.c for a simple use case.

![tpCamera](https://user-images.githubusercontent.com/322174/136641801-3f7f0a05-e79a-4f67-b05a-217e183eedde.gif)

### rlFreeCamera
TODO
