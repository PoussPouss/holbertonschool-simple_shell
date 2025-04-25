#!/bin/bash
# Couleurs pour une meilleure lisibilité
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
echo -e "${BLUE}==== Test de la commande exit avec un code de sortie ====${NC}"
# Test 1: exit sans argument
echo -e "\n${BLUE}Test 1: 'exit' sans argument${NC}"
echo "exit" > test_exit.txt
./hsh < test_exit.txt
RESULT=$?
if [ $RESULT -eq 0 ]; then
    echo -e "${GREEN}✓ OK: 'exit' a retourné 0${NC}"
else
    echo -e "${RED}✗ ERREUR: 'exit' a retourné $RESULT au lieu de 0${NC}"
fi
# Test 2: exit avec un argument numérique
echo -e "\n${BLUE}Test 2: 'exit 42'${NC}"
echo "exit 42" > test_exit.txt
./hsh < test_exit.txt
RESULT=$?
if [ $RESULT -eq 42 ]; then
    echo -e "${GREEN}✓ OK: 'exit 42' a retourné 42${NC}"
else
    echo -e "${RED}✗ ERREUR: 'exit 42' a retourné $RESULT au lieu de 42${NC}"
fi
# Test 3: exit avec un autre argument numérique
echo -e "\n${BLUE}Test 3: 'exit 127'${NC}"
echo "exit 127" > test_exit.txt
./hsh < test_exit.txt
RESULT=$?
if [ $RESULT -eq 127 ]; then
    echo -e "${GREEN}✓ OK: 'exit 127' a retourné 127${NC}"
else
    echo -e "${RED}✗ ERREUR: 'exit 127' a retourné $RESULT au lieu de 127${NC}"
fi
# Test 4: exit avec un argument non numérique
echo -e "\n${BLUE}Test 4: 'exit abc' (devrait retourner 0 ou 2)${NC}"
echo "exit abc" > test_exit.txt
./hsh < test_exit.txt
RESULT=$?
if [ $RESULT -eq 0 ] || [ $RESULT -eq 2 ]; then
    echo -e "${GREEN}✓ OK: 'exit abc' a retourné $RESULT (acceptable)${NC}"
else
    echo -e "${RED}✗ ERREUR: 'exit abc' a retourné $RESULT (inattendu)${NC}"
fi
# Nettoyage
rm -f test_exit.txt
echo -e "\n${BLUE}==== Fin des tests ====${NC}"
