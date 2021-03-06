//
//  QuestController.h
//  IF
//
//  Created by ganxiaohua on 13-11-4.
//
//

#ifndef __IF__QuestController__
#define __IF__QuestController__

#define QUEST_NUM_CHANGE "questNumChange"
#define QUEST_STATE_UPDATE "questStateUpdate"
#define User_LV_REWARD_DELAY "levelUp.reward.delay"
#define QUEST_STAGE_UPDATE "quest.stage.update"
#define GETRT_REWARD_INFO "get.rt.reward.info"
#define QUEST_GETRWD_ANIMATION "quest_getrwd_animation"

enum QuestType1{
    QUEST_NORMAL = 1,
    QUEST_LEAGUE,
};

enum QuestState{
    ACCEPT,//已接受
    COMPLETE,//已完成
    REWARD,//已领奖
};

//城建(批量)：0；研究科技：1；训练：2；资源产出：3；完成任务：4；领主等级：5；英雄等级：6；英雄数量：7。显示同类别任务时，城建：8，科技（批量）9由此判断。
enum QuestType2{
    QUEST_BUILDING_AUTO,
    QUEST_SCIENCE,
    QUEST_TRAING,
    QUEST_RESOURCE,
    QUEST_COMPLETE,
    QUEST_LORD,
    QUEST_HERO_LEVEL,
    QUEST_HERO_NUM,
    QUEST_BUILDING,
    QUEST_SCIENCE_AUTO,
};

enum SortType{
    SORT_RECOMMED,
    SORT_COMMPLETE,
    SORT_TRAING,
    SORT_BUILDING,
    SORT_MISC,
    SORT_RES,
    SORT_RESERCH,
};

enum NewSortType{//2.0.1任务显示新的分类
    NEWSORT_NONE = 0,
    NEWSORT_CASTLE,
    NEWSORT_WORLD,
    NEWSORT_MONSTER,
    NEWSORT_OTHER,
    NEWSORT_SPECIAL,
};

#include "CommonInclude.h"
#include "QuestInfo.h"

const int numPerTypeShow = 5;

class QuestController:public CCNode{
public:
    static QuestController *getInstance();
    static void purgeData();
    QuestController();
    ~QuestController();
    //
    void postQuestNumChangeNotification();
    void postQuestStateChangeNotification();
    //加任务
    void initQuest(CCArray* showTask);
    void updateTask(CCArray* tasks);
    
    void addQuest(std::string itemId, int state, int type);
    //删除任务
    void removeQuest(std::string itemId, bool postNotification = true);
    //更新状态
    void updateQuestState(std::string itemId, int state, bool postNotification = true);
    //领奖
    void getReward(std::string itemId, bool isMain=false, bool showTip = true);
    //
    void setQuestReward(std::string questId, CCArray *arr);
    
    void onEnterFrame(float t);
    
    std::string getTypeName(int type);
    std::string getTypeIcon(int type);
    std::string getQuestIcon(QuestInfo *info);
    
    bool onCheckSpeTask(std::string itemId);
    
    void resetBuildQuest(bool postNotification = true);
    void resetResearchQuest();
    bool goToQuestTarget(QuestInfo *info, bool isSt = false);
    QuestInfo *getRecommendQuest(bool includeComplete = true);
    int getCompleteQuestNum();
    void getRewardSuccessHandle(std::string itemId);

    QuestInfo *getQuestBuilding(int itemId, int state = ACCEPT);
    void addQuestToBuildingList(int bid, int level, CCArray *arr);
    void addQuestToByScienceList(int sid, int level);
    QuestInfo *getQuestFormMapById(std::string itemId);
    CCDictionary *getShowQuest();
    void resetGettingRewardFlag(float t);
    void initCKFTask(CCArray* showTask);
    void updateCKFTask(CCArray* tasks);
    void clickToGetRecommendRwd();
    bool isGettingReward;
    
    map<int, int> achMap;
    map<std::string, QuestInfo*> achList;
    map<std::string, QuestInfo*> currentAchList;//当前显示的成就
    map<std::string, QuestInfo*> currentCKFList;//当前显示跨服目标
    bool m_init;
    bool m_returnFromWorld;
    
    //阶段奖励 数据
    int m_stageRdId;//当前阶段奖励的id
    int m_stageNum;//当前阶段数值
    map<int, CCSafeObject<CCArray>> m_stageRDMap;//当前阶段奖励的内容
    
    //获取奖励信息
    void startGetRewardById(int itemId);
    void endGetRewardById(CCDictionary* dict);
    //领取阶段奖励
    void startGetStageRd();
    void endGetStateRd(CCDictionary* dict);
    
    bool m_monsterFlag;//当前正在推荐的是怪物任务
    
    //特殊任务
    map<std::string, QuestInfo*> speAchList;
    CCSafeObject<Array> speAchArray;
    //城内任务
    map<std::string, QuestInfo*> castleAchList;
    CCSafeObject<Array> castleAchArray;
    //城外任务
    map<std::string, QuestInfo*> worldAchList;
    CCSafeObject<Array> worldAchArray;
    //野怪任务
    map<std::string, QuestInfo*> monsterAchList;
    CCSafeObject<Array> monsterAchArray;
    //杂项任务
    map<std::string, QuestInfo*> otherAchList;
    CCSafeObject<Array> otherAchArray;
    
private:
    void insertToArr(CCArray *arr, std::string itemId, bool isComplete);
    void generateRecommedQuest(CCDictionary *dict);
    void delayPopUpUerUpdate(CCObject* p);
    void popUPUserUPdateView(float t);
    //任务
    map<std::string, QuestInfo*> questList;
    //建筑任务
    map<std::string, QuestInfo*> buildQuestList;
    //科技任务
    map<std::string, QuestInfo*> researchQuestList;
    //按para1取配置
    map<int, CCDictionary*> config;
    
    int tmpRewardId;
    
    //////////新版任务排序显示
    void initQuestToSort(CCArray* showTask);
    void updateQuestToSort1(CCDictionary *dic);
    void updateQuestToSort2(CCDictionary *dic);
    void sortQuest(int type);
    void getRewardSuccessThenSort(std::string itemId);
    
    int getCompleteQuest();
    int getCompleteQuestByNewSort();
    
    void popupPSoilderView(float t);
    int ps_bid;
    int ps_needNum;
    string ps_armyId;
};
#endif /* defined(__IF__QuestController__) */
