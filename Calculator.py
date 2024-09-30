# Calculator.py
from PyQt5.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QLineEdit, QPushButton, QGridLayout
from PyQt5.QtCore import Qt
import keyboard

class CalculatorApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Calcolatrice Scientifica')
        self.setGeometry(100, 100, 300, 400)
        self.initUI()

    def initUI(self):
        # Widget centrale
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Layout principale
        main_layout = QVBoxLayout()
        central_widget.setLayout(main_layout)

        # Display
        self.display = QLineEdit()
        self.display.setAlignment(Qt.AlignRight)
        self.display.setReadOnly(True)
        main_layout.addWidget(self.display)

        # Pulsanti
        buttons = [
            '7', '8', '9', '/', 'sin',
            '4', '5', '6', '*', 'cos',
            '1', '2', '3', '-', 'tan',
            '0', '.', '=', '+', 'log'
        ]
        grid_layout = QGridLayout()
        row, col = 0, 0
        for button_text in buttons:
            button = QPushButton(button_text)
            button.clicked.connect(self.button_clicked)
            grid_layout.addWidget(button, row, col)
            col += 1
            if col > 4:
                col = 0
                row += 1
        main_layout.addLayout(grid_layout)

        # Assegna il tasto ESC per aprire il launcher
        keyboard.add_hotkey('esc', self.open_launcher)

    def button_clicked(self):
        sender = self.sender()
        text = sender.text()
        if text == '=':
            try:
                result = str(eval(self.display.text()))
                self.display.setText(result)
            except Exception:
                self.display.setText('Errore')
        else:
            self.display.setText(self.display.text() + text)

    def open_launcher(self):
        import launcher
        self.launcher = launcher.LauncherApp()
        self.launcher.show()
        self.close()
