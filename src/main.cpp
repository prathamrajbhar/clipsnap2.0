#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextStream>
#include "app/Application.h"
#include "ipc/SingleInstance.h"
#include "settings/Settings.h"
#include "ui/AppController.h"
#include "ui/HistoryModel.h"
#include "screenshot/PortalScreenshotBackend.h"
#include "screenshot/ImageEditor.h"
#include "capability/CapabilityDetector.h"
#include "diagnostics/DoctorCommand.h"
#include "logging/Logger.h"
#include <QClipboard>

int main(int argc, char* argv[]) {
    Logger::init();

    QGuiApplication app(argc, argv);
    app.setApplicationName("clipsnap");
    app.setApplicationVersion("0.1.0");
    app.setOrganizationName("clipsnap");
    app.setQuitOnLastWindowClosed(false);

    QStringList args = app.arguments();

    // CLI-only commands that don't need a running instance or QML
    if (args.contains("--version") || args.contains("-v")) {
        QTextStream out(stdout);
        out << "clipsnap " << app.applicationVersion() << "\n";
        return 0;
    }

    if (args.contains("logs") || args.contains("--logs") || args.contains("log") || args.contains("--log")) {
        if (args.contains("--clear") || args.contains("-c")) {
            Logger::clearLogs();
            QTextStream out(stdout);
            out << "ClipSnap logs cleared.\n";
        } else {
            Logger::printRecentLogs(100);
        }
        return 0;
    }

    if (args.size() >= 2 && args[1] == "doctor") {
        Capabilities caps = CapabilityDetector::detect();
        DoctorCommand doctor(caps);
        doctor.run();
        return 0;
    }

    if (args.contains("--help") || args.contains("-h") || (args.size() >= 2 && args[1] == "help")) {
        QTextStream out(stdout);
        out << "ClipSnap " << app.applicationVersion() << " - Clipboard History & Region Screenshot Manager\n\n"
            << "Usage: clipsnap [command] [options]\n\n"
            << "Commands:\n"
            << "  history, show          Open clipboard history window (default: Alt+H)\n"
            << "  capture, screenshot    Start region screenshot capture (default: Alt+Shift+S)\n"
            << "  install, --install     Install & configure shortcuts, systemd service, extension\n"
            << "  uninstall, --uninstall Remove shortcuts, user systemd service, and extension\n"
            << "  setup, --setup         Reconfigure desktop shortcuts and user service\n"
            << "  pause                  Pause background clipboard monitoring\n"
            << "  resume                 Resume background clipboard monitoring\n"
            << "  doctor                 Run comprehensive environment diagnostics\n"
            << "  logs [--clear]         Print or clear recent application logs\n"
            << "  --version, -v          Show version information\n";
        return 0;
    }

    if (args.contains("--uninstall") || args.contains("uninstall") || args.contains("--remove") || args.contains("remove")) {
        QTextStream out(stdout);
        out << "Removing ClipSnap desktop integration and user service...\n";
        bool ok = CapabilityDetector::removeDesktopIntegration();
        if (ok) {
            out << "ClipSnap service stopped and disabled.\n";
            out << "ClipSnap shortcuts and extension removed.\n";
            out << "Uninstallation of user integration complete.\n";
        } else {
            out << "Uninstallation encountered warnings.\n";
        }
        return 0;
    }

    if (args.contains("--setup") || args.contains("setup") || args.contains("--install") || args.contains("install")) {
        QTextStream out(stdout);
        out << "Configuring ClipSnap desktop integration...\n";
        bool ok = CapabilityDetector::setupDesktopIntegration();
        if (ok) {
            out << "ClipSnap GNOME Extension installed & enabled.\n";
            out << "ClipSnap Global Shortcuts (Alt+H, Alt+Shift+S) configured.\n";
            out << "Setup complete!\n";
        } else {
            out << "Setup encountered warnings. Run 'clipsnap doctor' for diagnostics.\n";
        }
        return 0;
    }

    SingleInstance instance;
    if (!instance.isPrimary()) {
        // Send command to existing instance and exit
        instance.sendCommand(args.mid(1));
        return 0;
    }

    // Auto-setup GNOME integration on primary launch if not yet installed
    Capabilities caps = CapabilityDetector::detect();
    if (caps.isGnome && !caps.hasGnomeExtension) {
        CapabilityDetector::setupDesktopIntegration();
    }

    // We are the primary instance: initialize everything
    Application clipsnap;
    QObject::connect(&instance, &SingleInstance::commandReceived,
                     &clipsnap, &Application::handleCommand);
    clipsnap.initialize();

    AppController appController;
    HistoryModel historyModel(clipsnap.history());
    PortalScreenshotBackend screenshotBackend;
    
    // Create editor model (owns the image provider)
    ImageEditor* imageEditor = new ImageEditor(&appController);

    // Wire Application IPC commands to AppController
    QObject::connect(&clipsnap, &Application::historyRequested,
                     &appController, &AppController::historyRequested);
    QObject::connect(&clipsnap, &Application::captureRequested,
                     &appController, &AppController::captureRequested);
    QObject::connect(&clipsnap, &Application::pauseRequested,
                     &appController, &AppController::pauseMonitoring);
    QObject::connect(&clipsnap, &Application::resumeRequested,
                     &appController, &AppController::resumeMonitoring);
    QObject::connect(&appController, &AppController::clipboardCheckRequested,
                     &clipsnap, &Application::checkClipboardNow);

    // When editor finishes, emit editFinished
    QObject::connect(imageEditor, &ImageEditor::editFinished, &clipsnap, [&clipsnap](const QImage& finalImage) {
        QGuiApplication::clipboard()->setImage(finalImage);
        clipsnap.saveImageToHistory(finalImage, "screenshot");
    });

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app", &appController);
    engine.rootContext()->setContextProperty("settings", Settings::instance());
    engine.rootContext()->setContextProperty("historyModel", &historyModel);
    engine.rootContext()->setContextProperty("screenshotBackend", &screenshotBackend);
    engine.rootContext()->setContextProperty("imageEditor", imageEditor);
    
    engine.addImageProvider("editor", imageEditor);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // Determine initial action if explicit CLI argument provided
    if (args.contains("history") || args.contains("--history") || args.contains("-h") || args.contains("show")) {
        emit appController.historyRequested();
    } else if (args.contains("capture") || args.contains("--capture") || args.contains("--screenshot") || args.contains("-s")) {
        emit appController.captureRequested();
    }

    return app.exec();
}
