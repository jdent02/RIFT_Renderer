#include "bvh_node.h"

#include "utility/utility_functions.h"

bool bvh_node::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    if (b_box.hit(r, t_min, t_max))
    {
        hit_record left_rec, right_rec;
        bool hit_left = left->hit(r, t_min, t_max, left_rec);
        bool hit_right = right->hit(r, t_min, t_max, right_rec);
        if (hit_left && hit_right)
        {
            if (left_rec.t < right_rec.t)
            {
                rec = left_rec;
            }
            else
            {
                rec = right_rec;
            }
            return true;
        }
        else if (hit_left)
        {
            rec = left_rec;
            return true;
        }
        else if (hit_right)
        {
            rec = right_rec;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool bvh_node::bounding_box(float t0, float t1, aabb& box) const
{
    box = b_box;
    return true;
}

bvh_node::bvh_node(
    ihitable** l,
    int n,
    float time0,
    float time1)
{
    int axis = int(3 * (rand() * inv_rand_max));
    if (axis == 0)
    {
        qsort(l, static_cast<size_t>(n), sizeof(ihitable*), box_x_compare);
    }
    else if (axis == 1)
    {
        qsort(l, static_cast<size_t>(n), sizeof(ihitable*), box_y_compare);
    }
    else
    {
        qsort(l, static_cast<size_t>(n), sizeof(ihitable*), box_z_compare);
    }

    if (n == 1)
    {
        left = right = l[0];
    }
    else if (n == 2)
    {
       left = l[0];
       right = l[1];
    }
    else
    {
        left = new bvh_node(l, n/2, time0, time1);
        right = new bvh_node(l + n/2, n - n/2, time0, time1);
    }
    aabb box_left, box_right;
    if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
    {
        std::cerr << "No bounding box in constructor" << std::endl;
    }

    b_box = surrounding_box(box_left, box_right);
}
