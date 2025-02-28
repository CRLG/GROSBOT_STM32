/*! \file CElectrobot.cpp
    \brief Classe qui contient les méthodes la gestion de la carte Electrobot
*/
#include "RessourcesHardware.h"
#include "CGlobale.h"
#include "CElectrobot.h"

//___________________________________________________________________________
/*!
   \brief Constructeur

   \param --
   \return --
*/
CElectrobot::CElectrobot()
{
}

//___________________________________________________________________________
/*!
   \brief Destructeur

   \param --
   \return --
*/
CElectrobot::~CElectrobot()
{

}


//___________________________________________________________________________
/*!
   \brief Initialisation du module capteur

   \param --
   \return --
*/
void CElectrobot::Init(void)
{
}


//___________________________________________________________________________
/*!
   \brief Acquisition et filtrage des capteurs

   \param --
   \return --
   \remark cette fonction est a appeler periodiquement par l'applicatif
*/
void CElectrobot::Traitement(void)
{
    AcquisitionEntreesTOR();
    AcquisitionEntreesANA();
    TraitementTensionBatterie();
}


//___________________________________________________________________________
/*!
   \brief Acquisition des entrées TOR brutes

   \param --
   \return --
*/
void CElectrobot::AcquisitionEntreesTOR(void)
{
    m_b_Etor1 		= HAL_GPIO_ReadPin(Etor1_GPIO_Port, Etor1_Pin);
    m_b_Etor2 		= HAL_GPIO_ReadPin(Etor2_GPIO_Port, Etor2_Pin);
    m_b_Etor3 		= HAL_GPIO_ReadPin(Etor3_GPIO_Port, Etor3_Pin);
    m_b_Etor4 		= HAL_GPIO_ReadPin(Etor4_GPIO_Port, Etor4_Pin);
}


//___________________________________________________________________________
/*!
   \brief Acquisition des entrées TOR brutes

   \param --
   \return --
*/
void CElectrobot::AcquisitionEntreesANA(void)
{
    m_b_Eana1       = readAnalogVolt(1);
    m_b_Eana2       = readAnalogVolt(2);
    m_b_Eana3       = readAnalogVolt(3);
    m_b_Eana4       = readAnalogVolt(4);
    m_b_Eana5       = readAnalogVolt(5);
    m_b_Mes_Vbat    = readAnalogVolt(6);
}

//___________________________________________________________________________
/*!
   \brief Traitement pour la mesure de la tension batterie

   \param --
   \return --
*/
void CElectrobot::TraitementTensionBatterie(void)
{
    m_tension_batterie = (m_b_Mes_Vbat / 0.17543859649) + 0.76; // TODO : à calibrer en fonction des valeurs du pont diviseur
    m_alerte_batterie_faible = Hysterisis(m_tension_batterie, &m_alerte_batterie_faible, SEUIL_TENSION_BATT_FAIBLE, SEUIL_TENSION_BATT_FAIBLE+3, 1, 0);
}

// _____________________________________________________
/*!
   \brief Calcul la moyenne glissante sur un nombre donné d'échantillon pour des données de type char
    \param currentVal : le dernier echantillon recu
    \param *old_samples : le tableau des échantillons précédents
    \param samplesNumbers : le nombre d'echantillons pour le calcul la moyenne glissante
    \return La valeur moyenne entre le dernier echantillon recu et les (nbreEchantillonsMoyenne)  precedents echantillons

    \remarks La moyenne se fait sur "samplesNumbers" valeurs :
            - L'echantillons courant currentVal
            - Les (samplesNumbers-1) echantillons precedents
            Le tableau old_sanmples doit donc avoir une taille de (samplesNumber - 1) valeurs
*/
float CElectrobot::MoyenneGlissante_float(float currentVal, float *buf_oldSamples, unsigned int samplesNumbers)
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

    moy = moy / (float)samplesNumbers;

    return(moy);
}


// _____________________________________________________
/*!
   \brief Gestion d'un hysterisis
    \param vin le signal d'entree
    \param *etat la valeur precedente de la sortie
    \param swapOff le seuil de basculement vers inactif
    \param swapOn le seuil de basculement vers actif
    \param valOff la valeur de la sortie a l'etat inactif
    \param valOn la valeur de la sortie a l'etat actif

    \return la valeur de la sortie apres passage dans l'hysterisis

    \remarks
*/
unsigned char CElectrobot::Hysterisis (float vin, unsigned char *etat, float swapOff, float swapOn, unsigned char valOff, unsigned char valOn)
{
    if (vin <= swapOff) { // seuil bas
        *etat = valOff;
    } else if (vin >= swapOn) { // seuil haut
        *etat = valOn;
    } else {
        //on ne fait rien
    }
    if (*etat == 0xFF) { // cas d'init
        *etat = valOff;
    } // else on ne fait rien
    return *etat;
}
