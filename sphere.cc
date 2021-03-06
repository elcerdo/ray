#include "sphere.h"

#include <cstdlib>
#define my_max(a,b) ((a)<(b)?(b):(a))
#define my_min(a,b) ((a)>(b)?(b):(a))
#define my_sign(a) ((a)<0?(-1):(+1))

Sphere::Sphere(const Vecteur &pos, float diam) : position(pos), light(-5,5,-5), radius2((diam/2)*(diam/2)) {
    light.normer();
}

void Sphere::deplacer(const Vecteur &dx) {
    this->position += dx;
}

bool  Sphere::isIntersection(Rayon &rayon) const {
    
    Vecteur L = this->position - rayon.origine;
    float t_ca = L * rayon.direction;
    if (t_ca < 0) return false;

    float d2 = L * L - t_ca * t_ca;
    if (d2 > this->radius2) return false;

    float t_hc = sqrtf(this->radius2 - d2);
    rayon.distance = my_min(t_ca - t_hc, t_ca + t_hc);
    rayon.intersection = rayon.origine + rayon.direction * rayon.distance;
    return rayon.distance > 0;
}

float Sphere::luminosite(const Rayon &rayon, const World &world) const {
    Vecteur N = rayon.intersection - this->position;
    N.normer();

    float res = this->light * N;
    return my_max(.2+.8*res,0.);
}

/*
#include "vecteur3.h"
#include <cmath>

int profondeur;

class Sphere: public Element {
    private:
        Vecteur3f position;
        Vecteur3f positionLastIntersection;
        Vecteur3f lightRay;
        Vecteur3f vecteurIncident;
        float diametre;
        float distance;
        float r2; // Rayon * Rayon
            
    public:
        Sphere(Vecteur3f pos, float diam):position(pos), diametre(diam) {
            this->r2 = (this->diametre / 2) * (this->diametre / 2);
            this->lightRay = Vecteur3f(-5,5,-5);
            this->lightRay.normer();
        }

        bool isIntersection(Vecteur3f origineRayon, Vecteur3f directionRayon) {
            Vecteur3f L;
            float t_ca, t_hc; 
            float d2;
            
            L = this->position - origineRayon;
            t_ca = L * directionRayon;
            if(t_ca < 0) return false;
            d2 = L * L - t_ca * t_ca;
            if(d2 > this->r2) return false;
            t_hc = std::sqrt(this->r2 - d2);
            this->distance = my_min(t_ca - t_hc, t_ca + t_hc);
            this->positionLastIntersection = origineRayon + directionRayon * this->distance;
            this->vecteurIncident = directionRayon;
            return this->distance > 0;

            // directionRayon doit être normé.. A=1 dans ce cas donc il est ignoré....
            T B = 2*(directionRayon * (origineRayon - this->position));
            T C = (origineRayon - this->position ).norme() - (this->rayon * this->rayon);
            T Q, x1, x2;

            T delta = (B * B - 4 * C);

            if ( delta >= (T)0 ) {
                x1 = (-B-std::sqrt(delta)/2);
                x2 = (-B+std::sqrt(delta)/2);
                this->distance = my_min(x1,x2);
                //Q = -0.5 * ( B + my_sign(B) * sqrt(delta) );
                //this->distance = my_min(Q, C/Q);
                return this->distance > 0;
            } else
                return false;
            
        }
    
        float distanceIntersection() {
            return this->distance;
        }



        float luminosite(std::vector<Element * > monde) {
            Vecteur3f N = (this->positionLastIntersection - this->position);
            N.normer();
            float res = this->lightRay * N;
            if(profondeur < 3) {
            std::vector<Element* >::const_iterator it;
            for( it = monde.begin(); it != monde.end(); ++it) {
               if((*it) != this && (*it)->isIntersection(this->positionLastIntersection, N - this->vecteurIncident) ) {
                   if( (*it)->distanceIntersection() > 0)
                       profondeur ++;
                       res = (res + (*it)->luminosite(monde)) / 2;
                       profondeur --;
               }
            }
            }
            return my_max(res, 0);
        }
                  
};


*/
