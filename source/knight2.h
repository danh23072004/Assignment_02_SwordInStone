#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum KnightType { UNKNOWN_KNIGHT = -1, PALADIN = 0, LANCELOT = 1, DRAGON = 2, NORMAL = 3 };
enum ItemType { UNKNOWN_ITEM = -1, ANTIDOTE = 0, PHOENIX_1 = 1, PHOENIX_2 = 2, PHOENIX_3 = 3, PHOENIX_4 = 4};

class BaseKnight; // forward declaration for BaseKnight

class BaseItem {
protected:
    ItemType itemType;
public:
    BaseItem();
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
    static BaseItem* setItem(ItemType);
    ItemType getType();
    string typeToString();
};

class Antidote : public BaseItem
{
protected:
    ItemType itemType = ANTIDOTE;
public:
    Antidote();
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

class PhoenixDownI : public BaseItem
{
protected:
    ItemType itemType = PHOENIX_1;
public:
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

class PhoenixDownII : public BaseItem
{
protected:
    ItemType itemType = PHOENIX_2;
public:
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

class PhoenixDownIII : public BaseItem
{
protected:
    ItemType itemType = PHOENIX_3;
public:
    virtual bool canUse(BaseKnight* knight) override;
    virtual void use(BaseKnight* knight) override;
};

class PhoenixDownIV : public BaseItem
{
protected:
    ItemType itemType = PHOENIX_4;
public:
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
    BaseKnight* knight;
    BagNode* head;
    BagNode* tail;
public:
    BaseBag(BaseKnight* knight);
    virtual bool insertFirst(BaseItem* item);
    int getCount();
    bool isEmpty();
    virtual BaseItem* get(ItemType itemType);
    virtual string toString() const;
};

class BaseKnight {
private:
    static bool isPaladinKnight(int maxHP);
    static bool isLancelotKnight(int maxHP);
    static bool isDragonKnight(int maxHP);
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    BaseBag* bag;
    KnightType knightType;
public:
    BaseKnight();
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int getID();
    int getHP();
    int getLevel();
	int getGil();
    BaseBag* getBag();
    KnightType getKnightType();
    void setID(int _new_id);
    void setHP(int _new_hp);
    void setLevel(int _new_level);
    void setGil(int _new_gil);
    void setBag();
    string toString() const;
    bool fight();
};

class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight();
};

class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight();
};

class DragonKnight : public BaseKnight
{
public:
    DragonKnight();
};

class NormalKnight : public BaseKnight
{
public:
    NormalKnight();
};

class BaseOpponent
{

};

class MadBear : public BaseOpponent
{

};

class Bandit : public BaseOpponent
{

};

class LordLupin : public BaseOpponent
{

};

class Elf : public BaseOpponent
{

};

class Troll : public BaseOpponent
{

};

class TornBery : public BaseOpponent
{

};

class Events {
private:
    int eventList[1000] = {};
public:
    int count() const;
    int get(int i) const;
    Events();
    ~Events();
};

class ArmyKnights {
private:
    int numOfKnights;
    BaseKnight** listOfKnights; // list of Knights
public:
    ArmyKnights(const string & file_armyknights);
    ~ArmyKnights();

    bool fight(BaseOpponent * opponent);
    bool adventure(Events * events);
    int count() const;
    BaseKnight* lastKnight() const;

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