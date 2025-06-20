#include <QtTest>
#include <QPushButton>
#include <QStackedWidget>
#include "mainwindow.h"

class TestMainWindow : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void test_loginButton_present();
    void test_guestLogin_navigation();
    void test_playButton_navigatesToModeSelection();
    void test_vsPlayer_opensGameBoard();
    void test_aiEasy_move_simulation();
    void cleanupTestCase();

private:
    MainWindow* window;
};

void TestMainWindow::initTestCase() {
    window = new MainWindow();
    window->show();
    QVERIFY(QTest::qWaitForWindowActive(window));
}

void TestMainWindow::test_loginButton_present() {
    auto* loginButton = window->findChild<QPushButton*>("loginButton");
    QVERIFY2(loginButton, "Login button should be present");
}

void TestMainWindow::test_guestLogin_navigation() {
    auto* guestButton = window->findChild<QPushButton*>("GuestButton");
    QVERIFY(guestButton);
    QTest::mouseClick(guestButton, Qt::LeftButton);
    QTest::qWait(500);
    auto* menus = window->findChild<QStackedWidget*>("Menus");
    QVERIFY(menus);
    QCOMPARE(menus->currentIndex(), 1);
}

void TestMainWindow::test_playButton_navigatesToModeSelection() {
    auto* playButton = window->findChild<QPushButton*>("PlayButton");
    QVERIFY(playButton);
    QTest::mouseClick(playButton, Qt::LeftButton);
    QTest::qWait(500);
    auto* menus = window->findChild<QStackedWidget*>("Menus");
    QCOMPARE(menus->currentIndex(), 2);
}

void TestMainWindow::test_vsPlayer_opensGameBoard() {
    auto* vsPlayerButton = window->findChild<QPushButton*>("VsPlayer");
    QVERIFY(vsPlayerButton);
    QTest::mouseClick(vsPlayerButton, Qt::LeftButton);
    QTest::qWait(500);
    auto* menus = window->findChild<QStackedWidget*>("Menus");
    QCOMPARE(menus->currentIndex(), 4);
}

void TestMainWindow::test_aiEasy_move_simulation() {
    auto* aiEasyButton = window->findChild<QPushButton*>("VsAI");
    QVERIFY(aiEasyButton);
    QTest::mouseClick(aiEasyButton, Qt::LeftButton);
    QTest::qWait(1000);  // wait for board load and AI move

    auto* btn = window->findChild<QPushButton*>("index0");
    QVERIFY(btn);
    QTest::mouseClick(btn, Qt::LeftButton);  // Player move
    QTest::qWait(1000);  // Wait for AI to respond

    bool aiMoved = false;
    for (int i = 0; i < 9; ++i) {
        auto* b = window->findChild<QPushButton*>(QString("index%1").arg(i));
        if (!b->isEnabled() && b != btn) aiMoved = true;
    }
    QVERIFY2(aiMoved, "AI should have made a move after player");
}

void TestMainWindow::cleanupTestCase() {
    delete window;
}

QTEST_MAIN(TestMainWindow)
#include "test_mainwindow.moc"
