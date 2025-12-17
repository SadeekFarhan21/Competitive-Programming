import datetime
import random
import os

# --- Configuration: TARGET GAP FOR NEW DATES ---
# The existing commits will have their timestamps randomly set within this date range.
GAP_START_DATE = datetime.datetime(2025, 3, 1)  # March 1st, 2025
GAP_END_DATE = datetime.datetime(2025, 4, 30)    # April 30th, 2025
# ------------------------------------------------

def adjust_timestamp(timestamp):
    """
    Shifts the timestamp to be a random time within the target gap.
    The original timestamp is ignored, as we are scattering commits randomly.
    """
    
    # Calculate a random time within the target gap
    time_delta = GAP_END_DATE - GAP_START_DATE
    
    # Get a random number of seconds within the total duration of the gap
    random_seconds = random.randint(0, int(time_delta.total_seconds()))
    
    # Create the new datetime object
    new_dt = GAP_START_DATE + datetime.timedelta(seconds=random_seconds)
    
    # Return the new timestamp (epoch time)
    return int(new_dt.timestamp())

# git-filter-repo passes environment variables for the commit date.
# We modify these raw epoch timestamps before the commit is rewritten.
if __name__ == '__main__':
    # Get the raw timestamp and timezone from the environment
    author_date_raw = os.environ.get('GIT_AUTHOR_DATE_RAW')
    committer_date_raw = os.environ.get('GIT_COMMITTER_DATE_RAW')

    # Process Author Date
    if author_date_raw:
        # e.g., '1701979200 +0000' -> timestamp='1701979200', timezone='+0000'
        author_parts = author_date_raw.split()
        author_timestamp = int(author_parts[0])
        author_timezone = author_parts[1]
        
        new_author_timestamp