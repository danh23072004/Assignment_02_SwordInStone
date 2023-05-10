#include "knight2.h"

/* * * BagNode * * */

BagNode::BagNode(BaseItem* _item = nullptr, BagNode* _nextPtr = nullptr) : item(_item), nextPtr(_nextPtr)
{
}

/* * * BagNode * * */

/* * * BaseBag * * */

BaseBag::BaseBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote) : 
    countItem(0), knight(_knight), head(nullptr), tail(nullptr)
{
    int maxSize = 0;
    switch (knight->getKnightType())
    {
        case DRAGON:
			maxSize = 14;
			break;
        case LANCELOT:
            maxSize = 16;
            break;
        case NORMAL:
            maxSize = 19;
            break;
        default:
            // maxSize = 0 means this knight is PALADIN
            break;
    }
    // These lines below are to make sure the number of items in the bag is not over the maximum size
    if (_countPhoenixDownI > maxSize)
    {
		_countPhoenixDownI = maxSize;
	}
    if (_countPhoenixDownI > 0 && (_countPhoenixDownI < maxSize || maxSize == 0))
    {
        for (int i = 0; i < _countPhoenixDownI; i++)
        {
            PhoenixDownI *phoenixDown1 = new PhoenixDownI();
            insertFirst(phoenixDown1);
        }
    }
    maxSize = maxSize - _countPhoenixDownI;
    if (_countAntidote > maxSize)
    {
        _countAntidote = maxSize;
    }
    if (_countAntidote > 0 || maxSize == 0)
    {
        for (int i = 0; i < _countAntidote; i++)
        {
			Antidote *antidote = new Antidote();
			insertFirst(antidote);
		}
	}
}

bool BaseBag::insertFirst(BaseItem* _new_item)
{
    // create a deep copy from the parameter, because the source outside the parameter will
    // be deleted after single loop
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
    return true;
}

int BaseBag::getCount()
{
    return countItem;
}


// Definition of these two virtual methods can be changed or override in the future
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

int BaseBag::getBagCount()
{
    return countItem;
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
        while (iterateNode != nullptr)
        {
            list_item = list_item + iterateNode->item->typeToString() + ',';
            iterateNode = iterateNode->nextPtr;
        }
        list_item.erase(list_item.length() - 1, 1);
    }
    return "Bag[count=<" + count + ">;<" + list_item + ">]";
}

bool BaseBag::isEmpty()
{
    if (head == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int BaseBag::isOverSize(int numAdd, ItemType item)
{
    return 0;
}

/* * * BaseBag * * */

/* * * BaseKnight * * */

BaseKnight* BaseKnight::create(int _id, int _maxhp, int _level, int _gil, int _antidote, int _phoenixdownI)
{   
    BaseKnight* new_knight;
    if (isPaladinKnight(_maxhp))
    {
        new_knight = new PaladinKnight();
        new_knight->bag = new PaladinBag(new_knight, _phoenixdownI, _antidote);
    }
    else if (isLancelotKnight(_maxhp))
    {
        new_knight = new LancelotKnight();
        new_knight->bag = new LancelotBag(new_knight, _phoenixdownI, _antidote);
    }
    else if (isDragonKnight(_maxhp))
    {
        new_knight = new DragonKnight();
        new_knight->bag = new DragonBag(new_knight, _phoenixdownI, _antidote);
    }
    else
    {
        new_knight = new NormalKnight();
        new_knight->bag = new NormalBag(new_knight, _phoenixdownI, _antidote);
    }
    new_knight->id = _id;
    new_knight->maxhp = _maxhp;
    new_knight->hp = _maxhp;
    new_knight->level = _level;
    new_knight->gil = _gil;
    /*cout << new_knight->bag << endl;*/

    return new_knight;
}

int BaseKnight::getID() const
{
    return id;
}

int BaseKnight::getHP() const
{
    return hp;
}

int BaseKnight::getMaxHP() const
{
    return maxhp;
}

int BaseKnight::getLevel() const
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

BaseKnight::BaseKnight() : id(0), hp(0), maxhp(0), level(0), gil(0), bag(nullptr), knightType(NORMAL)
{
}

BaseKnight::~BaseKnight()
{
}

int BaseKnight::getGil() const
{
    return gil;
}

BaseBag* BaseKnight::getBag() const
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

bool BaseKnight::fight(BaseOpponent* opponent)
{

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

Events::Events(const string& _file_events)
{
    ifstream file;
    file.open(_file_events);
    file >> countEvent;
    for (int i = 0; i < countEvent; i++)
    {
        file >> eventList[i];
    }
    isMetOmegaWeapon = false;
    isMetHades = false;
    armyKnights = nullptr;
}

Events::~Events()
{
}


ArmyKnights* Events::getArmyKnights()
{
    return armyKnights;
}

void Events::setArmyKnights(ArmyKnights* _armyKnights)
{
	armyKnights = _armyKnights;
}

int Events::count() const
{
    return 0;
}

int Events::get(int eventIndex) const
{
    return eventList[eventIndex];
}

void Events::runEvent(int _eventID)
{
    // Write code create opponent based on each type of _event_i


    //if (1 <= event_i <= 5)
    //else if (event_i == 6)
    //else if (event_i == 7)
    //else if (event_i == 8)
    //else if (event_i == 9)
    //else if (event_i == 10 && isMetOmegaWeapon == false)
    //else if (event_i == 11 && isMetHades == false)
    //else if (event_i >= 112 && event_i <= 114)
    //else if (event_i >= 95 && event_i <= 97)
    //else if (event_i == 98)
    //else if (event_i == 99)
}

/* * * Events * * */

/* * * ArmyKnights * * */
ArmyKnights::ArmyKnights(const string& _file_armyknights) :
    isPaladinShield(false), isLancelotSpear(false), isGuinevereHair(false), isExcaliburSword(false)
{
    ifstream file;
    file.open(_file_armyknights);
    file >> numOfKnights;
    listOfKnights = new BaseKnight*[numOfKnights];
    int HP = 0, level = 0, phoenixdownI = 0, gil = 0, antidote = 0;
    for (int i = 0; i < numOfKnights; i++)
    {
        file >> HP >> level >> phoenixdownI >> gil >> antidote;
        listOfKnights[i] = BaseKnight::create(i + 1, HP, level, gil, antidote, phoenixdownI);
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
    return isPaladinShield;
}

bool ArmyKnights::hasLancelotSpear() const
{
    return isLancelotSpear;
}

bool ArmyKnights::hasGuinevereHair() const
{
    return isGuinevereHair;
}

bool ArmyKnights::hasExcaliburSword() const
{
    return isExcaliburSword;
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
    events = new Events(_file_events);
}

void KnightAdventure::run()
{
    for (int i = 0; i < events->count(); i++)
    {

    }
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

Antidote::Antidote() : BaseItem()
{
    itemType = ANTIDOTE;
}



/* * * Antidote * * */

/* * * PhoenixDownI * * */

PhoenixDownI::PhoenixDownI() : BaseItem()
{
    itemType = PHOENIX_1;
}

bool PhoenixDownI::canUse(BaseKnight* _knight)
{
    return false;
}

void PhoenixDownI::use(BaseKnight* _knight)
{
}

/* * * PhoenixDownI * * */

/* * * PhoenixDownII * * */

PhoenixDownII::PhoenixDownII() : BaseItem()
{
    itemType = PHOENIX_2;
}

bool PhoenixDownII::canUse(BaseKnight* _knight)
{
    return false;
}

void PhoenixDownII::use(BaseKnight* _knight)
{
}

/* * * PhoenixDownII * * */

/* * * PhoenixDownIII * * */

PhoenixDownIII::PhoenixDownIII() : BaseItem()
{
    itemType = PHOENIX_3;
}

bool PhoenixDownIII::canUse(BaseKnight* _knight)
{
    return false;
}

void PhoenixDownIII::use(BaseKnight* _knight)
{
}

/* * * PhoenixDownIII * * */

/* * * PhoenixDownIV * * */

PhoenixDownIV::PhoenixDownIV() : BaseItem()
{
    itemType = PHOENIX_4;
}

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

PaladinBag::PaladinBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote) :
    BaseBag( _knight, _countPhoenixDownI, _countAntidote)
{
}

int PaladinBag::isOverSize(int _numAdd, ItemType _item)
{
    return 0;
}

LancelotBag::LancelotBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote) :
    BaseBag(_knight, _countPhoenixDownI, _countAntidote)
{
}

int LancelotBag::isOverSize(int _numAdd, ItemType _item)
{
    int count = getCount();
    if (count + _numAdd > 16)
    {
        return count + _numAdd - 16;
    }
    else
    {
        return 0;
    }
}

DragonBag::DragonBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote) :
    BaseBag(_knight, _countPhoenixDownI, _countAntidote)
{
}

int DragonBag::isOverSize(int _numAdd, ItemType _item)
{
    int count = getCount();
    if (count + _numAdd > 14 || _item == ANTIDOTE)
    {
        return count + _numAdd - 14;
    }
    else
    {
        return 0;
    }
}

NormalBag::NormalBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote) :
    BaseBag(_knight, _countPhoenixDownI, _countAntidote)
{
}

int NormalBag::isOverSize(int _numAdd, ItemType _item)
{
    int count = getCount();
    if (count + _numAdd > 19)
    {
        return count + _numAdd - 19;
    }
    else
    {
        return 0;
    }
}

/* * * BasicMonster * * */

void BasicMonster::calculateLevelO()
{
    levelO = (eventOrder + eventID) % 10 + 1;
}

BasicMonster::BasicMonster(int _eventOrder, int _eventID) : baseDamage(0), gilReward(0)
{
    calculateLevelO();
}

int BasicMonster::getLevelO()
{
    return levelO;
}

void BasicMonster::dealDamage(BaseKnight* knight)
{

}

/* * * BasicMonster * * */

MadBear::MadBear(int eventOrder, int eventID) : BasicMonster(eventOrder, eventID)
{
	baseDamage = 10;
	gilReward = 100;
}