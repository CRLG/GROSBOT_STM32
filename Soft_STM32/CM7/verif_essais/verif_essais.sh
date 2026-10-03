#!/bin/bash
# Atelier evitement 2027 -- construit et lance la verification geometrique des scripts d'essai.
# Depuis n'importe ou : Soft_STM32/CM7/verif_essais/verif_essais.sh
set -e
cd "$(dirname "$0")/.."
SORTIE="${TMPDIR:-/tmp}/verif_essais_atelier"
g++ -std=c++14 -O1 -Wall -I verif_essais/stub -I Modelia -I Includes \
    verif_essais/verif_essais.cpp Modelia/essais_atelier.cpp -o "$SORTIE"
"$SORTIE"
