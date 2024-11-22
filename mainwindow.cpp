#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "trainingselectionwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSettings>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QPixmap>
#include <QFileDialog>
#include <QBuffer>
#include <QDebug>

// Работа  в главном окне
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pixmap("C:/Users/Mikhail/Documents/BrainDrain.jpg");
    ui->startImg->setPixmap(pixmap);

    ui->startImg->setStyleSheet(
        "border: 2px solid #3498db; "
        "border-radius: 10px; "
        "background-color: #ecf0f1;"
    );

    QPixmap rightBackbuttonPixmap("C:/Users/Mikhail/Documents/rightBack.png");
    QIcon rightBackbuttonIcon(rightBackbuttonPixmap);
    ui->backButton->setIcon(rightBackbuttonIcon);
    ui->backButton->setIconSize(rightBackbuttonPixmap.rect().size());

    QPixmap questionbuttonPixmap("C:/Users/Mikhail/Documents/question.png");
    QIcon questionbuttonIcon(questionbuttonPixmap);
    ui->questButtonSecondWindow->setIcon(questionbuttonIcon);
    ui->questButtonSecondWindow->setIconSize(questionbuttonPixmap.rect().size());

    ui->questButtonFirstWindow->setIcon(questionbuttonIcon);
    ui->questButtonFirstWindow->setIconSize(questionbuttonPixmap.rect().size());

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open())
    {
        QMessageBox::critical(this, "Ошибка подключения к БД", db.lastError().text());
    }
    else
    {
        checkAndCreateTable();
    }

    setWindowTitle("BrainDrain");

    QFile styleFile(":/style/styles.css");
    if (styleFile.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);

    }

    setFixedSize(920, 720);

    ui->imgLabel->setStyleSheet(
        "border: 1px solid #3498db; "
        "border-radius: 10px; "
        "background-color: #ecf0f1;"
    );

    ui->imgLabel->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

/* Первое окно - Стартовое */

//Справочная информация
void MainWindow::on_questButtonFirstWindow_clicked()
{
    QMessageBox::information(
                this,
                "Справочная информация",
                "Добро пожаловать в BrainDrain!\n\n"
                "BrainDrain — это адаптивный комплекс тренировок для мозга, "
                "разработанный для улучшения когнитивных навыков и умственных способностей.\n\n"
                "Текущее окно предназначено для входа в свой профиль. Если у вас ещё нет аккаунта, "
                "вы можете зарегистрироваться, чтобы начать тренировки."
            );
}

// Кнопка "Войти"
void MainWindow::on_enterButton_clicked()
{
    QString email = ui->loginMail->text().trimmed();
        QString password = ui->loginPassword->text().trimmed();

        QSqlQuery query;
        query.prepare("SELECT username, name, image FROM users WHERE username = :username AND password = :password");
        query.bindValue(":username", email);
        query.bindValue(":password", password);

        if (query.exec() && query.next())
        {
            QString username = query.value("username").toString();
            QString name = query.value("name").toString();
            QByteArray imageData = query.value("image").toByteArray();
            QPixmap userImage;
            userImage.loadFromData(imageData);

            QMessageBox::information(this, "Успешный вход", "Добро пожаловать!");

            trainingWindow = new TrainingSelectionWindow();
            trainingWindow->setUserProfile(username, name, userImage, 1);
            trainingWindow->show();
            this->close();
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
        }
}

// Кнопка "Регистрация"
void MainWindow::on_registerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// Кнопка "Выйти"
void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}



/* Второе окно - создание профиля (аккаунта) */

// Справочная информация
void MainWindow::on_questButtonSecondWindow_clicked()
{
    QMessageBox::information(this, "Справка по регистрации",
                             "На странице регистрации заполните следующие поля:\n\n"
                             "1. Имя — введите ваше имя.\n"
                             "2. Электронная почта — укажите ваш действующий адрес электронной почты.\n"
                             "3. Пароль — создайте надежный пароль, который соответствует требованиям безопасности.\n\n"
                             "После ввода всех данных нажмите кнопку \"Зарегистрироваться\".");
}

// Загрузка изображения из файловой системы
void MainWindow::on_loadImgButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Выберите изображение",
        QString(),
        "Изображения (*.png *.jpg *.jpeg *.bmp)"
    );

    if (filePath.isEmpty())
    {
        return;
    }

    QPixmap pixmap(filePath);

    if (pixmap.isNull())
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение.");
        return;
    }

    loadedImage = pixmap;
    ui->imgLabel->setPixmap(pixmap.scaled(ui->imgLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// Кнопка "Зарегистрироваться"
void MainWindow::on_rgBtn_clicked()
{
    QString email = ui->emailLine->text().trimmed();
        QString password = ui->passwordLine->text().trimmed();
        QString name = ui->nameLine->text().trimmed();

        if (email.isEmpty() || password.isEmpty() || name.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
            return;
        }

        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Ошибка", "База данных не подключена!");
            return;
        }

        QSqlQuery query;

        // SQL-запрос
        query.prepare("INSERT INTO users (username, password, name, image) "
                      "VALUES (:username, :password, :name, :image)");

        query.bindValue(":username", email);
        query.bindValue(":password", password);
        query.bindValue(":name", name);

        // Работа с изображением
        QByteArray imageData;
        QPixmap pixmap = ui->imgLabel->pixmap() ? *ui->imgLabel->pixmap() : QPixmap();
        if (!pixmap.isNull()) {
            QBuffer buffer(&imageData);
            buffer.open(QIODevice::WriteOnly);
            pixmap.save(&buffer, "PNG"); // Сохраняем изображение в формате PNG
        } else {
            imageData = QByteArray(); // Если изображения нет, передаем пустое значение
        }

        query.bindValue(":image", imageData);

        if (!query.exec()) {
            QMessageBox::warning(this, "Ошибка", "Ошибка выполнения запроса: " + query.lastError().text());
        } else {
            QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
        }
}

// Возвращение из второго окна в первое
void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::checkAndCreateTable() {
    QSqlQuery query;

    QString checkTableQuery = R"(
        SELECT name FROM sqlite_master WHERE type='table' AND name='users';
    )";

    if (!query.exec(checkTableQuery)) {
        qDebug() << "Ошибка проверки таблицы:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        QString createTableQuery = R"(
            CREATE TABLE users (
                username TEXT PRIMARY KEY,
                password TEXT NOT NULL,
                name TEXT,
                image BLOB
            );
        )";

        if (!query.exec(createTableQuery)) {
            qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
        } else {
            qDebug() << "Таблица users успешно создана.";
        }
    } else {
        qDebug() << "Таблица users уже существует.";
    }
}

