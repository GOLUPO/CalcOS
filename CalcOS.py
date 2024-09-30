# CalcOS.py
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel
from PyQt5.QtCore import Qt, QTimer
import Calculator
import keyboard

class CalcOS(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('CalcOS')
        self.setGeometry(100, 100, 300, 400)
        self.show_splash_screen()
        self.initUI()

    def show_splash_screen(self):
        self.label = QLabel('CalcOS', self)
        self.label.setAlignment(Qt.AlignCenter)
        self.setCentralWidget(self.label)
        self.show()
        QApplication.processEvents()
        # Attendi 2 secondi prima di avviare la calcolatrice
        QTimer.singleShot(2000, self.start_calculator)

    def initUI(self):
        # Assegna il tasto ESC per aprire il launcher
        keyboard.add_hotkey('esc', self.open_launcher)

    def start_calculator(self):
        self.calculator = Calculator.CalculatorApp()
        self.calculator.show()
        self.close()

    def open_launcher(self):
        import launcher
        self.launcher = launcher.LauncherApp()
        self.launcher.show()
        self.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = CalcOS()
    sys.exit(app.exec_())
