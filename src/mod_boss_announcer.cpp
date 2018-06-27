//by SymbolixDEV
//Reworked by Talamortis
#include "ScriptMgr.h"
#include "Config.h"
#include <Player.h>
#include "Group.h"
#include "GroupMgr.h"
#include "InstanceScript.h"

class Boss_Announcer : public PlayerScript
{
public:
	Boss_Announcer() : PlayerScript("Boss_Announcer") {}
	
    void OnLogin(Player *player)
    {
        if (sConfigMgr->GetBoolDefault("Boss.Announcer.Enable", true))
        {
            if (sConfigMgr->GetBoolDefault("Boss.Announcer.Announce", true))
            {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00BossAnnouncer |rmodule.");
            }
        }
    }

    void OnCreatureKill(Player* player, Creature* boss)
    {
        if (sConfigMgr->GetBoolDefault("Boss.Announcer.Enable", true))
        {
            if (boss->GetMap()->IsRaid() && boss->getLevel() > 80 && boss->IsDungeonBoss())
            {
                //lets get the info we want
                Map* map = player->GetMap();
                std::string p_name = player->GetGroup()->GetLeaderName();
                std::string g_name;
                std::string boss_name = boss->GetName();
                std::string IsHeroicMode;
                std::string IsNormal;
                std::string tag_colour = "7bbef7";
                std::string plr_colour = "7bbef7";
                std::string guild_colour = "00ff00";
                std::string boss_colour = "ff0000";
                std:string alive_text = "00ff00";
                uint32 raid_id = player->GetMap()->GetInstanceId();
                uint32 Alive_players = 0;
                Map::PlayerList const & playerlist = map->GetPlayers();

                if (player->GetMap()->Is25ManRaid())
                    IsNormal = "25";
                else
                    IsNormal = "10";

                if (player->GetMap()->IsHeroic())
                    IsHeroicMode = "|cffff0000Heroic|r";
                else
                    IsHeroicMode = "|cff00ff00Normal|r";

                std::ostringstream stream;

                for (Map::PlayerList::const_iterator itr = playerlist.begin(); itr != playerlist.end(); ++itr)
                {
                    if (!itr->GetSource())
                        continue;

                    if (itr->GetSource()->IsAlive())
                        Alive_players++;

                    if (!player->GetGuild())
                    {
                        if (itr->GetSource()->GetGroup()->IsLeader(itr->GetSource()->GetGUID()))
                            g_name = itr->GetSource()->GetGuildName();
                    }
                    else
                        g_name = player->GetGuildName();
                }

                stream << "|CFF" << tag_colour << "|r|cff" << plr_colour << " " << p_name << "|r's Guild |cff" << guild_colour << "" << g_name << "|r has slain |CFF" << boss_colour << "[" << boss_name << "]|r with remaining |cff" << alive_text << "" << Alive_players << " /" << IsNormal << "|r players alive on " << IsHeroicMode << " mode";
                sWorld->SendServerMessage(SERVER_MSG_STRING, stream.str().c_str());


            }
        }
    }
};

class Boss_Announcer_World : public WorldScript
{
public:
	Boss_Announcer_World() : WorldScript("Boss_Announcer_World") { }

	void OnBeforeConfigLoad(bool reload) override
	{
		if (!reload) {
			std::string conf_path = _CONF_DIR;
			std::string cfg_file = conf_path + "/mod_boss_announcer.conf";
#ifdef WIN32
			cfg_file = "mod_boss_announcer.conf";
#endif
			std::string cfg_def_file = cfg_file + ".dist";
			sConfigMgr->LoadMore(cfg_def_file.c_str());

			sConfigMgr->LoadMore(cfg_file.c_str());
		}
	}
};

void AddBoss_AnnouncerScripts()
{
	new Boss_Announcer_World;
	new Boss_Announcer;
}