#include <stdio.h>
#include <stdbool.h>
#include "objects.h"
#include "ray.h"
#include "material.h"
#include "consts.h"
#include "util.h"

Object makeSphere(vec3 pos, float radius, Material mat) {
    Object o;
    o.mat = mat;
    o.type = ObjectTypeSphere;
    o.mesh.sphere = (Sphere){pos,radius};
    o.boundingBox = (Box){
        vec3Sub(pos,vec3Scale(VEC1,radius-0.5)),
        vec3Add(pos,vec3Scale(VEC1,radius-0.5))
    };
    return o;
}

Object makeTriangle(vec3 v0, vec3 v1, vec3 v2, Material mat) {
    Object o;
    o.mat = mat;
    o.type = ObjectTypeTriangle;
    o.mesh.triangle = (Triangle){v0,v1,v2};
    o.boundingBox = (Box){
        vec3Min(vec3Min(v0,v1),v2),
        vec3Max(vec3Max(v0,v1),v2),
    };
    return o;
}

Object makeBox(vec3 bMin, vec3 bMax, Material mat) {
    Object o;
    o.mat = mat;
    o.type = ObjectTypeBox;
    o.mesh.box = (Box){bMin,bMax};
    o.boundingBox = o.mesh.box;
    return o;
}


HitInfo intersectRaySphere(Ray r, Sphere s) {
    HitInfo hit = makeHitInfo();

    vec3 offsetRayOrigin = vec3Sub(r.origin,s.pos);

    float a = vec3Dot(r.dir,r.dir);
    float b = 2 * vec3Dot(offsetRayOrigin,r.dir);
    float c = vec3Dot(offsetRayOrigin,offsetRayOrigin) - s.radius * s.radius;
    
    float discriminant = b * b - 4 * a * c; 

    // No solution when discriminant < 0 (ray misses sphere)
    if (discriminant >= 0) {
        float dst = (-b - sqrt(discriminant)) / (2 * a);

        // ignore hits that are behind the ray, where dst < 0
        if (dst >= 0) {
            hit.didHit = true;
            hit.point = vec3Add(r.origin, vec3Scale(r.dir, dst));
            hit.normal = vec3Normalize(vec3Sub(hit.point,s.pos));
            hit.dist = dst;
        }
    }

    return hit;
}

HitInfo intersectRayTriangle(Ray r, Triangle tri) {
    HitInfo hit = makeHitInfo();

    // Compute the plane's normal
    vec3 v0v1 = vec3Sub(tri.v1,tri.v0);
    vec3 v0v2 = vec3Sub(tri.v2,tri.v0);
    // No need to normalize
    vec3 N = vec3Cross(v0v1,v0v2);
    float area2 = vec3Distance(N);
 
    // Step 1: Finding P
    
    // Check if the ray and plane are parallel
    // float NdotRayDirection = N.dotProduct(dir);
    float NdotRayDirection = vec3Dot(N,r.dir);
    if (fabs(NdotRayDirection) < EPSILON) // Almost 0
        return hit; // They are parallel, so they don't intersect!

    // Compute d parameter using equation 2
    float d = -vec3Dot(N,tri.v0);
    
    // Compute t (equation 3)
    float t = -(vec3Dot(N,r.origin) + d) / NdotRayDirection;
    
    // Check if the triangle is behind the ray
    if (t < 0) return hit; // The triangle is behind
 
    // Compute the intersection point using equation 1
    // vec3 P = r.origin + t * r.dir;
    vec3 P = vec3Add(r.origin, vec3Scale(r.dir,t));
 
    // Step 2: Inside-Outside Test
    vec3 C; // Vector perpendicular to triangle's plane
 
    // Edge 0
    vec3 edge0 = v0v1; 
    vec3 vp0 = vec3Sub(P, tri.v0);
    C = vec3Cross(edge0,vp0);
    if (vec3Dot(N,C) < 0) return hit; // P is on the right side
 
    // Edge 1
    vec3 edge1 = vec3Sub(tri.v2,tri.v1);
    vec3 vp1 = vec3Sub(P,tri.v1);
    C = vec3Cross(edge1,vp1);
    if (vec3Dot(N,C) < 0) return hit; // P is on the right side
 
    // Edge 2
    vec3 edge2 = v0v2;
    vec3 vp2 = vec3Sub(P,tri.v2);
    C = vec3Cross(edge2,vp2);
    if (vec3Dot(N,C) > 0) return hit; // P is on the right side

    hit.didHit = true;
    hit.dist = t;
    hit.point = P;
    hit.normal = N;

    return hit;
}

HitInfo intersectRayBox(Ray r, Box b) {
    HitInfo hit = makeHitInfo();
    vec3 tMin = vec3Div(vec3Sub(b.min,r.origin),r.dir);
    vec3 tMax = vec3Div(vec3Sub(b.max,r.origin),r.dir);
    vec3 t1 = vec3Min(tMin, tMax);
    vec3 t2 = vec3Max(tMin, tMax);
    float tNear = max(max(t1.x, t1.y), t1.z);
    float tFar = min(min(t2.x, t2.y), t2.z);
    
    if (tNear > tFar || tFar < 0) return hit;

    hit.didHit = true;
    hit.dist = tNear;
    hit.point = vec3Add(r.origin,vec3Scale(r.dir,tNear));
    hit.normal = vec3Normalize(vec3Sub(hit.point,BOX_CENTER(b)));

    return hit;
};

bool testRayBox(Ray r, Box b) {
    vec3 tMin = vec3Div(vec3Sub(b.min,r.origin),r.dir);
    vec3 tMax = vec3Div(vec3Sub(b.max,r.origin),r.dir);
    vec3 t1 = vec3Min(tMin, tMax);
    vec3 t2 = vec3Max(tMin, tMax);
    float tNear = max(max(t1.x, t1.y), t1.z);
    float tFar = min(min(t2.x, t2.y), t2.z);
    
    if (tNear > tFar || tFar < 0) return false;
    return true;
};