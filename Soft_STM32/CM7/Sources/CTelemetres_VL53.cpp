/*! \file CTelemetres_VL53.cpp
    \brief Classe qui contient les méthodes pour le dialogue avec la capteur ultrason SRF08
*/
#include "RessourcesHardware.h"
#include "CTelemetres_VL53.h"
#include "ConfigSpecifiqueCoupe.h"
#include "CGlobale.h"

//___________________________________________________________________________
/*!
   \brief Constructeur

   \param --
   \return --
*/
CTelemetresVL53::CTelemetresVL53()
: m_vl53(&I2C_HDL_ELECTROBOT)
{
    m_facteur_converion_unites = (UNITES_MESURE == UNITES_cm)?10:1;
}

//___________________________________________________________________________
/*!
   \brief Destructeur

   \param --
   \return --
*/
CTelemetresVL53::~CTelemetresVL53()
{

}


//___________________________________________________________________________
float CTelemetresVL53::getDistanceAVG()
{
    return m_dist_filt[IDX_VL53_AVG];
}

float CTelemetresVL53::getDistanceAVD()
{
    return m_dist_filt[IDX_VL53_AVD];
}

float CTelemetresVL53::getDistanceARG()
{
    return m_dist_filt[IDX_VL53_ARG];
}

float CTelemetresVL53::getDistanceARD()
{
    return m_dist_filt[IDX_VL53_ARD];
}

float CTelemetresVL53::getDistanceARGCentre()
{
    return 9999.;  // pas de capteur
}

float CTelemetresVL53::getDistanceARDCentre()
{
    return 9999.;  // pas de capteur
}

//___________________________________________________________________________
/*!
   \brief Initialisation des capteurs

   \param --
   \return --
*/
bool CTelemetresVL53::init(void)
{
	   m_vl53.init();
	   return true;
}

//___________________________________________________________________________
void CTelemetresVL53::periodicTask(void)
{
    m_vl53.read();
    // Filtrage moyenne glissante
    for (int i=0; i<VL53_COUNT; i++) {
        float current_dist = m_vl53.get_last_distance(i) / (float)m_facteur_converion_unites;  // conversion [mm] -> [cm] si besoin
        m_dist_filt[i] = MoyenneGlissante_float(current_dist, m_buff_moy_dist_vl53[i], BUFF_SIZE_MOYENNE);
    }
}


//___________________________________________________________________________
/*!
   \brief Filrtage des donnees brutes des capteurs ultrason

   \param currentVal la valeur du dernier échantillon pour le calcul de la moyenne
   \param buf_oldSamples le buffer contenant les derniers échantillons de mesures
   \param samplesNumbers le nombre de point pour la moyenne glissante
   \return la valeur moeyennée
*/
float CTelemetresVL53::MoyenneGlissante_float(float currentVal, float *buf_oldSamples, unsigned int samplesNumbers)
{
    float moy=currentVal;
    int i=0;  // Attention : doit être un "int" et non un "unsigned int" à cause du test de fin dans le "for"

    // Traite tous les échantillons sauf le 1er (index 0 du tableau) qui est un cas particulier
    for (i=(samplesNumbers-2); i>0; i--) {
        moy = moy + buf_oldSamples[i];
        buf_oldSamples[i] = buf_oldSamples[i-1];
    }

    // Cas particulier pour la 1ère case du tableau où la nouvelle valeur ne provient pas de l'index précédent du tableau mais du nouvel échantillon
    moy = moy + buf_oldSamples[0];
    buf_oldSamples[0] = currentVal;

    moy = moy / samplesNumbers;

    return(moy);
}
