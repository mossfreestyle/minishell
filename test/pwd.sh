#!/bin/bash
MINISHELL_PATH="$(cd "$(dirname "$0")"/.. && pwd)/minishell"
BASH="bash --posix"
TMPDIR=pwd_test_tmp
mkdir -p $TMPDIR
cd $TMPDIR

run_test() {
    desc="$1"
    bash_cmd="$2"
    mini_cmd="$3"
    test_num="$4"

    echo "=== [$test_num] $desc ==="
    # Bash (commande + exit comme pour minishell)
    echo -e "$bash_cmd\nexit" | $BASH 2>bash_err.txt 1>bash_out.txt
    bash_ret=$?
    # Minishell
    echo "$mini_cmd" | $MINISHELL_PATH 2>mini_err.txt 1>mini_out.txt
    mini_ret=$?

    echo "BASH code: $bash_ret"
    echo "MINI code: $mini_ret"
    echo "--- BASH stdout ---"
    cat bash_out.txt
    echo "--- MINI stdout ---"
    cat mini_out.txt
    echo "--- BASH stderr ---"
    cat bash_err.txt
    echo "--- MINI stderr ---"
    cat mini_err.txt
    echo "---"

    if diff -u <(cat bash_out.txt | tr -d '\r') <(grep -v -e '^minishell\$' -e '^exit$' mini_out.txt | tr -d '\r'); then
        echo "[$test_num] ==> [OK] stdout identique"
    else
        echo "[$test_num] ==> [KO] stdout différent"
    fi
    if diff -u \
        <(sed -E 's/^(bash: line [0-9]+: |minishell: )//' bash_err.txt | tr -d '\r') \
        <(sed -E 's/^(bash: line [0-9]+: |minishell: )//' mini_err.txt | tr -d '\r'); then
        echo "[$test_num] ==> [OK] stderr identique"
    else
        echo "[$test_num] ==> [KO] stderr différent"
    fi
    if [ "$bash_ret" = "$mini_ret" ]; then
        echo "[$test_num] ==> [OK] Codes de retour identiques"
    else
        echo "[$test_num] ==> [KO] Codes de retour différents"
    fi
    echo
}
# Tests PWD
run_test "pwd simple" "pwd" "pwd" 1
run_test "pwd avec option inconnue (refusée)" "pwd --toto" "pwd --toto" 4
run_test "pwd avec argument (refusé)" "pwd arg" "pwd arg" 5 


# Test dans un sous-dossier
mkdir -p a/b
cd a/b
run_test "pwd dans sous-dossier" "pwd" "pwd" 6
cd ../..

# Nettoyage
cd ..
rm -rf $TMPDIR

echo "Tests terminés."