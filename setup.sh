#!/usr/bin/env bash

# Bootstrap this competitive-programming workspace on macOS.
# Run from inside the repository:
#   ./setup.sh
# Or download this one file on a fresh Mac; it will clone the repository too.
#   /bin/bash -c "$(/usr/bin/curl -fsSL https://raw.githubusercontent.com/SadeekFarhan21/Competitive-Programming/main/setup.sh)"
#
# A read-only health check is also available:
#   ./setup.sh --check

set -Eeuo pipefail
IFS=$'\n\t'

readonly BOOTSTRAP_SOURCE="${BASH_SOURCE[0]:-$0}"
readonly SCRIPT_DIR="$(cd "$(dirname "$BOOTSTRAP_SOURCE")" && pwd)"
readonly REPOSITORY_URL="https://github.com/SadeekFarhan21/Competitive-Programming.git"
readonly DEFAULT_REPO_DIR="${HOME}/Documents/Competitive-Programming"

REPO_DIR=""
WORKSPACE_FILE=""

MODE="install"
FAILURES=0
BREW=""
CODIUM=""

readonly -a FORMULAE=(
    gcc
    boost
    clang-format
)

readonly -a CASKS=(
    vscodium
    font-geist-mono
)

# These reproduce the VSCodium setup used by this repository.
readonly -a EXTENSIONS=(
    langningchen.cph-ng
    llvm-vs-code-extensions.vscode-clangd
    pkief.material-icon-theme
    pkief.material-product-icons
    vscodevim.vim
    wakatime.vscode-wakatime
    xaver.clang-format
    zhuangtongfa.material-theme
)

usage() {
    printf '%s\n' \
        "Usage: ./setup.sh [--check]" \
        "" \
        "With no option, installs and configures the complete workspace." \
        "--check verifies the setup without changing anything."
}

log() {
    printf '\n\033[1;34m==>\033[0m %s\n' "$*"
}

ok() {
    printf '    \033[1;32mOK\033[0m  %s\n' "$*"
}

warn() {
    printf '    \033[1;33mWARN\033[0m %s\n' "$*" >&2
}

missing() {
    printf '    \033[1;31mMISSING\033[0m %s\n' "$*" >&2
    FAILURES=$((FAILURES + 1))
}

die() {
    printf '\n\033[1;31mError:\033[0m %s\n' "$*" >&2
    exit 1
}

find_brew() {
    if command -v brew >/dev/null 2>&1; then
        command -v brew
    elif [[ -x /opt/homebrew/bin/brew ]]; then
        printf '%s\n' /opt/homebrew/bin/brew
    elif [[ -x /usr/local/bin/brew ]]; then
        printf '%s\n' /usr/local/bin/brew
    else
        return 1
    fi
}

configure_homebrew_shell() {
    [[ "$MODE" == "install" ]] || return 0

    local profile_file="${HOME}/.zprofile"
    local shellenv_line="eval \"\$(${BREW} shellenv)\""
    /usr/bin/touch "$profile_file"
    if ! /usr/bin/grep -Fqx "$shellenv_line" "$profile_file"; then
        printf '\n%s\n' "$shellenv_line" >> "$profile_file"
    fi
}

ensure_command_line_tools() {
    log "Checking Apple Command Line Tools"

    if /usr/bin/xcode-select -p >/dev/null 2>&1; then
        ok "Apple Command Line Tools"
        return
    fi

    if [[ "$MODE" == "check" ]]; then
        missing "Apple Command Line Tools"
        return
    fi

    warn "Apple requires its installer dialog for the Command Line Tools."
    /usr/bin/xcode-select --install >/dev/null 2>&1 || true

    if [[ ! -t 0 ]]; then
        die "Complete the Command Line Tools installation, then run ./setup.sh again."
    fi

    until /usr/bin/xcode-select -p >/dev/null 2>&1; do
        printf 'Complete the Apple installer, then press Return to continue: '
        read -r _
    done

    ok "Apple Command Line Tools"
}

ensure_repository() {
    log "Checking competitive-programming repository"

    local adjacent_workspace="${SCRIPT_DIR}/competitive-programming.code-workspace"
    local default_workspace="${DEFAULT_REPO_DIR}/competitive-programming.code-workspace"

    if [[ -f "$adjacent_workspace" ]]; then
        REPO_DIR="$SCRIPT_DIR"
    elif [[ -f "$default_workspace" ]]; then
        REPO_DIR="$DEFAULT_REPO_DIR"
    elif [[ "$MODE" == "check" ]]; then
        missing "Repository clone at ${DEFAULT_REPO_DIR}"
        return
    else
        if [[ -e "$DEFAULT_REPO_DIR" ]]; then
            die "${DEFAULT_REPO_DIR} already exists but is not a complete repository clone. Move it aside, then rerun setup.sh."
        fi

        /bin/mkdir -p "$(dirname "$DEFAULT_REPO_DIR")"
        /usr/bin/git clone "$REPOSITORY_URL" "$DEFAULT_REPO_DIR"
        REPO_DIR="$DEFAULT_REPO_DIR"
    fi

    WORKSPACE_FILE="${REPO_DIR}/competitive-programming.code-workspace"
    [[ -f "$WORKSPACE_FILE" ]] || die "The repository clone is missing its workspace file."
    ok "$REPO_DIR"
}

ensure_homebrew() {
    log "Checking Homebrew"

    BREW="$(find_brew || true)"
    if [[ -n "$BREW" ]]; then
        configure_homebrew_shell
        ok "$($BREW --version | /usr/bin/head -n 1)"
        return
    fi

    if [[ "$MODE" == "check" ]]; then
        missing "Homebrew"
        return
    fi

    log "Installing Homebrew"
    NONINTERACTIVE=1 /bin/bash -c "$(/usr/bin/curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

    BREW="$(find_brew || true)"
    [[ -n "$BREW" ]] || die "Homebrew installed, but its executable could not be found."

    # Make brew available in future zsh sessions as well as this script.
    configure_homebrew_shell

    ok "$($BREW --version | /usr/bin/head -n 1)"
}

ensure_formula() {
    local formula="$1"

    if "$BREW" list --formula "$formula" >/dev/null 2>&1; then
        ok "Homebrew formula: $formula"
    elif [[ "$MODE" == "check" ]]; then
        missing "Homebrew formula: $formula"
    else
        "$BREW" install "$formula"
        ok "Homebrew formula: $formula"
    fi
}

ensure_cask() {
    local cask="$1"

    if "$BREW" list --cask "$cask" >/dev/null 2>&1; then
        ok "Homebrew cask: $cask"
    elif [[ "$MODE" == "check" ]]; then
        missing "Homebrew cask: $cask"
    else
        "$BREW" install --cask "$cask"
        ok "Homebrew cask: $cask"
    fi
}

find_codium() {
    local brew_prefix
    brew_prefix="$($BREW --prefix)"

    if command -v codium >/dev/null 2>&1; then
        command -v codium
    elif [[ -x "${brew_prefix}/bin/codium" ]]; then
        printf '%s\n' "${brew_prefix}/bin/codium"
    elif [[ -x /Applications/VSCodium.app/Contents/Resources/app/bin/codium ]]; then
        printf '%s\n' /Applications/VSCodium.app/Contents/Resources/app/bin/codium
    else
        return 1
    fi
}

ensure_extensions() {
    log "Checking VSCodium extensions"

    CODIUM="$(find_codium || true)"
    if [[ -z "$CODIUM" ]]; then
        missing "VSCodium command-line launcher"
        return
    fi

    local installed_extensions
    installed_extensions="$($CODIUM --list-extensions 2>/dev/null || true)"

    local extension
    for extension in "${EXTENSIONS[@]}"; do
        if printf '%s\n' "$installed_extensions" | /usr/bin/grep -Fiqx "$extension"; then
            ok "VSCodium extension: $extension"
        elif [[ "$MODE" == "check" ]]; then
            missing "VSCodium extension: $extension"
        elif "$CODIUM" --install-extension "$extension"; then
            ok "VSCodium extension: $extension"
        else
            missing "VSCodium extension: $extension"
        fi
    done
}

find_gpp() {
    local gcc_prefix="$1"
    local candidate
    local version
    local best_version=-1
    local best_path=""

    for candidate in "${gcc_prefix}"/bin/g++-[0-9]*; do
        [[ -x "$candidate" ]] || continue
        version="${candidate##*-}"
        [[ "$version" =~ ^[0-9]+$ ]] || continue
        if ((version > best_version)); then
            best_version="$version"
            best_path="$candidate"
        fi
    done

    [[ -n "$best_path" ]] || return 1
    printf '%s\n' "$best_path"
}

sync_workspace_paths() {
    log "Synchronizing workspace tool paths"

    local gcc_prefix
    local boost_prefix
    local format_prefix
    local gpp
    local gcc_version
    local gcc_target
    local gcc_include_base
    local gcc_target_include
    local boost_include
    local clang_format

    gcc_prefix="$($BREW --prefix gcc)"
    boost_prefix="$($BREW --prefix boost)"
    format_prefix="$($BREW --prefix clang-format)"
    gpp="$(find_gpp "$gcc_prefix" || true)"

    [[ -n "$gpp" ]] || die "Could not find Homebrew's versioned g++ executable."

    gcc_version="${gpp##*-}"
    gcc_target="$($gpp -dumpmachine)"
    gcc_include_base="${gcc_prefix}/include/c++/${gcc_version}"
    gcc_target_include="${gcc_include_base}/${gcc_target}"
    boost_include="${boost_prefix}/include"
    clang_format="${format_prefix}/bin/clang-format"

    [[ -x "$clang_format" ]] || die "clang-format was installed but is not executable at ${clang_format}."

    if [[ ! -f "${REPO_DIR}/.clangd" ]]; then
        if [[ "$MODE" == "check" ]]; then
            missing "${REPO_DIR}/.clangd"
        else
            printf '%s\n' \
                'CompileFlags:' \
                "  Compiler: ${gpp}" \
                '  Add:' \
                '    - -std=c++17' \
                "    - -I${boost_include}" > "${REPO_DIR}/.clangd"
            ok "Created repository clangd configuration"
        fi
    fi

    local -a config_files=()
    local file
    for file in \
        "${REPO_DIR}/.vscode/settings.json" \
        "${REPO_DIR}/.vscode/tasks.json" \
        "${REPO_DIR}/.vscode/c_cpp_properties.json" \
        "${REPO_DIR}/.clangd" \
        "${REPO_DIR}/compile_flags.txt"; do
        [[ -f "$file" ]] && config_files+=("$file")
    done

    if [[ "$MODE" == "install" ]]; then
        CP_GPP="$gpp" \
        CP_GCC_INCLUDE_BASE="$gcc_include_base" \
        CP_GCC_TARGET_INCLUDE="$gcc_target_include" \
        CP_BOOST_INCLUDE="$boost_include" \
        CP_CLANG_FORMAT="$clang_format" \
        /usr/bin/perl -0pi -e '
            s{/(?:opt/homebrew|usr/local)/opt/gcc/bin/g\+\+-[0-9]+}{$ENV{CP_GPP}}g;
            s{/(?:opt/homebrew|usr/local)/opt/gcc/include/c\+\+/[0-9]+/(?:aarch64|x86_64)-apple-darwin[0-9]+}{$ENV{CP_GCC_TARGET_INCLUDE}}g;
            s{/(?:opt/homebrew|usr/local)/opt/gcc/include/c\+\+/[0-9]+/backward}{$ENV{CP_GCC_INCLUDE_BASE}/backward}g;
            s{/(?:opt/homebrew|usr/local)/opt/gcc/include/c\+\+/[0-9]+}{$ENV{CP_GCC_INCLUDE_BASE}}g;
            s{/(?:opt/homebrew|usr/local)/opt/boost/include}{$ENV{CP_BOOST_INCLUDE}}g;
            s{/(?:opt/homebrew|usr/local)/(?:Cellar/clang-format/[^/"\s]+|opt/clang-format)/bin/clang-format}{$ENV{CP_CLANG_FORMAT}}g;
        ' "${config_files[@]}"
    fi

    local all_config
    all_config="$(/bin/cat "${config_files[@]}")"

    if printf '%s' "$all_config" | /usr/bin/grep -Fq "$gpp"; then
        ok "GNU compiler path: $gpp"
    else
        missing "Workspace references current GNU compiler: $gpp"
    fi

    if printf '%s' "$all_config" | /usr/bin/grep -Fq "$clang_format"; then
        ok "clang-format path: $clang_format"
    else
        missing "Workspace references current clang-format: $clang_format"
    fi

    if printf '%s' "$all_config" | /usr/bin/grep -Fq "$boost_include"; then
        ok "Boost include path: $boost_include"
    else
        missing "Workspace references current Boost headers: $boost_include"
    fi
}

verify_workspace() {
    log "Running C++ toolchain smoke test"

    local gcc_prefix
    local boost_prefix
    local gpp
    local temp_dir
    local source_file
    local output_file

    gcc_prefix="$($BREW --prefix gcc)"
    boost_prefix="$($BREW --prefix boost)"
    gpp="$(find_gpp "$gcc_prefix" || true)"
    [[ -n "$gpp" ]] || die "Could not find Homebrew g++."

    temp_dir="$(/usr/bin/mktemp -d "${TMPDIR:-/tmp}/cp-setup.XXXXXX")"
    source_file="${temp_dir}/smoke.cpp"
    output_file="${temp_dir}/smoke"

    printf '%s\n' \
        '#include <bits/stdc++.h>' \
        '#include <ext/pb_ds/assoc_container.hpp>' \
        '#include <ext/pb_ds/tree_policy.hpp>' \
        'using namespace __gnu_pbds;' \
        'int main() {' \
        '    tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update> values;' \
        '    values.insert(7);' \
        '    return values.order_of_key(8) == 1 ? 0 : 1;' \
        '}' > "$source_file"

    if "$gpp" -std=c++17 -I"${boost_prefix}/include" "$source_file" -o "$output_file" && "$output_file"; then
        ok "GCC, bits/stdc++.h, and PBDS"
    else
        missing "GCC/PBDS smoke test"
    fi

    if "$($BREW --prefix clang-format)/bin/clang-format" \
        --style=file \
        --assume-filename="${REPO_DIR}/smoke.cpp" \
        "$source_file" >/dev/null; then
        ok "clang-format and repository style"
    else
        missing "clang-format smoke test"
    fi

    /bin/rm -rf -- "$temp_dir"

    if [[ -s "${REPO_DIR}/.vscode/cpp.json.code-snippets" ]]; then
        ok "C++ workspace snippets"
    else
        missing "${REPO_DIR}/.vscode/cpp.json.code-snippets"
    fi

    if [[ -s "${REPO_DIR}/.clang-format" ]]; then
        ok "Repository clang-format rules"
    else
        missing "${REPO_DIR}/.clang-format"
    fi

    if [[ -x /usr/bin/clangd ]]; then
        ok "Apple clangd: $(/usr/bin/clangd --version | /usr/bin/head -n 1)"
    else
        missing "Apple clangd"
    fi
}

main() {
    case "${1:-}" in
        "")
            ;;
        --check)
            MODE="check"
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            usage >&2
            exit 2
            ;;
    esac

    [[ "$(uname -s)" == "Darwin" ]] || die "This setup targets macOS."

    ensure_command_line_tools
    ensure_repository

    if [[ -z "$REPO_DIR" ]]; then
        printf '\nSetup check found %d missing component(s).\n' "$FAILURES"
        exit 1
    fi

    ensure_homebrew

    if [[ -z "$BREW" ]]; then
        printf '\nSetup check found %d missing component(s).\n' "$FAILURES"
        exit 1
    fi

    log "Checking Homebrew packages"
    local item
    for item in "${FORMULAE[@]}"; do
        ensure_formula "$item"
    done
    for item in "${CASKS[@]}"; do
        ensure_cask "$item"
    done

    ensure_extensions

    # Only inspect paths when their packages are available.
    if "$BREW" list --formula gcc boost clang-format >/dev/null 2>&1; then
        sync_workspace_paths
        verify_workspace
    fi

    if ((FAILURES > 0)); then
        printf '\n\033[1;31mSetup found %d problem(s).\033[0m\n' "$FAILURES" >&2
        exit 1
    fi

    if [[ "$MODE" == "check" ]]; then
        printf '\n\033[1;32mEverything is installed and configured.\033[0m\n'
        exit 0
    fi

    log "Setup complete"
    printf '%s\n' \
        "The compiler, Boost, clangd, clang-format, Geist Mono, snippets," \
        "VSCodium, and workspace extensions are ready."
    warn "WakaTime still requires your account/API-key sign-in because secrets are not stored in Git."

    log "Opening the competitive-programming workspace"
    "$CODIUM" "$WORKSPACE_FILE" >/dev/null 2>&1 &
}

main "$@"
