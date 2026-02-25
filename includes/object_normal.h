#ifndef OBJECT_NORMAL_H
# define OBJECT_NORMAL_H

# include "minirt.h"

static inline t_vect3   sphere_normal(t_object *object, t_vect3 point, t_vect3 ray)
{
    t_vect3 normal;

    normal.x = point.x - object->pos.x;
    normal.y = point.y - object->pos.y;
    normal.z = point.z - object->pos.z;
    normal = vector_norm(normal);
    if (dot_product(normal, ray) < 0)
        return (normal);
    return (vectors_sub((t_vect3){0, 0, 0}, normal));
}

#endif