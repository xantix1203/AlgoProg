//
//  main.c
//  AlgoProg
//
//  Created by COTTEN on 02/10/2020.
//

#include <stdio.h>
#include <math.h>

//change

typedef struct {
    unsigned longueur;
    unsigned largeur;
    unsigned epaisseur;
    unsigned type;
} Panneau;

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point center;
    float radius;
} Cercle;

typedef struct {
    int num;
    unsigned den;
} Rat;

Panneau panneau_init(void);
float Panneau_volume(Panneau panneau);
void Panneau_display(Panneau panneau);
Point Point_init(void);
void Point_affiche(Point point);
float Point_dist(Point p1, Point p2);
Cercle Cercle_init(void);
void Cercle_display(Cercle cercle);
int Cercle_is_in(Point p, Cercle c);
Rat Rat_init(void);
void Rat_display(Rat rat);
Rat Rat_multiply(Rat rat1, Rat rat2);
Rat Rat_add(Rat rat1, Rat rat2);


int main(int argc, const char * argv[]) {
//    Panneau panneau = {5, 4, 3, 2};
//    Panneau_affiche(panneau);
//    printf("%f\n", Panneau_volume(panneau));
//    Point point = Point_init();
//    Point_affiche(point);
//    Point p1 = {0.0, 1.0};
//    Point p2 = {1.0, 1.0};
//    printf("%f\n", Point_dist(p1, p2));
//    Cercle cercle = Cercle_init();
//    Cercle_affiche(cercle);
//    printf("%d\n", Cercle_is_in(p1, cercle));
    Rat rat1 = Rat_init();
//    Rat_display(rat1);
    Rat rat2 = Rat_init();
    Rat_display(Rat_multiply(rat1, rat2));
    Rat_display(Rat_add(rat1, rat2));
    
    return 0;
}

Panneau panneau_init(){
    Panneau panneau;
    printf("longueur: ");
    scanf("%u\n", &panneau.longueur);
    printf("largeur: ");
    scanf("%u\n", &panneau.largeur);
    printf("epaisseur: ");
    scanf("%u\n", &panneau.epaisseur);
    printf("type: ");
    scanf("%u\n", &panneau.type);
    return panneau;
}

void Panneau_display(Panneau panneau){
    printf("longueur: %u\n", panneau.longueur);
    printf("largeur: %u\n", panneau.largeur);
    printf("epaisseur: %u\n", panneau.epaisseur);
    printf("type: %u\n", panneau.type);
}

float Panneau_volume(Panneau panneau){
    return ((float)(panneau.longueur * panneau.largeur * panneau.epaisseur) * 0.001);
}


Point Point_init(){
    Point point;
    printf("abscisse: ");
    scanf("%f", &point.x);
    printf("\nordonnee: ");
    scanf("%f", &point.y);
    printf("\n");
    return point;
}

void Point_affiche(Point point){
    printf("abscisse: %f\n", point.x);
    printf("ordonnee: %f\n", point.y);
}

float Point_dist(Point p1, Point p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}


Cercle Cercle_init(){
    Cercle cercle;
    cercle.center = Point_init();
    printf("Rayon du cercle: ");
    scanf("%f", &cercle.radius);
    return cercle;
}


void Cercle_display(Cercle cercle){
    printf("Les coordonnees du cercle sont: \n");
    Point_affiche(cercle.center);
    printf("Le rayon du cercle est: %f\n", cercle.radius);
}

int Cercle_is_in(Point p, Cercle c){
    if (Point_dist(p, c.center) <= c.radius)
        return 1;
    else
        return 0;
}


Rat Rat_init(){
    Rat rat;
    printf("numerator: ");
    scanf("%d", &rat.num);
    printf("\ndenominator: ");
    scanf("%u", &rat.den);
    printf("\n");
    return rat;
}

void Rat_display(Rat rat){
    printf("rat = %d/%u\n", rat.num, rat.den);
}

Rat Rat_add(Rat rat1, Rat rat2){
    Rat rat3;
    rat3.den = rat1.den * rat2.den;
    rat3.num = rat1.num * rat2.den +rat2.num * rat1.den;
    return rat3;
}

Rat Rat_multiply(Rat rat1, Rat rat2){
    Rat rat3;
    rat3.num = rat1.num * rat2.num;
    rat3.den = rat1.den * rat3.den;
    return rat3;
}
