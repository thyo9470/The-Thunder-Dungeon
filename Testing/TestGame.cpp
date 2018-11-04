#include <QtTest>

#include "./headers/Board.h"
#include "./headers/Entity.h"
#include "./headers/Modifer.h"
#include "./headers/Skill.h"
#include <vector>
#include <QJsonObject>

class TestGame : public QObject
{
  Q_OBJECT

private slots:
  void TestBoardInit();
  void TestBoardInit_data();
  void TestSkillModifiers();
};

/*
 * Test the board's robustness to being initialized with different sizes
 * */
void TestGame::TestBoardInit()
{
  QFETCH(int, layers);
  QFETCH(int, rooms_x);
  QFETCH(int, rooms_y);
  try {
    Board * board = new Board(layers, rooms_x, rooms_y);
    QVERIFY(true);
  } catch (const std::exception& e) {
    QFAIL("Board threw an exception");
  }
}

void TestGame::TestBoardInit_data()
{
  QTest::addColumn<int>("layers");
  QTest::addColumn<int>("rooms_x");
  QTest::addColumn<int>("rooms_y");

  QTest::newRow("small board") << 3 << 3 << 3;
  QTest::newRow("medium board") << 3 << 5 << 5;
  QTest::newRow("large board") << 3 << 10 << 10;
}

/**
 * @brief TestGame::TestSkillModifiers
 *
 * Tests the functionalities of the ApplySkill() function
 */
void TestGame::TestSkillModifiers()
{
  QJsonObject entity_data;
  entity_data["max_health"] = 100;
  entity_data["max_magic"] = 100;
  entity_data["strength"] = 100;
  entity_data["speed"] = 100;

  Entity octopus(entity_data);

  std::vector<Modifier> mods;
  Modifier damage_mod(ModifierType::Health, ModifierOperation::Additive, -10);
  Modifier drain_mod(ModifierType::Magic, ModifierOperation::Multiplicative, 0.9f);
  Modifier strength_to_0(ModifierType::Strength, ModifierOperation::Additive, -120);
  mods.push_back(damage_mod);
  mods.push_back(drain_mod);
  mods.push_back(strength_to_0);

  Skill attack_skill("", "", mods);

  octopus.ApplySkill(attack_skill);

  QCOMPARE(octopus.GetHealth(), 90);
  QCOMPARE(octopus.GetMagic(), 90);
  QCOMPARE(octopus.GetStrength(), 0);
}

QTEST_APPLESS_MAIN(TestGame)

#include "TestGame.moc"
