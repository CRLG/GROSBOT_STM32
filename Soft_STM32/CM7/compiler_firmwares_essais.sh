#!/bin/bash
# =====================================================================================================
# Atelier evitement 2027 -- construit les firmwares des DEUX robots pour les essais sur table
#
#   ./compiler_firmwares_essais.sh            depuis Soft_STM32/CM7
#
# Les deux robots du club sont identiques (ecran, Raspberry, STM32, lidar) sauf ce que regroupe
# ROBOT_CIBLE dans Includes/ConfigSpecifiqueCoupe.h : telemetres (US SRF08 / VL53), odometrie,
# position de depart, servos (verrouilles en position rangee sur CRLGirls). Strategie et couleur se
# choisissent a l'ecran.
#
# Produit dans build_essais/ :
#   ElectrobotH755_CM7_CRLG.{bin,hex,elf}      a flasher sur CRLG
#   ElectrobotH755_CM7_CRLGIRLS.{bin,hex,elf}  a flasher sur CRLGirls
#   VERSION.txt                                commits et options : a recopier en tete du carnet d'essais
#
# Flasher (ST-Link) :  make install ROBOT=CRLG   ou   make install ROBOT=CRLGIRLS
#   (ou : st-flash write build_essais/ElectrobotH755_CM7_<ROBOT>.bin 0x8000000 && st-flash reset)
# =====================================================================================================
set -e
cd "$(dirname "$0")"

SORTIE=build_essais
CIBLE=ElectrobotH755_CM7
ROBOTS="CRLG CRLGIRLS"
mkdir -p "$SORTIE"

# Etat des sources : une mesure sans version est une mesure perdue (plan de validation)
etat_depot() {
    local depot="$1"
    local sha=$(git -C "$depot" rev-parse --short HEAD)
    local branche=$(git -C "$depot" branch --show-current)
    local modifs=""
    [ -n "$(git -C "$depot" status --porcelain --untracked-files=no)" ] && modifs=" + MODIFICATIONS NON COMMITEES"
    echo "$sha ($branche)$modifs"
}

for robot in $ROBOTS; do
    echo "=== Construction du firmware $robot"
    make -j8 ROBOT=$robot > "$SORTIE/make_$robot.log" 2>&1 || { echo "ECHEC : voir $SORTIE/make_$robot.log"; exit 1; }
    for ext in bin hex elf; do
        cp "build_$robot/$CIBLE.$ext" "$SORTIE/${CIBLE}_$robot.$ext"
    done
    arm-none-eabi-size "$SORTIE/${CIBLE}_$robot.elf" | tail -1
done

# Option de telemetrie d'essai en match : elle retarde la fin de match (cf. ConfigSpecifiqueCoupe.h)
if grep -qE '^[[:space:]]*#define[[:space:]]+TELEMETRIE_ESSAIS_EVITEMENT_EN_MATCH' Includes/ConfigSpecifiqueCoupe.h; then
    TELEMETRIE="ACTIVE (essais seulement : fin de match retardee de ~1 a 2 s, a couper pour la competition)"
else
    TELEMETRIE="inactive"
fi

{
    echo "Firmwares d'essai -- atelier evitement 2027"
    echo "Construits le : $(date '+%Y-%m-%d %H:%M')"
    echo
    echo "Depots :"
    echo "  GROSBOT_STM32  $(etat_depot ../..)"
    echo "  CppRobLib      $(etat_depot ../ext/CppRobLib)"
    echo "  CppRobLibSTM32 $(etat_depot ../ext/CppRobLibSTM32)"
    echo
    echo "Telemetrie d'essai en match : $TELEMETRIE"
    echo
    for robot in $ROBOTS; do
        echo "${CIBLE}_$robot.bin  sha256 $(sha256sum "$SORTIE/${CIBLE}_$robot.bin" | cut -c1-16)"
    done
    echo
    echo "CRLG     : telemetres US SRF08, voie 30.7 cm, depart Y=171.5 cm"
    echo "CRLGIRLS : telemetres VL53, voie 32 cm, depart Y=165 cm, servos verrouilles en position rangee"
} > "$SORTIE/VERSION.txt"

echo
cat "$SORTIE/VERSION.txt"
echo
echo "Flasher : make install ROBOT=CRLG   /   make install ROBOT=CRLGIRLS"
