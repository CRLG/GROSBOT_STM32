/*! \file CTelemetres.cpp
    \brief Classe qui contient les méthodes pour le dialogue avec la capteur ultrason SRF08
*/
#include "RessourcesHardware.h"
#include "CTelemetres.h"
#include "ConfigSpecifiqueCoupe.h"
#include "CGlobale.h"

//___________________________________________________________________________
/*!
   \brief Constructeur

   \param --
   \return --
*/
CTelemetres::CTelemetres() 
{

}

//___________________________________________________________________________
/*!
   \brief Destructeur

   \param --
   \return --
*/
CTelemetres::~CTelemetres() 
{

}


//___________________________________________________________________________
float CTelemetres::getDistanceAVG()
{
    return m_distance[INDEX_TELEMETRE_AVG];
}

float CTelemetres::getDistanceAVD()
{
    return m_distance[INDEX_TELEMETRE_AVD];
}

float CTelemetres::getDistanceARG()
{
    return m_distance[INDEX_TELEMETRE_ARG];
}

float CTelemetres::getDistanceARD()
{
    return m_distance[INDEX_TELEMETRE_ARD];
}

float CTelemetres::getDistanceARGCentre()
{
    return 1000;  // CDR2025 inhibition forcée des capteurs (valeur non fiable des télémètres analogiques)
    //return m_distance[INDEX_TELEMETRE_ARGCentre];
}

float CTelemetres::getDistanceARDCentre()
{
    return 1000;  // CDR2025 inhibition forcée des capteurs (valeur non fiable des télémètres analogiques)
    //return m_distance[INDEX_TELEMETRE_ARDCentre];
}


//___________________________________________________________________________
/*!
   \brief Configuration

   \param --
   \return --
*/
void CTelemetres::Config(void)
{
    unsigned char i=0;

    for (i=0; i<NOMBRE_TELEMETRES_I2C; i++) {
        // Suppose que adresses I2C des capteurs sont configurées pour se suivre
        m_adresseI2C[i] = ADRESSE_SRF08_BASE + (i*2);
        WriteRegister(m_adresseI2C[i], SRF08_reg_RANGE, SRF08_RESOLUTION_MAX); // Résolution max  de 46*0.043m + 0.043m = 2mètres environ
        WriteRegister(m_adresseI2C[i], SRF08_reg_MAX_GAIN, SRF08_MAX_GAIN);    // Résolution max  de 100*0.043m = 4.3mètres environ
    }
    // Initialise la machine d'état
    m_numSRF08 = 0;
}

//___________________________________________________________________________
void CTelemetres::Traitement(void)
{
    Traitement_I2C();
    Traitement_Analog();
}


//___________________________________________________________________________
/*!
   \brief Traitement des capteurs I2C

   \param --
   \return --
   \remark la gestion des capteurs a ultrasons doit se faire de manière séquentielle
   c'est à dire que la mesure de distance est lancée sur un capteur puis à la séquence
   d'après sur l'autre et ainsi de suite.
   La période d'appel de cette fonction doit être calibrée pour que l'écho ultrason de la
   précédente mesure soit revenu avant de lancer une mesure sur un nouveau capteur.
   Cette méthode permet d'éviter les perturbations mutuelles d'un capteur sur l'autre.
*/
void CTelemetres::Traitement_I2C(void)
{
    static unsigned char tempoBootSRF08 = 0;
    unsigned int ui_tmp=0;
    unsigned char index;

    // Permet de s'assurer que le capteur a booté avant de commencer les mesures (problème de blocage constaté en pratique)
    if (tempoBootSRF08 < 10) {
        tempoBootSRF08++;
        if (tempoBootSRF08 == 7) {  // Une fois booté, on envoie la config au SRF et on laisse un petit temps avant les mesures
            Config();
        }
        return;   // Ne fait pas les mesures durant le temps de boot des SRF08
    }

    // Lit les informations du dernier capteur
    if (m_numSRF08 == 0) {
        index = NOMBRE_TELEMETRES_I2C - 1;
    }
    else {
        index = m_numSRF08-1;
    }
    m_buff[0] = SRF08_reg_1st_ECHO_MSB;
    HAL_I2C_Master_Transmit(&I2C_HDL_ELECTROBOT, m_adresseI2C[index], (uint8_t*)m_buff, 1, I2C_DEFAULT_TIMEOUT);
    HAL_I2C_Master_Receive(&I2C_HDL_ELECTROBOT, m_adresseI2C[index], (uint8_t*)m_buff, 2, I2C_DEFAULT_TIMEOUT);
    ui_tmp = (((unsigned int)m_buff[0])<<8) + ((unsigned int)m_buff[1]);
    if (ui_tmp > 1) {  // Patch pour éliminer les situations où d'un seul coup, la mesure passe à "0" pendant quelques échantillons -> pas de mise à jour de la donnée sur le CAN si valeur erronée
        m_distance[index] = MoyenneGlissante_float(ui_tmp,
                                                   m_buff_moy_us_i2c[index],
                                                   TAILLE_MOYENNE_GLISSANTE_CAPTEURS_US_I2C);
    }
    else m_distance[index] = 250;   // laisse une valeur hors detection d'obstacle

    // Lance la mesure pour le télémètre suivant
    WriteRegister(m_adresseI2C[index], SRF08_reg_COMMAND, SRF08_MEASURE_CM);

    // Passe au capteur suivant
    m_numSRF08++;
    if (m_numSRF08 >= NOMBRE_TELEMETRES_I2C) { m_numSRF08 = 0; }

}

//___________________________________________________________________________
/*!
   \brief Traitement desd capteurs analogiques

   \param --
   \return --
   \remark
*/
//#define COEF_TELEMETRE_ULTRASON (3.3 * 259.183)
#define COEF_TELEMETRE_ULTRASON (3.3 / (18./28.) * 259.183)   // (18./28.) pour compenser le pont diviseur 10k-18k sur la carte


void CTelemetres::Traitement_Analog(void)
{
    m_distance[INDEX_TELEMETRE_ARGCentre] = MoyenneGlissante_float(Application.m_electrobot.m_b_Eana2 * COEF_TELEMETRE_ULTRASON,
                                                                   m_buff_moy_us_arg_centre,
                                                                   TAILLE_MOYENNE_GLISSANTE_CAPTEURS_US_ANA);
    m_distance[INDEX_TELEMETRE_ARDCentre] = MoyenneGlissante_float(Application.m_electrobot.m_b_Eana3 * COEF_TELEMETRE_ULTRASON,
                                                                   m_buff_moy_us_ard_centre,
                                                                   TAILLE_MOYENNE_GLISSANTE_CAPTEURS_US_ANA);

}

//___________________________________________________________________________
/*!
   \brief Filrtage des donnees brutes des capteurs ultrason

   \param currentVal la valeur du dernier échantillon pour le calcul de la moyenne
   \param buf_oldSamples le buffer contenant les derniers échantillons de mesures
   \param samplesNumbers le nombre de point pour la moyenne glissante
   \return la valeur moeyennée
*/
float CTelemetres::MoyenneGlissante_float(float currentVal, float *buf_oldSamples, unsigned int samplesNumbers)
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


//___________________________________________________________________________
/*!
   \brief Ecrit dans un registre

   \param --
   \return --
*/
void CTelemetres::WriteRegister(unsigned char add, unsigned char reg, unsigned char val)
{
    m_buff[0] = reg;
    m_buff[1] = val;
    HAL_I2C_Master_Transmit(&I2C_HDL_ELECTROBOT, add, (uint8_t*)m_buff, 2, I2C_DEFAULT_TIMEOUT);
}


// -------------------------------------------------------
// Séquence à respecter tel décrit dans la spec
void CTelemetres::ChangeAdresse(unsigned char oldAdd, unsigned char newAdd)
{
    WriteRegister(oldAdd, SRF08_reg_COMMAND, 0xA0);
    WriteRegister(oldAdd, SRF08_reg_COMMAND, 0xAA);
    WriteRegister(oldAdd, SRF08_reg_COMMAND, 0xA5);
    WriteRegister(oldAdd, SRF08_reg_COMMAND, newAdd);
}    



// END


