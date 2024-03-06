#include "Library.h"

Event::Event(string name) : name(name) {}

string Event::getName() const { return name; }

DebateEvent::DebateEvent(string name) : Event(name) {}

PublicSpeakingEvent::PublicSpeakingEvent(string name) : Event(name) {}

CommunityServiceEvent::CommunityServiceEvent(string name) : Event(name) {}

PolicyAnnouncementEvent::PolicyAnnouncementEvent(string name) : Event(name) {}

PressConferenceEvent::PressConferenceEvent(string name) : Event(name) {}

ProtestEvent::ProtestEvent(string name) : Event(name) {}

NewsReportEvent::NewsReportEvent(string name) : Event(name) {}

void DebateEvent::event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3, ElectoralDivision& division) {
    random_device rd;
    mt19937 gen(rd());

    // Points of each party to choose the winner
    double party1Points = politicalParty1.candidates[division.getNumber() - 1].getSkill() * 2 + politicalParty1.campaignTeam.getEfficiency();
    double party2Points = politicalParty2.candidates[division.getNumber() - 1].getSkill() * 2 + politicalParty2.campaignTeam.getEfficiency();
    double party3Points = politicalParty3.candidates[division.getNumber() - 1].getSkill() * 2 + politicalParty3.campaignTeam.getEfficiency();

    uniform_real_distribution<> dis(0.0, party1Points + party2Points + party3Points);

    // Generate a random number between 0 and the sum of the 3 parties's points
    // 0 ---------- <party 1 win> ---------- party1Points ---------- <party 2 win> ---------- party1Points + party2Points ---------- <party 3 win> ---------- sum of points (party1Points + party2Points + party3Points)
    // Who win will increase their popularity by an amount of (current skill) * 0.15 + (current campaign team efficiency) * 0.1
    // Their skill also increases by (current skill) * 0.2
    // Their campaign team efficiency increases by (current efficiency) * 0.15

    double winnerChance = dis(gen);

    double popularityIncreased = 0.0;
    double skillIncrease = 0.0;
    double efficiencyIncrease = 0.0;

    if (winnerChance <= party1Points) {
        popularityIncreased = politicalParty1.candidates[division.getNumber() - 1].getSkill() * 0.15 + politicalParty1.campaignTeam.getEfficiency() * 0.1;
        skillIncrease = politicalParty1.candidates[division.getNumber() - 1].getSkill() * 0.2;
        efficiencyIncrease = politicalParty1.campaignTeam.getEfficiency() * 0.15;

        politicalParty1.candidates[division.getNumber() - 1].setPopularity(politicalParty1.candidates[division.getNumber() - 1].getPopularity() + popularityIncreased);
        politicalParty1.candidates[division.getNumber() - 1].setSkill(politicalParty1.candidates[division.getNumber() - 1].getSkill() + skillIncrease);
        politicalParty1.campaignTeam.updateEfficiency(efficiencyIncrease);

        cout << "   Candidate of " << politicalParty1.getName() << " is the winner of the debate!" << endl;
        cout << "   His popularity has increased by " << popularityIncreased << endl;
        cout << "   His skill has increased by " << skillIncrease << endl;
        cout << "   His campaign team efficiency has increased by " << efficiencyIncrease << endl;
    } else if (winnerChance <= party1Points + party2Points) {
        popularityIncreased = politicalParty2.candidates[division.getNumber() - 1].getSkill() * 0.15 + politicalParty2.campaignTeam.getEfficiency() * 0.1;
        skillIncrease = politicalParty2.candidates[division.getNumber() - 1].getSkill() * 0.2;
        efficiencyIncrease = politicalParty2.campaignTeam.getEfficiency() * 0.15;

        politicalParty2.candidates[division.getNumber() - 1].setPopularity(politicalParty2.candidates[division.getNumber() - 1].getPopularity() + popularityIncreased);
        politicalParty2.candidates[division.getNumber() - 1].setSkill(politicalParty2.candidates[division.getNumber() - 1].getSkill() + skillIncrease);
        politicalParty2.campaignTeam.updateEfficiency(efficiencyIncrease);

        cout << "   Candidate of " << politicalParty2.getName() << " is the winner of the debate!" << endl;
        cout << "   His popularity has increased by " << popularityIncreased << endl;
        cout << "   His skill has increased by " << skillIncrease << endl;
        cout << "   His campaign team efficiency has increased by " << efficiencyIncrease << endl;
    } else {
        popularityIncreased = politicalParty3.candidates[division.getNumber() - 1].getSkill() * 0.15 + politicalParty3.campaignTeam.getEfficiency() * 0.1;
        skillIncrease = politicalParty3.candidates[division.getNumber() - 1].getSkill() * 0.2;
        efficiencyIncrease = politicalParty3.campaignTeam.getEfficiency() * 0.15;

        politicalParty3.candidates[division.getNumber() - 1].setPopularity(politicalParty3.candidates[division.getNumber() - 1].getPopularity() + popularityIncreased);
        politicalParty3.candidates[division.getNumber() - 1].setSkill(politicalParty3.candidates[division.getNumber() - 1].getSkill() + skillIncrease);
        politicalParty3.campaignTeam.updateEfficiency(efficiencyIncrease);

        cout << "   Candidate of " << politicalParty3.getName() << " is the winner of the debate! Their popularity has increased!" << endl;
        cout << "   His popularity has increased by " << popularityIncreased << endl;
        cout << "   His skill has increased by " << skillIncrease << endl;
        cout << "   His campaign team efficiency has increased by " << efficiencyIncrease << endl;
    }
}

// Candidate-related event
void PublicSpeakingEvent::event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3, ElectoralDivision& division) {
    random_device rd;
    mt19937 gen(rd());

    vector<PoliticalParty*> parties = {&politicalParty1, &politicalParty2, &politicalParty3};

    // Generate a random number between 0 and each candidate skill
    // If the random number is bigger than 40% of that candidate skill, he/she will increase popularity by (current skill) * 0.2
    // Their skill will be increased by (current skill) * 0.25
    // Else, he/she will decrease popularity by (current popularity) * 0.3
    // Their skill will be decrease by (current skill) * 0.375

    for (int i = 0; i < parties.size(); i++) {
        uniform_real_distribution<> dis(0.0, parties[i]->candidates[division.getNumber() - 1].getSkill());

        double speakQuality = dis(gen);

        double popularityChange = 0.0;
        double skillChange = 0.0;

        if (speakQuality > parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.4) {
            popularityChange = parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.2;
            skillChange = parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.25;

            parties[i]->candidates[division.getNumber() - 1].setPopularity(parties[i]->candidates[division.getNumber() - 1].getPopularity() + popularityChange);
            parties[i]->candidates[division.getNumber() - 1].setSkill(parties[i]->candidates[division.getNumber() - 1].getSkill() + skillChange);

            cout << "   Candidate of " << parties[i]->getName() << " has a gorgeous speech!" << endl;
            cout << "   His popularity has increased by " << popularityChange << endl;
            cout << "   His skill has increased by " << skillChange << endl;
        } else {
            popularityChange = parties[i]->candidates[division.getNumber() -1].getSkill() * 0.3;
            skillChange = parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.375;

            parties[i]->candidates[division.getNumber() - 1].setPopularity(parties[i]->candidates[division.getNumber() - 1].getPopularity() - popularityChange);
            parties[i]->candidates[division.getNumber() - 1].setSkill(parties[i]->candidates[division.getNumber() - 1].getSkill() - skillChange);

            cout << "   Candidate of " << parties[i]->getName() << " has a terrible speech!" << endl;
            cout << "   His popularity has decreased by " << popularityChange << endl;
            cout << "   His skill has decreased by " << skillChange << endl;
        }
    }
}

// Candidate-related event
void CommunityServiceEvent::event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3, ElectoralDivision& division) {
    random_device rd;
    mt19937 gen(rd());

    vector<PoliticalParty*> parties = {&politicalParty1, &politicalParty2, &politicalParty3};

    // Generate a random number between 0 and each candidate skill
    // If that number is greater than (their skill) * 0.66, the candidate popularity and skill will increase by (current skill) * 0.25 and (current skill) * 0.2, respectively
    // Else if that number is greater than (their skill) * 0.33, the candidate popularity and skill will increase by (current skill) * 0.15 and (current skill) * 0.1, respectively
    // Else, the candidate popularity will only increase by (current skill) * 0.05 and skill will not change

    for (int i = 0; i < parties.size(); i++) {
        uniform_real_distribution<> dis(0.0, parties[i]->candidates[division.getNumber() - 1].getSkill());

        double serviceQuality = dis(gen);

        double popularityChange = 0.0;
        double skillChange = 0.0;

        if (serviceQuality > parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.66) {
            popularityChange = parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.25;
            skillChange = parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.2;

            parties[i]->candidates[division.getNumber() - 1].setPopularity(parties[i]->candidates[division.getNumber() - 1].getPopularity() + popularityChange);
            parties[i]->candidates[division.getNumber() - 1].setSkill(parties[i]->candidates[division.getNumber() - 1].getSkill() + skillChange);

            cout << "   Candidate of " << parties[i]->getName() << " has provided excellent service quality!" << endl;
            cout << "   His popularity has dramatically increased by " << popularityChange << endl;
            cout << "   His skill has dramatically increased by " << skillChange << endl;
        } else if (serviceQuality > parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.33) {
            popularityChange = parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.15;
            skillChange = parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.1;

            parties[i]->candidates[division.getNumber() - 1].setPopularity(parties[i]->candidates[division.getNumber() - 1].getPopularity() + popularityChange);
            parties[i]->candidates[division.getNumber() - 1].setSkill(parties[i]->candidates[division.getNumber() - 1].getSkill() + skillChange);

            cout << "   Candidate of " << parties[i]->getName() << " has provided good service quality! Their popularity has increased!" << endl;
            cout << "   His popularity has increased by " << popularityChange << endl;
            cout << "   His skill has increased by " << skillChange << endl;
        } else {
            popularityChange = parties[i]->candidates[division.getNumber() - 1].getSkill() * 0.05;

            parties[i]->candidates[division.getNumber() - 1].setPopularity(parties[i]->candidates[division.getNumber() - 1].getPopularity() + popularityChange);

            cout << "   Candidate of " << parties[i]->getName() << " has provided not very good service quality!" << endl;
            cout << "   His popularity has increased a little by " << popularityChange << endl;
            cout << "   His skill does not change" << endl;
        }
    }
}

// Leader-related event
void PolicyAnnouncementEvent::event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3) {
    random_device rd;
    mt19937 gen(rd());

    vector<PoliticalParty*> parties = {&politicalParty1, &politicalParty2, &politicalParty3};

    // Generate a random number between 0 and the leader reputation
    // If that number is greater than reputation 40% of the leader's reputation, their popularity and reputation will be increased by (current reputation) * 0.2 and (current reputation) * 0.25, respectively
    // Else, their popularity and reputation will be decreased by (current popularity) * 0.3 and (current popularity) * 0.375, respectively

    for (int i = 0; i < parties.size(); i++) {
        uniform_real_distribution<> dis(0.0, parties[i]->leader.getReputation());

        double policyQuality = dis(gen);

        double popularityChange = 0.0;
        double reputationChange = 0.0;

        if (policyQuality > parties[i]->leader.getReputation() * 0.4) {
            popularityChange = parties[i]->leader.getReputation() * 0.2;
            reputationChange = parties[i]->leader.getReputation() * 0.25;

            parties[i]->leader.setPopularity(parties[i]->leader.getPopularity() + popularityChange);
            parties[i]->leader.setReputation(parties[i]->leader.getReputation() + reputationChange);

            cout << "   The new policy is great! The popularity of the leader of " << parties[i]->getName() << " has increased by " << popularityChange << endl;
            cout << "   His reputation has increased by " << reputationChange << endl;
        } else {
            popularityChange = parties[i]->leader.getReputation() * 0.3;
            reputationChange = parties[i]->leader.getReputation() * 0.375;

            parties[i]->leader.setPopularity(parties[i]->leader.getPopularity() - popularityChange);
            parties[i]->leader.setReputation(parties[i]->leader.getReputation() - reputationChange);

            cout << "   The new policy is awful! The popularity of the leader of " << parties[i]->getName() << " has decreased by " << popularityChange << endl;
            cout << "   His reputation has decreased by " << reputationChange << endl;
        }
    }
}

// Leader related event
void PressConferenceEvent::event(PoliticalParty& politicalParty1, PoliticalParty& politicalParty2, PoliticalParty& politicalParty3) {
    random_device rd;
    mt19937 gen(rd());

    vector<PoliticalParty*> parties = {&politicalParty1, &politicalParty2, &politicalParty3};

    // Generate a random number between 0 and the leader reputation
    // If that number is greater than 75% of the leader reputation, their popularity and reputation will be increased by (current reputation) * 0.25 and (current reputation) * 0.3, respectively
    // Else if that number is greater than 50% of the leader reputation, their popularity and reputation will be increased by (current reputation) * 0.15 and (current reputation) * 0.1, respectively
    // Else if that number is greater than 25% of the leader reputation, their popularity and reputation will be decreased by (current reputation) * 0.15 and (current reputation) * 0.1, respectively
    // Else, their popularity and reputation will be decreased by (current reputation) * 0.25 and (current reputation) * 0.3, respectively

    for (int i = 0; i < parties.size(); i++) {
        uniform_real_distribution<> dis(0.0, parties[i]->leader.getReputation());

        double conferenceSuccess = dis(gen);

        double popularityChange = 0.0;
        double reputationChange = 0.0;

        if (conferenceSuccess > parties[i]->leader.getReputation() * 0.75) {
            popularityChange = parties[i]->leader.getReputation() * 0.25;
            reputationChange = parties[i]->leader.getReputation() * 0.3;

            parties[i]->leader.setPopularity(parties[i]->leader.getPopularity() + popularityChange);
            parties[i]->leader.setReputation(parties[i]->leader.getReputation() + reputationChange);

            cout << "   The conference is excellent! The popularity of the leader of " << parties[i]->getName() << " has dramatically increased by " << popularityChange << endl;
            cout << "   His reputation has dramatically increased by " << reputationChange << endl;
        } else if (conferenceSuccess > parties[i]->leader.getReputation() * 0.5) {
            popularityChange = parties[i]->leader.getReputation() * 0.15;
            reputationChange = parties[i]->leader.getReputation() * 0.1;

            parties[i]->leader.setPopularity(parties[i]->leader.getPopularity() + popularityChange);
            parties[i]->leader.setReputation(parties[i]->leader.getReputation() + reputationChange);

            cout << "   The conference is good! The popularity of the leader of " << parties[i]->getName() << " has increased by " << popularityChange << endl;
            cout << "   His reputation has increased by " << reputationChange << endl;
        } else if (conferenceSuccess > parties[i]->leader.getReputation() * 0.25) {
            popularityChange = parties[i]->leader.getReputation() * 0.15;
            reputationChange = parties[i]->leader.getReputation() * 0.1;

            parties[i]->leader.setPopularity(parties[i]->leader.getPopularity() - popularityChange);
            parties[i]->leader.setReputation(parties[i]->leader.getReputation() - reputationChange);

            cout << "   The conference is awful! The popularity of the leader of " << parties[i]->getName() << " has decreased by " << popularityChange << endl;
            cout << "   His reputation has decreased by " << reputationChange << endl;
        } else {
            popularityChange = parties[i]->leader.getReputation() * 0.25;
            reputationChange = parties[i]->leader.getReputation() * 0.3;

            parties[i]->leader.setPopularity(parties[i]->leader.getPopularity() - popularityChange);
            parties[i]->leader.setReputation(parties[i]->leader.getReputation() - reputationChange);

            cout << "   The conference is terrible! The popularity of the leader of " << parties[i]->getName() << " has dramatically decreased by "<< popularityChange << endl;
            cout << "   His reputation has dramatically decreased by "<< reputationChange << endl;
        }
    }
}

// Issue-related event
void ProtestEvent::event(ElectoralDivision& division, PoliticalParty& party) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disEvent(0, 4);
    uniform_real_distribution<> dis(0.0, 15.0);

    // Generate 5 random integers from 0 to 4 for the index of the stances
    // The significance of the issue having the the protest will be increased by a random number between 0 and 15
    // If the significance of the issue is greater than that of the candidate, the significance of candidate will be increased by (issueSignificance - candidateSignificance) * 0.2
    // Else, the significance of candidate will be decreased by -(issueSignificance - candidateSignificance) * 0.2

    int eventChance = disEvent(gen);
    double protestImpact = dis(gen);

    division.stances[eventChance].updateSignificance(protestImpact);

    double significanceDistance;
    significanceDistance = division.stances[eventChance].getSignificance() - party.candidates[division.getNumber() - 1].getStance(eventChance).getSignificance();

    party.candidates[division.getNumber() - 1].updateStanceSignificance(significanceDistance * 0.2, eventChance);

    cout << "   There is a protest about " << division.stances[eventChance].getName() << "! Its significance has increased by " << protestImpact << endl;

    if (division.stances[eventChance].getSignificance() > party.candidates[division.getNumber() - 1].getStance(eventChance).getSignificance()) {
        cout << "   The significance of candidate of " << party.getName() << " about this issue has increased by " << significanceDistance * 0.2 << endl;
    } else {
        cout << "   The significance of candidate of " << party.getName() << " about this issue has decreased by " << -(significanceDistance * 0.2) << endl;
    }
}

// Issue-related event
void NewsReportEvent::event(ElectoralDivision& division, PoliticalParty& party) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disEvent(0, 4);
    uniform_real_distribution<> dis(0.0, 15.0);

    // Generate 4 random integers from 0 to 4 for the index of the stances
    // The approach of the issue having the the report will be increased by a random number between 0 and 15
    // If the approach of the issue is greater than that of the candidate, the approach of candidate will be increased by (issueApproach - candidateApproach) * 0.2
    // Else, the approach of candidate will be decreased by -(issueApproach - candidateApproach) * 0.2

    int eventChance = disEvent(gen);
    double reportImpact = dis(gen);

    division.stances[eventChance].updateApproach(reportImpact);

    double approachDistance;
    approachDistance = division.stances[eventChance].getApproach() - party.candidates[division.getNumber() - 1].getStance(eventChance).getApproach();

    party.candidates[division.getNumber() - 1].updateStanceApproach(approachDistance * 0.2, eventChance);

    cout << "   There is a report about " << division.stances[eventChance].getName() << "! Its approach has increased by " << reportImpact << endl;

    if (division.stances[eventChance].getApproach() > party.candidates[division.getNumber() - 1].getStance(eventChance).getApproach()) {
        cout << "   The approach of candidate of " << party.getName() << " about this issue has increased by " << approachDistance * 0.2 << endl;
    } else {
        cout << "   The approach of candidate of " << party.getName() << " about this issue has decreased by " << -(approachDistance * 0.2) << endl;
    }
}