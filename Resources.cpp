#include "Library.h"

string issueName(int i) {
    string name;

    if (i == 0) {
        name = "Diseases";
    } else if (i == 1) {
        name = "Deforestation";
    } else if (i == 2) {
        name = "Climate change";
    } else if (i == 3) {
        name = "Water contamination";
    } else {
        name = "Poverty";
    }

    return name;
}

Issue::Issue(string name, double significance, double approach) : name(name), significance(significance), approach(approach) {}

string Issue::getName() const { return name; }

double Issue::getSignificance() const { return significance; }

double Issue::getApproach() const { return approach; }

void Issue::updateSignificance(double addValue) { this->significance += addValue; }

void Issue::updateApproach(double addValue) { this->approach += addValue; }

PartyMember::PartyMember(double popularity) : popularity(popularity) {};

double PartyMember::getPopularity() const { return popularity; }

void PartyMember::setPopularity(double popularity) { this->popularity = popularity; }

void PartyMember::addStance(Issue stance) { this->stances.push_back(stance); }

vector<Issue> PartyMember::getStances() const { return stances; }

Issue PartyMember::getStance(int index) const { return stances[index]; }

void PartyMember::updateStanceSignificance(double addValue, int index) { this->stances[index].updateSignificance(addValue); }

void PartyMember::updateStanceApproach(double addValue, int index) { this->stances[index].updateApproach(addValue); }

Leader::Leader(double popularity, double reputation) : PartyMember(popularity), reputation(reputation) {};

double Leader::getReputation() const { return reputation; }

void Leader::setReputation(double reputation) { this->reputation = reputation; }

Candidate::Candidate(double popularity, double skill) : PartyMember(popularity), skill(skill) { votingScore = 0; };

double Candidate::getSkill() const { return skill; }

void Candidate::setSkill(double skill) { this->skill = skill; }

double Candidate::getVotingScore() const { return votingScore; }

void Candidate::updateVotingScore(double addValue) { this->votingScore += addValue; }

CampaignTeam::CampaignTeam(double efficiency) : efficiency(efficiency) {};

double CampaignTeam::getEfficiency() const { return efficiency; }

void CampaignTeam::updateEfficiency(double addValue) { this->efficiency += addValue; }

PoliticalParty::PoliticalParty(string name, Leader leader, vector<Candidate> candidates, CampaignTeam campaignTeam) : name(name), leader(leader), candidates(candidates), campaignTeam(campaignTeam) {
    divisionWon = 0;

    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < 5; i++) { // There are 5 issues
        uniform_real_distribution<> disUpper(50.0, 100.0); // Upper bound
        uniform_real_distribution<> disLower(0.0, 50.0);  // Lower bound

        double significanceRangeUpper = disUpper(gen); // Upper bound for significance
        double approachRangeUpper = disUpper(gen); // Upper bound for approach

        double significanceRangeLower = disLower(gen); // Lower bound for significance
        double approachRangeLower = disLower(gen); // Lower bound for approach

        uniform_real_distribution<> disSignificance(significanceRangeLower, significanceRangeUpper); // Significance range
        uniform_real_distribution<> disApproach(approachRangeLower, approachRangeUpper); // Approach range

        double significance = disSignificance(gen); // Generate significance between the significance range
        double approach = disApproach(gen); // Generate the approach between the approach range

        this->leader.addStance(Issue(issueName(i), significance, approach)); // Assign stance to leader

        for (Candidate& candidate : this->candidates) {
            candidate.addStance(Issue(issueName(i), significance, approach)); // Assign stance to each candidate
        }
    }
}

string PoliticalParty::getName() const { return name; }

int PoliticalParty::getDivisionWon() const { return divisionWon; }

void PoliticalParty::updateDivisionWon(int addValue) { this->divisionWon += addValue; }

ElectoralDivision::ElectoralDivision(int number) : number(number) {
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < 5; i++) { // There are 5 issues
        uniform_real_distribution<> dis(0.0, 100.0);
        double significance = dis(gen); // Generate significance
        double approach = dis(gen); // Generate the approach

        stances.push_back(Issue(issueName(i), significance, approach)); // Assign stance to electoral division
    }
}

int ElectoralDivision::getNumber() const { return number; }