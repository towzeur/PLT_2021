#!/bin/bash

EXIT_STATUS=0
MAKEFILE_FOUND=
SRC_FOUND=
RAPPORT_FOUND=
RAPPORT_DIR_FOUND=
DIA2CODE_FOUND=
FILES=$(ls -1)||exit 2
for file in $FILES; do
    # Mandatory files
    if [[ "$file" == "src" ]]; then
        SRC_FOUND=1
        if [ ! -d "$file" ]; then
            echo "$file n'est pas un dossier" 1>&2
            EXIT_STATUS=2
        fi
        continue;
    fi
    if [[ "$file" == "Makefile" ]]; then
        MAKEFILE_FOUND=1
        if [ ! -f "$file" ]; then
            echo "$file n'est pas un fichier" 1>&2
            EXIT_STATUS=2
        fi
        continue;
    fi
    if [[ "$file" == "rapport" ]]; then
        RAPPORT_DIR_FOUND=1
        if [ ! -d "$file" ]; then
            echo "$file n'est pas un dossier" 1>&2
            EXIT_STATUS=2
        fi
        continue;
    fi
    if [[ "$file" == "Rapport.pdf" ]]; then
        RAPPORT_FOUND=1
        if [ ! -f "$file" ]; then
            echo "$file n'est pas un fichier" 1>&2
            EXIT_STATUS=2
        fi
        if [[ "$(file -b --mime-type $file)" != "application/pdf" ]]; then
            echo "$file n'est pas au format pdf" 1>&2
            EXIT_STATUS=2
        fi
        continue;
    fi
    # Optional files
    if [[ "$file" == "CMakeLists.txt" ]]; then
        continue;
    fi
    if [[ "$file" == 'README'* ]]; then
        continue;
    fi
    if [[ "$file" == 'LICENSE' ]]; then
        continue;
    fi
    if [[ "$file" == "docker" ]]; then
        continue;
    fi
    if [[ "$file" == "extern" ]]; then
        continue;
    fi
    if [[ "$file" == "res" ]]; then
        continue;
    fi
    if [[ "$file" == "lib" ]]; then
        continue;
    fi
    if [[ "$file" == "check_repo.sh" ]]; then
        continue;
    fi
    echo "Le fichier '$file' n'a rien à faire dans la racine du dépôt" 1>&2
    EXIT_STATUS=2
done
if [ -z "$MAKEFILE_FOUND" ]; then
    echo "Pas de Makefile dans la racine du dépôt" 1>&2
    EXIT_STATUS=2
fi
if [ -z "$SRC_FOUND" ]; then
    echo "Pas de dossier src dans la racine du dépôt" 1>&2
    EXIT_STATUS=2
fi
if [ -z "$RAPPORT_DIR_FOUND" ]; then
    echo "Pas de dossier rapport dans la racine du dépôt" 1>&2
    EXIT_STATUS=2
fi
if [ -z "$RAPPORT_FOUND" ]; then
    echo "Pas de Rapport.pdf dans la racine du dépôt" 1>&2
    EXIT_STATUS=2
fi


# Check file types
while read -r file; do
    if [[ "$file" == './.git/'* ]]; then
        continue;
    fi
    if [[ "$file" == './res/'* ]]; then
        continue;
    fi
    if [[ "$file" == './src/'*'.dia' ]]; then
        continue;
    fi
    if [[ "$file" == './rapport/'*'.doc' ]]; then
        continue;
    fi
    if [[ "$file" == './rapport/'*'.docx' ]]; then
        continue;
    fi
    if [[ "$file" == './rapport/'*'.odt' ]]; then
        continue;
    fi
    MIME=$(file -b --mime-type "$file")||exit 2
    if [[ "$MIME" == 'text/'* ]]; then
        continue;
    fi
    if [[ "$MIME" == 'inode/x-empty' ]]; then
        if [[ "$file" == *'.h' ]] || [[ "$file" == *'.hpp' ]] || [[ "$file" == *'.c' ]] || [[ "$file" == *'.cpp' ]]; then
            continue;
        fi
    fi
    if [[ "$file" == "./Rapport.pdf" ]]; then
        continue;
    fi
    if [[ "$file" == './lib/'* ]]; then
        if [[ "$MIME" = 'application/x-archive' ]]; then
            continue;
        fi
        if [[ "$MIME" = 'application/x-dosexec' ]]; then
            continue;
        fi
    fi
    if [[ "$file" == './rapport/'* ]] || [[ "$file" == './res/'* ]]; then
        if [[ "$MIME" = 'image/'* ]]; then
            continue;
        fi
        if [[ "$MIME" = 'application/pdf' ]]; then
            continue;
        fi
    fi
    echo "Le fichier '$file' a un type mime non autorisé: $MIME" 1>&2
    EXIT_STATUS=2
done < <(find . -type f)

exit $EXIT_STATUS
