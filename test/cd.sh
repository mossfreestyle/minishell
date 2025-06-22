#!/bin/bash
MINISHELL_PATH="$(cd "$(dirname "$0")"/.. && pwd)/minishell"
BASH="bash --posix"
TMPDIR=cd_test_tmp
mkdir -p $TMPDIR
cd $TMPDIR

# Utilitaires
run_test() {
    desc="$1"
    cmd="$2"
    test_num="$3"

    echo "=== [$test_num] $desc ==="
    # Bash
    $BASH -c "$cmd" 2>bash_err.txt 1>bash_out.txt
    bash_ret=$?
    # Minishell
    echo "$cmd" | $MINISHELL_PATH 2>mini_err.txt 1>mini_out.txt
    mini_ret=$?

    echo "BASH code: $bash_ret"
    echo "MINI code: $mini_ret"
    echo "--- BASH stderr ---"
    cat bash_err.txt
    echo "--- MINI stderr ---"
    cat mini_err.txt
    echo "---"
    if [ "$test_num" = "11" ]; then
        echo "=== DEBUG: bash_err.txt ==="
        cat -A bash_err.txt
        echo "=== DEBUG: mini_err.txt ==="
        cat -A mini_err.txt
    fi
    # ==================

if diff -u <(sed 's/^bash:.*cd:/cd:/;s/^minishell: cd:/cd:/' bash_err.txt | tr -d '\r') <(sed 's/^bash:.*cd:/cd:/;s/^minishell: cd:/cd:/' mini_err.txt | tr -d '\r'); then        echo "[$test_num] ==> [OK] Messages identiques (hors préfixe)"
    else
        echo "[$test_num] ==> [KO] Messages différents"
    fi
    if [ "$bash_ret" = "$mini_ret" ]; then
        echo "[$test_num] ==> [OK] Codes de retour identiques"
    else
        echo "[$test_num] ==> [KO] Codes de retour différents"
    fi
    echo
}

# Préparation
mkdir -p a/n
touch fichier

run_test "cd sans argument" "cd" 1
run_test "cd ~" "cd ~" 2
run_test "cd --" "cd --" 3
run_test "cd - (OLDPWD non défini)" "cd -" 4
run_test "cd chemin existant" "cd a/n" 5
run_test "cd chemin inexistant" "cd inexistant" 6
run_test "cd fichier" "cd fichier" 7

mkdir no_perm
chmod 000 no_perm
run_test "cd dossier sans permission" "cd no_perm" 8
chmod 755 no_perm

run_test "cd trop d'arguments" "cd a/n a" 9
run_test "cd avec chemin relatif complexe" "cd ./a/../a/n" 10

mkdir -p a/b
cd a/b
rm -rf ../../a
cd ../..
run_test "cd .. après suppression du dossier courant" "cd a/b; rm -rf ../../a; cd .." 11

run_test "cd \"\"" "cd \"\"" 12

# Nettoyage
cd ..
rm -rf $TMPDIR

echo "Tests terminés."