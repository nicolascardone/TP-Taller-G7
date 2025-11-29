#ifndef QTMUSICMANAGER_H
#define QTMUSICMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QWidget>
#include <QPushButton>
#include <QBrush>
#include <QFile>

class QtMusicManager : public QObject {
    Q_OBJECT

public:
    static QtMusicManager& instance() {
        static QtMusicManager manager;
        return manager;
    }

    void playBackgroundMusic(const QString& filePath) {
        QFile file(filePath);
        if (!file.exists()) {
            qWarning() << "[QtMusicManager] El archivo no existe:" << filePath;
            return;
        }

        player.setSource(QUrl::fromLocalFile(filePath));

        // se validan errores del player
        QObject::connect(&player, &QMediaPlayer::errorOccurred, [](QMediaPlayer::Error error) {
            qWarning() << "[QtMusicManager] Error reproduciendo música:" << error;
        });

        player.setLoops(QMediaPlayer::Infinite); //se repite al terminar
        player.play();
    }

    void stop() { player.stop(); }
    void mute() {
        muted = !muted;
        audio.setMuted(muted);
    }
    bool isMuted() { return muted; }

    static QPushButton* createMuteButton(QWidget* parent) {
        QPushButton* muteButton = new QPushButton(parent);
        muteButton->setFixedSize(40, 40);

        // Texto inicial según mute
        muteButton->setText(QtMusicManager::instance().isMuted() ? "🔊" : "🔇");

        muteButton->setStyleSheet(
            "QPushButton {"
            "   background-color: rgba(255,0,0,0.7);"
            "   border: 2px solid white;"
            "   border-radius: 20px;"
            "   font-size: 20px;"
            "   color: white;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgba(255,50,50,0.9);"
            "}"
        );

        // Conexión al mute global
        QObject::connect(muteButton, &QPushButton::clicked, [muteButton]() {
            QtMusicManager::instance().mute();
            muteButton->setText(QtMusicManager::instance().isMuted() ? "🔊" : "🔇");
        });

        return muteButton;
    }

private:
    QtMusicManager()
        : player(), audio() {
        player.setAudioOutput(&audio);
        audio.setVolume(0.5);
    }

    QMediaPlayer player;
    QAudioOutput audio;
    bool muted = false;
};

#endif //QTMUSICMANAGER_H
