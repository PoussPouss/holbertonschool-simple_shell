#!/bin/bash

# Couleurs pour la lisibilité
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Fonction pour comparer les sorties et codes de retour
compare_outputs() {
    local cmd="$1"
    local title="$2"
    
    echo -e "\n${BLUE}========== TEST: $title ==========${NC}"
    echo -e "${YELLOW}Commande: $cmd${NC}"
    
    # Exécuter avec sh
    echo "$cmd" > tmp_sh_cmd.txt
    sh < tmp_sh_cmd.txt > tmp_sh_stdout.txt 2> tmp_sh_stderr.txt
    SH_STATUS=$?
    
    # Exécuter avec hsh
    echo "$cmd" > tmp_hsh_cmd.txt
    ./hsh < tmp_hsh_cmd.txt > tmp_hsh_stdout.txt 2> tmp_hsh_stderr.txt
    HSH_STATUS=$?
    
    # Comparer les codes de sortie
    if [ $SH_STATUS -eq $HSH_STATUS ]; then
        echo -e "${GREEN}✓ Codes de retour identiques: $SH_STATUS${NC}"
    else
        echo -e "${RED}✗ Codes de retour différents: sh=$SH_STATUS, hsh=$HSH_STATUS${NC}"
    fi
    
    # Comparer la sortie standard
    if diff -q tmp_sh_stdout.txt tmp_hsh_stdout.txt >/dev/null; then
        echo -e "${GREEN}✓ Sorties standard identiques${NC}"
    else
        echo -e "${RED}✗ Sorties standard différentes:${NC}"
        echo -e "${YELLOW}--- sh ---${NC}"
        cat tmp_sh_stdout.txt
        echo -e "${YELLOW}--- hsh ---${NC}"
        cat tmp_hsh_stdout.txt
    fi
    
    # Comparer la sortie d'erreur
    if diff -q tmp_sh_stderr.txt tmp_hsh_stderr.txt >/dev/null; then
        echo -e "${GREEN}✓ Sorties d'erreur identiques${NC}"
    else
        echo -e "${RED}✗ Sorties d'erreur différentes:${NC}"
        echo -e "${YELLOW}--- sh ---${NC}"
        cat tmp_sh_stderr.txt
        echo -e "${YELLOW}--- hsh ---${NC}"
        cat tmp_hsh_stderr.txt
    fi
}

echo -e "${BLUE}=====================================================${NC}"
echo -e "${BLUE}= COMPARAISON COMPLÈTE ENTRE DASH ET VOTRE SHELL HSH =${NC}"
echo -e "${BLUE}=====================================================${NC}"

# Tests de commandes de base
compare_outputs "ls" "Commande existante simple"
compare_outputs "ls -la" "Commande avec arguments"
compare_outputs "/bin/ls" "Commande avec chemin absolu"
compare_outputs "./hsh" "Exécuter le shell lui-même"
compare_outputs "nonexistentcmd" "Commande inexistante"
compare_outputs "/nonexistent/path" "Chemin inexistant"
compare_outputs "ls nonexistentfile" "Fichier inexistant comme argument"
compare_outputs "ls /" "Listage d'un répertoire"
compare_outputs "echo hello world" "Echo avec plusieurs arguments"
compare_outputs "pwd" "Affichage du répertoire courant"

# Tests spécifiques à exit
compare_outputs "exit" "Commande exit sans argument"
compare_outputs "exit 0" "Exit avec code 0"
compare_outputs "exit 42" "Exit avec code spécifique"
compare_outputs "exit abc" "Exit avec argument non numérique"

# Tests avec des caractères spéciaux
compare_outputs "ls \"file with spaces\"" "Guillemets doubles"
compare_outputs "ls 'file with spaces'" "Guillemets simples"
compare_outputs "ls file\\ with\\ spaces" "Caractères échappés"

# Tests de redirection et pipe (juste pour la forme, vous n'avez pas à les implémenter)
compare_outputs "ls | grep a" "Pipe simple"
compare_outputs "ls > output.txt" "Redirection de sortie"

# Tests des commandes intégrées
compare_outputs "env" "Variable d'environnement"
compare_outputs "cd /tmp" "Changement de répertoire"
compare_outputs "cd nonexistentdir" "Changement vers répertoire inexistant"

# Nettoyage
rm -f tmp_sh_cmd.txt tmp_hsh_cmd.txt tmp_sh_stdout.txt tmp_hsh_stdout.txt tmp_sh_stderr.txt tmp_hsh_stderr.txt output.txt

echo -e "\n${BLUE}=====================================================${NC}"
echo -e "${BLUE}=                 FIN DES TESTS                      =${NC}"
echo -e "${BLUE}=====================================================${NC}"