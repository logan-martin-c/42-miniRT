#ifndef REFRACTION_H
#define REFRACTION_H



static inline float	get_sphere_distance(t_object *obj, t_vect3 cam_pos)
{
    float	dist;

    dist = vector_mag(vectors_sub(obj->pos, cam_pos));
    if (dist + 0.1 < obj->u_data.sphere.radius)
        return (dist);
    return (-1);
}

static inline float	get_current_refraction(t_object *objs, int obj_count, t_vect3 pos)
{
    int		i;
    float	current_refraction;
    float	new_distance;
    float	distance;

    i = -1;
    distance = INFINITY;
    new_distance = -1;
    current_refraction = 1;
    while (++i < obj_count)
    {
        if (objs[i].e_type == _sphere)
            new_distance = get_sphere_distance(&objs[i], pos);
        if (new_distance != -1 && new_distance < distance)
        {
            distance = new_distance;
            current_refraction = objs[i].u_data.sphere.refraction;
        }
    }
    return (current_refraction);
}

#endif