/**
 * Atelier evitement 2027 -- scripts des essais sur table (plan de validation, doc_evitement/).
 *
 * Repere : voir sm_essai_atelier.h. Coordonnees terrain vues de la couleur 1, en cm : X depuis SA
 * PROPRE petite bordure, Y absolu (depart a Y = 100), teta 0 = face au centre. Les deux robots partent
 * arriere contre leur petite bordure, face a face sur la ligne Y = 100 ; sur une meme ordonnee, la
 * distance entre leurs centres vaut 300 - X_couleur1 - X_couleur2.
 *
 * Roles : A = couleur 1, B = couleur 2. Pour echanger les roles, on echange les COULEURS des robots.
 * Un robot quitte toujours sa bordure (X = 60) avant de pivoter : arriere colle, il la heurterait.
 * Chaque essai tient en 95 s (DUREE_MATCH = 100 s). Les fenetres d'intervention humaine sont donnees en
 * secondes de match, lisibles sur l'ecran.
 *
 * Toute modification de l'ordre ou des noms se reporte dans ConfigSpecifiqueCoupe.h
 * (eATTRIBUTION_STRATEGIES) et dans CEcran::strategyNumToString() (LaBotBox).
 */
#include "sm_essai_atelier.h"
#include "ConfigSpecifiqueCoupe.h"

#define DEMI_PI   (1.5708f)
#define UN_PI     (3.1416f)
#define DEG(a)    ((a) * 0.0174533f)

// Constructeurs de pas
#define ALLER(x, y, t, to)      { PAS_ALLER,     (x), (y), (t), 0.f,              (to), 0 }
#define POINT(x, y, t, to)      { PAS_ALLER,     (x), (y), (t), 0.f,              (to), 1 }
#define JUSQUA(s)               { PAS_JUSQUA,    0.f, 0.f, 0.f, (float)(s),       0,    0 }
#define VITESSE(v, w)           { PAS_VITESSE,   (v), (w), 0.f, 0.f,              0,    0 }
#define EVITEMENT(m)            { PAS_EVITEMENT, 0.f, 0.f, 0.f, (float)(m),       0,    0 }
#define FIN                     { PAS_FIN,       0.f, 0.f, 0.f, 0.f,              0,    0 }

// Sur la ligne de depart Y = 100 : se placer en X face au centre ; pivoter sur place en X
#define SUR_LIGNE(x, to)        ALLER((x), 100.f, 0.f, (to))
#define CAP(x, t)               ALLER((x), 100.f, (t), 3000)

// =====================================================================================================
// 0 -- IMMOBILE : strategie par defaut a la mise sous tension. Le robot ne bouge pas.
static const tPasEssai IMMOBILE[] = { EVITEMENT(EVIT_ESSAI_ATTENDRE), FIN };

// =====================================================================================================
// 1 / 2 -- E1_SEUL, E1_DECOR : chaque robot s'ecarte de sa bordure (X = 60) puis pivote d'un quart de
// tour toutes les 12 s : face au bas (15 s), a sa bordure (27 s), au haut (39 s), au centre (51 s).
// Ce que le lidar voit de lui-meme (tiges) sous quatre orientations ; l'autre robot est a 1,80 m.
// E1_DECOR : meme script, avec une personne debout derriere une bordure, l'element de jeu le plus haut
// et un empilement poses avant la mise sous tension.
static const tPasEssai SEUL[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 1.0f), SUR_LIGNE(60.f, 5000),
    JUSQUA(15), CAP(60.f, -DEMI_PI),
    JUSQUA(27), CAP(60.f, UN_PI),
    JUSQUA(39), CAP(60.f, DEMI_PI),
    JUSQUA(51), CAP(60.f, 0.f),
    JUSQUA(63), FIN
};

// =====================================================================================================
// 3 -- E1_DISTANCE : A immobile en X = 100 ; B s'avance par paliers sur la ligne : distance entre
// centres 120 (jusqu'a 24 s), 100 (25-33), 80 (34-42), 60 (43-63 : suivi d'un objet immobile),
// 50 (64-88 : objet douteux -- avant-bras a cote du mat de B de 67 a 77 s, boite tenue a hauteur du lidar
// a cote de lui de 79 a 88 s), 40 (89-100). Chaque robot voit l'autre : controle croise de la distance.
static const tPasEssai DISTANCE_A[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), SUR_LIGNE(100.f, 6000), FIN
};
static const tPasEssai DISTANCE_B[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), SUR_LIGNE(80.f, 6000),
    JUSQUA(24), SUR_LIGNE(100.f, 3000),
    JUSQUA(33), SUR_LIGNE(120.f, 3000),
    JUSQUA(42), SUR_LIGNE(140.f, 3000),
    JUSQUA(63), SUR_LIGNE(150.f, 3000),
    JUSQUA(88), SUR_LIGNE(160.f, 3000),
    FIN
};

// =====================================================================================================
// 4 -- E1_OMBRE : les deux robots a 60 cm l'un de l'autre (X = 100 et X = 140). A pivote pour placer B
// a 0, +20, -20, +60, -60, +120 et -120 degres de son axe (5 s chacun, de 15 a 50 s) : B passe derriere
// chacune des quatre tiges, et le signe de l'angle se verifie. Puis B fait de meme (52 a 87 s).
#define OMBRE_SERIE(x, t0) \
    JUSQUA((t0)),      CAP((x), 0.f), \
    JUSQUA((t0) + 5),  CAP((x), DEG(-20.f)), \
    JUSQUA((t0) + 10), CAP((x), DEG(20.f)), \
    JUSQUA((t0) + 15), CAP((x), DEG(-60.f)), \
    JUSQUA((t0) + 20), CAP((x), DEG(60.f)), \
    JUSQUA((t0) + 25), CAP((x), DEG(-120.f)), \
    JUSQUA((t0) + 30), CAP((x), DEG(120.f)), \
    JUSQUA((t0) + 35), CAP((x), 0.f)
static const tPasEssai OMBRE_A[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 1.5f), SUR_LIGNE(100.f, 6000), OMBRE_SERIE(100.f, 15), FIN
};
static const tPasEssai OMBRE_B[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 1.5f), SUR_LIGNE(140.f, 6000), OMBRE_SERIE(140.f, 52), FIN
};

// =====================================================================================================
// 5 -- E2_ROTATION : a 60 cm, A fait deux tours sur lui-meme (15-30 s), puis B (32-47 s) ; B recule a
// 110 cm (49 s) ; A refait deux tours (53-68 s), puis B (70-85 s). L'autre robot, immobile en coordonnees
// de terrain, passe derriere les quatre tiges : rien ne doit bouger dans le suivi.
#define DEUX_TOURS(x, t0) \
    JUSQUA((t0)), CAP((x), -DEMI_PI), CAP((x), -UN_PI), CAP((x), DEMI_PI), CAP((x), 0.f), \
                  CAP((x), -DEMI_PI), CAP((x), -UN_PI), CAP((x), DEMI_PI), CAP((x), 0.f)
static const tPasEssai ROTATION_A[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 1.5f), SUR_LIGNE(100.f, 6000),
    DEUX_TOURS(100.f, 15), DEUX_TOURS(100.f, 53), FIN
};
static const tPasEssai ROTATION_B[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 1.5f), SUR_LIGNE(140.f, 6000),
    DEUX_TOURS(140.f, 32), JUSQUA(49), SUR_LIGNE(90.f, 4000), DEUX_TOURS(90.f, 70), FIN
};

// =====================================================================================================
// 6 -- E2_APPROCHE : A immobile en X = 60 ; B s'approche de 170 a 50 cm et repart, lentement (20 cm/s,
// 15-35 s) puis vite (50 cm/s, 35-48 s) ; puis oscille de +-5 cm autour de 80 cm (48-82 s) : hysteresis.
static const tPasEssai APPROCHE2_A[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), SUR_LIGNE(60.f, 5000), FIN
};
static const tPasEssai APPROCHE2_B[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), SUR_LIGNE(70.f, 5000),
    JUSQUA(15), VITESSE(20.f, 1.5f), SUR_LIGNE(190.f, 9000),
    JUSQUA(25), SUR_LIGNE(70.f, 9000),
    JUSQUA(35), VITESSE(50.f, 2.f), SUR_LIGNE(190.f, 5000),
    JUSQUA(41), SUR_LIGNE(70.f, 5000),
    JUSQUA(48), VITESSE(20.f, 1.5f), SUR_LIGNE(160.f, 6000),
    JUSQUA(55), SUR_LIGNE(155.f, 2000), JUSQUA(58), SUR_LIGNE(165.f, 2000),
    JUSQUA(61), SUR_LIGNE(155.f, 2000), JUSQUA(64), SUR_LIGNE(165.f, 2000),
    JUSQUA(67), SUR_LIGNE(155.f, 2000), JUSQUA(70), SUR_LIGNE(165.f, 2000),
    JUSQUA(73), SUR_LIGNE(155.f, 2000), JUSQUA(76), SUR_LIGNE(165.f, 2000),
    JUSQUA(82), SUR_LIGNE(70.f, 8000),
    FIN
};

// =====================================================================================================
// 7 -- E2_TRAVERSE : A immobile en X = 100 ; B traverse devant lui a 60 cm (sa ligne : X = 140 cote B,
// soit 160 depuis la bordure de A) : trois passages de Y = 160 a Y = 40, de 15 a 45 s. Puis les roles
// s'inversent : B se poste en X = 100 et A traverse devant lui sur sa ligne X = 140 (50 a 90 s).
// Chaque serie finit EN BAS : au changement de role, l'un monte et l'autre est en bas, leurs trajets
// ne se croisent pas.
#define TRAVERSEE(t0) \
    JUSQUA((t0)),      ALLER(140.f, 40.f,  -DEMI_PI, 8000), \
    JUSQUA((t0) + 10), ALLER(140.f, 160.f, -DEMI_PI, 8000), \
    JUSQUA((t0) + 20), ALLER(140.f, 40.f,  -DEMI_PI, 8000)
static const tPasEssai TRAVERSE_A[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), SUR_LIGNE(100.f, 6000),
    JUSQUA(50), ALLER(140.f, 160.f, -DEMI_PI, 8000), TRAVERSEE(60), FIN
};
static const tPasEssai TRAVERSE_B[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), ALLER(140.f, 160.f, -DEMI_PI, 8000),
    TRAVERSEE(15), JUSQUA(50), SUR_LIGNE(100.f, 8000), FIN
};

// =====================================================================================================
// 8 -- E3_APPROCHE : B, immobile en X = 100 (a 2 m de la bordure de A), sert d'obstacle. A (evitement
// AE) quitte sa bordure (X = 60) et file vers X = 190 a 12 s : ralentissements puis arret devant B.
// A 30 s, B s'ecarte vers le haut (Y = 160) : A doit reprendre sa vitesse nominale. A 45 s, B se poste
// derriere A, a X = 200 (soit a 1 m de la bordure de A) ; a 60 s, A revient en marche arriere vers
// X = 60 : meme cascade, par l'arriere.
static const tPasEssai APPROCHE3_A[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(40.f, 2.f), SUR_LIGNE(60.f, 5000),
    JUSQUA(12), SUR_LIGNE(190.f, 30000),
    JUSQUA(60), SUR_LIGNE(60.f, 25000),
    FIN
};
static const tPasEssai APPROCHE3_B[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), SUR_LIGNE(100.f, 6000),
    JUSQUA(30), ALLER(100.f, 160.f, DEMI_PI, 6000),
    JUSQUA(45), ALLER(200.f, 160.f, 0.f, 6000), ALLER(200.f, 100.f, UN_PI, 6000),
    FIN
};

// =====================================================================================================
// 9 -- E3_A_VIDE : chaque robot parcourt une boucle dans sa moitie de terrain (X de 60 a 100, Y de 30 a
// 170), evitement AE : les deux robots restent a plus d'un metre l'un de l'autre. Etalon de vitesse a
// vide ; une personne debout derriere la grande bordure du haut, au droit de X = 60, et une derriere sa
// petite bordure, ne doivent provoquer aucune reaction (hors terrain).
#define BOUCLE_VIDE \
    ALLER(60.f, 170.f, DEMI_PI, 8000), ALLER(100.f, 170.f, 0.f, 6000), \
    ALLER(100.f, 30.f, -DEMI_PI, 10000), ALLER(60.f, 30.f, UN_PI, 6000), \
    ALLER(60.f, 100.f, DEMI_PI, 8000)
static const tPasEssai A_VIDE[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(40.f, 2.f), SUR_LIGNE(60.f, 5000),
    BOUCLE_VIDE, BOUCLE_VIDE, SUR_LIGNE(60.f, 4000), FIN
};

// =====================================================================================================
// 10 / 11 -- E4_FACE_AE, E4_FACE_ASYM : les deux robots quittent leur bordure puis foncent l'un vers
// l'autre sur la ligne de depart (10 s). FACE_AE : les deux en evitement AE. FACE_ASYM : A en AE, B en
// evitement historique.
#define FACE(mode) \
    EVITEMENT(mode), VITESSE(40.f, 2.f), SUR_LIGNE(60.f, 5000), JUSQUA(10), SUR_LIGNE(270.f, 60000), FIN
static const tPasEssai FACE_AE[] = { FACE(EVIT_ESSAI_AE) };
static const tPasEssai FACE_ATTENDRE[] = { FACE(EVIT_ESSAI_ATTENDRE) };

// =====================================================================================================
// 12 -- E4_CROISEMENT : B monte d'abord en (X = 60, Y = 170). A file sur la ligne de X = 60 vers
// X = 270 a partir de 11 s ; B descend en diagonale vers (X = 110, Y = 30) a partir de 9 s et coupe la
// ligne vers X = 85 de son cote (215 du cote de A) environ 4 s avant A. Les trajectoires se croisent
// sans se rencontrer : au plus un lever de pied, pas d'arret.
static const tPasEssai CROISEMENT_A[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(40.f, 2.f), SUR_LIGNE(60.f, 5000),
    JUSQUA(11), SUR_LIGNE(270.f, 30000), FIN
};
static const tPasEssai CROISEMENT_B[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(40.f, 2.f), ALLER(60.f, 170.f, DEMI_PI, 6000),
    JUSQUA(9), ALLER(110.f, 30.f, -1.22f, 15000), FIN
};

// =====================================================================================================
// 13 -- E4_POURSUITE : B se place en tete (X = 130 de son cote, soit 170 du cote de A), dos a A, et
// repart lentement vers sa bordure (15 cm/s, 12 s). A quitte sa bordure et file a 40 cm/s (12 s) : il
// rattrape B et doit lever le pied et le suivre, sans s'arreter ni manoeuvrer tant que B avance.
static const tPasEssai POURSUITE_A[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(40.f, 2.f),
    JUSQUA(4), SUR_LIGNE(60.f, 5000),
    JUSQUA(12), SUR_LIGNE(230.f, 25000), FIN
};
static const tPasEssai POURSUITE_B[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), ALLER(130.f, 100.f, UN_PI, 8000),
    JUSQUA(12), VITESSE(15.f, 1.5f), ALLER(40.f, 100.f, UN_PI, 15000), FIN
};

// =====================================================================================================
// 14 -- E4_COIN : A reste arriere colle a sa bordure. B s'avance face a lui jusqu'a X = 200 de son
// cote (soit 100 du cote de A) et s'arrete (vers 8 s). A 20 s, A s'avance lentement vers B : il ne doit
// pas reculer dans sa bordure, et tenir sa position plutot que de s'agiter.
static const tPasEssai COIN_A[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(20.f, 2.f),
    JUSQUA(20), SUR_LIGNE(150.f, 30000), FIN
};
static const tPasEssai COIN_B[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(40.f, 2.f), SUR_LIGNE(200.f, 10000), FIN
};

// =====================================================================================================
// 15 -- E5_HOMOLO : B joue le robot factice de l'homologation. Il se place a mi-terrain (8 s), puis
// avance lentement (10 cm/s) vers A a partir de 22 s, sans aucune reaction d'evitement ; une personne
// marche a cote avec l'avant-bras pres de son mat, comme l'arbitre. A quitte sa bordure et file vers
// lui a 20 s : detection et arret. A 50 s, A revient a sa bordure.
static const tPasEssai HOMOLO_A[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(40.f, 2.f), SUR_LIGNE(60.f, 5000),
    JUSQUA(20), SUR_LIGNE(200.f, 25000),
    JUSQUA(50), SUR_LIGNE(60.f, 20000), FIN
};
static const tPasEssai HOMOLO_B[] = {
    EVITEMENT(EVIT_ESSAI_INHIBE), VITESSE(40.f, 2.f), SUR_LIGNE(150.f, 8000),
    JUSQUA(22), VITESSE(10.f, 1.f), SUR_LIGNE(190.f, 15000), FIN
};

// =====================================================================================================
// 16 / 17 -- E6_PARCOURS_AE, E6_PARCOURS_ATTENDRE : les deux robots parcourent une boucle miroir dont
// trois sommets sont a 20 cm du sommet homologue de l'autre robot : ils se genent forcement. Un point
// par sommet atteint (score, 12 au plus). Meme parcours pour l'ancien et le nouvel evitement : seule la
// strategie d'evitement change.
#define BOUCLE \
    POINT(140.f, 100.f, 0.f, 12000), POINT(140.f, 40.f, -DEMI_PI, 12000), \
    POINT(60.f, 40.f, UN_PI, 12000), POINT(60.f, 160.f, DEMI_PI, 12000), \
    POINT(140.f, 160.f, 0.f, 12000), POINT(140.f, 100.f, -DEMI_PI, 12000)
static const tPasEssai PARCOURS_AE[] = {
    EVITEMENT(EVIT_ESSAI_AE), VITESSE(40.f, 2.f), SUR_LIGNE(60.f, 5000), BOUCLE, BOUCLE, FIN
};
static const tPasEssai PARCOURS_ATTENDRE[] = {
    EVITEMENT(EVIT_ESSAI_ATTENDRE), VITESSE(40.f, 2.f), SUR_LIGNE(60.f, 5000), BOUCLE, BOUCLE, FIN
};

// =====================================================================================================
const tEssaiAtelier ESSAIS_ATELIER[] = {
    { "IMMOBILE",              IMMOBILE,          IMMOBILE },
    { "E1_SEUL",               SEUL,              SEUL },
    { "E1_DECOR",              SEUL,              SEUL },
    { "E1_DISTANCE",           DISTANCE_A,        DISTANCE_B },
    { "E1_OMBRE",              OMBRE_A,           OMBRE_B },
    { "E2_ROTATION",           ROTATION_A,        ROTATION_B },
    { "E2_APPROCHE",           APPROCHE2_A,       APPROCHE2_B },
    { "E2_TRAVERSE",           TRAVERSE_A,        TRAVERSE_B },
    { "E3_APPROCHE",           APPROCHE3_A,       APPROCHE3_B },
    { "E3_A_VIDE",             A_VIDE,            A_VIDE },
    { "E4_FACE_AE",            FACE_AE,           FACE_AE },
    { "E4_FACE_ASYM",          FACE_AE,           FACE_ATTENDRE },
    { "E4_CROISEMENT",         CROISEMENT_A,      CROISEMENT_B },
    { "E4_POURSUITE",          POURSUITE_A,       POURSUITE_B },
    { "E4_COIN",               COIN_A,            COIN_B },
    { "E5_HOMOLO",             HOMOLO_A,          HOMOLO_B },
    { "E6_PARCOURS_AE",        PARCOURS_AE,       PARCOURS_AE },
    { "E6_PARCOURS_ATTENDRE",  PARCOURS_ATTENDRE, PARCOURS_ATTENDRE },
};
const unsigned char NOMBRE_ESSAIS_ATELIER = sizeof(ESSAIS_ATELIER) / sizeof(ESSAIS_ATELIER[0]);

static_assert(sizeof(ESSAIS_ATELIER) / sizeof(ESSAIS_ATELIER[0]) == NOMBRE_STRATEGIES_ATELIER,
              "ESSAIS_ATELIER et eATTRIBUTION_STRATEGIES doivent avoir le meme nombre d'entrees");
