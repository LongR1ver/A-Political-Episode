#include "Library.h"

void simulateElection(int n, int m) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(10.0, 60.0);

    vector<PoliticalParty*> politicalParties;
    vector<ElectoralDivision> electoralDivisions;
    
    vector<Candidate> candidates1;
    vector<Candidate> candidates2;
    vector<Candidate> candidates3;

    // Create candidate object for each division
    for (int i = 0; i < n; i++) {
        ElectoralDivision electoralDivision(i + 1);

        Candidate candidate1(dis(gen), dis(gen));
        Candidate candidate2(dis(gen), dis(gen));
        Candidate candidate3(dis(gen), dis(gen));

        electoralDivisions.push_back(electoralDivision);

        candidates1.push_back(candidate1);
        candidates2.push_back(candidate2);
        candidates3.push_back(candidate3);
    }

    Leader leader1(dis(gen), dis(gen));
    CampaignTeam campaignTeam1(dis(gen));
    PoliticalParty politicalParty1("Communist Party", leader1, candidates1, campaignTeam1);

    Leader leader2(dis(gen), dis(gen));
    CampaignTeam campaignTeam2(dis(gen));
    PoliticalParty politicalParty2("Democratic Party", leader2, candidates2, campaignTeam2);

    Leader leader3(dis(gen), dis(gen));
    CampaignTeam campaignTeam3(dis(gen));
    PoliticalParty politicalParty3("Republican Party", leader3, candidates3, campaignTeam3);

    politicalParties.push_back(&politicalParty1);
    politicalParties.push_back(&politicalParty2);
    politicalParties.push_back(&politicalParty3);

    // Display initial stats
    for (const PoliticalParty* party : politicalParties) {
        int i = 1;
        int j = 1;
        cout << "Political party name: " << party->getName() << endl;
        cout << "   Leader: popularity: " << party->leader.getPopularity() << ", reputation: " << party->leader.getReputation() << endl;
        cout << "   Candidate:" << endl;
        for (const Candidate& candidate : party->candidates) {
            cout << "       Candidate number: " << i << ", Popularity: " << candidate.getPopularity() << ", skill: " << candidate.getSkill() << endl;
            i++;
        }
        cout << "   Campaign team: efficiency: " << party->campaignTeam.getEfficiency() << endl;
        cout << "   Stances:" << endl;
        for (const Candidate& candidate : party->candidates) {
            cout << "       Candidate number " << j << ":" << endl;
            for (const Issue& issue : candidate.getStances()) {
                cout << "           Issue: " << issue.getName() << ", Significance: " << issue.getSignificance() << ", Approach: " << issue.getApproach() << endl;
            }
            j++;
            cout << endl;
        }
    }

    for (const ElectoralDivision& division : electoralDivisions) {
        cout << "Division number: " << division.getNumber() << endl;
        for (const Issue& issue : division.stances) {
            cout << "   Issue: " << issue.getName() << ", Significance: " << issue.getSignificance() << ", Approach: " << issue.getApproach() << endl;
        }
        cout << endl;
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "Event days" << endl << endl;

    // Simulate for each day
    for (int i = 0; i < m; i++) {
        // For each division in a day
        for (ElectoralDivision& division : electoralDivisions) {
            uniform_int_distribution<> disChance(0, 1);

            int Chance = disChance(gen);

            // If Chance = 1, 1 event happens, if Chance = 0, no event happens
            if (Chance == 1) {
                uniform_int_distribution<> disEvent(1, 4);

                int eventChance = disEvent(gen);

                cout << "Day " << i + 1 << ", division " << division.getNumber() << ":" << endl;

                // eventChance = 1, debate happens
                // eventChance = 2, candidate-related event happens
                // eventChance = 3, leader-related event happens
                // eventChance = 4, issue-related event happens

                // smallEventChance for happening 1 in 2 types of -related events

                if (eventChance == 1) {
                    DebateEvent debate("Debate");
                    cout << "   This is the " << debate.getName() << " event!" << endl;

                    debate.event(politicalParty1, politicalParty2, politicalParty3, division);

                    cout << endl;
                } else if (eventChance == 2) {
                    int smallEventChance = disChance(gen);
                    cout << "   This is the candidate-related event!" << endl;

                    if (smallEventChance == 0) {
                        PublicSpeakingEvent publicSpeaking("Public Speaking");

                        cout << "   This is the " << publicSpeaking.getName() << " event!" << endl;

                        publicSpeaking.event(politicalParty1, politicalParty2, politicalParty3, division);
                    } else {
                        CommunityServiceEvent communityService("Community Service");

                        cout << "   This is the " << communityService.getName() << " event!" << endl;

                        communityService.event(politicalParty1, politicalParty2, politicalParty3, division);
                    }

                    cout << endl;
                } else if (eventChance == 3) {
                    int smallEventChance = disChance(gen);
                    cout << "   This is the leader-related event!" << endl;

                    if (smallEventChance == 0) {
                        PolicyAnnouncementEvent policyAnnouncement("Policy Announcement");

                        cout << "   This is the " << policyAnnouncement.getName() << " event!" << endl;

                        policyAnnouncement.event(politicalParty1, politicalParty2, politicalParty3);
                    } else {
                        PressConferenceEvent pressConference("Press Conference");

                        cout << "   This is the " << pressConference.getName() << " event!" << endl;

                        pressConference.event(politicalParty1, politicalParty2, politicalParty3);
                    }

                    cout << endl;
                } else {
                    int smallEventChance = disChance(gen);
                    cout << "   This is the issue-related event!" << endl;

                    uniform_int_distribution<> disParty(0, 2);
                    int partyChance = disParty(gen);
                    
                    // partyChance for the radom party to take action on issue-related events happen

                    if (smallEventChance == 0) {
                        ProtestEvent protestEvent("Protest");

                        cout << "   There is a " << protestEvent.getName() << " event!" << endl;

                        if (partyChance == 0) {
                            protestEvent.event(division, politicalParty1);
                        } else if (partyChance == 1) {
                            protestEvent.event(division, politicalParty2);
                        } else {
                            protestEvent.event(division, politicalParty3);
                        }
                    } else {
                        NewsReportEvent newsReportEvent("News Report");

                        cout << "   There is a " << newsReportEvent.getName() << " event!" << endl;

                        if (partyChance == 0) {
                            newsReportEvent.event(division, politicalParty1);
                        } else if (partyChance == 1) {
                            newsReportEvent.event(division, politicalParty2);
                        } else {
                            newsReportEvent.event(division, politicalParty3);
                        }
                    }

                    cout << endl;
                }
            } else {
                cout << "Day " << i + 1 << ", division " << division.getNumber() << ": No event." << endl << "\n";
            }
        }

        // Display stats after each day
        for (const PoliticalParty* party : politicalParties) {
            int i = 1;
            int j = 1;
            cout << "Political party name: " << party->getName() << endl;
            cout << "   Leader: popularity: " << party->leader.getPopularity() << ", reputation: " << party->leader.getReputation() << endl;
            cout << "   Candidate:" << endl;
            for (const Candidate& candidate : party->candidates) {
                cout << "       Candidate number: " << i << ", Popularity: " << candidate.getPopularity() << ", skill: " << candidate.getSkill() << endl;
                i++;
            }
            cout << "   Campaign team: efficiency: " << party->campaignTeam.getEfficiency() << endl;
            cout << "   Stances:" << endl;
            for (const Candidate& candidate : party->candidates) {
                cout << "       Candidate number " << j << ":" << endl;
                for (const Issue& issue : candidate.getStances()) {
                    cout << "           Issue: " << issue.getName() << ", Significance: " << issue.getSignificance() << ", Approach: " << issue.getApproach() << endl;
                }
                j++;
                cout << endl;
            }
        }

        for (const ElectoralDivision& division : electoralDivisions) {
            cout << "Division number: " << division.getNumber() << endl;
            for (const Issue& issue : division.stances) {
                cout << "   Issue: " << issue.getName() << ", Significance: " << issue.getSignificance() << ", Approach: " << issue.getApproach() << endl;
            }
            cout << endl;
        }

        cout << "----------------------------------------------------------------" << endl << endl;
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "After campaign days" << endl << endl;

    // Display stats after campaign days
    for (const PoliticalParty* party : politicalParties) {
        int i = 1;
        int j = 1;
        cout << "Political party name: " << party->getName() << endl;
        cout << "   Leader: popularity: " << party->leader.getPopularity() << ", reputation: " << party->leader.getReputation() << endl;
        cout << "   Candidate:" << endl;
        for (const Candidate& candidate : party->candidates) {
            cout << "       Candidate number: " << i << ", Popularity: " << candidate.getPopularity() << ", skill: " << candidate.getSkill() << endl;
            i++;
        }
        cout << "   Campaign team: efficiency: " << party->campaignTeam.getEfficiency() << endl;
        cout << "   Stances:" << endl;
        for (const Candidate& candidate : party->candidates) {
            cout << "       Candidate number " << j << ":" << endl;
            for (const Issue& issue : candidate.getStances()) {
                cout << "           Issue: " << issue.getName() << ", Significance: " << issue.getSignificance() << ", Approach: " << issue.getApproach() << endl;
            }
            j++;
            cout << endl;
        }
    }

    for (const ElectoralDivision& division : electoralDivisions) {
        cout << "Division number: " << division.getNumber() << endl;
        for (const Issue& issue : division.stances) {
            cout << "   Issue: " << issue.getName() << ", Significance: " << issue.getSignificance() << ", Approach: " << issue.getApproach() << endl;
        }
        cout << endl;
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "Voting Results\n" << endl;

    // Compute voting score of each candidate in each division
    for (int i = 0; i < electoralDivisions.size(); i++) {
        for (PoliticalParty* party : politicalParties) {
            double euclidDistance = 0.0;
            double averageEuclidDistance;

            for (int j = 0; j < electoralDivisions[i].stances.size(); j++) {
                euclidDistance += sqrt(pow(electoralDivisions[i].stances[j].getSignificance() - party->candidates[i].getStance(j).getSignificance(), 2) + pow(electoralDivisions[i].stances[j].getApproach() - party->candidates[i].getStance(j).getApproach(), 2));
            }

            averageEuclidDistance = euclidDistance/5;

            party->candidates[i].updateVotingScore(1500/averageEuclidDistance + party->candidates[i].getPopularity()/5 + party->leader.getPopularity()/10);
        }

        cout << "Division number " << electoralDivisions[i].getNumber() << ":" << endl;

        for (const PoliticalParty* party : politicalParties) {
            cout << "   Voting score of candidate of " << party->getName() << ": ";
            cout << party->candidates[i].getVotingScore() << endl;
        }

        // Compare voting score of each candidate in each division
        if (politicalParties[0]->candidates[i].getVotingScore() > politicalParties[1]->candidates[i].getVotingScore() && politicalParties[0]->candidates[i].getVotingScore() > politicalParties[2]->candidates[i].getVotingScore()) {
            politicalParties[0]->updateDivisionWon(1);
            cout << "   Winner is " << politicalParties[0]->getName() << "!" << endl;
        } else if (politicalParties[1]->candidates[i].getVotingScore() > politicalParties[0]->candidates[i].getVotingScore() && politicalParties[1]->candidates[i].getVotingScore() > politicalParties[2]->candidates[i].getVotingScore()) {
            politicalParties[1]->updateDivisionWon(1);
            cout << "   Winner is " << politicalParties[1]->getName() << "!" << endl;
        } else {
            politicalParties[2]->updateDivisionWon(1);
            cout << "   Winner is " << politicalParties[2]->getName() << "!" << endl;
        }

        cout << endl;
    }

    // Compare number if divisions won of each party and check if it is greater than 50% of total divisions
    if (politicalParties[0]->getDivisionWon() > politicalParties[1]->getDivisionWon() && politicalParties[0]->getDivisionWon() > politicalParties[2]->getDivisionWon() && politicalParties[0]->getDivisionWon() >= ceil(static_cast<double>(electoralDivisions.size())/2)) {
        cout << politicalParties[1]->getName() << " won in " << politicalParties[1]->getDivisionWon() << " divisions." << endl;
        cout << politicalParties[2]->getName() << " won in " << politicalParties[2]->getDivisionWon() << " divisions." << endl << endl;
        cout << politicalParties[0]->getName() << " has won the country election with " << politicalParties[0]->getDivisionWon() << " divisions!" << endl;
        cout << "They leader will become our new president!" << endl;
    } else if (politicalParties[1]->getDivisionWon() > politicalParties[0]->getDivisionWon() && politicalParties[1]->getDivisionWon() > politicalParties[2]->getDivisionWon() && politicalParties[1]->getDivisionWon() >= ceil(static_cast<double>(electoralDivisions.size())/2)) {
        cout << politicalParties[0]->getName() << " won in " << politicalParties[0]->getDivisionWon() << " divisions." << endl;
        cout << politicalParties[2]->getName() << " won in " << politicalParties[2]->getDivisionWon() << " divisions." << endl << endl;
        cout << politicalParties[1]->getName() << " has won the country election with " << politicalParties[1]->getDivisionWon() << " divisions!" << endl;
        cout << "They leader will become our new president!" << endl;
    } else if (politicalParties[2]->getDivisionWon() > politicalParties[0]->getDivisionWon() && politicalParties[2]->getDivisionWon() > politicalParties[1]->getDivisionWon() && politicalParties[2]->getDivisionWon() >= ceil(static_cast<double>(electoralDivisions.size())/2)) {
        cout << politicalParties[0]->getName() << " won in " << politicalParties[0]->getDivisionWon() << " divisions." << endl;
        cout << politicalParties[1]->getName() << " won in " << politicalParties[1]->getDivisionWon() << " divisions." << endl << endl;
        cout << politicalParties[2]->getName() << " has won the country election with " << politicalParties[2]->getDivisionWon() << " divisions!" << endl;
        cout << "They leader will become our new president!" << endl;
    } else {
        cout << politicalParties[0]->getName() << " won in " << politicalParties[0]->getDivisionWon() << " divisions." << endl;
        cout << politicalParties[1]->getName() << " won in " << politicalParties[1]->getDivisionWon() << " divisions." << endl;
        cout << politicalParties[2]->getName() << " won in " << politicalParties[2]->getDivisionWon() << " divisions." << endl << endl;
        cout << "No party win." << endl;
        cout << "There will be a hung parliament." << endl;
    }
}