# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # Read teams into memory from file
    with open(sys.argv[1], "r") as file:

        reader = list(csv.DictReader(file))
        # Reading a row converting rating to int
        for row in reader:
            cur_team = row
            cur_team["rating"] = int(cur_team["rating"])
            teams.append(cur_team)

    counts = {}
    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)

        # If winner team is already in list then just update its rating
        if winner in counts:
            counts[winner] += 1
        # Else creat new dictionary for winner team and set its count to 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    # Returns winners of one round as a list
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # Initially consider all team as winners
    winners = teams
    while True:
        # If there are more than 1 winners
        if len(winners) != 1:
            winners = simulate_round(winners)
        # else just 1 winner is left
        else:
            break

    # Returns just team name as string
    return winners[0]["team"]


if __name__ == "__main__":
    main()
