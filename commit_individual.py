import subprocess
import os

def run_git_command(command, check=True, capture_output=True):
    """Executes a git command and handles output/errors."""
    try:
        result = subprocess.run(
            command,
            check=check,
            capture_output=capture_output, # Use the provided argument
            text=True,
            shell=False 
        )
        
        # Only try to strip/return output if it was captured
        if capture_output and result.stdout is not None:
            return result.stdout.strip()
        return None # Return None if output was not captured
        
    except subprocess.CalledProcessError as e:
        print(f"❌ Error running Git command: {' '.join(command)}")
        # Check if stderr was captured before trying to strip it
        if e.stderr is not None:
             print(f"Stderr: {e.stderr.strip()}")
        if check:
            exit(1)
        return ""
    except FileNotFoundError:
        print("❌ Error: Git command not found. Make sure Git is installed and in your PATH.")
        exit(1)

def auto_commit_files():
    """Resets staging, iterates through modified/untracked files, and commits them individually."""
    
    print("🚀 Starting automated individual file commit process...")
    print("---")

    # 1. Unstage all current changes
    print("🗑️ Resetting staging area (unstaging all files)...")
    run_git_command(["git", "reset"])

    # 2. Get the list of modified/added files (tracked files) AND untracked files
    
    # Tracked Files: Modified/Added since last commit
    modified_and_added_output = run_git_command(["git", "diff", "--name-only"])
    modified_files = modified_and_added_output.splitlines() if modified_and_added_output else []

    # Untracked Files: New files not yet tracked by git
    untracked_output = run_git_command(["git", "ls-files", "--others", "--exclude-standard"])
    untracked_files = untracked_output.splitlines() if untracked_output else []
    
    # Combine the lists and filter for actual existing files
    all_files_to_commit = []
    for f in modified_files + untracked_files:
        if f and os.path.exists(f) and f not in all_files_to_commit: # Check for existence and duplicates
            all_files_to_commit.append(f)


    if not all_files_to_commit:
        print("✅ No modified or untracked files found to commit. Exiting.")
        return

    # 3. Process and Commit
    for file_path in all_files_to_commit:
        # Construct the commit message
        file_name = os.path.basename(file_path)
        commit_message = f"Upload {file_name}"

        print("\n" + "-" * 50)
        print(f"File: **{file_path}**")
        
        # Stage the file
        # NOTE: git add is required for both modified (M) and untracked (??) files
        print(f"✨ Staging {file_path}...")
        run_git_command(["git", "add", file_path])
        
        # Commit the file
        print(f"✍️ Committing with message: **{commit_message}**")
        # We ensure capture_output=True here because we don't want commit output polluting the loop
        run_git_command(["git", "commit", "-m", commit_message])

    print("\n" + "-" * 50)
    print("✅ Automated commit process complete.")
    # Show final status, setting capture_output=False now works correctly
    run_git_command(["git", "status"], capture_output=False) 

if __name__ == "__main__":
    auto_commit_files()