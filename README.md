_This project has been created as part of the 42 curriculum by **adastugu**, **lomartin**_

# Description

MiniRT is a 42 project that serves as an introduction to the raytracing protocol.

Adastugu and I wanted to bring it further to learn more and to end with a program we could be proud of.

Just before we give you a detailed description of what our miniRT can do, enjoy some beautifil scenes it can render :

🚧 WORK IN PROGRESS 🚧

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