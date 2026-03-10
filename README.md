This project has been created as part of the 42 curriculum by adastugu, lomartin

# Description

The goal of this project is to create a program that generates images using the raytracing protocol.
Our miniRT represents a scene following the instructions given in the map file.
The scene can contain simple geometrics objects as **spheres**, **cones**, **cylinders** and **planes**. Each object has his own parameters.
The map is lightened by 2 types of lights :
- Spotlights, that lighten the scene from a position by its color. As a bonus is is possible to add multiple spotlights and to give it a diameter (for soft shadows).
- Ambient light, that lighten the whole scene by its color. The ambient light is unique and set to a default value if not set.
- Finally, the scene is viewed by a point of view defined by a camera, it has a position, a fov and a rotation.



# Insctructions

Compile using make command
```bash
make minishell
```

# Ressources

- [Raytracing in one week](https://raytracing.github.io/)
- [JSON standard](https://www.json.org/json-en.html)