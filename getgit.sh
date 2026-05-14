#!/bin/bash

CDIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]:-$0}")" &>/dev/null && pwd)"

getgit() {
    while IFS= read -r -d '' dir; do
        local gitdir="${dir%/.git}"
        local branch
        branch=$(cd "$gitdir" && git rev-parse --abbrev-ref HEAD 2>/dev/null)
        if [ -n "$branch" ]; then
            echo ">>> $gitdir (branche: $branch)"
            (cd "$gitdir" && git pull origin "$branch")
        else
            echo ">>> $gitdir — impossible de déterminer la branche, ignoré"
        fi
    done < <(find "$CDIR" -maxdepth 6 -name ".git" -print0)

    echo "Fin"
}

getgit
