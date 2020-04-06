# RayTracing

todo desc

![result-raytracing](./doc/results/raytracing.png)


## TODO

shadow
reflection (with example depth 0 1 2)

![result-raytracing-depth-0](./doc/results/raytracing_depth_0.png)

![result-raytracing-depth-1](./doc/results/raytracing_depth_1.png)

![result-raytracing-depth-2](./doc/results/raytracing_depth_2.png)


### Scene file format

TODO json

#### Camera description

- `position` : position in the space of the camera

- `target` : position in the space where the camera is pointing on

#### Scene description

- `shapes` : list of the shapes in the scene
	Where a shape can be either :
	- `box`
		* `minBox`
		* `maxBox`
	- `sphere`
		* `center`
		* `radius`

- `lights` : list of lights in the scene
	Where a sphere is defined by a position in the space and a color

- `backgroundColor` : background color of the scene

## Usage

* Compilation :
	- `mkdir build`
	- `cd build`
	- `cmake ../`
	- `make`

* Run : `./bin/raytracer width height depth`
	- *width* : width of the image
	- *height* : height of the image
	- *depth* : maximum number of ray reflections

* Delete binary : `make clean`
