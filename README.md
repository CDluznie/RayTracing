# RayTracing

Ray tracing renderering system based on glm with C++.

![result-raytracing](./doc/results/raytracing.png)


## Presentation

The goal of the project is to implement a photorealistic ray tracing renderer.
With this technique we can have interesting visual feature like shadows and surface reflection (like mirrors).
The program take a file describing the scene to render with the attached camera as an input and will produce the rendering result as an image file.

The quality of the rendering is modulated by the maximum number of reflections a ray is allowed to make.
For example if we want to produce a mirror surface we need to perform at least one reflection to retrieve the object reflected on the surface.

Here an example when the maxmimum number of reflection is 0 :

![result-raytracing-depth-0](./doc/results/raytracing_depth_0.png)

When it's 1 :

![result-raytracing-depth-1](./doc/results/raytracing_depth_1.png)

And when it's 2 :

![result-raytracing-depth-2](./doc/results/raytracing_depth_2.png)

The higher is the maximum number of ray reflections, the higher is the number of reflection details the program is able to render.


### Scene file format

The ray tracer file input should contains the following information about the camera and the scene.

#### Camera description

- `position` : position in the space of the camera

- `target` : position in the space where the camera is pointing on

#### Scene description

- `shapes` : list of the shapes in the scene

- `shape`:
	- `box`
		* `minBox` : minimum point of the box
		* `maxBox` : maximum point of the box
		* `color` : color of the box
		* `emissive` : emissive color of the box
		* `reflect` : reflection coefficients of the box
	- `sphere`
		* `center` : center of the sphere
		* `radius` : radius of the sphere
		* `color` : color of the box
		* `emissive` : emissive color of the box
		* `reflect` : reflection coefficients of the box

- `lights` : list of lights in the scene

- `light` : 
	- `position` : position in the space of the light
	- `color` : color of the light

- `backgroundColor` : background color of the scene

You can check in `scenes/scene_1.json` for an example.


## Usage

* Compilation :
	- `mkdir build`
	- `cd build`
	- `cmake ../`
	- `make`

* Run : `./bin/raytracer scene width height depth`
	- *scene* : path to the scene file
	- *width* : width of the image
	- *height* : height of the image
	- *depth* : maximum number of ray reflections

For example `./bin/raytracer ../scenes/scene_1.json 768 512 4` will create a file `scene_1.png` of size 768x512 containing the result the of the rendering on the scene file `../scenes/scene_1.json` with a maximum ray reflections of 4.

* Delete binary : `make clean`
