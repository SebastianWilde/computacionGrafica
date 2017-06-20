#ifndef BOID_H_INCLUDED
#define BOID_H_INCLUDED
#include "Vector3D.h"
#include <vector>
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define RAD_TO_DEG(rad) (rad * (180 / M_PI))
#define DEG_TO_RAD(deg) (deg * (M_PI / 180))
using namespace std;
int times =0;
int timebase=0;
class Boid
{
    Vector3D pos;
    Vector3D velocidad;
    Vector3D aceleracion;
    GLint texturaPez;
    float r;
    float maxforce;
    float maxspeed;
    public:
    Boid(){}
    Boid(Vector3D l, float ms, float mf)
    {
        aceleracion =  Vector3D(0,0,0);
        velocidad =  Vector3D((rand()%10)/100,(rand()%10)/100,0.05/*random(-1,1),random(-1,1)*/);
        pos = l.copy();
        r = 2.0f;
        maxspeed = ms;
        maxforce = mf;
//        texturaPez = TextureManager::Inst()->LoadTexture("texturaPex.jpg",GL_BGR_EXT,GL_RGB);
    }
    void run(vector<Boid> boids,vector<Vector3D> obstaculos)
    {
        flock(boids,obstaculos);
        update();
        borders();
        render();
    }
    void flock(vector<Boid> boids,vector<Vector3D> obstaculos)
    {
        Vector3D sep = separacion(boids,obstaculos);   // Separation
        Vector3D ali = alineacion(boids);      // Alignment
        Vector3D coh = cohesion(boids);   // Cohesion
             glColor3f(0.0f, 0.0f, 0.0f);
    // Arbitrarily weight these forces
        sep.mult(2.0f);
        ali.mult(1.0f);
        coh.mult(1.0f);
        aceleracion.add(sep);
        aceleracion.add(ali);
        aceleracion.add(coh);
    }

    void update()
    {
    // Update velocity
        times = glutGet(GLUT_ELAPSED_TIME);
        float dt = float (times -timebase)/10.0;
        timebase= times;
        velocidad.add(aceleracion*dt);
    // Limit speed
        velocidad.limit(maxspeed);
        pos.add(velocidad*1);
    // Reset accelertion to 0 each cycle
        aceleracion.setXYZ(0,0,0);
    }
    void seek(Vector3D target)
    {
        aceleracion.add(steer(target,false));
    }
    void arrive(Vector3D target)
    {
        aceleracion.add(steer(target,true));
    }
    Vector3D steer(Vector3D target, bool slowdown)
    {
        Vector3D steer;  // The steering vector
        Vector3D desired = target.sub(target,pos);  // A vector pointing from the location to the target
        float d = desired.magnitude(); // Distance from the target is the magnitude of the vector
        // If the distance is greater than 0, calc steering (otherwise return zero vector)
        if (d > 0)
        {
            // Normalize desired
            desired.normalize();
            // Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
            if ((slowdown) && (d < 100.0f)) desired.mult(maxspeed*(d/100.0f)); // This damping is somewhat arbitrary
            else desired.mult(maxspeed);
            // Steering = Desired minus Velocity
            steer = target.sub(desired,velocidad);
            steer.limit(maxforce);  // Limit to maximum steering force
        }
        else
        {
            steer =  Vector3D(0,0,0);
        }
        return steer;
    }

    void render()
    {
        float theta = velocidad.heading2D() + DEG_TO_RAD(90);
        glPushMatrix();
            glTranslatef(pos.x,pos.y,pos.z);
            glRotatef((float)RAD_TO_DEG(theta), 0.0f, 1.0f,0.0f );
            glTranslatef(0,0,-r*2);
            glutSolidCone(r,r*4,32,32);
        glPopMatrix();
    }

  // Wraparound
    void borders()
    {
        if (pos.x < -r-200) velocidad.x *=-1;// 200;
        if (pos.y < -r-10) velocidad.y *= -1;//200;
        if (pos.z < -r-200) velocidad.z *= -1;//200;
        if (pos.x > 200+r) velocidad.x *= -1;//-200;
        if (pos.y > 200+r) velocidad.y *= -1;//-200;
        if (pos.z > 200+r) velocidad.z *= -1;//-200;
    }

  // Separacion
    Vector3D separacion (vector<Boid> boids,vector<Vector3D> obstaculos)
    {
        float cercania = 25.0f;
        Vector3D sum =  Vector3D(0,0,0);
        int cont = 0;
        for (int i = 0 ; i < (int)boids.size(); i++)
        {
            Boid other = (Boid) boids[i];
            float d = pos.distance(pos,other.pos);
            if ((d > 0) && (d < cercania))
            {
                // Calculate vector pointing away from neighbor
                //Vector3D diff = pos.sub(pos,other.pos);
                Vector3D diferencia = pos-other.pos;
                diferencia.normalize();
                //diferencia.div(d);        // Weight by distance
                diferencia/=d;
               // sum.add(diferencia);
                sum+=diferencia;
                cont++;            // Keep track of how many
            }
        }
        for (int i = 0 ; i < (int)obstaculos.size(); i++)
        {
            Vector3D other = (Vector3D) obstaculos[i];
            float d = pos.distance(pos,other);
            if ((d > 0) && (d < cercania))
            {
                // Calculate vector pointing away from neighbor
                Vector3D diferencia = pos.sub(pos,other);
                diferencia.normalize();
                diferencia/=d;
                sum+=diferencia;
                //diferencia.div(d);        // Weight by distance
                //sum.add(diferencia);
                cont++;            // Keep track of how many
            }
        }
        // Average -- divide by how many
        if (cont > 0)
        {
            //sum.div((float)cont);
            sum/=((float)cont);
        }
        return sum;
    }

  // Alineacion - velocidad media
    Vector3D alineacion (vector<Boid> boids)
    {
        float rango = 50.0f;
        Vector3D sum =  Vector3D(0,0,0);
        int cont = 0;
        for (int i = 0 ; i < (int)boids.size(); i++)
        {
            Boid other = (Boid) boids[i];
            float d = pos.distance(pos,other.pos);
            if ((d > 0) && (d < rango))
            {
                //sum.add(other.velocidad);
                sum+=other.velocidad;
                cont++;
            }
        }
        if (cont > 0)
        {
            sum/=((float)cont);
            //sum.div((float)cont);
            sum.limit(maxforce);
        }
        return sum;
    }

  // Cohesion
    Vector3D cohesion (vector<Boid>boids)
    {
        float rango = 50.0f;
        Vector3D sum =  Vector3D(0,0,0);   // Start with empty vector to accumulate all locations
        int cont = 0;
        for (int i = 0 ; i < (int)boids.size(); i++)
        {
            Boid other = (Boid) boids[i];
            float d = pos.distance(pos,other.pos);
            if ((d >= 0) && (d < rango))
            {
                sum.add(other.pos); // Add location
                cont++;
            }
        }
        if (cont > 0)
        {
            sum/=((float)cont);
            return steer(sum,false);  // Steer towards the location
        }
        return sum;
    }
};
#endif // BOID_H_INCLUDED
