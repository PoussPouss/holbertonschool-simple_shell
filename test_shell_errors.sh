#!/bin/bash
# filepath: /home/lucas/holbertonschool-simple_shell/test_shell_errors.sh

# Couleurs pour une meilleure lisibilité
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Fonction pour comparer les sorties
compare_outputs() {
    local test_name=$1
    local command=$2
    local shell_path=$3
    
    echo -e "\n${YELLOW}Test: $test_name${NC}"
    echo -e "Commande: $command"
    
    # Exécuter avec /bin/sh
    echo -e "$command" | /bin/sh 2> sh_output.txt
    sh_status=$?
    
    # Exécuter avec votre shell
    echo -e "$command" | $shell_path 2> hsh_output.txt
    hsh_status=$?
    
    # Comparer les codes de sortie
    if [ "$sh_status" -eq "$hsh_status" ]; then
        echo -e "${GREEN}Code de sortie: OK (sh=$sh_status, hsh=$hsh_status)${NC}"
    else
        echo -e "${RED}Code de sortie: DIFFÉRENT! (sh=$sh_status, hsh=$hsh_status)${NC}"
    fi
    
    # Comparer les sorties
    diff -u sh_output.txt hsh_output.txt > diff_output.txt
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Sortie d'erreur: IDENTIQUE${NC}"
    else
        echo -e "${RED}Sortie d'erreur: DIFFÉRENTE!${NC}"
        echo -e "${YELLOW}Différences (format diff):${NC}"
        cat diff_output.txt | sed 's/^/    /'
        echo -e "\n${YELLOW}Sortie de /bin/sh:${NC}"
        cat sh_output.txt | sed 's/^/    /'
        echo -e "\n${YELLOW}Sortie de votre shell:${NC}"
        cat hsh_output.txt | sed 's/^/    /'
    fi
    
    echo -e "\n${YELLOW}Hex dump de la sortie de /bin/sh:${NC}"
    hexdump -C sh_output.txt | head -5 | sed 's/^/    /'
    echo -e "\n${YELLOW}Hex dump de la sortie de votre shell:${NC}"
    hexdump -C hsh_output.txt | head -5 | sed 's/^/    /'
    
    echo "----------------------------------------"
}

# Chemin vers votre shell
HSH_PATH="./hsh"

# Vérifier si votre shell existe
if [ ! -f "$HSH_PATH" ]; then
    echo -e "${RED}Erreur: $HSH_PATH n'existe pas.${NC}"
    echo "Veuillez compiler votre shell avec la commande 'gcc -Wall -Werror -Wextra -pedantic *.c -o hsh'"
    exit 1
fi

# Série de tests
echo -e "${YELLOW}=== Tests de comparaison entre /bin/sh et $HSH_PATH ===${NC}"

# 1. Commande introuvable
compare_outputs "Commande introuvable" "qwerty" "$HSH_PATH"

# 2. Commande avec chemin qui n'existe pas
compare_outputs "Fichier inexistant" "/tmp/nonexistent" "$HSH_PATH"

# 3. Essayer d'exécuter un répertoire
compare_outputs "Exécution d'un répertoire" "/tmp" "$HSH_PATH"

# 4. Essayer d'exécuter un fichier non exécutable
touch test_file
chmod -x test_file
compare_outputs "Fichier sans permission d'exécution" "./test_file" "$HSH_PATH"
rm test_file

# 5. Commande avec arguments
compare_outputs "Commande avec arguments qui n'existe pas" "nonexistent arg1 arg2" "$HSH_PATH"

# 6. Test de exit
compare_outputs "Commande exit" "exit" "$HSH_PATH"

# 7. Test avec une commande avant exit
compare_outputs "Commande avant exit" "nonexistent\nexit" "$HSH_PATH"

# 8. Test avec syntaxe incorrecte
compare_outputs "Syntaxe incorrecte" "ls | sort" "$HSH_PATH"

# 9. Test avec caractères spéciaux
compare_outputs "Caractères spéciaux" "!@#$%^&*" "$HSH_PATH"

# 10. Test avec commande vide
compare_outputs "Commande vide" "" "$HSH_PATH"

# Nettoyage
rm -f sh_output.txt hsh_output.txt diff_output.txt

echo -e "\n${GREEN}Tous les tests sont terminés.${NC}"
