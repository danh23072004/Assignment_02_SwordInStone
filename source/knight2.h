#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum KnightType 
{ 
    UNKNOWN_KNIGHT = -1, 
    PALADIN = 0, 
    LANCELOT = 1, 
    DRAGON = 2, 
    NORMAL = 3 
};
enum ItemType 
{ 
    UNKNOWN_ITEM = -1, 
    ANTIDOTE = 0, 
    PHOENIX_1 = 1, 
    PHOENIX_2 = 2, 
    PHOENIX_3 = 3, 
    PHOENIX_4 = 4
};
enum OpponentType
{
    BASIC_MONSTER = 0,
    TORNBERY = 1,
    QUEEN_OF_CARDS = 2,
    NINA_DE_RINGS = 3,
    DURIAN_GARDEN = 4,
    OMEGA_WEAPON = 5,
    HADES = 6,
    ULTIMECIA = 7,
    UNKNOWN = -1,
};

class BaseKnight; class ArmyKnights; // forward declaration for BaseKnight, ArmyKnights

class BaseItem {
protected:
    ItemType itemType;
public:
    BaseItem();
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
    ItemType getType();
    string typeToString();
};

class Antidote : public BaseItem
{
public:
    Antidote();
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

class PhoenixDownI : public BaseItem
{
public:
    PhoenixDownI();
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

class PhoenixDownII : public BaseItem
{
public:
    PhoenixDownII();
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

class PhoenixDownIII : public BaseItem
{
public:
    PhoenixDownIII();
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

class PhoenixDownIV : public BaseItem
{;
public:
    PhoenixDownIV();
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

struct BagNode
{
    BagNode(BaseItem* _item, BagNode* _nextPtr);
    BaseItem* item;
    BagNode* nextPtr;
};

class BaseBag {
private:
    int countItem;
    void deleteItemFromHead();
    void deleteFirstSpecificItem(ItemType _itemType);
    BagNode* getBagNode(ItemType itemType);
    void swapBagNode(BagNode* firstBagNode, BagNode* secondBagNode);
protected:
    int getBagCount();
    BaseKnight* knight;
    BagNode* head;
    BagNode* tail;
public:
    BaseBag(BaseKnight* knight, int countPhoenixDownI, int countAntidote);
    virtual bool insertFirst(BaseItem* item);
    int getCount();
    bool isEmpty();
    virtual int isOverSize(int numAdd, ItemType item = UNKNOWN_ITEM);
    virtual BaseItem* get(ItemType itemType);
    virtual string toString() const;
};

class PaladinBag : public BaseBag
{
public:
    PaladinBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote);
    virtual int isOverSize(int numAdd, ItemType item) override;
};

class LancelotBag : public BaseBag
{
public:
    LancelotBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote);
    virtual int isOverSize(int numAdd, ItemType item) override;
};

class DragonBag : public BaseBag
{
public:
    DragonBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote);
    virtual int isOverSize(int numAdd, ItemType item) override;
};

class NormalBag : public BaseBag
{
public:
    NormalBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote);
    virtual int isOverSize(int numAdd, ItemType item) override;
};

class BaseOpponent
{
protected:
    void calculateLevelO();
    int eventOrder;
    int levelO;
    int eventID;
    int baseDamage;
    int gilReward;
    void dealDamage(BaseKnight* knight);
public:
    BaseOpponent();
    OpponentType getOpponentType();
    int getLevelO();
    int getGilReward();
    virtual void behave(ArmyKnights* knight, bool knightWinState) = 0;
};

class Ultimecia
{
private:
public:
};

class BaseMonster : public BaseOpponent
{
public:
    BaseMonster(int eventOrder, int eventID);
    virtual void behave(ArmyKnights* knight, bool knightWinState) override;
    static BaseMonster* defineBasicMonster(int eventOrder, int eventID);
};

class MadBear : public BaseMonster
{
public: 
    MadBear(int eventOrder, int eventID);
};

class Bandit : public BaseMonster
{
public:
    Bandit(int eventOrder, int eventID);
};

class LordLupin : public BaseMonster
{
public:
    LordLupin(int eventOrder, int eventID);
};

class Elf : public BaseMonster
{
public:
    Elf(int eventOrder, int eventID);
};

class Troll : public BaseMonster
{
public:
    Troll(int eventOrder, int eventID);
};

class TornBery : public BaseOpponent
{
public:
    TornBery(int eventOrder, int eventID);
    virtual void behave(ArmyKnights* armyKnights, bool knightWinState) override;
};

class QueenOfCards : public BaseOpponent
{
    QueenOfCards(int eventOrder, int eventID);
    virtual void behave(ArmyKnights* armyKnights, bool knightWinState) override;
};

class NinaDeRings : public BaseOpponent
{
};

class DurianGarden : public BaseOpponent
{
};

class OmegaWeapon : public BaseOpponent
{
};

class Hades : public BaseOpponent
{
};

class BaseKnight {
private:
    static bool isPaladinKnight(int maxHP);
    static bool isLancelotKnight(int maxHP);
    static bool isDragonKnight(int maxHP);
protected:
    const int maxgil = 999;
    int maxhp;
    int id;
    int hp;
    int level;
    int gil;
    BaseBag* bag;
    KnightType knightType;
    bool isWonHades();
    bool isWonOmegaWeapon();
public:
    BaseKnight();
    ~BaseKnight();
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int getID() const;
    int getHP() const;
    int getMaxHP() const;
    int getLevel() const;
	int getGil() const;
    void buy();
    BaseBag* getBag() const;
    KnightType getKnightType();
    void setID(int new_id);
    void setHP(int new_hp);
    void reduceHP(int new_reducehp);
    void setLevel(int new_level);
    void addLevel();
    void setGil(int new_gil);
    void useMedicine(ItemType itemType);
    virtual void becomeInfect();

    string toString() const;
    virtual bool fight(BaseOpponent* opponent);
};

class PaladinKnight : public BaseKnight
{
private:
    const double baseDamage = 0.06;
public:
    PaladinKnight();
    virtual bool fight(BaseOpponent* opponent) override;
};

class LancelotKnight : public BaseKnight
{
private:
    const double baseDamage = 0.05;
public:
    LancelotKnight();
    virtual bool fight(BaseOpponent* opponent) override;
};

class DragonKnight : public BaseKnight
{
private:
    const double baseDamage = 0.075;
public:
    DragonKnight();
    virtual bool fight(BaseOpponent* opponent) override;
};

class NormalKnight : public BaseKnight
{
public:
    NormalKnight();
    virtual bool fight(BaseOpponent* opponent) override;
};

class ArmyKnights;

class Events {
private:
    int currentEventID;
    int currentEventOrder;
    ArmyKnights* armyKnights;
    int countEvent;
    int eventList[1000] = {};
    bool isMetOmegaWeapon;
    bool isMetHades;
    void eventBasicOpponent();
    void eventTornberry();
    void eventQueenOfCards();
    void eventNinaDeRings();
    void eventDurianGarden();
    void eventOmegaWeapon();
    void eventHades();
    void eventGetPhoenixDown();
    void eventGetAntidote();
    void eventGetExcaliburSword();
    void eventGetGuinevereHair();
    void eventGetLancelotSpear();
    void eventGetPaladinShield();
    void eventUltimecia();
public:
    ArmyKnights* getArmyKnights();
    void setArmyKnights(ArmyKnights* _armyKnights);
    int count() const;
    int get(int i) const;
    void runEvent();

    Events(const string& file_events);
    ~Events();
};

class ArmyKnights {
private:
    int numOfKnights;
    BaseKnight** listOfKnights; // list of Knights
    bool isPaladinShield;
    bool isLancelotSpear;
    bool isGuinevereHair;
    bool isExcaliburSword;
public:
    ArmyKnights(const string & file_armyknights);
    ~ArmyKnights();

    bool fight(BaseOpponent * opponent);
    bool adventure(Events * events);
    int count() const;
    BaseKnight* lastKnight() const;
    void addGil(int numOfGill);
    void addItem(ItemType item);
    void lastKnightUpdateStatus();
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;
public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

class Math 
{
public:
    static bool isPrime(int number);
    static bool isPythagoras(int number);
};

#endif // __KNIGHT2_H__