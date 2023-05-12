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


// Get the first item has the same _itemType, return nullptr if not found
BaseItem* BaseBag::get(ItemType _itemType)
{
    return findItem(_itemType)->item;
}

BaseItem* BaseBag::getFirst()
{
    if (head == nullptr)
    {
		return nullptr;
	}
    else
    {
		return head->item;
	}
}

void BaseBag::dropItem()
{
    deleteItemFromHead();
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

// return true if delete sucessfully, false if not
bool BaseBag::deleteFirstSpecificItem(ItemType _itemType)
{
    BagNode* deleteBagNode = findItem(_itemType);
    if (deleteBagNode == nullptr || head == nullptr)
    {
        return false;
    }
    else
    {
        swapBagNode(head, deleteBagNode);
        deleteItemFromHead();
        return true;
    }
}

BagNode* BaseBag::findItem(ItemType _itemType)
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

bool BaseBag::isOverSize(int numAdd, ItemType item)
{
    int maxSize = 0;
    if (knight->getKnightType() == PALADIN)
    {
        return false; // means PALADIN knight bag is unlimited
    }
    if (knight->getKnightType() == DRAGON && item == ANTIDOTE)
    {
        return true; // means DRAGON knight bag doesn't need ANTIDOTE
    }
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
			break;
	}
    if (countItem + numAdd > maxSize)
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

bool BaseKnight::isWonHades()
{
    if (level == 10 || (level == 8 && knightType == PALADIN))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BaseKnight::isWonOmegaWeapon()
{
    if ((level == 10 && hp == maxhp) || knightType == DRAGON)
    {
        return true;
    }
    else
    {
        return false;
    }
}

BaseKnight::BaseKnight() : id(0), hp(0), maxhp(0), level(0), gil(0), bag(nullptr), knightType(NORMAL), canFightUltimecia(false)
{
}

BaseKnight::~BaseKnight()
{
}

int BaseKnight::getGil() const
{
    return gil;
}

void ArmyKnights::addGil(int _numOfGill)
{
    int currentKnight = numOfKnights;
    while (_numOfGill > 0 && currentKnight >= 0)
    {
        if (listOfKnights[currentKnight]->getGil() + _numOfGill > 999)
        {
            _numOfGill -= 999 - listOfKnights[currentKnight]->getGil();
            listOfKnights[currentKnight]->setGil(999);
            currentKnight--;
        }
        else
        {
            listOfKnights[currentKnight]->setGil(listOfKnights[currentKnight]->getGil() + _numOfGill);
            break;
        }
    }
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

void BaseKnight::reduceHP(int new_reducehp)
{
    if (hp - new_reducehp > 0)
    {
        hp -= new_reducehp;
    }
    else
    {
        hp = 0;
    }
}

void BaseKnight::addHP(int new_addhp)
{
    if (hp + new_addhp < maxhp)
    {
		hp += new_addhp;
	}
    else
    {
		hp = maxhp;
	}
}

void BaseKnight::setLevel(int _new_level)
{
    level = _new_level;
}

void BaseKnight::addLevel()
{
    if (level + 1 < 10)
    {
        level++;
    }
}

void BaseKnight::setGil(int _new_gil)
{
    gil = _new_gil;
}

bool BaseKnight::useAntidote()
{
    return bag->deleteFirstSpecificItem(ANTIDOTE);
}

void BaseKnight::usePhoenixDown()
{

}

bool BaseKnight::isCanFightUltimecia()
{
    return canFightUltimecia;
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
    if (level > opponent->getLevelO())
    {
        return true;
    }
    else
    {
        //opponent->behave(this);
        return false;
    }
}



/* * * BaseKnight * * */

/* * * PaladinKnight * * */

PaladinKnight::PaladinKnight()
{
    knightType = PALADIN;
    canFightUltimecia = true;
}

bool PaladinKnight::fight(BaseOpponent* opponent)
{
    // If it doesn't run into if block, it means that the knight is dead
    bool result = false;
	switch (opponent->getOpponentType())
	{
	case BASIC_MONSTER:
		result = true;
		break;
	case TORNBERY:
	case QUEEN_OF_CARDS:
        result = BaseKnight::fight(opponent);
		break;
	case HADES:
        result = isWonHades();
		break;
	case OMEGA_WEAPON:
        result = isWonOmegaWeapon();
	default:
		break;
	}
    return result;
}

bool PaladinKnight::fightUltimecia(Ultimecia* ultimecia)
{
    int damage = int(hp * level * baseDamage);
    ultimecia->reduceHP(damage);
    if (ultimecia->getHP() == 0)
    {
        return true;
    }
    else
    {
        ultimecia->killKnight(this);
        return false;
    }
}

/* * * PaladinKnight * * */

/* * * LancelotKnight * * */

LancelotKnight::LancelotKnight()
{
    knightType = LANCELOT;
    canFightUltimecia = true;
}

bool LancelotKnight::fight(BaseOpponent* opponent)
{
    bool result = false;
	switch (opponent->getOpponentType())
	{
    case BASIC_MONSTER:
        result = true;
        break;
    case TORNBERY:
    case QUEEN_OF_CARDS:
        result = BaseKnight::fight(opponent);
        break;
    case HADES:
        result = isWonHades();
    case OMEGA_WEAPON:
        result = isWonOmegaWeapon();
    default: 
        break;
	}
    return result;
}

bool LancelotKnight::fightUltimecia(Ultimecia* ultimecia)
{
    int damage = int(hp * level * baseDamage);
    ultimecia->reduceHP(damage);
    if (ultimecia->getHP() == 0)
    {
        return true;
    }
    else
    {
        ultimecia->killKnight(this);
        return false;
    }
}

/* * * LancelotKnight * * */

/* * * DragonKnight * * */

DragonKnight::DragonKnight()
{
    knightType = DRAGON;
    canFightUltimecia = false;
}

bool DragonKnight::fight(BaseOpponent* opponent)
{
    bool result = false;
    switch (opponent->getOpponentType())
    {
    case BASIC_MONSTER:
    case QUEEN_OF_CARDS:
    case TORNBERY:
        result = BaseKnight::fight(opponent);
		break;
    case HADES:
        result = isWonHades();
    case OMEGA_WEAPON:
        result = isWonOmegaWeapon();
    default:
        break;
    }
    return result;
}

bool DragonKnight::fightUltimecia(Ultimecia* ultimecia)
{
    int damage = int(hp * level * baseDamage);
    ultimecia->reduceHP(damage);
    if (ultimecia->getHP() == 0)
    {
        return true;
    }
    else
    {
        ultimecia->killKnight(this);
        return false;
    }
}

/* * * DragonKnight * * */

/* * * NormalKnight * * */

NormalKnight::NormalKnight()
{
    knightType = NORMAL;
    canFightUltimecia = false;
}

bool NormalKnight::fight(BaseOpponent* opponent)
{
    bool result = false;
    switch (opponent->getOpponentType())
    {
    case BASIC_MONSTER:
    case QUEEN_OF_CARDS:
    case TORNBERY:
        result = BaseKnight::fight(opponent);
        break;
    case HADES:
        result = isWonHades();
    case OMEGA_WEAPON:
        result = isWonOmegaWeapon();
    default:
        break;
    }
    return result;
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
    currentEventID = 0;
    currentEventOrder = 0;
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

void Events::runEvent()
{
    // Write code create opponent based on each type of _event_i

    for (currentEventOrder = 0; currentEventOrder < count(); currentEventOrder++)
    {
        currentEventID = get(currentEventOrder);
        if (1 <= currentEventOrder && currentEventOrder <= 5)
            eventBasicOpponent();
        else if (currentEventID == 6)
            eventTornberry();
        else if (currentEventID == 7)
            eventQueenOfCards();
        else if (currentEventID == 8)
            eventNinaDeRings();
        else if (currentEventID == 9)
            eventDurianGarden();
        else if (currentEventID == 10 && isMetOmegaWeapon == false)
            eventOmegaWeapon();
        else if (currentEventID == 11 && isMetHades == false)
            eventHades();
        else if (currentEventID >= 112 && currentEventOrder <= 114)
            eventGetPhoenixDown();
        else if (currentEventID == 95)
            eventGetPaladinShield();
        else if (currentEventID == 96)
            eventGetLancelotSpear();
        else if (currentEventID == 97)
            eventGetGuinevereHair();
        else if (currentEventID == 98)
            eventGetExcaliburSword();
        else if (currentEventID == 99)
            eventUltimecia();
    }
}

void Events::eventBasicOpponent()
{
    BaseMonster* newMons;
    newMons = BaseMonster::defineBasicMonster(currentEventOrder, currentEventID);

}

void Events::eventTornberry()
{
}

void Events::eventQueenOfCards()
{
}

void Events::eventNinaDeRings()
{
}

void Events::eventDurianGarden()
{
}

void Events::eventOmegaWeapon()
{
}

void Events::eventHades()
{
}

void Events::eventGetPhoenixDown()
{
}

void Events::eventGetAntidote()
{
}

void Events::eventGetExcaliburSword()
{
}

void Events::eventGetGuinevereHair()
{
}

void Events::eventGetLancelotSpear()
{
}

void Events::eventGetPaladinShield()
{
}

void Events::eventUltimecia()
{
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
    return lastKnight()->fight(_opponent);
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

void ArmyKnights::lastKnightUpdateStatus()
{
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

void ArmyKnights::setPaladinShield(bool status)
{
    isPaladinShield = status;
}

void ArmyKnights::setLancelotSpear(bool status)
{
    isLancelotSpear = status;
}

void ArmyKnights::setGuinevereHair(bool status)
{
    isGuinevereHair = status;
}

void ArmyKnights::setExcaliburSword(bool status)
{
    isExcaliburSword = status;
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
    events->runEvent();
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

BaseItem* BaseItem::createItem(ItemType itemType)
{
    BaseItem* item = nullptr;
    switch (itemType)
    {
	case ANTIDOTE:
		item = new Antidote();
		break;
	case PHOENIX_1:
		item = new PhoenixDownI();
		break;
	case PHOENIX_2:
		item = new PhoenixDownII();
		break;
	case PHOENIX_3:
		item = new PhoenixDownIII();
		break;
	case PHOENIX_4:
		item = new PhoenixDownIV();
		break;
	default:
		item = nullptr;
		break;
	}
	return item;
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

bool PaladinBag::isOverSize(int _numAdd, ItemType _item)
{
    return 0;
}

LancelotBag::LancelotBag(BaseKnight* _knight, int _countPhoenixDownI, int _countAntidote) :
    BaseBag(_knight, _countPhoenixDownI, _countAntidote)
{
}

bool LancelotBag::isOverSize(int _numAdd, ItemType _item)
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

bool DragonBag::isOverSize(int _numAdd, ItemType _item)
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

bool NormalBag::isOverSize(int _numAdd, ItemType _item)
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

/* * * BaseMonster * * */

void BaseOpponent::calculateLevelO()
{
    levelO = (eventOrder + eventID) % 10 + 1;
}

BaseMonster::BaseMonster(int _eventOrder, int _eventID)
{
    baseDamage = 0;
    calculateLevelO();
}

int BaseOpponent::getLevelO()
{
    return levelO;
}

int BaseOpponent::getGilReward()
{
    return gilReward;
}

void BaseOpponent::dealDamage(BaseKnight* _knight)
{
    int knightLevel = _knight->getLevel();
    int reduceHP = baseDamage * (levelO - knightLevel);
    _knight->reduceHP(reduceHP);
}

void BaseMonster::behave(ArmyKnights* _knight, bool _knightWinState)
{
    BaseKnight* lastKnight = _knight->lastKnight();
    dealDamage(lastKnight);
}

BaseMonster* BaseMonster::defineBasicMonster(int _eventOrder, int _eventID)
{
    switch (_eventID)
    {
        case 1:
		    return new MadBear(_eventOrder, _eventID);
		    break;
        case 2:
            return new Bandit(_eventOrder, _eventID);
            break;
        case 3:
            return new LordLupin(_eventOrder, _eventID);
			break;
        case 4:
            return new Elf(_eventOrder, _eventID);
            break;
        case 5:
            return new Troll(_eventOrder, _eventID);
            break;
        default:
            return nullptr;
            break;
    }
}

/* * * BaseMonster * * */

/* * * MadBear * * */

MadBear::MadBear(int _eventOrder, int _eventID) : BaseMonster(eventOrder, eventID)
{
	baseDamage = 10;
	gilReward = 100;
}

/* * * MadBear * * */

/* * * Bandit * * */

Bandit::Bandit(int _eventOrder, int _eventID) : BaseMonster(eventOrder, eventID)
{
	baseDamage = 15;
	gilReward = 150;
}

/* * * Bandit * * */

/* * * LordLupin * * */

LordLupin::LordLupin(int _eventOrder, int _eventID) : BaseMonster(eventOrder, eventID)
{
	baseDamage = 45;
	gilReward = 450;
}

/* * * LordLupin * * */

/* * * Elf * * */

Elf::Elf(int _eventOrder, int _eventID) : BaseMonster(eventOrder, eventID)
{
	baseDamage = 75;
	gilReward = 750;
}

/* * * Elf * * */

/* * * Troll * * */

Troll::Troll(int _eventOrder, int _eventID) : BaseMonster(eventOrder, eventID)
{
	baseDamage = 95;
	gilReward = 800;
}


/* * * Troll * * */

/* * * BaseOpponent * * */

BaseOpponent::BaseOpponent() : eventOrder(0), eventID(0), levelO(0), gilReward(0), baseDamage(0)
{
}

OpponentType BaseOpponent::getOpponentType()
{
    if (1 <= eventID && eventID <= 5)
    {
        return BASIC_MONSTER;
    }
    else if (eventID == 6)
    {
        return TORNBERY;
    }
    else if (eventID == 7)
    {
        return QUEEN_OF_CARDS;
    }
    else if (eventID == 8)
    {
        return NINA_DE_RINGS;
    }
    else if (eventID == 9)
    {
        return DURIAN_GARDEN;
    }
    else if (eventID == 10)
    {
        return OMEGA_WEAPON;
    }
    else if (eventID == 11)
    {
        return HADES;
    }
    else if (eventID == 99)
    {
        return ULTIMECIA;
    }
    else
    {
        return UNKNOWN;
    }
}

/* * * BaseOpponent * * */

/* * * TornBery * * */

TornBery::TornBery(int _eventOrder, int _eventID) : BaseOpponent()
{
    eventOrder = _eventOrder;
	eventID = _eventID;
    calculateLevelO();
}

void TornBery::behave(ArmyKnights* _knight, bool _knightWinState)
{
    BaseKnight* lastKnight = _knight->lastKnight();
    if (_knightWinState == false)
    {
        dealDamage(lastKnight);
        if (lastKnight->getKnightType() != DRAGON)
        {
            if (lastKnight->useAntidote() == false)
            {
                infect(lastKnight);
            }
        }
    }
    else
    {
        lastKnight->addLevel();
    }
}

void TornBery::infect(BaseKnight* knight)
{
    knight->reduceHP(10);
    knight->getBag()->dropItem();
    knight->getBag()->dropItem();
    knight->getBag()->dropItem();
}

/* * * TornBery * * */

/* * * Queen Of Cards * * */

QueenOfCards::QueenOfCards(int _eventOrder, int _eventID)
{
    eventOrder = _eventOrder;
	eventID = _eventID;
	calculateLevelO();
}

void QueenOfCards::behave(ArmyKnights* armyKnights, bool winState)
{
    BaseKnight* lastKnight = armyKnights->lastKnight();
    if (winState == false)
    {
        lastKnight->setGil(lastKnight->getGil()/2);
    }
    else
    {
        if (lastKnight->getGil() * 2 < 999)
        {
            lastKnight->setGil(lastKnight->getGil() * 2);
        }
        else
        {
            // double gils means add the same amount of gils of the last knight to the army
            armyKnights->addGil(lastKnight->getGil());
        }
    }
}

/* * * Nina De Rings * * */

void NinaDeRings::behave(ArmyKnights* armyKnights, bool knightWinState = true)
{
    BaseKnight* lastKnight = armyKnights->lastKnight();
    if (lastKnight->getGil() >= 50 && lastKnight->getHP() < (1/3)*lastKnight->getMaxHP())
    {
        lastKnight->setGil(lastKnight->getGil() - 50);
        lastKnight->addHP(int(lastKnight->getMaxHP() * 0.2));
    }
}

/* * * Nina De Rings * * */

/* * * Durian Garden * * */

void DurianGarden::behave(ArmyKnights* armyKnights, bool knightWinState = true)
{
    armyKnights->lastKnight()->setHP(armyKnights->lastKnight()->getMaxHP());
}

/* * * Durian Garden * * */

/* * * Omega Weapon * * */

void OmegaWeapon::behave(ArmyKnights* armyKnights, bool knightWinState)
{
    BaseKnight* lastKnight = armyKnights->lastKnight();
    if (knightWinState == false)
    {
        lastKnight->setHP(0);
	}
    else
    {
        lastKnight->setLevel(10);
	}
}

/* * * Omega Weapon * * */

/* * * Hades * * */

void Hades::behave(ArmyKnights* armyKnights, bool knightWinState)
{
    BaseKnight* lastKnight = armyKnights->lastKnight();
    if (knightWinState == false)
    {
		lastKnight->setHP(0);
	}
    else
    {
        armyKnights->setPaladinShield(true);
	}
}

/* * * Hades * * */

Ultimecia::Ultimecia() : hp(5000)
{
}

void Ultimecia::reduceHP(int _hp)
{
    hp -= _hp;
    if (hp <= 0)
    {
        hp = 0;
	}
}

int Ultimecia::getHP()
{
    return hp;
}

void Ultimecia::killKnight(BaseKnight* knight)
{
    knight->setHP(0);
}

