#! /bin/bash
# SOF
#
# Check LaTeX language files against a reference one.
# Obviously, it doesn't check if it's really translated, just if the file
# in the other language exists.
#
# TODO:
#  - force to have a language to check? i.e., not French as default

# Help
function help {
    echo "Usage: "$(basename $0)" [-h]|[lang_translate_to [lang_reference]]"
}

# Entry

while getopts "h" option;
do
    case "${option}" in
        h )
            help
            exit
            ;;
        \? )
            help
            exit
            ;;
    esac
done

# Avoid issues with language
LC_ALL=C

# Define language to check, define default if no given here
RE4B_LANG=${1:-FR}

# Define language to check against, default to English
RE4B_LANG_REF=${2:-EN}

# List reference files and check if the translated file name exist
find . -name "*_${RE4B_LANG_REF}.tex" \
  |sed -e "s/_${RE4B_LANG_REF}/_${RE4B_LANG}/" \
  |xargs ls -1 2>&1 >/dev/null \
  |awk '{print substr($4,4,length($4)-5)}' \
  |sort

# EOF
