_This project has been created as part of the 42 curriculum by **adastugu**, **lomartin**_

# Description

The goal of this project is to create a program that generates images using the raytracing protocol.
Our miniRT represents a scene following the instructions given in the map file.
The scene can contain simple geometrics objects as **spheres**, **cones**, **cylinders** and **planes**. Each object has his own parameters.
The map is lightened by 2 types of lights :
- **Spotlights**, that lighten the scene from a position by its color. As a bonus is is possible to add multiple spotlights and to give it a diameter (for soft shadows).
- **Ambient light**, that lighten the whole scene by its color. The ambient light is unique and set to a default value if not set.
- Finally, the scene is viewed by a point of view defined by a **camera**, it has a position, a fov and a rotation.

This miniRT includes some bonus features :
- Objects have an **advanced material attribute** where possible parameters are :
  - Texture
  - Bump map
  - Transparency
  - Reflectivity
  - Refraction
  - Smoothness
- Each object and light can be **selected** by a click on it and can be **moved**, **rotated** and **resized**.
- To achieve certain other bonuses features implementation, maps file can be given in a **.json**
- **Cam parameters can be modified** in the program (fov, speed)

# Instructions

Compile using make command
```bash
make miniRT
```

Run with a valid map
```bash
./miniRT_debug maps/validmap[.json|.rt]
```

## Map instructions

- Ambient Light and Camera are unique, there can't be 2 instance of each.
- Each object must have at least a position and a color
- Spheres must have a diameter
- Cylinders must have a diameter and a height
- Cones must have a diameter and a height
- Planes do not need additional parameters

**Parameters**

- ratio : 0.0-0.1
- color : [0-255],0-255,0-255,0-255 (alpha, red, green, blue)
- position : x,y,z
- rotation : x,y,z normalized rotation vector
- fov : 0-180
- texture : path to the xpm image
- bump_map : path to the xmp image

### .rt map instruction

Objects should be defined this way :

- **Ambient Light** :
```
A   ratio   color
```

- **Camera** :
```
C   position    rotation    fov
```

- **Light** :
```
L   position    ratio   color   [diameter]
```

- **Plane** :
```
pl  position    rotation    color   [texture]  [bump_map]
```

- **Sphere** :
```
sp  position    rotation    diameter    color   [texture]  [bump_map]
```

- **Cylinder** :
```
cy  position    rotation    diameter    height  color   [texture]  [bump_map]
```

### .json map instruction

Objects should be defined this way :

```json
{
  "sphere|cylinder|cone|plane|light|cam|ambient_light" :
  {
    "[bump_map|texture]" : "path",
    "diameter|height|ratio" : 21.42,
    "position|rotation|color" : [1, 2, 3, 4]
  }
}
```

# Ressources

- [Raytracing in one week](https://raytracing.github.io/)
- [JSON standard](https://www.json.org/json-en.html)
- [Objects collisions](https://iquilezles.org/articles/intersectors/)
- [Cesia (visual appearance)](https://en.wikipedia.org/wiki/Cesia_(visual_appearance))
- [ScratchPixel](https://scratchapixel.com/)