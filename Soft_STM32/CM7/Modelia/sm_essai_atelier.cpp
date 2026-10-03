/**
 * Atelier evitement 2027 -- mission generique des essais sur table (cf. sm_essai_atelier.h)
 */
#include "sm_essai_atelier.h"
#include "CGlobale.h"
#include "ConfigSpecifiqueCoupe.h"

SM_EssaiAtelier::SM_EssaiAtelier()
    : m_essai(nullptr)
{
    m_main_mission_type = true;
    m_max_score = 0;
}

const char* SM_EssaiAtelier::getName()
{
    return "SM_EssaiAtelier";
}

// _____________________________________
// Un etat par pas du script : l'etat SM_FIRST_STATE + i joue le pas i
const char* SM_EssaiAtelier::stateToName(unsigned short state)
{
    const tPasEssai *role = roleCourant();
    if (!role || (state < SM_FIRST_STATE)) return "UNKNOWN_STATE";
    switch (role[state - SM_FIRST_STATE].type) {
    case PAS_ALLER :        return "PAS_ALLER";
    case PAS_JUSQUA :       return "PAS_JUSQUA";
    case PAS_VITESSE :      return "PAS_VITESSE";
    case PAS_EVITEMENT :    return "PAS_EVITEMENT";
    case PAS_FIN :          return "PAS_FIN";
    }
    return "UNKNOWN_STATE";
}

// _____________________________________
void SM_EssaiAtelier::setEssai(const tEssaiAtelier *essai)
{
    m_essai = essai;
    // Le role n'est connu qu'a la tirette (couleur) : on retient le plus grand des deux maxima
    unsigned short max1 = essai ? pointsDuRole(essai->role_couleur_1) : 0;
    unsigned short max2 = essai ? pointsDuRole(essai->role_couleur_2) : 0;
    m_max_score = (max1 > max2) ? max1 : max2;
}

// _____________________________________
unsigned short SM_EssaiAtelier::pointsDuRole(const tPasEssai *role)
{
    unsigned short total = 0;
    if (!role) return 0;
    for (int i = 0; role[i].type != PAS_FIN; i++) total += role[i].points;
    return total;
}

// _____________________________________
// Le role suit la couleur : elle est figee a la tirette (SM_Main::ATTENTE_TIRETTE)
const tPasEssai *SM_EssaiAtelier::roleCourant()
{
    if (!m_essai) return nullptr;
    if (internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2) return m_essai->role_couleur_2;
    return m_essai->role_couleur_1;
}

// _____________________________________
// L'inhibition agit sur la chaine lidar dans IA::step() : la perception, le suivi, l'evaluation
// tactique et la telemetrie continuent ; seules l'entree en evitement et le plafond de vitesse AE
// sont neutralises.
void SM_EssaiAtelier::appliquerEvitement(unsigned char mode)
{
    switch (mode) {
    case EVIT_ESSAI_AE :
        internals()->evit_inhibe_obstacle = false;
        internals()->evit_choix_strategie = SM_DatasInterface::STRATEGIE_EVITEMENT_AE;
        break;
    case EVIT_ESSAI_ATTENDRE :
        internals()->evit_inhibe_obstacle = false;
        internals()->evit_choix_strategie = SM_DatasInterface::STRATEGIE_EVITEMENT_ATTENDRE;
        break;
    case EVIT_ESSAI_INHIBE :
    default :
        internals()->evit_inhibe_obstacle = true;
        internals()->evit_choix_strategie = SM_DatasInterface::STRATEGIE_EVITEMENT_ATTENDRE;
        break;
    }
}

// _____________________________________
// Le premier pas d'un script choisit l'evitement du role, mais il ne s'execute qu'une fois le match
// lance. Or le sequenceur peut lancer l'evitement des le premier passage du match si un obstacle est
// deja detecte a la tirette : un robot cible se figerait alors et decalerait toute la chronologie de
// l'essai. Le mode du role est donc applique pendant l'attente de la tirette, ou la strategie et la
// couleur choisies a l'ecran sont deja connues.
void SM_EssaiAtelier::preparerEvitement()
{
    const tPasEssai *role = roleCourant();
    if (!role) return;
    for (int i = 0; role[i].type != PAS_FIN; i++) {
        if (role[i].type == PAS_EVITEMENT) {
            appliquerEvitement((unsigned char)role[i].valeur);
            return;
        }
    }
}

// _____________________________________
// Script en coordonnees terrain (vue couleur 1, X depuis sa propre petite bordure) -> repere de
// l'asservissement, dont l'origine est le point de depart du robot (IA::match_started)
void SM_EssaiAtelier::allerTerrain(float x_terrain, float y_terrain, float teta)
{
    float x0, y0;
    if (internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2) {
        x0 = LONGUEUR_TERRAIN_CM - X_ROBOT_TERRAIN_INIT_COULEUR_2;
        y0 = Y_ROBOT_TERRAIN_INIT_COULEUR_2;
    }
    else {
        x0 = X_ROBOT_TERRAIN_INIT_COULEUR_1;
        y0 = Y_ROBOT_TERRAIN_INIT_COULEUR_1;
    }
    outputs()->CommandeMouvementXY_TETA_sym(x_terrain - x0, y_terrain - y0, teta);
}

// _____________________________________
void SM_EssaiAtelier::step()
{
    const tPasEssai *role = roleCourant();
    if (!role || (m_state < SM_FIRST_STATE)) {
        stop();
        return;
    }
    const tPasEssai &pas = role[m_state - SM_FIRST_STATE];
    const unsigned short suivant = m_state + 1;

    switch (pas.type) {
    // ___________________________
    case PAS_ALLER :
        if (onEntry()) {
            allerTerrain(pas.x, pas.y, pas.teta);
        }
        if (inputs()->FrontM_Convergence) {
            m_score += pas.points;
            gotoState(suivant);
        }
        gotoStateAfter(suivant, pas.timeout_ms);
        if (onExit()) { }
        break;
    // ___________________________
    case PAS_JUSQUA :
        if (onEntry()) { }
        gotoStateIfTrue(suivant, internals()->TempsMatch >= pas.valeur);
        if (onExit()) { }
        break;
    // ___________________________
    case PAS_VITESSE :
        if (onEntry()) {
            Application.m_asservissement.CommandeVitesseMouvement(pas.x, pas.y);
        }
        gotoState(suivant);
        if (onExit()) { }
        break;
    // ___________________________
    case PAS_EVITEMENT :
        if (onEntry()) {
            appliquerEvitement((unsigned char)pas.valeur);
        }
        gotoState(suivant);
        if (onExit()) { }
        break;
    // ___________________________
    case PAS_FIN :
    default :
        m_succes = true;
        stop();
        break;
    }
}
