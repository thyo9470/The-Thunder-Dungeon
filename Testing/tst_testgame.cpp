#include <QtTest>

#include "./headers/Board.h"

class TestGame : public QObject
{
  Q_OBJECT

public:
  TestGame();
  ~TestGame();

private slots:
  void test_case1();

};

TestGame::TestGame()
{
  Board * board = new Board(3, 50, 50);
}

TestGame::~TestGame()
{

}

void TestGame::test_case1()
{

}

QTEST_APPLESS_MAIN(TestGame)

#include "tst_testgame.moc"
