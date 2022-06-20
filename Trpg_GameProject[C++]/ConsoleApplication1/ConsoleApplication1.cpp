#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "Timer.h"

#define MAP_SIZE 10
#define GRASSLAND_PORTAL_COUNT 4


// ������
enum SceneType
{
    VILIAGE,
    PORTION_SHOP,
    WEAPON_SHOP,

    // ����;�
    GRASSLAND,
    FOREST,
    LAVA,
    SWAMP,
    DUNGEON,

    // ���θ޴� ��
    MENU,

    // �κ��丮 ��
    INVENTORY,

    // ����ȸ�� / ���� ��
    TOWNHALL,
    PUB,
    // ������
    COMBAT,
    COMBATRESULT,

    // ��������
    EXIT
}; // �� ������ ������.

enum Portion
{
    HP_PORTION,
    MP_PORTION,
    HP_STRONGMILK,
    MP_MANAELIXIR
};

enum Equipmnet
{
    TOP,
    BOTTOM,
    WEAPON,
};

enum weapon
{
    FIRESWORD,
    FISHSPIKE,
    CHAINSAW,
    SIVERDAWN,
};

enum Hero
{
    SWORD,
    WIZARD,
    PUNCH
};

enum Monster
{
    // �ʿ�����
    SLIME, // ������
    GOBLIN, // ���
    SNAIL, // ������

    // ����� ��
    GROOT, // �׷�Ʈ
    ELF, // ���� ����
    WITCH, // ����� ����

    // ������
    MELTKNIGHT, // ��Ʈ ����Ʈ
    DRAUG, // ����� 
    WRAITH, // ����

    // �������
    DRAGON, // �ִϾ� �巡��
    BALROG, // �߷�
    BRAND, // �귣��

    // ����
    GHOST, // ����
    SKELETON, // ���̷���
    DARKNIGHT, // ����� ���
};

enum QuestItem
{
    ATRIA_ITEM,
    RUNA_ITEM
};


struct GameData
{
    // ���� ���� ������
    std::string HeroName[3];
    int HeroLevel[3];
    int HeroCurrentExperience[3];
    int HeroTotalExperience[3];

    int HeroHealth[3];
    int HeroTotalHealth[3];

    int HeroMana[3];
    int HeroTotalMana[3];

    int PlayerGold;
    int HeroInfoPosCount;

    // ���� ���� ������
    std::string MonsterName[15];
    int MonsterHealth[15];
    int MosterTotalHealth[15];

    int MonsterPower[15];

    // ���� �����ϰ��ִ� ������ ������
    std::vector<std::string> playerItem;


    // ���������� �ʿ��� ������.
    bool isPurchase;
    bool isNoMoney;
    std::string PortionShopItem[4];
    std::string WeaponShopItem[4];
    std::vector<std::string> DropItem;
    std::vector<std::string> DropItemInfo;
    std::string CurrentPurchaseItem;

    // �κ��丮������ �ʿ��� ������.
    int PlayerPortionCount[4];
    int PlayerPrevPortionCount[4];
    std::string Equipments[3];

    // ����Ʈ ������ ȹ�濩�� ������.
    bool isGetQuestItem[50];

    // ������ ���� �� ������.
    int NowCombatTurn;
    int RandomMonster;
    int MonsterRandomDamage;
    int MonsterRandomPointToHero;
    bool isPlayerTurn;
    bool isPickMonster;
    bool isMonsterDied;
    std::string monsterAttacking;

    // �� ��ȯ ������.

    std::string SceneName[15];
    SceneType s_currentScene;
    SceneType s_prevScene;
};// �ڡڡڡڡ�

GameData Data;

Hero hero;


class Map
{
public:

    virtual void SetPlayerPos(int playerPosX, int playerPosY)
    {
        mPlayerPosX = playerPosX;
        mPlayerPosY = playerPosY;
    }

    virtual void SetMonster1Pos(int monsterPosX, int monsterPosY)
    {
        mMonster1PosX = monsterPosX;
        mMonster1PosY = monsterPosY;
    }

    virtual void SetMonster2Pos(int monsterPosX, int monsterPosY)
    {
        mMonster2PosX = monsterPosX;
        mMonster2PosY = monsterPosY;
    }

    virtual void SetMonster3Pos(int monsterPosX, int monsterPosY)
    {
        mMonster3PosX = monsterPosX;
        mMonster3PosY = monsterPosY;
    }

    virtual void UpdateMap()
    {
        for (int y = 0; y < MAP_SIZE; y++)
        {
            for (int x = 0; x < MAP_SIZE; x++)
            {
                // Ÿ�� ����
                mMap[y][x] = mtile;

                // ��Ż ��ġ ����
                if (y == mPortalPoY && x == mPortalPosX)
                {
                    mMap[y][x] = mPortal;
                }

                // ���� ��ġ ����
                if (y == mMonster1PosY && x == mMonster1PosX)
                {
                    mMap[y][x] = 'M';
                }

                if (y == mMonster2PosY && x == mMonster2PosX)
                {
                    mMap[y][x] = 'M';
                }

                if (y == mMonster3PosY && x == mMonster3PosX)
                {
                    mMap[y][x] = 'M';
                }

                // �÷��̾� ��ġ ����
                if (y == mPlayerPosY && x == mPlayerPosX)
                {
                    mMap[y][x] = 'p';
                }
            }
        }
    }

    virtual void SetValue(int portalPosX, int portalPosY, char tile, char portal)
    {
        mPortalPosX = portalPosX;
        mPortalPoY = portalPosY;
        mPortal = portal;
        mtile = tile;
    }

    virtual int GetPortalX()
    {
        return mPortalPosX;
    }

    virtual int GetPortalY()
    {
        return mPortalPoY;
    }

    void PrintMap()
    {
        for (int y = 0; y < MAP_SIZE; y++)
        {
            for (int x = 0; x < MAP_SIZE; x++)
            {
                std::cout << mMap[y][x];
            }
            std::cout << "\n";
        }
    }

private:
    int mPortalPosX; // ��Ż X��ǥ
    int mPortalPoY; // ��Ż Y��ǥ

    int mPlayerPosX;
    int mPlayerPosY;

    int mMonster1PosX;
    int mMonster1PosY;

    int mMonster2PosX;
    int mMonster2PosY;

    int mMonster3PosX;
    int mMonster3PosY;

    char mtile; // Ÿ�� ��ȣ
    char mPortal;
    char mMap[MAP_SIZE][MAP_SIZE]; // �� ������
};

class GrassMap : public Map
{
public:

    void SetPlayerPos(int playerPosX, int playerPosY)
    {
        mPlayerPosX = playerPosX;
        mPlayerPosY = playerPosY;
    }

    void SetMonster1Pos(int monsterPosX, int monsterPosY)
    {
        mMonster1PosX = monsterPosX;
        mMonster1PosY = monsterPosY;
    }

    void SetMonster2Pos(int monsterPosX, int monsterPosY)
    {
        mMonster2PosX = monsterPosX;
        mMonster2PosY = monsterPosY;
    }

    void SetMonster3Pos(int monsterPosX, int monsterPosY)
    {
        mMonster3PosX = monsterPosX;
        mMonster3PosY = monsterPosY;
    }

    void UpdateMap()
    {
        for (int y = 0; y < MAP_SIZE; y++)
        {
            for (int x = 0; x < MAP_SIZE; x++)
            {
                // Ÿ�� ����
                mMap[y][x] = mtile;

                // ��Ż ��ġ ����
                if ((y == 9 && x == 4) || (y == 4 && x == 0) || (y == 4 && x == 9) || (y == 0 && x == 4))
                {
                    mMap[y][x] = mPortal;
                }

                // ���� ��ġ ����
                if (y == mMonster1PosY && x == mMonster1PosX)
                {
                    mMap[y][x] = 'M';
                }

                if (y == mMonster2PosY && x == mMonster2PosX)
                {
                    mMap[y][x] = 'M';
                }

                if (y == mMonster3PosY && x == mMonster3PosX)
                {
                    mMap[y][x] = 'M';
                }

                // �÷��̾� ��ġ ����
                if (y == mPlayerPosY && x == mPlayerPosX)
                {
                    mMap[y][x] = 'p';
                }
            }
        }
    }

    void SetValue(char tile, char portal)
    {
        mtile = tile;
        mPortal = portal;
    }

    int GetPortalX(int mapType)
    {
        switch (mapType)
        {
        case FOREST:
            return 4;
            break;
        case LAVA:
            return 9;
            break;
        case SWAMP:
            return 0;
            break;
        case DUNGEON:
            return 4;
            break;
        }
    }

    int GetPortalY(int mapType)
    {
        switch (mapType)
        {
        case FOREST:
            return 0;
            break;
        case LAVA:
            return 4;
            break;
        case SWAMP:
            return 4;
            break;
        case DUNGEON:
            return 9;
            break;
        }
    }

    int GetMonster1PosX()
    {
        return mMonster1PosX;
    }

    int GetMonster1PosY()
    {
        return mMonster1PosY;
    }

    int GetMonster2PosX()
    {
        return mMonster2PosX;
    }

    int GetMonster2PosY()
    {
        return mMonster2PosY;
    }

    int GetMonster3PosX()
    {
        return mMonster3PosX;
    }

    int GetMonster3PosY()
    {
        return mMonster3PosY;
    }

    void PrintMap()
    {
        for (int y = 0; y < MAP_SIZE; y++)
        {
            for (int x = 0; x < MAP_SIZE; x++)
            {
                std::cout << mMap[y][x];
            }
            std::cout << "\n";
        }
    }

private:
    int mPortalPosX; // ��Ż X��ǥ
    int mPortalPoY; // ��Ż Y��ǥ
    int mPlayerPosX;
    int mPlayerPosY;

    int mMonster1PosX;
    int mMonster1PosY;

    int mMonster2PosX;
    int mMonster2PosY;

    int mMonster3PosX;
    int mMonster3PosY;

    char mtile; // Ÿ�� ��ȣ
    char mPortal;
    char mMap[MAP_SIZE][MAP_SIZE]; // �� ������
};

class MiniMapCharacter
{
public:

    void SetValue(int PosX, int PosY)
    {
        mPosX = PosX;
        mPosY = PosY;
    }

    void SetShape(char shape)
    {
        mShape = shape;
    }

public:
    int mPosX;
    int mPosY;
    int mPrevPosX;
    int mPrevPosY;
    char mShape;
};


// �� �ν��Ͻ�
GrassMap Grass;
Map Forest;
Map Lava;
Map Swamp;
Map Dungeon;

MiniMapCharacter Player;
MiniMapCharacter MiniMonster1;
MiniMapCharacter MiniMonster2;
MiniMapCharacter MiniMonster3;

void CombatDataInit()
{
    // ���� ����
    Data.NowCombatTurn = SWORD;
    Data.RandomMonster = SLIME;
    Data.isPlayerTurn = true; // �� ����.
    Data.isPickMonster = false; // ���Ͱ� �������� �������� ����.
    Data.isMonsterDied = false; // ���Ͱ� �׾����� ����.

    // �÷��̾� ���� �ʱ�ȭ
    for (int i = 0; i < 3; i++)
    {
        Data.HeroHealth[i] = Data.HeroTotalHealth[i];
    }

    // �÷��̾� ������ �ʱ�ȭ

    for (int i = 0; i < 3; i++)
    {
        Data.HeroMana[i] = Data.HeroTotalMana[i];
    }

    // ���� ���� �ʱ�ȭ
    for (int i = 0; i < 15; i++)
    {
        Data.MonsterHealth[i] = (50 + i * 10);
    }

    for (int i = 0; i < 15; i++)
    {
        Data.MosterTotalHealth[i] = (50 + i * 10);
    }

    // �÷��̾� �̴ϸ� �ʱ�ȭ.
    Player.SetValue(3, 5);
    Player.SetShape('P');

}


void DataInit()
{
    // �� ������ �ʱ�ȭ
    Data.s_currentScene = VILIAGE;
    Data.s_prevScene = VILIAGE;
    // ���� ĳ���� ���� �ʱ�ȭ 
    hero = SWORD;

    // ���� ���� �ʱ�ȭ
    Data.HeroName[SWORD] = " �˻� ";
    Data.HeroName[WIZARD] = "������";
    Data.HeroName[PUNCH] = "������";
    Data.PlayerGold = 1500;

    for (int i = 0; i < 3; i++) { Data.HeroLevel[i] = 1; }
    for (int i = 0; i < 3; i++) { Data.HeroCurrentExperience[i] = 0; }
    for (int i = 0; i < 3; i++) { Data.HeroTotalExperience[i] = 1000; }
    for (int i = 0; i < 3; i++) { Data.HeroHealth[i] = 60; }
    for (int i = 0; i < 3; i++) { Data.HeroTotalHealth[i] = 60; }
    for (int i = 0; i < 3; i++) { Data.HeroMana[i] = 60; }
    for (int i = 0; i < 3; i++) { Data.HeroTotalMana[i] = 60; }

    // ���� ���� �ʱ�ȭ
    // 0 , 1 , 2
    Data.MonsterName[SLIME] = "������";
    Data.MonsterName[GOBLIN] = "���";
    Data.MonsterName[SNAIL] = "������";

    // 3, 4, 5
    Data.MonsterName[GROOT] = "�׷�Ʈ";
    Data.MonsterName[ELF] = "�渶����";
    Data.MonsterName[WITCH] = "��ġ";

    // 6, 7, 8
    Data.MonsterName[MELTKNIGHT] = "��Ʈ ����Ʈ";
    Data.MonsterName[DRAUG] = "�����";
    Data.MonsterName[WRAITH] = "����";

    // 9, 10, 11
    Data.MonsterName[DRAGON] = "�ִϾ� �巡��";
    Data.MonsterName[BALROG] = "�߷�";
    Data.MonsterName[BRAND] = "�귣��";

    // 12, 13, 14
    Data.MonsterName[GHOST] = "����";
    Data.MonsterName[SKELETON] = "���̷���";
    Data.MonsterName[DARKNIGHT] = "����� ���";




    // ���� ���Ż��� �ʱ�ȭ
    Data.isNoMoney = false;
    Data.isPurchase = false;

    // �� �̸� �ʱ�ȭ
    Data.SceneName[0] = "����";
    Data.SceneName[1] = "���� ����";
    Data.SceneName[2] = "���� ����";
    Data.SceneName[3] = "�ʿ� ����";
    Data.SceneName[4] = "����� ��";
    Data.SceneName[5] = "��� ����";
    Data.SceneName[6] = "�� ����";
    Data.SceneName[7] = "����";
    Data.SceneName[8] = "�޴�";
    Data.SceneName[9] = "�κ��丮";
    Data.SceneName[10] = "����ȸ��";
    Data.SceneName[11] = "�ܶ�����";
    Data.SceneName[12] = "����";
    Data.SceneName[13] = "���� ���";

    // �� ������ �ʱ�ȭ.
    Data.PortionShopItem[HP_PORTION] = "HP ����";
    Data.PortionShopItem[MP_PORTION] = "MP ����";
    Data.PortionShopItem[HP_STRONGMILK] = "�������";
    Data.PortionShopItem[MP_MANAELIXIR] = "����������";

    Data.WeaponShopItem[FIRESWORD] = "�Ұ�";
    Data.WeaponShopItem[FISHSPIKE] = "������ۻ�";
    Data.WeaponShopItem[CHAINSAW] = "������";
    Data.WeaponShopItem[SIVERDAWN] = "���� ����";

    // �ʱ� ���� ��� �ʱ�ȭ.
    Data.Equipments[TOP] = "�㸧�� ���� ����";
    Data.Equipments[BOTTOM] = "�㸧�� ���� ����";
    Data.Equipments[WEAPON] = "�߱� �����";

    // �̴ϸ� �ʱ�ȭ
    Grass.SetValue('#', '@');
    Forest.SetValue(4, 9, 'T', '@');
    Lava.SetValue(0, 4, '^', '@');
    Swamp.SetValue(9, 4, '~', '@');
    Dungeon.SetValue(4, 0, '*', '@');

    // �̴ϸ� �� �÷��̾� ��ġ �ʱ�ȭ



    CombatDataInit();

}

void DotEffet()
{
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
    Sleep(100); std::cout << ".";
}

void Title()
{
    Sleep(100); std::cout << "��";
    Sleep(100); std::cout << "Ʈ";
    Sleep(100); std::cout << "��";
    Sleep(100); std::cout << "��";
    Sleep(100); std::cout << " ";
    Sleep(100); std::cout << "��";
    Sleep(100); std::cout << "��";
    Sleep(100); std::cout << "��";
    Sleep(100); std::cout << "��";
    Sleep(100);
    std::cout << std::endl;
    std::cout << std::endl;
    Sleep(400); std::cout << "�ε���";
    DotEffet();
}


int main()
{
    // Ÿ��Ʋ ȭ�� ����.
    Title();

    // ���� ������ �ʱ�ȭ
    DataInit();

    while (true)
    {
        system("cls");
        switch (Data.s_currentScene)
        {
// ����
#pragma region VILIAGE
        case VILIAGE:
            Data.s_prevScene = VILIAGE;
            std::cout << "[[[[[" << Data.SceneName[VILIAGE] << "]]]]]" << std::endl;
            std::cout << std::endl;
            std::cout << "1. ���ǻ���" << std::endl;
            std::cout << "2. �������" << std::endl;
            std::cout << "3. ����ȸ��" << std::endl;
            std::cout << "4. �ܶ�����" << std::endl;
            std::cout << "5. �����" << std::endl;
            std::cout << "6. ���θ޴�" << std::endl;

            switch (_getch())
            {
            case '1':
                Data.s_currentScene = PORTION_SHOP;
                break;
            case '2':
                Data.s_currentScene = WEAPON_SHOP;
                break;
            case '3':
                Data.s_currentScene = TOWNHALL;
                break;
            case '4':
                Data.s_currentScene = PUB;
                break;
            case '5':
                Data.s_currentScene = GRASSLAND;
                break;
            case '6':
                Data.s_currentScene = MENU;
                break;
            }
            break;
#pragma endregion

// ����ȸ��
#pragma region TOWNHALL
        case TOWNHALL:
            Data.s_prevScene = TOWNHALL;
            std::cout << "[[[[[" << Data.SceneName[TOWNHALL] << "]]]]]" << std::endl;
            std::cout << std::endl;
            std::cout << "1. [�ٷ�]�� ��ȭ�ϱ�." << std::endl;
            std::cout << "2. [��Ʈ��]�� ��ȭ�ϱ�" << std::endl;
            std::cout << "3. [���̽�]�� ��ȭ�ϱ�" << std::endl;
            std::cout << "4. [������ ???]�� ��ȭ�ϱ�" << std::endl;
            std::cout << "5. ����ȸ�� ������" << std::endl;

            switch (_getch())
            {
            case '1':
                system("cls");
                std::cout << "[[[[[" << "[�ٷ�]" << "]]]]]" << std::endl;
                std::cout << std::endl;
                std::cout << "���� �츮���� �����ְԳ�. �츮���� �׵�� �ο� ���� ����." << std::endl; Sleep(700);
                std::cout << std::endl;
                std::cout << "1. ���ư���" << std::endl;
                if (_getch() == '1')
                {
                    Data.s_currentScene = TOWNHALL;
                }
                break;
            case '2':
                system("cls");
                std::cout << "[[[[[" << "[��Ʈ��]" << "]]]]]" << std::endl;
                std::cout << std::endl;
                std::cout << "��ŵ鵵 ������ �����ּ�? ������ �߾��� ���������� �߸����� ����.. �߾��� �ٷ�" << std::endl; Sleep(700);
                std::cout << std::endl;
                std::cout << "1. ���ư���" << std::endl;
                if (_getch() == '1')
                {
                    Data.s_currentScene = TOWNHALL;
                }
                break;
            case '3':
                system("cls");
                std::cout << "[[[[[" << "[���̽�]" << "]]]]]" << std::endl;
                std::cout << std::endl;
                std::cout << "�������� ������ �۾��� ����..." << std::endl; Sleep(700);
                std::cout << "�ڳ׵� �����ϰ�, �� ���� �� ������ ��ǳ�� ����ġ�� ������.." << std::endl; Sleep(700);
                std::cout << "�׷�... �̸� ������..." << std::endl; Sleep(700);
                std::cout << std::endl;
                std::cout << "1. ���ư���" << std::endl;
                if (_getch() == '1')
                {
                    Data.s_currentScene = TOWNHALL;
                }
                break;
            case '4':
                system("cls");
                std::cout << "[[[[[" << "[������ ???]" << "]]]]]" << std::endl;
                std::cout << std::endl;
                std::cout << "�ڳ׿��� ����� ������, ���� �� ���ΰ� ������ �־���" << std::endl; Sleep(700);
                std::cout << "�� ����� ����� ���ο� Ǯ���� ���� ���� ������...." << std::endl; Sleep(700);
                std::cout << "����� ���� �����縦 �����ϰ� ���ϸ� �𵥵� ���͵��� ��ȯ�ϴ�.." << std::endl; Sleep(700);
                std::cout << std::endl;
                std::cout << "1. ���ư���" << std::endl;
                if (_getch() == '1')
                {
                    Data.s_currentScene = TOWNHALL;
                }
                break;
            case '5':
                Data.s_currentScene = VILIAGE;
                break;
            }
            break;
#pragma endregion

// �ܶ�����
#pragma region PUB
        case PUB:
            Data.s_prevScene = PUB;
            std::cout << "[[[[[" << Data.SceneName[PUB] << "]]]]]" << std::endl;
            std::cout << std::endl;
            std::cout << "1. [�糪]�� ��ȭ�ϱ�." << std::endl;
            std::cout << "2. [Ʈ����]�� ��ȭ�ϱ�" << std::endl;
            std::cout << "3. [��������]�� ��ȭ�ϱ�" << std::endl;
            std::cout << "4. [��Ʈ����]�� ��ȭ�ϱ�" << std::endl;
            std::cout << "5. �ܶ����� ������" << std::endl;

            switch (_getch())
            {
            case '1':
                system("cls");
                std::cout << "[[[[[" << "[�糪]" << "]]]]]" << std::endl;
                std::cout << std::endl;
                std::cout << "[�ǵ���] ���ڽ�... ������ ������ ��� �㵵���� �𸣰� ��������Ⱦ�" << std::endl; Sleep(700);
                std::cout << "Ȥ��... �ڳ�..." << std::endl; Sleep(700);
                std::cout << "[�ǵ���] �� ã���� �� �ֳ�?" << std::endl; Sleep(700);
                std::cout << "�� �ڸ� �������� �����Ѱ� �ڳ׿��� �ְڳ�..." << std::endl; Sleep(700);
                std::cout << std::endl;
                std::cout << "1. ���ư���" << std::endl;
                std::cout << "2. ����Ʈ ����" << std::endl;
                switch (_getch())
                {
                case '1':
                    Data.s_currentScene = PUB;
                    break;
                case '2':
                    system("cls");
                    std::cout << "����Ʈ ���� �Ϸ�" << std::endl; Sleep(700);
                    std::cout << "������������[����Ʈ �̸�]��������������" << std::endl;
                    std::cout << "<q. �ǵ��� NPC ã��>" << std::endl; Sleep(700);
                    std::cout << std::endl;
                    std::cout << "������������[����Ʈ ����]��������������" << std::endl;
                    std::cout << "��Ʈ���� 1EA" << std::endl;
                    std::cout << std::endl;
                    std::cout << "1. ���ư���" << std::endl;
                    switch (_getch())
                    {
                    case '1':
                        Data.s_currentScene = PUB;
                        break;
                    }
                    break;
                }
                break;
            case '2':
                system("cls");
                std::cout << "[[[[[" << "[Ʈ����]" << "]]]]]" << std::endl;
                std::cout << std::endl;
                std::cout << "Ư���� �������� ���� �׳� �������� ��̳� ���� ã�� �����ƴٴϴ°�.." << std::endl; Sleep(700);
                std::cout << "�װ���.. �����̾�" << std::endl; Sleep(700);
                std::cout << std::endl;
                std::cout << "1. ���ư���" << std::endl;
                std::cout << std::endl;
                switch (_getch())
                {
                case '1':
                    Data.s_currentScene = PUB;
                    break;
                }
                break;
            case '3':
                system("cls");
                std::cout << "[[[[[" << "[��������]" << "]]]]]" << std::endl;
                std::cout << std::endl;
                std::cout << "���� ���� ��⸦ ������ �� ����� ������?" << std::endl; Sleep(700);
                std::cout << "�������� ���� ��⸦ ������ ������......." << std::endl; Sleep(700);
                std::cout << std::endl;
                std::cout << "1. ���ư���" << std::endl;
                std::cout << std::endl;
                switch (_getch())
                {
                case '1':
                    Data.s_currentScene = PUB;
                    break;
                }
                break;
            case '4':
                system("cls");
                std::cout << "[[[[[" << "[��Ʈ����]" << "]]]]]" << std::endl;
                std::cout << std::endl;
                if (Data.isGetQuestItem[ATRIA_ITEM] == false)
                {
                    std::cout << "�ڳ� �� ������ ��Ű���� ����ΰ�?" << std::endl; Sleep(700);
                    std::cout << "�׷��ٸ� ȯ���̳�!" << std::endl; Sleep(700);
                    std::cout << "�ްԳ�. �츮 ���� ���� ���ؿ��� �ǹ� å�̾�..." << std::endl; Sleep(700);
                    std::cout << "�ܽð� ���� ����� ���������..." << std::endl; Sleep(700);
                    std::cout << "������ �����ϸ� �ڳ׿��� ���� ������ �ɲ���." << std::endl; Sleep(700);
                    std::cout << std::endl;
                    std::cout << "1. ���ư���" << std::endl;
                    std::cout << "2. [�ǹ� å] ȹ���ϱ�" << std::endl;
                }
                else
                {
                    std::cout << "�׷� ..." << std::endl; Sleep(700);
                    std::cout << "�ڳ��� ������ ���ؼ� ������ ���ڳ�.." << std::endl; Sleep(700);
                    std::cout << std::endl;
                    std::cout << "1. ���ư���" << std::endl;
                }
                std::cout << std::endl;
                switch (_getch())
                {
                case '1':
                    Data.s_currentScene = PUB;
                    break;
                case '2':                    
                    if (Data.isGetQuestItem[ATRIA_ITEM] == false)
                    {
                        system("cls");
                        std::cout << "������ ȹ�� �Ϸ�!" << std::endl; Sleep(700);
                        std::cout << "                " << std::endl;
                        std::cout << "������������[������ �̸�]��������������" << std::endl;
                        std::cout << "<�� �� å>" << std::endl; Sleep(700);
                        std::cout << "                " << std::endl;
                        std::cout << "������������[�� ��]��������������" << std::endl;
                        std::cout << "\"��Ʈ���� ������ ���� ���ؿ��� �ǹ� å\", �������� ������ 50�÷��ش�." << std::endl; Sleep(700);
                        std::cout << "                " << std::endl;
                        std::cout << "1. ���ư���" << std::endl;

                        Data.DropItem.push_back("�ǹ� å");
                        Data.DropItemInfo.push_back("\"��Ʈ���� ������ ���� ���ؿ��� �ǹ� å\", �������� ������ 50�÷��ش�.");
                        Data.HeroMana[2] += 50;
                        Data.HeroTotalMana[2] += 50;

                        switch (_getch())
                        {
                        case '1':
                            Data.isGetQuestItem[ATRIA_ITEM] = true;
                            Data.s_currentScene = PUB;
                            break;
                        }
                        break;
                    }
                }
                break;
            case '5':
                Data.s_currentScene = VILIAGE;
                break;
            }
            break;
#pragma endregion

// ���� ����
#pragma region PORTION_SHOP
        case PORTION_SHOP:
            std::cout << "[[[[[" << Data.SceneName[PORTION_SHOP] << "]]]]]" << std::endl;
            std::cout << std::endl;
            std::cout << "1. HP���� 50 GOLD" << std::endl;
            std::cout << "2. MP���� 50 GOLD" << std::endl;
            std::cout << "3. ������� 500 GOLD" << std::endl;
            std::cout << "4. ���������� 500 GOLD" << std::endl;
            std::cout << "5. ������" << std::endl;
            std::cout << std::endl;
            std::cout << "________________________" << std::endl;
            std::cout << "���� ���� ��� : " << Data.PlayerGold << std::endl;

            if (Data.isPurchase)
            {
                std::cout << Data.CurrentPurchaseItem << "���� �Ϸ�!" << std::endl;
            }

            if (Data.isNoMoney)
            {
                std::cout << "�����ݾ��� �����մϴ�" << std::endl;
            }

            switch (_getch())
            {
            case '1':
                if (Data.PlayerGold > 50) 
                { 

                    Data.CurrentPurchaseItem = Data.PortionShopItem[HP_PORTION];
                    Data.playerItem.push_back(Data.PortionShopItem[HP_PORTION]);
                    Data.PlayerGold -= 50; 
                    ++Data.PlayerPortionCount[HP_PORTION];
                    ++Data.PlayerPrevPortionCount[HP_PORTION];
                    Data.isPurchase = true;
                    Data.isNoMoney = false; 
                }
                else 
                { 
                    Data.isNoMoney = true; 
                    Data.isPurchase = false;
                }
                break;
            case '2':
                if (Data.PlayerGold > 50)
                { 
                    Data.CurrentPurchaseItem = Data.PortionShopItem[MP_PORTION];
                    Data.playerItem.push_back(Data.PortionShopItem[MP_PORTION]);
                    Data.PlayerGold -= 50; 
                    ++Data.PlayerPortionCount[MP_PORTION];
                    ++Data.PlayerPrevPortionCount[MP_PORTION];
                    Data.isPurchase = true;
                    Data.isNoMoney = false; 
                }
                else 
                { 
                    Data.isNoMoney = true; 
                    Data.isPurchase = false;
                }
                break;
            case '3':
                if (Data.PlayerGold > 500) 
                { 
                    Data.CurrentPurchaseItem = Data.PortionShopItem[HP_STRONGMILK];
                    Data.playerItem.push_back(Data.PortionShopItem[HP_STRONGMILK]);
                    Data.PlayerGold -= 500; 
                    ++Data.PlayerPortionCount[HP_STRONGMILK];
                    ++Data.PlayerPrevPortionCount[HP_STRONGMILK];
                    Data.isPurchase = true;
                    Data.isNoMoney = false; 
                }
                else 
                { 
                    Data.isNoMoney = true; 
                    Data.isPurchase = false;
                }
                break;
            case '4':
                if (Data.PlayerGold > 500)
                { 
                    Data.CurrentPurchaseItem = Data.PortionShopItem[MP_MANAELIXIR];
                    Data.playerItem.push_back(Data.PortionShopItem[MP_MANAELIXIR]);
                    Data.PlayerGold -= 500; 
                    ++Data.PlayerPortionCount[MP_MANAELIXIR];
                    ++Data.PlayerPrevPortionCount[MP_MANAELIXIR];
                    Data.isPurchase = true;
                    Data.isNoMoney = false;
                }
                else 
                { 
                    Data.isNoMoney = true; 
                    Data.isPurchase = false;
                }
                break;
            case '5':
                Data.isNoMoney = false;
                Data.isPurchase = false;
                Data.s_currentScene = VILIAGE;
                break;
            }

            break;

#pragma endregion


// ���� ����
#pragma region WEAPON_SHOP
        case WEAPON_SHOP:

            std::cout << "[[[[[" << Data.SceneName[WEAPON_SHOP] << "]]]]]" << std::endl;
            std::cout << std::endl;
            std::cout << "1. ȭ���� 500 GOLD" << std::endl;
            std::cout << "2. ����� �ۻ� 1000 GOLD" << std::endl;
            std::cout << "3. ������ 1500 GOLD" << std::endl;
            std::cout << "4. ���� ���� 2000 GOLD" << std::endl;
            std::cout << "5. ������" << std::endl;
            std::cout << std::endl;
            std::cout << "________________________" << std::endl;
            std::cout << "���� ���� ��� : " << Data.PlayerGold << std::endl;

            if (Data.isPurchase)
            {
                std::cout << Data.CurrentPurchaseItem << "���� �Ϸ�!" << std::endl;
            }

            if (Data.isNoMoney)
            {
                std::cout << "�����ݾ��� �����մϴ�" << std::endl;
            }

            switch (_getch())
            {
            case '1':
                if (Data.PlayerGold > 500)
                {
                    Data.PlayerGold -= 500;
                    Data.CurrentPurchaseItem = Data.WeaponShopItem[FIRESWORD];
                    Data.Equipments[WEAPON] = Data.WeaponShopItem[FIRESWORD];
                    Data.isPurchase = true;
                    Data.isNoMoney = false;
                }
                else
                {
                    Data.isNoMoney = true;
                }
                break;
            case '2':
                if (Data.PlayerGold > 1000)
                {
                    Data.PlayerGold -= 1000;
                    Data.CurrentPurchaseItem = Data.WeaponShopItem[FISHSPIKE];
                    Data.Equipments[WEAPON] = Data.WeaponShopItem[FISHSPIKE];
                    Data.isPurchase = true;
                    Data.isNoMoney = false;
                }
                else
                {
                    Data.isNoMoney = true;
                }
                break;
            case '3':
                if (Data.PlayerGold > 1500)
                {
                    Data.PlayerGold -= 1500;
                    Data.CurrentPurchaseItem = Data.WeaponShopItem[CHAINSAW];
                    Data.Equipments[WEAPON] = Data.WeaponShopItem[CHAINSAW];
                    Data.isPurchase = true;
                    Data.isNoMoney = false;
                }
                else
                {
                    Data.isNoMoney = true;
                }
                break;
            case '4':
                if (Data.PlayerGold > 2000)
                {
                    Data.PlayerGold -= 2000;
                    Data.CurrentPurchaseItem = Data.WeaponShopItem[SIVERDAWN];
                    Data.Equipments[WEAPON] = Data.WeaponShopItem[SIVERDAWN];
                    Data.isPurchase = true;
                    Data.isNoMoney = false;
                }
                else
                {
                    Data.isNoMoney = true;
                }
                break;
            case '5':
                Data.isNoMoney = false;
                Data.isPurchase = false;
                Data.s_currentScene = VILIAGE;
                break;
            }

            break;
#pragma endregion


// �����
#pragma region GRASSLAND 
        case GRASSLAND:
            /*
                �̰��� �ʿ� ����, 
                Ư¡�� �� �߿��� �����ϰ� ������ �̵��� �� �ִ� �ʵ��Դϴ�.
                �̰��� ���� ���ʹ� ������, ���, �������Դϴ�.
                ��Ż�� �������� �� 4���� ������ ���ʺ��� �ð��������, ����� ��, �������, ����, �� ����� �����Ǿ��ֽ��ϴ�.
            */

            // ���� �ʿ��� GrassLand�� �Ѿ�� �÷��̾� ��ġ ��ǥ �ʱ�ȭ
            if (Data.s_prevScene == FOREST || Data.s_prevScene == LAVA || Data.s_prevScene == DUNGEON || Data.s_prevScene == SWAMP)
            {
                Player.mPosX = Player.mPrevPosX; 
                Player.mPosY = Player.mPrevPosY;
            }

            // �� ����
            Data.s_prevScene = GRASSLAND;

            // [dŰ] ���� ���� ����ϱ�
            for (int i = 0; i < 3; i++)
            {
                if (hero == i)
                {
                    std::cout << "INFO: <" << Data.HeroName[i] << ">" << " ���� " << Data.HeroLevel[i] << " | " << "����ġ " << Data.HeroCurrentExperience[i]
                        << " / " << Data.HeroTotalExperience[i] << " | " << "ü�� " << Data.HeroHealth[i] << " | " << "���� " << Data.HeroMana[i] << " | " << "��� " << Data.PlayerGold << std::endl;
                }
            }
            std::cout << std::endl;

            // ���� ��(��) ���� ����ϱ�
            std::cout << "�������������������������� [ " << Data.SceneName[GRASSLAND] << " ]������������������������������������������������������������������������������" << std::endl;
            std::cout << std::endl;
            std::cout << "| W : �� |" << " A : �� |" << " S : �� |" << " D : �� |" << " Q : ��� ���� �ٲٱ�" << std::endl;
            std::cout << std::endl;

            // �Է¿� ���� ���� �ѹ� ������Ʈ �����ش�.
            Grass.SetPlayerPos(Player.mPosX, Player.mPosY);
            Grass.SetMonster1Pos(7, 3);
            Grass.SetMonster2Pos(3, 7);
            Grass.UpdateMap();
            Grass.PrintMap(); 

            std::cout << std::endl;
            std::cout << "������������������������������������������������������������������������������������������������������������������������������������" << std::endl;

            // ������ ���
            std::cout << "1. �κ��丮" << std::endl;
            std::cout << "2. ������ ���ư���" << std::endl;
            std::cout << "3. ���θ޴�" << std::endl;

            // �Էº�
            switch (_getch())
            {
            case '1':
                Data.s_currentScene = INVENTORY;
                break;
            case '2':
                Data.s_currentScene = VILIAGE;
                break;
            case '3':
                Data.s_currentScene = MENU;
                break;
            case 'w':
                if (Player.mPosY > 0) { --Player.mPosY;  }
                break;
            case 's':
                if (Player.mPosY < 9) { ++Player.mPosY; }
                break;
            case 'a':
                if (Player.mPosX > 0) { --Player.mPosX; }
                break;
            case 'd':
                if (Player.mPosX < 9) { ++Player.mPosX; }
                break;

            case 'q':
                // dŰ�� ������ HeroInfoPosCount�������� ���� ������ �ٲ��.
                ++Data.HeroInfoPosCount;

                if (Data.HeroInfoPosCount == 3)
                {
                    Data.HeroInfoPosCount = 0;
                }

                hero = (Hero)Data.HeroInfoPosCount;
                break;
            }

            // �÷��̾���ǥ�� ��Ż��ǥ�� ���ٸ� ���� �ʵ�� �̵��Ѵ�.
            for (int portal = 0; portal < GRASSLAND_PORTAL_COUNT; portal++)
            {
                if (Player.mPosX == Grass.GetPortalX(portal + 4) && Player.mPosY == Grass.GetPortalY(portal + 4))
                {
                    Player.mPrevPosX = Player.mPosX;
                    Player.mPrevPosY = Player.mPosY;
                    Data.s_currentScene = (SceneType)(portal + 4);
                }
            }

            if ((Player.mPosX == Grass.GetMonster1PosX() && Player.mPosY == Grass.GetMonster1PosY()) ||
                (Player.mPosX == Grass.GetMonster2PosX() && Player.mPosY == Grass.GetMonster2PosY()) ||
                (Player.mPosX == Grass.GetMonster2PosX() && Player.mPosY == Grass.GetMonster2PosY()))
            {
                Data.s_currentScene = COMBAT;
            }

            break;
#pragma endregion

#pragma region FOREST
        case FOREST:
            /*
                �̰��� ����� ��, �ʿ������ ���� ��Ż(4, 9)�� �����մϴ�.
            */

            // grass���忡�� forest�� �Ѿ�� �÷��̾� ��ġ ��ǥ �ʱ�ȭ
            if (Data.s_prevScene == GRASSLAND)
            {
                Player.mPosX = 4; Player.mPosY = 8;
            }

            // �� ����
            Data.s_prevScene = FOREST;
 

            // [dŰ] ���� ���� ����ϱ�
            for (int i = 0; i < 3; i++)
            {
                if (hero == i)
                {
                    std::cout << "INFO: <" << Data.HeroName[i] << ">" << " ���� " << Data.HeroLevel[i] << " | " << "����ġ " << Data.HeroCurrentExperience[i]
                        << " / " << Data.HeroTotalExperience[i] << " | " << "ü�� " << Data.HeroHealth[i] << " | " << "���� " << Data.HeroMana[i] << " | " << "��� " << Data.PlayerGold << std::endl;
                }
            }
            std::cout << std::endl;


            // ���� ��(��) ���� ����ϱ�
            std::cout << "�������������������������� [ " << Data.SceneName[FOREST] << " ]������������������������������������������������������������������������������" << std::endl;
            std::cout << std::endl;
            std::cout << "| W : �� |" << " A : �� |" << " S : �� |" << " D : �� |" << " Q : ��� ���� �ٲٱ�" << std::endl;
            std::cout << std::endl;


            // �Է¿� ���� ���� �ѹ� ������Ʈ �����ش�.
            Forest.SetPlayerPos(Player.mPosX, Player.mPosY);
            Forest.SetMonster1Pos(7, 3);
            Forest.SetMonster2Pos(3, 7);
            Forest.UpdateMap();
            Forest.PrintMap();      

            std::cout << std::endl;
            std::cout << "������������������������������������������������������������������������������������������������������������������������������������" << std::endl;

            // ������ ���
            std::cout << "1. �κ��丮" << std::endl;
            std::cout << "2. ���θ޴�" << std::endl;


            // �Էº�
            switch (_getch())
            {

            case '1':
                Data.s_currentScene = INVENTORY;
                break;
            case '2':
                Data.s_currentScene = MENU;
                break;
            case 'w':
                if (Player.mPosY > 0){ --Player.mPosY;}
                break;
            case 's':
                if (Player.mPosY < 9){ ++Player.mPosY;}
                break;
            case 'a':
                if (Player.mPosX > 0){ --Player.mPosX;}
                break;
            case 'd':
                if (Player.mPosX < 9){ ++Player.mPosX;}
                break;

            case 'q':
                // dŰ�� ������ HeroInfoPosCount�������� ���� ������ �ٲ��.
                ++Data.HeroInfoPosCount;

                if (Data.HeroInfoPosCount == 3)
                {
                    Data.HeroInfoPosCount = 0;
                }

                hero = (Hero)Data.HeroInfoPosCount;
                break;
            }

            // �÷��̾���ǥ�� ��Ż��ǥ�� ���ٸ� ���� �ʵ�� �̵��Ѵ�.
            if (Player.mPosX == Forest.GetPortalX() && Player.mPosY == Forest.GetPortalY())
            {
                Data.s_currentScene = GRASSLAND;
            }

            break;
#pragma endregion

#pragma region LAVA
            case LAVA:
            /*
                �̰��� ����� ��, �ʿ������ ���� ��Ż(4, 9)�� �����մϴ�.
            */

            // grass���忡�� forest�� �Ѿ�� �÷��̾� ��ġ ��ǥ �ʱ�ȭ
            if (Data.s_prevScene == GRASSLAND)
            {
                Player.mPosX = 0; Player.mPosY = 4;
            }

            // �� ����
            Data.s_prevScene = LAVA;


            // [dŰ] ���� ���� ����ϱ�
            for (int i = 0; i < 3; i++)
            {
                if (hero == i)
                {
                    std::cout << "INFO: <" << Data.HeroName[i] << ">" << " ���� " << Data.HeroLevel[i] << " | " << "����ġ " << Data.HeroCurrentExperience[i]
                        << " / " << Data.HeroTotalExperience[i] << " | " << "ü�� " << Data.HeroHealth[i] << " | " << "���� " << Data.HeroMana[i] << " | " << "��� " << Data.PlayerGold << std::endl;
                }
            }
            std::cout << std::endl;

            // ���� ��(��) ���� ����ϱ�
            std::cout << "�������������������������� [ " << Data.SceneName[LAVA] << " ]������������������������������������������������������������������������������" << std::endl;
            std::cout << std::endl;
            std::cout << "| W : �� |" << " A : �� |" << " S : �� |" << " D : �� |" << " Q : ��� ���� �ٲٱ�" << std::endl;
            std::cout << std::endl;


            // �Է¿� ���� ���� �ѹ� ������Ʈ �����ش�.
            Lava.SetPlayerPos(Player.mPosX, Player.mPosY);
            Lava.SetMonster1Pos(7, 3);
            Lava.SetMonster2Pos(3, 7);
            Lava.UpdateMap();
            Lava.PrintMap();            // ����� �� �� ���
            std::cout << std::endl;
            std::cout << "������������������������������������������������������������������������������������������������������������������������������������" << std::endl;

            // ������ ���
            std::cout << "1. �κ��丮" << std::endl;
            std::cout << "2. ���θ޴�" << std::endl;


            // �Էº�
            switch (_getch())
            {

            case '1':
                Data.s_currentScene = INVENTORY;
                break;
            case '2':
                Data.s_currentScene = MENU;
                break;
            case 'w':
                if (Player.mPosY > 0) { --Player.mPosY; }
                break;
            case 's':
                if (Player.mPosY < 9) { ++Player.mPosY; }
                break;
            case 'a':
                if (Player.mPosX > 0) { --Player.mPosX; }
                break;
            case 'd':
                if (Player.mPosX < 9) { ++Player.mPosX; }
                break;

            case 'q':
                // dŰ�� ������ HeroInfoPosCount�������� ���� ������ �ٲ��.
                ++Data.HeroInfoPosCount;

                if (Data.HeroInfoPosCount == 3)
                {
                    Data.HeroInfoPosCount = 0;
                }

                hero = (Hero)Data.HeroInfoPosCount;
                break;
            }

            // �÷��̾���ǥ�� ��Ż��ǥ�� ���ٸ� ���� �ʵ�� �̵��Ѵ�.
            if (Player.mPosX == Lava.GetPortalX() && Player.mPosY == Lava.GetPortalY())
            {
                Data.s_currentScene = GRASSLAND;
            }

            break;
#pragma endregion

#pragma region DUNGEON
            case DUNGEON:
                /*
                    �̰��� ����� ��, �ʿ������ ���� ��Ż(4, 9)�� �����մϴ�.
                */

                // grass���忡�� forest�� �Ѿ�� �÷��̾� ��ġ ��ǥ �ʱ�ȭ
                if (Data.s_prevScene == GRASSLAND)
                {
                    Player.mPosX = 4; Player.mPosY = 0;
                }

                // �� ����
                Data.s_prevScene = DUNGEON;


                // [dŰ] ���� ���� ����ϱ�
                for (int i = 0; i < 3; i++)
                {
                    if (hero == i)
                    {
                        std::cout << "INFO: <" << Data.HeroName[i] << ">" << " ���� " << Data.HeroLevel[i] << " | " << "����ġ " << Data.HeroCurrentExperience[i]
                            << " / " << Data.HeroTotalExperience[i] << " | " << "ü�� " << Data.HeroHealth[i] << " | " << "���� " << Data.HeroMana[i] << " | " << "��� " << Data.PlayerGold << std::endl;
                    }
                }
                std::cout << std::endl;


                // �Է¿� ���� ���� �ѹ� ������Ʈ �����ش�.
                Dungeon.SetPlayerPos(Player.mPosX, Player.mPosY);
                Dungeon.SetMonster1Pos(7, 3);
                Dungeon.SetMonster2Pos(3, 7);
                Dungeon.UpdateMap();


                // ���� ��(��) ���� ����ϱ�
                std::cout << "�������������������������� [ " << Data.SceneName[DUNGEON] << " ]������������������������������������������������������������������������������" << std::endl;
                std::cout << std::endl;
                std::cout << "| W : �� |" << " A : �� |" << " S : �� |" << " D : �� |" << " Q : ��� ���� �ٲٱ�" << std::endl;


                std::cout << std::endl;
                Dungeon.PrintMap();            // ����� �� �� ���
                std::cout << std::endl;
                std::cout << "������������������������������������������������������������������������������������������������������������������������������������" << std::endl;

                // ������ ���
                std::cout << "1. �κ��丮" << std::endl;
                std::cout << "2. ���θ޴�" << std::endl;

                // �Էº�
                switch (_getch())
                {

                case '1':
                    Data.s_currentScene = INVENTORY;
                    break;
                case '2':
                    Data.s_currentScene = MENU;
                    break;
                case 'w':
                    if (Player.mPosY > 0) { --Player.mPosY; }
                    break;
                case 's':
                    if (Player.mPosY < 9) { ++Player.mPosY; }
                    break;
                case 'a':
                    if (Player.mPosX > 0) { --Player.mPosX; }
                    break;
                case 'd':
                    if (Player.mPosX < 9) { ++Player.mPosX; }
                    break;

                case 'q':
                    // dŰ�� ������ HeroInfoPosCount�������� ���� ������ �ٲ��.
                    ++Data.HeroInfoPosCount;

                    if (Data.HeroInfoPosCount == 3)
                    {
                        Data.HeroInfoPosCount = 0;
                    }

                    hero = (Hero)Data.HeroInfoPosCount;
                    break;
                }

                // �÷��̾���ǥ�� ��Ż��ǥ�� ���ٸ� ���� �ʵ�� �̵��Ѵ�.
                if (Player.mPosX == Dungeon.GetPortalX() && Player.mPosY == Dungeon.GetPortalY())
                {
                    Data.s_currentScene = GRASSLAND;
                }

                break;
#pragma endregion

#pragma region SWAMP
            case SWAMP:
                /*
                    �̰��� ����� ��, �ʿ������ ���� ��Ż(4, 9)�� �����մϴ�.
                */

                // grass���忡�� forest�� �Ѿ�� �÷��̾� ��ġ ��ǥ �ʱ�ȭ
                if (Data.s_prevScene == GRASSLAND)
                {
                    Player.mPosX = 9; Player.mPosY = 4;
                }

                // �� ����
                Data.s_prevScene = SWAMP;


                // [dŰ] ���� ���� ����ϱ�
                for (int i = 0; i < 3; i++)
                {
                    if (hero == i)
                    {
                        std::cout << "INFO: <" << Data.HeroName[i] << ">" << " ���� " << Data.HeroLevel[i] << " | " << "����ġ " << Data.HeroCurrentExperience[i]
                            << " / " << Data.HeroTotalExperience[i] << " | " << "ü�� " << Data.HeroHealth[i] << " | " << "���� " << Data.HeroMana[i] << " | " << "��� " << Data.PlayerGold << std::endl;
                    }
                }
                std::cout << std::endl;

                // ���� ��(��) ���� ����ϱ�
                std::cout << "�������������������������� [ " << Data.SceneName[SWAMP] << " ]������������������������������������������������������������������������������" << std::endl;
                std::cout << std::endl;
                std::cout << "| W : �� |" << " A : �� |" << " S : �� |" << " D : �� |" << " Q : ��� ���� �ٲٱ�" << std::endl;
                std::cout << std::endl;

                // �Է¿� ���� ���� �ѹ� ������Ʈ �����ش�.
                Swamp.SetPlayerPos(Player.mPosX, Player.mPosY);
                Swamp.SetMonster1Pos(7, 3);
                Swamp.SetMonster2Pos(3, 7);
                Swamp.UpdateMap();

                Swamp.PrintMap();            // ����� �� �� ���
                std::cout << std::endl;
                std::cout << "������������������������������������������������������������������������������������������������������������������������������������" << std::endl;

                // ������ ���
                std::cout << "1. �κ��丮" << std::endl;
                std::cout << "2. ���θ޴�" << std::endl;


                // �Էº�
                switch (_getch())
                {

                case '1':
                    Data.s_currentScene = INVENTORY;
                    break;
                case '2':
                    Data.s_currentScene = MENU;
                    break;
                case 'w':
                    if (Player.mPosY > 0) { --Player.mPosY; }
                    break;
                case 's':
                    if (Player.mPosY < 9) { ++Player.mPosY; }
                    break;
                case 'a':
                    if (Player.mPosX > 0) { --Player.mPosX; }
                    break;
                case 'd':
                    if (Player.mPosX < 9) { ++Player.mPosX; }
                    break;

                case 'q':
                    // dŰ�� ������ HeroInfoPosCount�������� ���� ������ �ٲ��.
                    ++Data.HeroInfoPosCount;

                    if (Data.HeroInfoPosCount == 3)
                    {
                        Data.HeroInfoPosCount = 0;
                    }

                    hero = (Hero)Data.HeroInfoPosCount;
                    break;
                }

                // �÷��̾���ǥ�� ��Ż��ǥ�� ���ٸ� ���� �ʵ�� �̵��Ѵ�.
                if (Player.mPosX == Swamp.GetPortalX() && Player.mPosY == Swamp.GetPortalY())
                {
                    Data.s_currentScene = GRASSLAND;
                }

                break;
#pragma endregion


//���θ޴�
#pragma region MENU
        case MENU:

            switch (Data.s_prevScene)
            {
            case VILIAGE:
                std::cout << "[[[[[" << Data.SceneName[VILIAGE] << "]]]]]" << std::endl;
                break;
            case GRASSLAND:
                std::cout << "[[[[[" << Data.SceneName[GRASSLAND] << "]]]]]" << std::endl;
                break;
            case FOREST:
                std::cout << "[[[[[" << Data.SceneName[FOREST] << "]]]]]" << std::endl;
                break;
            case LAVA:
                std::cout << "[[[[[" << Data.SceneName[LAVA] << "]]]]]" << std::endl;
                break;
            case SWAMP:
                std::cout << "[[[[[" << Data.SceneName[SWAMP] << "]]]]]" << std::endl;
                break;
            case DUNGEON:
                std::cout << "[[[[[" << Data.SceneName[DUNGEON] << "]]]]]" << std::endl;
                break;
            }

            std::cout << std::endl;
            std::cout << "1. ���ư���" << std::endl;
            std::cout << "2. ����" << std::endl;

            switch (_getch())
            {
            case '1':
                Data.s_currentScene = Data.s_prevScene;
                system("cls");
                break;

            case '2':
                return 0;
                break;

            }
            break;
#pragma endregion

//�κ��丮
#pragma region INVENTORY
        case INVENTORY:
            switch (Data.s_prevScene)
            {
            case VILIAGE:
                std::cout << "[[[[[" << Data.SceneName[VILIAGE] << "]]]]]" << std::endl;
                break;
            case GRASSLAND:
                std::cout << "[[[[[" << Data.SceneName[GRASSLAND] << "]]]]]" << std::endl;
                break;
            case FOREST:
                std::cout << "[[[[[" << Data.SceneName[FOREST] << "]]]]]" << std::endl;
                break;
            case LAVA:
                std::cout << "[[[[[" << Data.SceneName[LAVA] << "]]]]]" << std::endl;
                break;
            case SWAMP:
                std::cout << "[[[[[" << Data.SceneName[SWAMP] << "]]]]]" << std::endl;
                break;
            case DUNGEON:
                std::cout << "[[[[[" << Data.SceneName[DUNGEON] << "]]]]]" << std::endl;
                break;
            }

            // �����Ȳ
            std::cout << std::endl;
            std::cout << "[���]" << std::endl;
            std::cout << "���� : " << Data.Equipments[TOP] << std::endl;
            std::cout << "���� : " << Data.Equipments[BOTTOM] << std::endl;
            std::cout << "���� : " << Data.Equipments[WEAPON] << std::endl;
            std::cout << std::endl;

            // �Ҹ������ ��Ȳ
            std::cout << "[������]" << std::endl;

            for (int i = 0; i < 4; i++)
            {
                if (Data.PlayerPortionCount[i] > 0)
                {
                    std::cout << Data.PortionShopItem[i] << Data.PlayerPortionCount[i] << std::endl;
                }
            }

            for (int i = 0; i < Data.DropItem.size(); i++)
            {
                std::cout << "��" + Data.DropItem[i] << std::endl;
            }

            std::cout << std::endl;
            std::cout << "1.���ư���" << std::endl;

            switch (_getch())
            {
            case '1':
                Data.s_currentScene = Data.s_prevScene;
                break;
            }
            break;
#pragma endregion


//����
#pragma region COMBAT

        case COMBAT:
            // ���͸� �������� �̾� �ְ�, ���� �������� ������ ������ �ʴ´�.
            if (Data.isPickMonster == false)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (Data.s_prevScene == (i + 3))
                    {
                        Data.RandomMonster = rand() % 3 + 3 * i;
                    }
                }
                Data.isPickMonster = true;
            }

            // ���� �ʵ������ ����.
            switch (Data.s_prevScene)
            {
            case GRASSLAND:
                std::cout << "[[[[[" << Data.SceneName[GRASSLAND] << "]]]]]" << std::endl;
                break;
            case FOREST:
                std::cout << "[[[[[" << Data.SceneName[FOREST] << "]]]]]" << std::endl;
                break;
            case LAVA:
                std::cout << "[[[[[" << Data.SceneName[LAVA] << "]]]]]" << std::endl;
                break;
            case SWAMP:
                std::cout << "[[[[[" << Data.SceneName[SWAMP] << "]]]]]" << std::endl;
                break;
            case DUNGEON:
                std::cout << "[[[[[" << Data.SceneName[DUNGEON] << "]]]]]" << std::endl;
                break;
            }

            // �������� ����Ѵ�.

            if (Data.isPlayerTurn == true)
            {
                std::cout << "���������������������������������������������� | " << " ������ : " << Data.HeroName[Data.NowCombatTurn] << " |����������������������������������������������" << std::endl;
            }
            else
            {
                std::cout << "���������������������������������������������� | " << " ������ : " << Data.MonsterName[Data.RandomMonster] << " |����������������������������������������������" << std::endl;
            }

            std::cout << "                                                         " << std::endl;
            std::cout << "                                                         " << std::endl;
            std::cout << "      <" << Data.HeroName[SWORD] << ">             <" << Data.HeroName[WIZARD] << ">             <" << Data.HeroName[PUNCH] << ">" << std::endl;
            std::cout << "                                                         " << std::endl;
            std::cout << "ü�� : " << Data.HeroHealth[SWORD] << " / " << Data.HeroTotalHealth[SWORD] << "              " << Data.HeroHealth[WIZARD] << " / " << Data.HeroTotalHealth[WIZARD] << "              " << Data.HeroHealth[PUNCH] << " / " << Data.HeroTotalHealth[PUNCH] << std::endl;
            std::cout << "���� : " << Data.HeroMana[SWORD] << " / " << Data.HeroTotalMana[SWORD] << "              " << Data.HeroMana[WIZARD] << " / " << Data.HeroTotalMana[WIZARD] << "              " << Data.HeroMana[PUNCH] << " / " << Data.HeroTotalMana[PUNCH] << std::endl;
            std::cout << "1.     ����                 " << "��������Ʈ           " << "������" << std::endl;
            std::cout << "2.     �ʽ´� ����          " << "���׿�               " << "��������" << std::endl;
            std::cout << "3.     �����ϼ�             " << "�������             " << "��������" << std::endl;
            std::cout << "4.     õ������ ���ɰ��    " << "����� ����        " << "����ġ" << std::endl;
            std::cout << "                                                         " << std::endl;
            std::cout << "                                                         " << std::endl;
            std::cout << "��������������������������������������������| ���� ������ |������������������������������������������" << std::endl;

            // ���� ������ ������ ������Ʈ �Ѵ�. ���� �κ��丮�� ������ ������ ������� �ʴ´�. 
            for (int i = 0; i < 4; i++)
            {
                if (Data.PlayerPortionCount[i] > 0)
                {
                    std::cout << 5 + i << ".      " << Data.PortionShopItem[i] << Data.PlayerPortionCount[i] << " / " << Data.PlayerPrevPortionCount[i] << " ���" << std::endl;
                }
            }

            // �������� ���� ������ ������ ������Ʈ�Ѵ�. ���ʹ� �÷��̾� ���� ������ ������ �Ѵ�.
            std::cout << std::endl;
            std::cout << "����������������������������������������������| ���� ���� |��������������������������������������������" << std::endl;
            std::cout << "                                                         " << std::endl;
            std::cout << "                                                         " << std::endl;
            std::cout << Data.MonsterName[Data.RandomMonster] << std::endl;
            std::cout << Data.MonsterHealth[Data.RandomMonster] << " / " << Data.MosterTotalHealth[Data.RandomMonster] << std::endl;
            std::cout << "                                                         " << std::endl;

            // 1. ����ڰ� ���ݹ�ư�� ������ ��ų����������  ������ �ǰ� ���δ�. 
            // 2. ��ų�� ����ϴ� ��� �� ����� ������ ���δ�. (1�� �⺻������ ����)
            // 3. ������ ������ �÷��̾� ���� ��Ȱ��ȭ ��Ű��, ���� ������ �ٲ۴�.
            // 4. ���� ��縦 �ٲ۴�.

            if (Data.isMonsterDied == false)
            {
                switch (_getch())
                {
                case '1':
                    Data.MonsterHealth[Data.RandomMonster] -= 5;
                    std::cout << Data.MonsterName[Data.RandomMonster] << "�� HP�� - 5 ����" << std::endl;
                    Data.isPlayerTurn = false;
                    ++Data.NowCombatTurn;
                    break;
                case '2':
                    Data.MonsterHealth[Data.RandomMonster] -= 10;
                    Data.HeroMana[Data.NowCombatTurn] -= 10;
                    std::cout << Data.MonsterName[Data.RandomMonster] << "�� HP�� - 10 ����" << std::endl;
                    Data.isPlayerTurn = false;
                    ++Data.NowCombatTurn;
                    break;
                case '3':
                    Data.MonsterHealth[Data.RandomMonster] -= 15;
                    Data.HeroMana[Data.NowCombatTurn] -= 20;
                    std::cout << Data.MonsterName[Data.RandomMonster] << "�� HP�� - 15 ����" << std::endl;
                    Data.isPlayerTurn = false;
                    ++Data.NowCombatTurn;
                    break;
                case '4':
                    Data.MonsterHealth[Data.RandomMonster] -= 30;
                    Data.HeroMana[Data.NowCombatTurn] -= 40;
                    std::cout << Data.MonsterName[Data.RandomMonster] << "�� HP�� - 30 ����" << std::endl;
                    Data.isPlayerTurn = false;
                    ++Data.NowCombatTurn;
                    break;
                }

                if (Data.MonsterHealth[Data.RandomMonster] <= 0)
                {
                    Data.isMonsterDied = true;
                    std::cout << "�١١١١١١١١١١١١١١١� ���� �¸� �١١١١١١١١١١١١١�" << std::endl; 
                    std::cout << "ȭ�� ��ȯ ��" << std::endl; DotEffet(); DotEffet();
                    
                    Data.s_currentScene = COMBATRESULT;
                }
            }

            // ���� ������ ��ȯ�Ǹ�, ���ʹ� ������ �Ѵ�.
            // ���� ������... �̶�� ȭ���� ����.
            // DotEffet() �Լ��� ������ �ð��� ������ �÷��̾������� ��ȯ�Ѵ�.
            if (Data.isPlayerTurn == false && Data.isMonsterDied == false)
            {
                std::cout << "���� ������"; DotEffet();

                Data.MonsterRandomDamage = rand() % 3 + 15; // ���� ������ �ֱ�
                Data.MonsterRandomPointToHero = rand() % 3; // �������� ��� �����ϱ�

                Data.HeroHealth[Data.MonsterRandomPointToHero] -= Data.MonsterRandomDamage;
                std::cout << std::endl;
                std::cout << std::endl;

                // ���� �������� 10�� �Ѿ�� ġ��Ÿ �ߵ��� ����.
                if (Data.MonsterRandomDamage > 15)
                {
                    std::cout << Data.MonsterName[Data.RandomMonster] << "�� ġ��Ÿ �ߵ�!" << std::endl;
                }
                std::cout << std::endl;
                std::cout << Data.HeroName[Data.MonsterRandomPointToHero] << "�� HP�� " << Data.MonsterRandomDamage << " ����" << std::endl;

                std::cout << "�÷��̾� ������ ��ȯ��" << std::endl; DotEffet();
                std::cout << std::endl;
                Data.isPlayerTurn = true;
            }

            // ��縦 �Ѱ����� ������ �ε����� �Ѱ�����, �ٽ� �˻�� �ʱ�ȭ ��Ų��.
            if (Data.NowCombatTurn == 3)
            {
                Data.NowCombatTurn = 0;
            }

            break;
#pragma endregion

// ���� ���

#pragma region COMBATRESULT
        case COMBATRESULT:

            // ������� ������.
            int CombatRewardMoney = 500 + (rand() % 10) * 10;

            int CombatRewardExperience1 = 200 + (rand() % 10) * 5;
            int CombatRewardExperience2 = 200 + (rand() % 10) * 5;
            int CombatRewardExperience3 = 200 + (rand() % 10) * 5;

            Data.PlayerGold += CombatRewardMoney;
            Data.HeroCurrentExperience[SWORD] += CombatRewardExperience1;
            Data.HeroCurrentExperience[WIZARD] += CombatRewardExperience2;
            Data.HeroCurrentExperience[PUNCH] += CombatRewardExperience3;

            std::cout << "�� ȹ���� ��� : " << CombatRewardMoney << std::endl;
            std::cout << std::endl;
            std::cout << "�� ȹ���� ����ġ : ";
            std::cout << std::endl;
            std::cout << Data.HeroName[SWORD] << " | " << CombatRewardExperience1 << std::endl;
            std::cout << Data.HeroName[WIZARD] << " | " << CombatRewardExperience2 <<std::endl;
            std::cout << Data.HeroName[PUNCH] << " | " << CombatRewardExperience3 <<std::endl;
            std::cout << std::endl;
            DotEffet();
            std::cout << std::endl;
            std::cout << std::endl;

            CombatDataInit();

            // ������ �ʱ�ȭ �۾� ����
            std::cout << "1. ����ͷ� ���ư���" << std::endl;
            switch (_getch())
            {
            case '1':
                Data.s_currentScene = Data.s_prevScene;
                break;
            }

            break;
#pragma endregion
        }

     
    }

    return 0;
}
