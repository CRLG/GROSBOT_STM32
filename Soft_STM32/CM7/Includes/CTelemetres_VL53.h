#ifndef _TELEMETRES_VL53_H_
#define _TELEMETRES_VL53_H_

#include "CTelemetresBase.h"
#include "vl53l0xMulti.h"

// Types
// ---------------------------------

// -----------------------------
//! Classe de gestion des options d'exécution passees en ligne de commande
class CTelemetresVL53 : public CTelemetresBase
{
public :
    CTelemetresVL53();
    ~CTelemetresVL53();
	
    // ________________________________________________________
    // Ré-implémentation des méthodes virtuelles pures de la classe de base CTelemetresBase
    /*virtual*/ float getDistanceAVG() override;
    /*virtual*/ float getDistanceAVD() override;
    /*virtual*/ float getDistanceARG() override;
    /*virtual*/ float getDistanceARD() override;
    /*virtual*/ float getDistanceARGCentre() override;
    /*virtual*/ float getDistanceARDCentre() override;


    bool init();
    void periodicTask();


    // Filtrage des capteurs US analogiques
    float MoyenneGlissante_float(float currentVal, float *buf_oldSamples, unsigned int samplesNumbers);

private :
    typedef enum {
        IDX_VL53_AVG = 0,
        IDX_VL53_AVD,
        IDX_VL53_ARG,
        IDX_VL53_ARD
    }tAffectationTelemetres;

    typedef enum {
        UNITES_mm,
        UNITES_cm
    }tUnites;
    const tUnites UNITES_MESURE = UNITES_cm;
    unsigned int m_facteur_converion_unites;

    VL53L0xMulti m_vl53;

    static const unsigned short BUFF_SIZE_MOYENNE = 2;
    float m_buff_moy_dist_vl53[VL53_COUNT][BUFF_SIZE_MOYENNE];
    float m_dist_filt[VL53_COUNT];
};

#endif

// END
