#include "languagetrainingwindow.h"
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator>

LanguageTrainingWindow::LanguageTrainingWindow(QWidget *parent)
    : QDialog(parent),
      taskLabel(new QLabel(this)),
      answerInput(new QLineEdit(this)),
      startButton(new QPushButton("Начать тренировку", this)),
      checkAnswerButton(new QPushButton("Проверить ответ", this)),
      timerLabel(new QLabel("Время: 0", this)),
      timer(new QTimer(this)),
      remainingTime(10)
{
    setWindowTitle("Тренировка по языкам");
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(taskLabel);
    layout->addWidget(timerLabel);
    layout->addWidget(answerInput);
    layout->addWidget(startButton);
    layout->addWidget(checkAnswerButton);

    connect(startButton, &QPushButton::clicked, this, &LanguageTrainingWindow::onStartButtonClicked);
    connect(checkAnswerButton, &QPushButton::clicked, this, &LanguageTrainingWindow::onCheckAnswerButtonClicked);
    connect(timer, &QTimer::timeout, this, &LanguageTrainingWindow::onTimerTimeout);

    checkAnswerButton->setEnabled(false);

    if (!initializeDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось инициализировать базу данных.");
        return;
    }

    // Добавление примеров пользователей
    addUser("user1", "password1");
    addUser("user2", "password2");

    // Добавление примеров слов
    addWord("hello", "привет");
    addWord("world", "мир");
    addWord("cat", "кот");
    addWord("dog", "собака");
}

LanguageTrainingWindow::~LanguageTrainingWindow()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool LanguageTrainingWindow::initializeDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("language_training.db");

        if (!db.open()) {
            qDebug() << "Не удалось открыть базу данных:" << db.lastError().text();
            return false;
        }

        // Создание таблицы для пользователей
        QSqlQuery query;
        QString createUsersTableQuery =
            "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT NOT NULL, "
            "password TEXT NOT NULL)";
        if (!query.exec(createUsersTableQuery)) {
            qDebug() << "Не удалось создать таблицу users:" << query.lastError().text();
            return false;
        }

        // Создание таблицы для слов
        QString createWordsTableQuery =
            "CREATE TABLE IF NOT EXISTS words ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "word TEXT NOT NULL, "
            "translation TEXT NOT NULL)";
        if (!query.exec(createWordsTableQuery)) {
            qDebug() << "Не удалось создать таблицу words:" << query.lastError().text();
            return false;
        }

        return true;

}

bool LanguageTrainingWindow::addUser(const QString &username, const QString &password)
{
    QSqlQuery query;
        query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (!query.exec()) {
            qDebug() << "Ошибка добавления пользователя:" << query.lastError().text();
            return false;
        }

        return true;
}

bool LanguageTrainingWindow::addWord(const QString &word, const QString &translation)
{
    QSqlQuery query;
        query.prepare("INSERT INTO words (word, translation) VALUES (:word, :translation)");
        query.bindValue(":word", word);
        query.bindValue(":translation", translation);

        if (!query.exec()) {
            qDebug() << "Ошибка добавления слова:" << query.lastError().text();
            return false;
        }

        return true;
}

QStringList LanguageTrainingWindow::getWords()
{
    QStringList wordList;
    QSqlQuery query("SELECT word, translation FROM words");

    while (query.next()) {
        QString word = query.value(0).toString();
        QString translation = query.value(1).toString();
        wordList << word + ";" + translation;
    }

    return wordList;
}

void LanguageTrainingWindow::generateTask()
{
    QStringList words = getWords();
        if (words.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "База данных пуста.");
            return;
        }

        int randomIndex = QRandomGenerator::global()->bounded(words.size());
        QStringList wordPair = words[randomIndex].split(";");
        if (wordPair.size() != 2) {
            QMessageBox::warning(this, "Ошибка", "Неверный формат данных в базе.");
            return;
        }

        currentWord = wordPair[0];
        correctTranslation = wordPair[1];
        taskLabel->setText("Переведите слово: " + currentWord);

        remainingTime = 10;
        timerLabel->setText(QString("Время: %1").arg(remainingTime));
        timer->start(1000);
}

void LanguageTrainingWindow::resetTask()
{
    answerInput->clear();
    startButton->setEnabled(true);
    checkAnswerButton->setEnabled(false);
    timer->stop();
    remainingTime = 10;
}

void LanguageTrainingWindow::onStartButtonClicked()
{
    generateTask();
    startButton->setEnabled(false);
    checkAnswerButton->setEnabled(true);
}

void LanguageTrainingWindow::onCheckAnswerButtonClicked()
{
    QString userAnswer = answerInput->text().trimmed();
    if (userAnswer.compare(correctTranslation, Qt::CaseInsensitive) == 0) {
        QMessageBox::information(this, "Правильный ответ", "Вы правильно перевели слово!");
    } else {
        QMessageBox::warning(this, "Неправильный ответ", "Ответ неверный. Правильный перевод: " + correctTranslation);
    }
    resetTask();
}

void LanguageTrainingWindow::onTimerTimeout()
{
    if (remainingTime > 0) {
        remainingTime--;
        timerLabel->setText(QString("Время: %1").arg(remainingTime));
    } else {
        timer->stop();
        QMessageBox::warning(this, "Время вышло", "Вы не успели ответить. Правильный перевод: " + correctTranslation);
        resetTask();
    }
}
