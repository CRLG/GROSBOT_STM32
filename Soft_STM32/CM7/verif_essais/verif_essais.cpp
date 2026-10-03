/**
 * Atelier evitement 2027 -- verification geometrique des scripts d'essai (Modelia/essais_atelier.cpp).
 *
 * Joue les deux roles de chaque essai sur un modele cinematique simple, SANS evitement, avec la loi de
 * l'asservissement polaire (cMODE_XY_TETA) : le robot se tourne vers le point, recule si le point est
 * derriere lui, puis s'oriente au cap final. Mesure, pour chaque essai :
 *   - la distance minimale entre les centres des deux robots, et sa date ;
 *   - les sorties de terrain (centre a moins d'un rayon englobant d'une bordure) ;
 *   - la duree du script, a comparer aux 100 s du match.
 * Une distance minimale inferieure a deux rayons englobants est un CONTACT si l'evitement est inhibe
 * des deux cotes : c'est la seule situation ou rien ne l'empecherait. Elle est voulue dans les essais
 * ou un robot au moins est en evitement (c'est ce qu'on teste).
 *
 * Construction et lancement (depuis Soft_STM32/CM7) : verif_essais/verif_essais.sh
 */
#include <cmath>
#include <cstdio>
#include "sm_essai_atelier.h"
#include "ConfigSpecifiqueCoupe.h"

static const float RAYON_ROBOT = 18.f;      // rayon englobant (CTacticalEvaluator), confirme pour les 2 robots
static const float DT = 0.02f;              // pas du modele [s]
static const float T_MAX = 100.f;           // DUREE_MATCH

struct Robot {
    const tPasEssai *script;
    float x0;               // recul du centre derriere la bordure (depart)
    int couleur;            // 1 ou 2
    // Etat dans le repere propre (X depuis sa bordure, Y absolu, cap 0 = face au centre)
    float X, Y, cap;
    float v, w;             // vitesses max
    int i;                  // pas courant
    float t_pas;            // date d'entree dans le pas
    bool inhibe;            // evitement inhibe pour ce role
    bool fini;
    float t_fin;
};

static float norm(float a) { while (a > M_PI) a -= 2 * M_PI; while (a <= -M_PI) a += 2 * M_PI; return a; }

// Position terrain absolue
static void terrain(const Robot &r, float &xt, float &yt)
{
    xt = (r.couleur == 1) ? r.X : LONGUEUR_TERRAIN_CM - r.X;
    yt = r.Y;
}

// Un pas de modele vers la consigne (x, y, teta) ; renvoie vrai a convergence
static bool avancer(Robot &r, const tPasEssai &p)
{
    float dx = p.x - r.X, dy = p.y - r.Y;
    float d = std::sqrt(dx * dx + dy * dy);
    if (d > 1.0f) {
        float cible = std::atan2(dy, dx);
        float err = norm(cible - r.cap);
        float sens = 1.f;
        if (std::fabs(err) > M_PI / 2) { err = norm(err - M_PI); sens = -1.f; }  // point derriere : marche arriere
        if (std::fabs(err) > 0.05f) {
            float da = std::copysign(std::fmin(std::fabs(err), r.w * DT), err);
            r.cap = norm(r.cap + da);
        }
        else {
            float pasd = std::fmin(d, r.v * DT);
            r.X += sens * pasd * std::cos(r.cap);
            r.Y += sens * pasd * std::sin(r.cap);
        }
        return false;
    }
    float err = norm(p.teta - r.cap);
    if (std::fabs(err) > 0.02f) {
        r.cap = norm(r.cap + std::copysign(std::fmin(std::fabs(err), r.w * DT), err));
        return false;
    }
    return true;
}

static void pasModele(Robot &r, float t)
{
    if (r.fini) return;
    const tPasEssai &p = r.script[r.i];
    bool suivant = false;
    switch (p.type) {
    case PAS_EVITEMENT: r.inhibe = ((int)p.valeur == EVIT_ESSAI_INHIBE); suivant = true; break;
    case PAS_VITESSE:   r.v = p.x; r.w = p.y; suivant = true; break;
    case PAS_JUSQUA:    suivant = (t >= p.valeur); break;
    case PAS_ALLER:     suivant = avancer(r, p) || ((t - r.t_pas) * 1000.f > p.timeout_ms); break;
    default:            r.fini = true; r.t_fin = t; return;
    }
    if (suivant) { r.i++; r.t_pas = t; }
}

static void jouer(int num, float x0_a, float x0_b, bool detail)
{
    const tEssaiAtelier &e = ESSAIS_ATELIER[num];
    Robot a = { e.role_couleur_1, x0_a, 1, x0_a, 100.f, 0.f, 40.f, 2.f, 0, 0.f, false, false, 0.f };
    Robot b = { e.role_couleur_2, x0_b, 2, x0_b, 100.f, 0.f, 40.f, 2.f, 0, 0.f, false, false, 0.f };
    float dmin = 1e9f, t_dmin = 0.f, marge_min = 1e9f;
    bool contact = false;
    for (float t = 0.f; t < T_MAX; t += DT) {
        pasModele(a, t);
        pasModele(b, t);
        float xa, ya, xb, yb;
        terrain(a, xa, ya); terrain(b, xb, yb);
        float d = std::hypot(xa - xb, ya - yb);
        if (d < dmin) { dmin = d; t_dmin = t; }
        if (d < 2 * RAYON_ROBOT && a.inhibe && b.inhibe) contact = true;
        // Sortie de terrain (on ignore le depart, arriere colle a la bordure par construction)
        for (int k = 0; k < 2; k++) {
            float xr = k ? xb : xa, yr = k ? yb : ya;
            float m = std::fmin(std::fmin(xr, LONGUEUR_TERRAIN_CM - xr), std::fmin(yr, 200.f - yr));
            const Robot &r = k ? b : a;
            if ((r.i > 3) || (t > 6.f)) marge_min = std::fmin(marge_min, m);
        }
    }
    float duree = std::fmax(a.fini ? a.t_fin : T_MAX, b.fini ? b.t_fin : T_MAX);
    printf("%2d %-22s  dmin=%6.1f cm a %5.1f s  marge bordure=%5.1f cm  fin=%5.1f s %s%s%s\n",
           num, e.nom, dmin, t_dmin, marge_min, duree,
           contact ? " ** CONTACT (evitement inhibe des deux cotes) **" : "",
           (marge_min < RAYON_ROBOT) ? " ** PRES D'UNE BORDURE **" : "",
           (duree >= 99.f) ? " ** SCRIPT NON TERMINE EN 100 s **" : "");
    if (detail) {
        // non utilise : place pour une trace pas a pas si besoin
    }
}

int main()
{
    int defauts = 0;
    const float departs[][2] = { { 28.5f, 28.5f }, { 28.5f, 35.f }, { 35.f, 28.5f } };
    const char *noms[] = { "CRLG / CRLG", "A = CRLG, B = CRLGirls", "A = CRLGirls, B = CRLG" };
    for (int k = 0; k < 3; k++) {
        printf("\n=== Departs : %s\n", noms[k]);
        for (int n = 0; n < NOMBRE_ESSAIS_ATELIER; n++) jouer(n, departs[k][0], departs[k][1], false);
    }
    (void)defauts;
    return 0;
}
