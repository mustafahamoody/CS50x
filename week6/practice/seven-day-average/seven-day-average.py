import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    previous_cases = dict()

    for state in reader:
        if state["state"] in previous_cases:
            new_cases_today = int(state["cases"]) - int(previous_cases[state["state"]])
            if len(new_cases[state["state"]]) < 14:
                new_cases[state["state"]].append((new_cases_today))
            else:
                new_cases[state["state"]].pop(0)
                new_cases[state["state"]].append(new_cases_today)

            previous_cases[state["state"]] = state["cases"]

        else:
            new_cases[state["state"]] = list()
            new_cases[state["state"]].append(int(state["cases"]))
            previous_cases[state["state"]] = state["cases"]

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        thisWeekAvg = sum(new_cases[state][0:7]) / 7
        lastWeekAvg = sum(new_cases[state][7:14]) / 7

        avg = thisWeekAvg - lastWeekAvg
        avg = round(avg)

        try:
            percent = avg / lastWeekAvg * 100
            percent = round(percent)
        except ZeroDivisionError:
            raise ZeroDivisionError

        if lastWeekAvg > thisWeekAvg:
            incDec = "decrease"
        else:
            incDec = "increase"

        print(
            "{} had a 7-day average of {} and an {} of {}%".format(
                state, avg, incDec, percent
            )
        )


main()
