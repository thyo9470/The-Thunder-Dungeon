#include <QtTest>

#include "./headers/Board.h"

class TestGame : public QObject
{
  Q_OBJECT

private slots:
  void TestBoardInit();
  void TestBoardInit_data();
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

QTEST_APPLESS_MAIN(TestGame)

#include "TestGame.moc"