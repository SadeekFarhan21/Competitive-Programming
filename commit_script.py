#!/bin/bash
set -e
for i, file_path in enumerate(files):
    commit_date = start_date - timedelta(days=i)
    date_str = commit_date.strftime("%Y-%m-%d")
    problem_name = os.path.splitext(os.path.basename(file_path))[0]
    commit_message = f"feat: Add solution for {problem_name}"
    f.write(f'git add "{file_path}"\n')
    f.write(f'GIT_COMMITTER_DATE="{date_str} 12:00:00" git commit --author="farhan <farhan@gmail.com>" --date="{date_str} 12:00:00" -m "{commit_message}"\n')

print("Generated run_commits.sh")
