#ifndef GAME_FEATURE_H
#define GAME_FEATURE_H

#include <string>
#include <vector>

class TeamProfile;
class PlayerProfile;
class CoachProfile;
class GameSession;
class HighlightClip;
class MVPHighlightReel;
class ScoutingReport;

class Game{
public:
    Game(const std::string& id, 
        const std::string& title,
        const std::string& version);
    void startGame();
    void loadUser(const std::string& userId);
    void saveData();

    std::string getGameId() const;
    std::string getTitle() const;
    std::string getVeresion() const;

private:
    std::string gameId;
    std::string title;
    std::string version;
};

class UserAccount{
public:
    UserAccount(const std::string& id, 
        const std::string& name);

    void viewProfile() const;
    void addFriend(UserAccount* user);
    void removeFriend(const std::string& userId);

    void addTeam(TeamProfile* team);
    void addSavedReel(MVPHighlightReel* reel);

    std::string getUserId() const;
    std::string getGamertag() const;

private:
    std::string userId;
    std::string gamertag;
    std::vector<UserAccount*> friends;
    std::vector<TeamProfile*> ownedTeams;
    std::vector<MVPHighlightReel*> savedReels;
};

class Data{
public:
    Data(const std::string& id);

    void loadSessions();
    void storeReel(MVPHighlightReel* reel);
    void loadReports();

private:
    std::string dataId;
    std::vector<GameSession*> sessions;
    std::vector<MVPHighlightReel*> reels;
    std::vector<ScoutingReport*> reports;
};

class TeamProfile {
public:
    TeamProfile(const std::string& id, const std::string& name);

    void addPlayer(PlayerProfile* player);
    void assignCoach(CoachProfile* coach);
    std::vector<PlayerProfile*> getRoster() const;
    
    std::string getTeamId() const;
    std::string getTeamName() const;
    CoachProfile* getCoach() const;

private:
    std::string teamId;
    std::string teamName;
    CoachProfile* coach;
    std::vector<PlayerProfile*> roster;
    std::vector<GameSession*> gameHistory;
};

class PlayerProfile {
public:
    PlayerProfile(const std::string& id, 
        const std::string& name,
        const std::string& pos);
    
    void addMVPReel(MVPHighlightReel* reel);
    std::vector<MVPHighlightReel*> 
    getRecentReels(std::size_t limit) const;
    void getStats() const;

    std::string getPlayerId() const;
    std::string getPlayerName() const;
    std::string getPosition() const;

private:
    std::string playerId;
    std::string playerName;
    std::string position;
    TeamProfile* team;
    std::vector<MVPHighlightReel*> mvpReels;
};

class CoachProfile {
public:
    CoachProfile(const std::string& id, 
        const std::string& name,
        const std::string& role);
    
    void assignToTeam(TeamProfile* team);
    void addReel(MVPHighlightReel* reel);
    void viewCareerRecord() const;
    void getCoachingStyle() const;

    std::string getCoachId() const;
    std::string getCoachName() const;
    std::string getCoachRole() const;

private:
    std::string coachId;
    std::string coachName;
    std::string coachRole;
    TeamProfile* team;
    int wins;
    int losses;
    std::string coachStyle;
    std::vector<MVPHighlightReel*> savedReels;
};

class GameSession {
public:
    GameSession(const std::string& id, 
        const std::string& mode);

    void setTeams(TeamProfile* away);
    void recordClip(HighlightClip* clip);
    PlayerProfile* calculateMVP() const;
    MVPHighlightReel* generateMVPReel();

    std::string getSessionId() const;
    std::string getMode() const;

private:
    std::string gameSessionId;
    std::string mode;
    TeamProfile* homeTeam;
    TeamProfile* awayTeam;
    std::vector<HighlightClip*> highlightClips;
    PlayerProfile* mvpPlayer;
    MVPHighlightReel* mvpReel;
};

class HighlightClip{
public:
    HighlightClip(const std::string& id,
                const std::string& type,
                float timeStamp);

    void playClip() const;
    std::string getSummary() const;

    std::string getClipId() const;
    std::string getPlayType() const;
    float getTimeStamp() const;

private:
    std::string clipId;
    std::string playType;
    float timestamp;
    std::vector<PlayerProfile*> involvedPlayers;
};

class MVPHighlightReel{
public:
    MVPHighlightReel(const std::string& id,
                    bool rituals);
    
    void addClip(HighlightClip* clip);
    void removeClip(const std::string& clipId);
    void playReel() const;
    void getReelStats() const;

    std::string getReelId() const;
    bool hasRituals() const;

private:
    std::string rand;
    bool includesRituals;
    PlayerProfile* player;
    CoachProfile* coach;
    GameSession* game;
    std::vector<HighlightClip*> clips;
};

class ScoutingReport{
public:
    ScoutingReport(const std::string& id, 
                TeamProfile* targetTeam);
    
    void addReel(MVPHighlightReel* reel);
    void generateSummary();
    void updateGamePlan();

    std::string getReportId() const;
    TeamProfile* getTargetTeam() const;

private:
    std::string reportId;
    TeamProfile* targetTeam;
    CoachProfile* targetCoach;
    std::vector<PlayerProfile*> targetKeyPlayers;
    std::vector<MVPHighlightReel*> analyzedReels;
    std::vector<std::string> strengths;
    std::vector<std::string> weaknesses;
    std::string recommendedGamePlan;    
};

#endif