# rlFPCamera
A simple first person camera controller for raylib

# API
All data for the first person camera is managed by the rlFPCamera structure.

This structure is setup by calling rlFPCameraInit with a camera, FOV, and Position.
```
rlFPCameraInit(&camera, fov, pos);
```

The fov argument is the vertical field of view, 45degrees is a good starting point. The horizontal view will be computed using the aspect ratio of the screen.
The position will be the inital location of the camera in world space.

Once the camera is initalized, options in the camera structure can be set, such as view bob, speed, control keys, and render distance.

Whenever a window, or render texture is resized rlFPCameraResizeView needs to be called for any cameras used in that space, to properly recompute the FOV.

Once per frame rlFPCameraUpdate with the camera should be called, this will apply any input events and move the camera.
Once a camera is updated it can be used on screen or in a render texture by calling.

rlFPCameraBeginMode3D and rlFPCameraEndMode3D. These work just like BeginMode3d and EndMode3d for raylib cameras, but use the extended features of rlFPCamera


