#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
using namespace std;

// Return name of the issue
string issueName(int i);

class Issue {
    private:
        string name;
        double significance, approach;

    public:
        Issue(string name, double significance, double approach);
        string getName() const;
        double getSignificance() const;
        double getApproach() const;
        void updateSignificance(double addValue);
        void updateApproach(double addValue);
};

// Base class for Leader and Candidate
class PartyMember {
    private:
        double popularity;
        vector<Issue> stances;

    public:
        PartyMember(double popularity);
        double getPopularity() const;
        void setPopularity(double popularity);
        vector<Issue> getStances() const;
        Issue getStance(int index) const;
        void addStance(Issue stance);
        void updateStanceSignificance(double addValue, int index);
        void updateStanceApproach(double addValue, int index);
};

// Inheritances from PartyMember
class Leader : public PartyMember {
    private:
        double reputation;

    public:
        Leader(double popularity, double reputation);
        double getReputation() const;
        void setReputation(double reputation);
};

// Inheritances from PartyMember
class Candidate : public PartyMember {
    private:
        double skill;
        double votingScore;

    public:
        Candidate(double popularity, double skill);
        double getSkill() const;
        void setSkill(double skill);
        double getVotingScore() const;
        void updateVotingScore(double addValue);
};

class CampaignTeam {
    private:
        double efficiency;

    public:
        CampaignTeam(double efficiency);
        double getEfficiency() const;
        void updateEfficiency(double addValue);
};

class PoliticalParty {
    private:
        string name;
        int divisionWon;

    public:
        Leader leader;
        vector<Candidate> candidates;
        CampaignTeam campaignTeam;

        PoliticalParty(string name, Leader leader, vector<Candidate> candidates, CampaignTeam campaignTeam);
        string getName() const;
        int getDivisionWon() const;
        void updateDivisionWon(int addValue);
};

class ElectoralDivision {
    private:
        int number;

    public:
        vector<Issue> stances;

        ElectoralDivision(int number);
        int getNumber() const;
};

class Event {
    private:
        string name;

    public:
        Event(string name);
        string getName() const;
};

class DebateEvent : public Event {
    public:
        DebateEvent(string name);
        void event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3, ElectoralDivision& division);
};

// Candidate-related event
class PublicSpeakingEvent : public Event {
    public:
        PublicSpeakingEvent(string name);
        void event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3, ElectoralDivision& division);
};

// Candidate-related event
class CommunityServiceEvent : public Event {
    public:
        CommunityServiceEvent(string name);
        void event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3, ElectoralDivision& division);
};

// Leader-related event
class PolicyAnnouncementEvent : public Event {
    public:
        PolicyAnnouncementEvent(string name);
        void event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3);
};

// Leader-related event
class PressConferenceEvent : public Event {
    public:
        PressConferenceEvent(string name);
        void event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3);
};

// Issue-related event
class ProtestEvent : public Event {
    public:
        ProtestEvent(string name);
        void event(ElectoralDivision& division, PoliticalParty& party);
};

// Issue-related event
class NewsReportEvent : public Event {
    public:
        NewsReportEvent(string name);
        void event(ElectoralDivision& division, PoliticalParty& party);
};

// Simulate the election
void simulateElection(int n, int m); // n for number of divisions, m for number of days

#endif