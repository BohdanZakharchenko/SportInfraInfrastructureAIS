#pragma once

#ifndef AIS_H
#define AIS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <chrono>
#include <set>
#include <unordered_set>
#include <utility>
#include <limits> 
#include <iomanip>
#include <sstream>
#include <map>


using namespace std;

class Stadium {
private:
    string name;
    string type;
    int capacity;

    // Приватний конструктор
    Stadium(const string& n, const string& t, int c) : name(n), type(t), capacity(c) {}

public:
    string getName() const {
        return name;
    }

    string getType() const {
        return type;
    }

    int getCapacity() const {
        return capacity;
    }

    // Клас-будівельник для Stadium
    class Builder {
    private:
        string name;
        string type;
        int capacity;

    public:
        Builder& setName(const string& n) {
            name = n;
            return *this;
        }

        Builder& setType(const string& t) {
            type = t;
            return *this;
        }

        Builder& setCapacity(int c) {
            capacity = c;
            return *this;
        }

        Stadium build() {
            return Stadium(name, type, capacity);
        }
    };

    // Функція для зчитування даних про стадіони з файлу
    static vector<Stadium> readStadiumsFromFile(const string& filename) {
        vector<Stadium> stadiums;
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                size_t firstSpace = line.find(" ");
                size_t secondSpace = line.find(" ", firstSpace + 1);
                string name = line.substr(0, firstSpace);
                int capacity = stoi(line.substr(firstSpace + 1, secondSpace - firstSpace - 1));
                string type = line.substr(secondSpace + 1);
                Stadium stadium = Stadium::Builder().setName(name).setType(type).setCapacity(capacity).build();
                stadiums.push_back(stadium);
            }
            inputFile.close();
        }
        return stadiums;
    }

    // Функція для фільтрації стадіонів за типом покриття
    static vector<Stadium> filterStadiumsByType(const vector<Stadium>& stadiums, string searchedType) {
        vector<Stadium> filteredStadiums;
       
        
        if (searchedType == "Будь-яке") {
            for (const auto& stadium : stadiums) {
                filteredStadiums.push_back(stadium);
                
            }
            return filteredStadiums;
        }
       
        for (const auto& stadium : stadiums) {
            if (stadium.getType() == searchedType) {
                filteredStadiums.push_back(stadium);
            }
        }
        return filteredStadiums;
    }

    // Функція для виводу даних про стадіони
    /*static void printStadiums(const vector<Stadium>& stadiums) {
        cout << "Кількість знайдених стадіонів: " << stadiums.size() << endl;
        for (size_t i = 0; i < stadiums.size(); ++i) {
            cout << i + 1 << ". Споруда: " << stadiums[i].getName() << endl
                << " Тип покриття: " << stadiums[i].getType() << endl
                << " Місткість споруди: " << stadiums[i].getCapacity() << endl
                << "----------------------------------------------------" << endl;
        }
    }*/
};


class Athlete {
private:
    string nameOfAthlete;
    vector<string> kindOfSport;
    string athleteCategory;
    vector<string> trainer;
    string trainerCategory;
    string building;
    string sportClub;
    string dividingLine;

public:
    // Геттери
    string getNameOfAthlete() const { return nameOfAthlete; }
    vector<string> getKindOfSport() const { return kindOfSport; }
    string getAthleteCategory() const { return athleteCategory; }
    vector<string> getTrainer() const { return trainer; }
    string getTrainerCategory() const { return trainerCategory; }
    string getBuilding() const { return building; }
    string getSportClub() const { return sportClub; }
    string getDividingLine() const { return dividingLine; }

    // Сеттери
    void setNameOfAthlete(const string& name) { nameOfAthlete = name; }
    void addKindOfSport(const string& sport) { kindOfSport.push_back(sport); }
    void setAthleteCategory(const string& category) { athleteCategory = category; }
    void addTrainer(const string& trainerName) { trainer.push_back(trainerName); }
    void setTrainerCategory(const string& category) { trainerCategory = category; }
    void setBuilding(const string& buildingName) { building = buildingName; }
    void setSportClub(const string& club) { sportClub = club; }
    void setDividingLine(const string& line) { dividingLine = line; }
public:
    // Інтерфейс стратегії фільтрації
    class AthleteFilterStrategy {
    public:
        virtual vector<Athlete> filter(const vector<Athlete>& athletes) const = 0;
        virtual ~AthleteFilterStrategy() {}
    };

    // Конкретні реалізації стратегії фільтрації за видом спорту та рівнем атлета
    class SportCategoryFilterStrategy : public AthleteFilterStrategy {
    private:
        string searchedSport;
        string searchedCategory;

    public:
        SportCategoryFilterStrategy(const string& sport, const string& category)
            : searchedSport(sport), searchedCategory(category) {}

        vector<Athlete> filter(const vector<Athlete>& athletes) const override {
            vector<Athlete> filteredAthletes;
            for (const auto& athlete : athletes) {
                for (const auto& sport : athlete.getKindOfSport()) {
                    if (sport == searchedSport && athlete.getAthleteCategory() == searchedCategory) {
                        filteredAthletes.push_back(athlete);
                        break;
                    }
                }
            }
            return filteredAthletes;
        }
    };

    // Фільтрація спортсменів за спорткомплексом
    class BuildingFilterStrategy : public AthleteFilterStrategy {
    private:
        string searchedBuilding;

    public:
        BuildingFilterStrategy(const string& building) : searchedBuilding(building) {}

        vector<Athlete> filter(const vector<Athlete>& athletes) const override {
            vector<Athlete> filteredAthletes;
            for (const auto& athlete : athletes) {
                if (athlete.getBuilding() == searchedBuilding) {
                    filteredAthletes.push_back(athlete);
                }
            }
            return filteredAthletes;
        }
    };

    // Конкретні реалізації стратегії фільтрації за тренерами та розрядами спортсменів
    class TrainerCategoryFilterStrategy : public AthleteFilterStrategy {
    private:
        string searchedTrainer;
        string searchedCategory;

    public:
        TrainerCategoryFilterStrategy(const string& trainer, const string& category)
            : searchedTrainer(trainer), searchedCategory(category) {}

        vector<Athlete> filter(const vector<Athlete>& athletes) const override {
            vector<Athlete> filteredAthletes;
            for (const auto& athlete : athletes) {
                for (const auto& trainer : athlete.getTrainer()) {
                    if (trainer == searchedTrainer && athlete.getAthleteCategory() == searchedCategory) {
                        filteredAthletes.push_back(athlete);
                        break;
                    }
                }
            }
            return filteredAthletes;
        }


    };


    // Конкретні реалізації стратегії фільтрації спортсменів за кількома видами спорту
    class MultipleSportsFilterStrategy : public AthleteFilterStrategy {
    private:
        string sport1;
        string sport2;

    public:
        MultipleSportsFilterStrategy(const string& sport1, const string& sport2)
            : sport1(sport1), sport2(sport2) {}

        vector<Athlete> filter(const vector<Athlete>& athletes) const override {
            vector<Athlete> filteredAthletes;
            for (const Athlete& athlete : athletes) {
                if (athlete.getKindOfSport().size() > 1) {
                    bool hasFirstSport = false;
                    bool hasSecondSport = false;
                    for (const auto& sport : athlete.getKindOfSport()) {
                        if (sport == sport1) {
                            hasFirstSport = true;
                        }
                        else if (sport == sport2) {
                            hasSecondSport = true;
                        }
                    }
                    if (hasFirstSport && hasSecondSport) {
                        filteredAthletes.push_back(athlete);
                    }
                }
            }
            return filteredAthletes;
        }
    };



    // Фільтрація спортсменів за іменем
    class NameFilterStrategy : public AthleteFilterStrategy {
    private:
        string athleteName;

    public:
        NameFilterStrategy(const string& name) : athleteName(name) {}

        vector<Athlete> filter(const vector<Athlete>& athletes) const override {
            vector<Athlete> filteredAthletes;
            for (const auto& athlete : athletes) {
                if (athlete.getNameOfAthlete() == athleteName) {
                    filteredAthletes.push_back(athlete);
                }
            }
            return filteredAthletes;
        }
    };

    class AthleteFilter {
    private:
        AthleteFilterStrategy* strategy;

    public:
        AthleteFilter(AthleteFilterStrategy* strategy) : strategy(strategy) {}

        vector<Athlete> filterAthletes(const vector<Athlete>& athletes) const {
            return strategy->filter(athletes);
        }
    };

    static vector<Athlete> filterAthletes(const vector<Athlete>& athletes, const AthleteFilterStrategy& strategy) {
        return strategy.filter(athletes);
    }

    //Функція для зчитування даних про спортсменів
    static vector<Athlete> readAthletesFromFile(const string& filename) {
        vector<Athlete> athletes;
        ifstream input(filename);
        if (!input) {
            cout << "Error: Unable to open file." << endl;
            return athletes;
        }
        string line;
        while (getline(input, line)) {
            Athlete athlete;
            athlete.setNameOfAthlete(line);
            getline(input, line);
            string sport;
            for (size_t i = 0; i < line.length(); i++) {
                if (line[i] == ',' || line[i] == ' ') {
                    if (!sport.empty()) {
                        athlete.addKindOfSport(sport);
                        sport.clear();
                    }
                }
                else {
                    sport.push_back(line[i]);
                }
            }
            if (!sport.empty()) {
                athlete.addKindOfSport(sport);
            }
            getline(input, line);
            athlete.setAthleteCategory(line);
            getline(input, line);
            string trainers;
            string trainersString;
            for (size_t i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    if (!trainers.empty()) {
                        athlete.addTrainer(trainers);
                        trainers.clear();
                    }
                }
                else {
                    trainers.push_back(line[i]);
                }
            }
            if (!trainers.empty()) {
                athlete.addTrainer(trainers);
            }
            getline(input, line);
            athlete.setTrainerCategory(line);
            getline(input, line);
            athlete.setBuilding(line);
            getline(input, line);
            athlete.setSportClub(line);
            getline(input, line);
            athlete.setDividingLine(line);

            athletes.push_back(athlete);
        }
        input.close();

        return athletes;
    }

    //Функція для виводу інформації про спортсменів
    static void printAthletes(const vector<Athlete>& athletes) {
        cout << "======================================================" << endl;
        for (const Athlete& athlete : athletes) {
            cout << "ПІБ атлета: " << athlete.getNameOfAthlete() << endl;
            cout << "Вид спорту: ";
            for (const string& sport : athlete.getKindOfSport()) {
                cout << sport << ", ";
            }
            cout << endl;
            cout << "Розряд атлета: " << athlete.getAthleteCategory() << endl;
            cout << "Тренер: ";
            for (size_t i = 0; i < athlete.getTrainer().size(); i++) {
                cout << athlete.getTrainer()[i];
                if (i != athlete.getTrainer().size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            cout << "Розряд тренера: " << athlete.getTrainerCategory() << endl;
            cout << "Будівля: " << athlete.getBuilding() << endl;
            cout << "Спортивний клуб: " << athlete.getSportClub() << endl;
            cout << athlete.getDividingLine() << endl;
        }
    }


};




class Trainer : public Athlete {
public:

    class TrainerFilterStrategy {
    public:
        virtual vector<Athlete> filter(const vector<Athlete>& athletes) const = 0;
        virtual ~TrainerFilterStrategy() {}
    };

    class TrainersBySportFilterStrategy : public TrainerFilterStrategy {
    private:
        string searchedSport;

    public:
        TrainersBySportFilterStrategy(const string& sport)
            : searchedSport(sport) {}

        vector<Athlete> filter(const vector<Athlete>& athletes) const override {
            vector<Athlete> trainers;
            for (const auto& athlete : athletes) {
                for (size_t i = 0; i < athlete.getKindOfSport().size(); i++) {
                    if (athlete.getKindOfSport()[i] == searchedSport && i < athlete.getTrainer().size()) {
                        trainers.push_back(athlete);
                        break;
                    }
                }
            }
            return trainers;
        }

        // Функція для друку тренерів певного виду спорту
        void printTrainers(const vector<Athlete>& trainers) const {
            cout << "Тренери за видом спорту " << searchedSport << ":" << endl;
            unordered_set<string> uniqueTrainers;

            for (const auto& athlete : trainers) {
                for (size_t i = 0; i < athlete.getKindOfSport().size(); i++) {
                    if (athlete.getKindOfSport()[i] == searchedSport && i < athlete.getTrainer().size()) {
                        uniqueTrainers.emplace(athlete.getTrainer()[i]);
                    }
                }
            }

            for (const auto& trainer : uniqueTrainers) {
                cout << trainer << endl;
            }
        }
    };

    class TrainersByAthletesNameFilterStrategy : public TrainerFilterStrategy {
    private:
        string searchedName;

    public:
        TrainersByAthletesNameFilterStrategy(const string& name)
            : searchedName(name) {}

        vector<Athlete> filter(const vector<Athlete>& athletes) const override {
            vector<Athlete> filteredAthletes;
            for (const auto& athlete : athletes) {
                if (athlete.getNameOfAthlete() == searchedName) {
                    filteredAthletes.push_back(athlete);
                }
            }
            return filteredAthletes;
        }

        // Функція для друку тренерів певного спортсмена
        void printTrainers(const vector<Athlete>& athletes) const {
            cout << "Тренери спортсмена " << searchedName << ":" << endl;
            unordered_set<string> uniqueTrainers;

            for (const auto& athlete : athletes) {
                if (athlete.getNameOfAthlete() == searchedName) {
                    for (const auto& trainer : athlete.getTrainer()) {
                        uniqueTrainers.emplace(trainer);
                    }
                }
            }

            for (const auto& trainer : uniqueTrainers) {
                cout << trainer << endl;
            }
        }
    };
};

class Competition {
private:
    string nameOfTheCompetition;
    string sport;
    string organizer;
    string date;
    string buildins;
    string firstPlace;
    string secondPlace;
    string thirdPlace;
    string dividingLine;

public:
    Competition() {}

    Competition(const string& nameOfTheCompetition, const string& sport, const string& organizer, const string& date, const string& buildins, const string& firstPlace, const string& secondPlace, const string& thirdPlace, const string& dividingLine)
        : nameOfTheCompetition(nameOfTheCompetition), sport(sport), organizer(organizer), date(date), buildins(buildins), firstPlace(firstPlace), secondPlace(secondPlace), thirdPlace(thirdPlace), dividingLine(dividingLine) {}

    // Геттери
    string getNameOfTheCompetition() const { return nameOfTheCompetition; }
    string getSport() const { return sport; }
    string getOrganizer() const { return organizer; }
    string getDate() const { return date; }
    string getBuildins() const { return buildins; }
    string getFirstPlace() const { return firstPlace; }
    string getSecondPlace() const { return secondPlace; }
    string getThirdPlace() const { return thirdPlace; }
    string getDividingLine() const { return dividingLine; }

    // Сеттери
    void setNameOfTheCompetition(const string& name) { nameOfTheCompetition = name; }
    void setSport(const string& sport) { this->sport = sport; }
    void setOrganizer(const string& organizer) { this->organizer = organizer; }
    void setDate(const string& date) { this->date = date; }
    void setBuildins(const string& buildins) { this->buildins = buildins; }
    void setFirstPlace(const string& firstPlace) { this->firstPlace = firstPlace; }
    void setSecondPlace(const string& secondPlace) { this->secondPlace = secondPlace; }
    void setThirdPlace(const string& thirdPlace) { this->thirdPlace = thirdPlace; }
    void setDividingLine(const string& line) { dividingLine = line; }

    // Зчитування даних про змагання з файлу
    static vector<Competition> readCompetitionsFromFile(const string& filename) {
        vector<Competition> competitions;
        ifstream input(filename);
        if (!input) {
            cout << "Error: Unable to open file." << endl;
            return competitions;
        }
        string line;
        while (getline(input, line)) {
            Competition competition;
            competition.setNameOfTheCompetition(line);
            getline(input, line);
            competition.setSport(line);
            getline(input, line);
            competition.setOrganizer(line);
            getline(input, line);
            competition.setDate(line);
            getline(input, line);
            competition.setBuildins(line);
            getline(input, line);
            competition.setFirstPlace(line);
            getline(input, line);
            competition.setSecondPlace(line);
            getline(input, line);
            competition.setThirdPlace(line);
            getline(input, line);
            competition.setDividingLine(line);

            competitions.push_back(competition);
        }
        input.close();

        return competitions;
    }

    // Вивід інформації про змагання
    static void printCompetitions(const vector<Competition>& competitions) {
        for (const auto& competition : competitions) {
            cout << "Назва змагання: " << competition.nameOfTheCompetition << endl;
            cout << "Вид спорту: " << competition.sport << endl;
            cout << "Організатор: " << competition.organizer << endl;
            cout << "Дата проведення: " << competition.date << endl;
            cout << "Будівля: " << competition.buildins << endl;
            cout << "Перше місце: " << competition.firstPlace << endl;
            cout << "Друге місце: " << competition.secondPlace << endl;
            cout << "Третє місце: " << competition.thirdPlace << endl;
            cout << "Розділювальна лінія: " << competition.dividingLine << endl;
            cout << "--------------------------" << endl;
        }
    }

    // Вивід інформації про змагання
    static void printCompetitionsWins(const vector<Competition>& competitions) {
        for (const auto& competition : competitions) {

            cout << "Перше місце: " << competition.firstPlace << endl;
            cout << "Друге місце: " << competition.secondPlace << endl;
            cout << "Третє місце: " << competition.thirdPlace << endl;

            cout << "--------------------------" << endl;
        }
    }
    // Інтерфейс стратегії фільтрації
    class CompetitionFilterStrategy {
    public:
        virtual vector<Competition> filter(const vector<Competition>& competitions) const = 0;
        virtual ~CompetitionFilterStrategy() {}
    };

    // Фільтрація змагань за клубами та кількістю учасників
    class ClubsAndCompetitorsFilterStrategy {
    private:
        map<string, set<string>> clubToCompetitors;

    public:
        ClubsAndCompetitorsFilterStrategy(const vector<Athlete>& athletes) {
            for (const auto& athlete : athletes) {
                clubToCompetitors[athlete.getSportClub()].insert(athlete.getNameOfAthlete());
            }
        }

        void printClubWinnersCount(const vector<Competition>& competitions) const {
            map<string, int> clubWinnersCount;

            for (const auto& competition : competitions) {
                if (clubToCompetitors.count(competition.getFirstPlace())) {
                    clubWinnersCount[competition.getFirstPlace()]++;
                }
                if (clubToCompetitors.count(competition.getSecondPlace())) {
                    clubWinnersCount[competition.getSecondPlace()]++;
                }
                if (clubToCompetitors.count(competition.getThirdPlace())) {
                    clubWinnersCount[competition.getThirdPlace()]++;
                }
            }

            for (const auto& entry : clubWinnersCount) {
                cout << "Клуб: " << entry.first << " - Кількість перемог: " << entry.second << endl;
            }
        }
    };

    // Фільтрація змагань за участю спортсменів
    class AthletesParticipatingInCompetitionsFilterStrategy : public CompetitionFilterStrategy {
    private:
        set<string> participatingAthletes;

    public:
        AthletesParticipatingInCompetitionsFilterStrategy(const vector<Athlete>& athletes) {
            for (const auto& athlete : athletes) {
                participatingAthletes.insert(athlete.getNameOfAthlete());
            }
        }

        vector<Athlete> filter(const vector<Competition>& competitions, const vector<Athlete>& athletes) const {
            vector<Athlete> nonParticipatingAthletes;

            set<string> competingAthletes;
            for (const auto& competition : competitions) {
                competingAthletes.insert(competition.getFirstPlace());
                competingAthletes.insert(competition.getSecondPlace());
                competingAthletes.insert(competition.getThirdPlace());
            }

            for (const auto& athlete : athletes) {
                if (competingAthletes.find(athlete.getNameOfAthlete()) == competingAthletes.end()) {
                    nonParticipatingAthletes.push_back(athlete);
                }
            }

            return nonParticipatingAthletes;
        }
    };

    // Фільтрація змагань за датою
    class DateFilterStrategy : public CompetitionFilterStrategy {
    private:
        int days;

    public:
        DateFilterStrategy(int days) : days(days) {}

        vector<Competition> filter(const vector<Competition>& competitions) const override {
            vector<Competition> filteredCompetitions;
            auto now = chrono::system_clock::now();
            auto currentTime = chrono::system_clock::to_time_t(now);

            for (const auto& competition : competitions) {
                tm competitionTime = {};
                istringstream ss(competition.getDate());
                ss >> get_time(&competitionTime, "%Y-%m-%d");
                auto competitionTimeT = mktime(&competitionTime);
                auto diff = difftime(currentTime, competitionTimeT) / (60 * 60 * 24);

                if (diff <= days) {
                    filteredCompetitions.push_back(competition);
                }
            }

            return filteredCompetitions;
        }
    };

    // Фільтрація змагань за організатором
    class OrganizerFilterStrategy : public CompetitionFilterStrategy {
    private:
        string organizer;

    public:
        OrganizerFilterStrategy(const string& organizer) : organizer(organizer) {}

        vector<Competition> filter(const vector<Competition>& competitions) const override {
            vector<Competition> filteredCompetitions;
            for (const auto& competition : competitions) {
                if (competition.getOrganizer() == organizer) {
                    filteredCompetitions.push_back(competition);
                }
            }
            return filteredCompetitions;
        }
    };

    // Фільтрація змагань за будівлею та видом спорту
    class BuildingAndSportFilterStrategy : public CompetitionFilterStrategy {
    private:
        string building;
        string sport;

    public:
        BuildingAndSportFilterStrategy(const string& building, const string& sport)
            : building(building), sport(sport) {}

        vector<Competition> filter(const vector<Competition>& competitions) const override {
            vector<Competition> filteredCompetitions;
            for (const auto& competition : competitions) {
                if (competition.getBuildins() == building && competition.getSport() == sport) {
                    filteredCompetitions.push_back(competition);
                }
            }
            return filteredCompetitions;
        }
    };

    class WinnerFilterStrategy {
    public:
        virtual vector<Competition> filterWinners(const vector<Competition>& competitions) const = 0;
        virtual ~WinnerFilterStrategy() {}
    };

    // Конкретная стратегия для фильтрации победителей по названию соревнования
    class CompetitionNameWinnerFilterStrategy : public WinnerFilterStrategy {
    private:
        string competitionName;

    public:
        CompetitionNameWinnerFilterStrategy(const string& name) : competitionName(name) {}
        vector<Competition> filterWinners(const vector<Competition>& competitions) const override {
            vector<Competition> filteredCompetitions;

            for (const auto& competition : competitions) {
                if (competition.getNameOfTheCompetition() == competitionName) {
                    filteredCompetitions.push_back(competition);
                }
            }

            return filteredCompetitions;
        }
    };

    class NoParticipationInPeriodStrategy : public Athlete::AthleteFilterStrategy {
    private:
        int days;
        vector<Competition> competitions;

    public:
        NoParticipationInPeriodStrategy(int days, const vector<Competition>& comps) : days(days), competitions(comps) {}

        vector<Athlete> filter(const vector<Athlete>& athletes) const override {
            vector<Athlete> filteredAthletes;

            auto currentTime = chrono::system_clock::now();
            auto targetTime = currentTime - chrono::hours(24 * days);

            for (const auto& athlete : athletes) {
                bool hasParticipated = false;

                for (const auto& competition : competitions) {
                    int year, month, day;
                    if (sscanf(competition.getDate().c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
                        // Якщо формат дати некоректний, пропускаємо це змагання
                        continue;
                    }
                    std::tm competitionTimeStruct{};
                    competitionTimeStruct.tm_year = year - 1900;
                    competitionTimeStruct.tm_mon = month - 1;
                    competitionTimeStruct.tm_mday = day;
                    auto competitionTimePoint = chrono::system_clock::from_time_t(mktime(&competitionTimeStruct));

                    if (competitionTimePoint >= targetTime) {
                        if (athlete.getNameOfAthlete() == competition.getFirstPlace() ||
                            athlete.getNameOfAthlete() == competition.getSecondPlace() ||
                            athlete.getNameOfAthlete() == competition.getThirdPlace()) {
                            hasParticipated = true;
                            break;
                        }
                    }
                }

                if (!hasParticipated) {
                    filteredAthletes.push_back(athlete);
                }
            }

            return filteredAthletes;
        }
    };

    class OrganizerCountStrategy : public Athlete::AthleteFilterStrategy {
    public:
        static map<string, int> countAndPrintOrganizers(const vector<Competition>& competitions) {
            map<string, int> organizerCounts;

            // Підрахунок кількості змагань для кожного організатора
            for (const auto& competition : competitions) {
                const string& organizer = competition.getOrganizer();
                organizerCounts[organizer]++;
            }

            // Виведення результатів
            return organizerCounts;
        }
    };



    // Функция, использующая стратегию для фильтрации победителей
    static vector<Competition> filterWinnersByCompetitions(const vector<Competition>& competitions, WinnerFilterStrategy& filterStrategy) {
        return filterStrategy.filterWinners(competitions);
    }
};

//class Stadium {
//private:
//    std::string name;
//    std::string type;
//    int capacity;
//
//    // Приватний конструктор
//    Stadium(const std::string& n, const std::string& t, int c);
//
//public:
//    std::string getName() const;
//    std::string getType() const;
//    int getCapacity() const;
//
//    // Клас-будівельник для Stadium
//    class Builder {
//    private:
//        std::string name;
//        std::string type;
//        int capacity;
//
//    public:
//        Builder& setName(const std::string& n);
//        Builder& setType(const std::string& t);
//        Builder& setCapacity(int c);
//        Stadium build();
//    };
//
//    // Функція для зчитування даних про стадіони з файлу
//    static std::vector<Stadium> readStadiumsFromFile(const std::string& filename);
//
//    // Функція для фільтрації стадіонів за типом покриття
//    static std::vector<Stadium> filterStadiumsByType(const std::vector<Stadium>& stadiums, int type);
//
//    // Функція для виводу даних про стадіони
//    static void printStadiums(const std::vector<Stadium>& stadiums);
//};
//
//
//class Athlete {
//private:
//    std::string nameOfAthlete;
//    std::vector<std::string> kindOfSport;
//    std::string athleteCategory;
//    std::vector<std::string> trainer;
//    std::string trainerCategory;
//    std::string building;
//    std::string sportClub;
//    std::string dividingLine;
//
//public:
//    // Геттери
//    std::string getNameOfAthlete() const;
//    std::vector<std::string> getKindOfSport() const;
//    std::string getAthleteCategory() const;
//    std::vector<std::string> getTrainer() const;
//    std::string getTrainerCategory() const;
//    std::string getBuilding() const;
//    std::string getSportClub() const;
//    std::string getDividingLine() const;
//
//    // Сеттери
//    void setNameOfAthlete(const std::string& name);
//    void addKindOfSport(const std::string& sport);
//    void setAthleteCategory(const std::string& category);
//    void addTrainer(const std::string& trainerName);
//    void setTrainerCategory(const std::string& category);
//    void setBuilding(const std::string& buildingName);
//    void setSportClub(const std::string& club);
//    void setDividingLine(const std::string& line);
//
//    // Інтерфейс стратегії фільтрації
//    class AthleteFilterStrategy {
//    public:
//        virtual std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const = 0;
//        virtual ~AthleteFilterStrategy() {}
//    };
//
//    // Конкретні реалізації стратегії фільтрації за видом спорту та рівнем атлета
//    class SportCategoryFilterStrategy : public AthleteFilterStrategy {
//    private:
//        std::string searchedSport;
//        std::string searchedCategory;
//
//    public:
//        SportCategoryFilterStrategy(const std::string& sport, const std::string& category);
//
//        std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const override;
//    };
//
//    // Фільтрація спортсменів за спорткомплексом
//    class BuildingFilterStrategy : public AthleteFilterStrategy {
//    private:
//        std::string searchedBuilding;
//
//    public:
//        BuildingFilterStrategy(const std::string& building);
//
//        std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const override;
//    };
//
//    // Конкретні реалізації стратегії фільтрації за тренерами та розрядами спортсменів
//    class TrainerCategoryFilterStrategy : public AthleteFilterStrategy {
//    private:
//        std::string searchedTrainer;
//        std::string searchedCategory;
//
//    public:
//        TrainerCategoryFilterStrategy(const std::string& trainer, const std::string& category);
//
//        std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const override;
//    };
//
//    // Конкретні реалізації стратегії фільтрації спортсменів за кількома видами спорту
//    class MultipleSportsFilterStrategy : public AthleteFilterStrategy {
//    private:
//        std::string sport1;
//        std::string sport2;
//
//    public:
//        MultipleSportsFilterStrategy(const std::string& sport1, const std::string& sport2);
//
//        std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const override;
//    };
//
//    // Фільтрація спортсменів за іменем
//    class NameFilterStrategy : public AthleteFilterStrategy {
//    private:
//        std::string athleteName;
//
//    public:
//        NameFilterStrategy(const std::string& name);
//
//        std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const override;
//    };
//
//    class AthleteFilter {
//    private:
//        AthleteFilterStrategy* strategy;
//
//    public:
//        AthleteFilter(AthleteFilterStrategy* strategy);
//
//        std::vector<Athlete> filterAthletes(const std::vector<Athlete>& athletes) const;
//    };
//
//    static std::vector<Athlete> filterAthletes(const std::vector<Athlete>& athletes, const AthleteFilterStrategy& strategy);
//
//    //Функція для зчитування даних про спортсменів
//    static std::vector<Athlete> readAthletesFromFile(const std::string& filename);
//
//    //Функція для виводу інформації про спортсменів
//    static void printAthletes(const std::vector<Athlete>& athletes);
//};
//
//class Trainer : public Athlete {
//public:
//
//    class TrainerFilterStrategy {
//    public:
//        virtual std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const = 0;
//        virtual ~TrainerFilterStrategy() {}
//    };
//
//    class TrainersBySportFilterStrategy : public TrainerFilterStrategy {
//    private:
//        std::string searchedSport;
//
//    public:
//        TrainersBySportFilterStrategy(const std::string& sport)
//            : searchedSport(sport) {}
//
//        std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const override;
//
//        // Функція для друку тренерів певного виду спорту
//        void printTrainers(const std::vector<Athlete>& trainers) const;
//    };
//
//    class TrainersByAthletesNameFilterStrategy : public TrainerFilterStrategy {
//    private:
//        std::string searchedName;
//
//    public:
//        TrainersByAthletesNameFilterStrategy(const std::string& name)
//            : searchedName(name) {}
//
//        std::vector<Athlete> filter(const std::vector<Athlete>& athletes) const override;
//
//        // Функція для друку тренерів певного спортсмена
//        void printTrainers(const std::vector<Athlete>& athletes) const;
//    };
//};
//
//
//class Competition {
//private:
//    std::string nameOfTheCompetition;
//    std::string sport;
//    std::string organizer;
//    std::string date;
//    std::string buildins;
//    std::string firstPlace;
//    std::string secondPlace;
//    std::string thirdPlace;
//    std::string dividingLine;
//
//public:
//    Competition() {}
//
//    Competition(const std::string& nameOfTheCompetition, const std::string& sport, const std::string& organizer, const std::string& date, const std::string& buildins, const std::string& firstPlace, const std::string& secondPlace, const std::string& thirdPlace, const std::string& dividingLine)
//        : nameOfTheCompetition(nameOfTheCompetition), sport(sport), organizer(organizer), date(date), buildins(buildins), firstPlace(firstPlace), secondPlace(secondPlace), thirdPlace(thirdPlace), dividingLine(dividingLine) {}
//
//    // Геттери
//    std::string getNameOfTheCompetition() const { return nameOfTheCompetition; }
//    std::string getSport() const { return sport; }
//    std::string getOrganizer() const { return organizer; }
//    std::string getDate() const { return date; }
//    std::string getBuildins() const { return buildins; }
//    std::string getFirstPlace() const { return firstPlace; }
//    std::string getSecondPlace() const { return secondPlace; }
//    std::string getThirdPlace() const { return thirdPlace; }
//    std::string getDividingLine() const { return dividingLine; }
//
//    // Сеттери
//    void setNameOfTheCompetition(const std::string& name) { nameOfTheCompetition = name; }
//    void setSport(const std::string& sport) { this->sport = sport; }
//    void setOrganizer(const std::string& organizer) { this->organizer = organizer; }
//    void setDate(const std::string& date) { this->date = date; }
//    void setBuildins(const std::string& buildins) { this->buildins = buildins; }
//    void setFirstPlace(const std::string& firstPlace) { this->firstPlace = firstPlace; }
//    void setSecondPlace(const std::string& secondPlace) { this->secondPlace = secondPlace; }
//    void setThirdPlace(const std::string& thirdPlace) { this->thirdPlace = thirdPlace; }
//    void setDividingLine(const std::string& line) { dividingLine = line; }
//
//    // Зчитування даних про змагання з файлу
//    static std::vector<Competition> readCompetitionsFromFile(const std::string& filename);
//
//    // Вивід інформації про змагання
//    static void printCompetitions(const std::vector<Competition>& competitions);
//
//    // Вивід інформації про переможців змагань
//    static void printCompetitionsWins(const std::vector<Competition>& competitions);
//
//    // Інтерфейс стратегії фільтрації
//    class CompetitionFilterStrategy {
//    public:
//        virtual std::vector<Competition> filter(const std::vector<Competition>& competitions) const = 0;
//        virtual ~CompetitionFilterStrategy() {}
//    };
//
//    // Фільтрація змагань за клубами та кількістю учасників
//    class ClubsAndCompetitorsFilterStrategy : public CompetitionFilterStrategy {
//    private:
//        std::map<std::string, std::set<std::string>> clubToCompetitors;
//
//    public:
//        ClubsAndCompetitorsFilterStrategy(const std::vector<Athlete>& athletes);
//
//        void printClubWinnersCount(const std::vector<Competition>& competitions) const;
//    };
//
//    // Фільтрація змагань за участю спортсменів
//    class AthletesParticipatingInCompetitionsFilterStrategy : public CompetitionFilterStrategy {
//    private:
//        std::set<std::string> participatingAthletes;
//
//    public:
//        AthletesParticipatingInCompetitionsFilterStrategy(const std::vector<Athlete>& athletes);
//
//        std::vector<Athlete> filter(const std::vector<Competition>& competitions, const std::vector<Athlete>& athletes) const;
//    };
//
//    // Фільтрація змагань за датою
//    class DateFilterStrategy : public CompetitionFilterStrategy {
//    private:
//        int days;
//
//    public:
//        DateFilterStrategy(int days) : days(days) {}
//
//        std::vector<Competition> filter(const std::vector<Competition>& competitions) const override;
//    };
//
//    // Фільтрація змагань за організатором
//    class OrganizerFilterStrategy : public CompetitionFilterStrategy {
//    private:
//        std::string organizer;
//
//    public:
//        OrganizerFilterStrategy(const std::string& organizer) : organizer(organizer) {}
//
//        std::vector<Competition> filter(const std::vector<Competition>& competitions) const override;
//    };
//
//    // Фільтрація змагань за будівлею та видом спорту
//    class BuildingAndSportFilterStrategy : public CompetitionFilterStrategy {
//    private:
//        std::string building;
//        std::string sport;
//
//    public:
//        BuildingAndSportFilterStrategy(const std::string& building, const std::string& sport)
//            : building(building), sport(sport) {}
//
//        std::vector<Competition> filter(const std::vector<Competition>& competitions) const override;
//    };
//
//    class WinnerFilterStrategy {
//    public:
//        virtual std::vector<Competition> filterWinners(const std::vector<Competition>& competitions) const = 0;
//        virtual ~WinnerFilterStrategy() {}
//    };
//
//    // Конкретная стратегия для фильтрации победителей по названию соревнования
//    class CompetitionNameWinnerFilterStrategy : public WinnerFilterStrategy {
//    private:
//        std::string competitionName;
//
//    public:
//        CompetitionNameWinnerFilterStrategy(const std::string& name) : competitionName(name) {}
//
//        std::vector<Competition> filterWinners(const std::vector<Competition>& competitions) const override;
//    };
//
//    // Функция, использующая стратегию для фильтрации победителей
//    static std::vector<Competition> filterWinnersByCompetitions(const std::vector<Competition>& competitions, WinnerFilterStrategy& filterStrategy);
//};

#endif