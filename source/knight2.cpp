#include "knight2.h"

/* * * BagNode * * */

BagNode::BagNode(BaseItem* _item = nullptr, BagNode* _nextPtr = nullptr) : item(_item), nextPtr(_nextPtr)
{

}

/* * * BagNode * * */

/* * * BaseBag * * */

BaseBag::BaseBag(BaseKnight* _knight)
{
    countItem = 0;
    knight = _knight;
    head = nullptr;
    tail = nullptr;
}

bool BaseBag::insertFirst(BaseItem* _new_item)
{
    BagNode* newItem = new BagNode(_new_item, nullptr);
    if (isEmpty() == true)
    {
        head = newItem;
        tail = newItem;
    }
    else
    {
        newItem->nextPtr = head;
        head = newItem;
    }
    countItem++;
    return false;
}

int BaseBag::getCount()
{
    return countItem;
}

BaseItem* BaseBag::get(ItemType _itemType)
{
    return getBagNode(_itemType)->item;
}

void BaseBag::deleteItemFromHead()
{
    if (head == nullptr)
    {
        return;
    }
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        BagNode* tmpBagNode = head;
        head = head->nextPtr;
        delete tmpBagNode;
    }
}

void BaseBag::deleteFirstSpecificItem(ItemType _itemType)
{
    BagNode* deleteBagNode = getBagNode(_itemType);
    if (deleteBagNode == nullptr || head == nullptr)
    {
        return;
    }
    else
    {
        swapBagNode(head, deleteBagNode);
        deleteItemFromHead();
    }
}

BagNode* BaseBag::getBagNode(ItemType _itemType)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    BagNode* findItem = head;
    while (findItem->item->getType() != _itemType)
    {
        findItem = findItem->nextPtr;
        if (findItem->nextPtr == nullptr)
        {
            return nullptr;
        }
        findItem = findItem->nextPtr;
    }
    return findItem;
}

void BaseBag::swapBagNode(BagNode* _firstBagNode, BagNode* _secondBagNode)
{
    BaseItem *temp = nullptr;
    temp = _firstBagNode->item;
    _firstBagNode->item = _secondBagNode->item;
    _secondBagNode->item = temp;
}

string BaseBag::toString() const
{
    string count = to_string(countItem);
    string list_item = "";
    BagNode *iterateNode = head;
    if (head == nullptr)
    {
        list_item = "";
    }
    else
    {
        while (iterateNode->item != nullptr)
        {
            list_item = list_item + iterateNode->item->typeToString() + ',';
        }
        list_item.erase(list_item.length() - 1, 1);
    }
    return "Bag[count=<" + count + ">;<" + list_item + ">]";
}

bool BaseBag::isEmpty()
{
    if (head == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* * * BaseBag * * */

/* * * BaseKnight * * */

BaseKnight* BaseKnight::create(int _id, int _maxhp, int _level, int _gil, int _antidote, int _phoenixdownI)
{   
    BaseKnight* new_knight;
    if (isPaladinKnight(_maxhp))
        new_knight = new PaladinKnight();
    else if (isLancelotKnight(_maxhp))
        new_knight = new LancelotKnight();
    else if (isDragonKnight(_maxhp))
        new_knight = new DragonKnight();
    else
        new_knight = new NormalKnight();

    new_knight->id = _id;
    new_knight->maxhp = _maxhp;
    new_knight->level = _level;
    new_knight->gil = _gil;
    return new_knight;
}

int BaseKnight::getID()
{
    return id;
}

int BaseKnight::getHP()
{
    return maxhp;
}

int BaseKnight::getLevel()
{
    return level;
}

bool BaseKnight::isPaladinKnight(int _maxHP)
{
    if (Math::isPrime(_maxHP) == true)
        return true;
    else
        return false;
}

bool BaseKnight::isLancelotKnight(int _maxHP)
{
    if (_maxHP == 888)
        return true;
    else
        return false;
}

bool BaseKnight::isDragonKnight(int _maxHP)
{
    if (Math::isPythagoras(_maxHP) == true)
        return true;
    else
        return false;
}

BaseKnight::BaseKnight() : knightType(NORMAL), id(0), hp(0), maxhp(0), level(0), gil(0)
{
    bag = new BaseBag(this);
}

int BaseKnight::getGil()
{
    return gil;
}

BaseBag* BaseKnight::getBag()
{
    return bag;
}

KnightType BaseKnight::getKnightType()
{
    return knightType;
}

void BaseKnight::setID(int _new_id)
{
    id = _new_id;
}

void BaseKnight::setHP(int _new_hp)
{
    hp = _new_hp;
}

void BaseKnight::setLevel(int _new_level)
{
    level = _new_level;
}

void BaseKnight::setGil(int _new_gil)
{
    gil = _new_gil;
}

void BaseKnight::setBag()
{
}

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

bool BaseKnight::fight()
{
    return false;
}

/* * * BaseKnight * * */

/* * * PaladinKnight * * */

PaladinKnight::PaladinKnight()
{
    knightType = PALADIN;
}

/* * * PaladinKnight * * */

/* * * LancelotKnight * * */

LancelotKnight::LancelotKnight()
{
    knightType = LANCELOT;
}

/* * * LancelotKnight * * */

/* * * DragonKnight * * */

DragonKnight::DragonKnight()
{
    knightType = DRAGON;
}

/* * * DragonKnight * * */

/* * * NormalKnight * * */

NormalKnight::NormalKnight()
{
    knightType = NORMAL;
}

/* * * NormalKnight * * */

/* * * Events * * */

Events::Events()
{

}

Events::~Events()
{
}

int Events::count() const
{
    return 0;
}

int Events::get(int eventIndex) const
{
    return 0;
}

/* * * Events * * */

/* * * ArmyKnights * * */
ArmyKnights::ArmyKnights(const string& _file_armyknights)
{
    ifstream file;
    file.open(_file_armyknights);
    file >> numOfKnights;
    listOfKnights = new BaseKnight*[numOfKnights];
    int HP = 0, level = 0, phoenixdownI = 0, gil = 0, antidote = 0;
    for (int i = 0; i < numOfKnights; i++)
    {
        file >> HP >> level >> phoenixdownI >> gil >> antidote;
        listOfKnights[i] = BaseKnight::create(i, HP, level, gil, antidote, phoenixdownI);
        cout << listOfKnights[i]->toString() << endl;
        //cout << listOfKnights[i]->getHP() << endl;
        //cout << listOfKnights[i]->getKnightType() << endl;
    }
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << count();
    if (count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << hasPaladinShield()
        << ";LancelotSpear:" << hasLancelotSpear()
        << ";GuinevereHair:" << hasGuinevereHair()
        << ";ExcaliburSword:" << hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool _win) const {
    cout << (_win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::~ArmyKnights()
{

}

bool ArmyKnights::fight(BaseOpponent* _opponent)
{
    return false;
}

bool ArmyKnights::adventure(Events * _events)
{
    return false;
}

int ArmyKnights::count() const
{
    return numOfKnights;
}

BaseKnight* ArmyKnights::lastKnight() const
{
    return listOfKnights[0];
}

bool ArmyKnights::hasPaladinShield() const
{
    return false;
}

bool ArmyKnights::hasLancelotSpear() const
{
    return false;
}

bool ArmyKnights::hasGuinevereHair() const
{
    return false;
}

bool ArmyKnights::hasExcaliburSword() const
{
    return false;
}

/* * * ArmyKnights * * */

/* * * KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string& _file_armyknights)
{
    armyKnights = new ArmyKnights(_file_armyknights);
}

void KnightAdventure::loadEvents(const string& _file_events)
{

}

void KnightAdventure::run()
{

}

KnightAdventure::~KnightAdventure()
{

}

/* * * KnightAdventure * * */

/* * * BaseItem * * */

BaseItem::BaseItem()
{
    itemType = UNKNOWN_ITEM;
}

BaseItem* BaseItem::setItem(ItemType _type)
{
    BaseItem* newItem;
    switch (_type)
    {
    case ANTIDOTE:
        newItem = new Antidote();
        newItem->itemType = _type;
        break;
    case PHOENIX_1:
        newItem = new Antidote();
        newItem->itemType = _type;
        break;
    case PHOENIX_2:
        newItem = new Antidote();
        newItem->itemType = _type;
        break;
    case PHOENIX_3:
        newItem = new Antidote();
        newItem->itemType = _type;
        break;
    case PHOENIX_4:
        newItem = new Antidote();
        newItem->itemType = _type;
        break;
    default:
        newItem = new Antidote();
        newItem->itemType = _type;
        break;
    }
    return newItem;
}

ItemType BaseItem::getType()
{
    return itemType;
}

string BaseItem::typeToString()
{
    string typeStr = "";
    switch (itemType)
    {
    case UNKNOWN_ITEM:
        typeStr = "Unknown";
        break;
    case ANTIDOTE:
        typeStr = "Antidote";
        break;
    case PHOENIX_1:
        typeStr = "PhoenixDownI";
        break;
    case PHOENIX_2:
        typeStr = "PhoenixDownII";
        break;
    case PHOENIX_3:
        typeStr = "PhoenixDownIII";
        break;
    case PHOENIX_4:
        typeStr = "PhoenixDownIV";
        break;
    default:
        typeStr = "";
        break;
    }
    return typeStr;
}

/* * * BaseItem * * */

/* * * Antidote * * */

bool Antidote::canUse(BaseKnight* knight)
{
    return false;
}

void Antidote::use(BaseKnight* knight)
{
}

Antidote::Antidote()
{
}



/* * * Antidote * * */

/* * * PhoenixDownI * * */

bool PhoenixDownI::canUse(BaseKnight* _knight)
{
    return false;
}

void PhoenixDownI::use(BaseKnight* _knight)
{
}

/* * * PhoenixDownI * * */

/* * * PhoenixDownII * * */

bool PhoenixDownII::canUse(BaseKnight* _knight)
{
    return false;
}

void PhoenixDownII::use(BaseKnight* _knight)
{
}

/* * * PhoenixDownII * * */

/* * * PhoenixDownIII * * */

bool PhoenixDownIII::canUse(BaseKnight* _knight)
{
    return false;
}

void PhoenixDownIII::use(BaseKnight* _knight)
{
}

/* * * PhoenixDownIII * * */

/* * * PhoenixDownIV * * */

bool PhoenixDownIV::canUse(BaseKnight* _knight)
{
    return false;
}

void PhoenixDownIV::use(BaseKnight* _knight)
{
}

/* * * PhoenixDownIV * * */

/* * * Math * * */

bool Math::isPrime(int _number)
{
    if (_number <= 1)
        return false;
    for (int i = 2; i * i <= _number; i++)
    {
        if (_number % i == 0)
            return false;
    }
    return true;
}

bool Math::isPythagoras(int _number)
{
    if (_number == 345 || _number == 354 || _number == 435 || 
        _number == 453 || _number == 534 || _number == 543)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* * * Math * * */
