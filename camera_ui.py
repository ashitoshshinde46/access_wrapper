import sys
import cv2
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QPushButton,QComboBox, QHBoxLayout,QVBoxLayout, QWidget,QGridLayout,QScrollArea
from PyQt5.QtCore import QTimer
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPixmap, QImage
from vidgear.gears import NetGear
from imutils import build_montages

class MultiCameraViewer(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Winch Camera")
        self.setGeometry(100, 100, 800, 600)
        self.frame_dict = {}

        self.num_cameras = ["/mnt/f/home_camera/captured_video_16_03_2023.mp4","/mnt/f/home_camera/captured_video17_03_2023.mp4","/mnt/f/home_camera/IMG_2377_.mp4"]
        
        self.options = {"multiserver_mode": True,"jpeg_compression": True,
    "jpeg_compression_quality": 90,
    "jpeg_compression_fastdct": True,
    "jpeg_compression_fastupsample": True,}
        self.client = NetGear(
    address="172.23.98.89",
    port=(5566, 5567,5568),
    protocol="tcp",
    pattern=1,
    receive_mode=True,
    **self.options
)
        
        
        self.video_captures = [cv2.VideoCapture(i) for i in self.num_cameras]

        self.zoom_factor = 1.0

        self.scroll_cam = 0

        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)
        # self.scrollArea = QScrollArea()
        self.main_video_label = QLabel(self)
        self.main_video_label.setAlignment(Qt.AlignCenter)
        self.main_video_label.setStyleSheet("border: 2px solid black;")
        
        self.scroll = QScrollArea()
        self.scroll.setWidgetResizable(True)
        self.scroll_widget = QWidget()
        self.scroll_layout = QVBoxLayout( self.scroll_widget)
        self.scroll_layout.addWidget(self.main_video_label)
        self.scroll.setWidget(self.scroll_widget)
        self.scroll_widget.mousePressEvent = self.on_mouse_press_scroll

        self.cb = QComboBox()
        # self.cb.addItem("Cam 1")
        # self.cb.addItem("Cam 1")
        self.cb.addItems(["Cam 1", "Cam 2", "Cam 3"])
        self.cb.currentIndexChanged.connect(self.selectionchange)

        self.video_labels = [QLabel(self) for _ in range(len(self.num_cameras))]
        for i, label in enumerate(self.video_labels):
            label.setAlignment(Qt.AlignCenter)
            label.setStyleSheet("border: 2px solid black;")
            label.setMaximumHeight(100)
            

        self.record_button = QPushButton("Record", self)
        self.record_button.clicked.connect(self.toggle_recording)
        layout=QHBoxLayout(self.central_widget)
        layout_1 = QVBoxLayout()
        for label in self.video_labels:
            layout_1.addWidget(label)
            # self.scrollArea.setWidget(label)
        layout_2 = QVBoxLayout()
        layout_2.addWidget(self.cb)
        layout_2.addWidget(self.record_button)
        layout.addWidget(self.scroll)
        layout.addLayout(layout_1)
        layout.addLayout(layout_2)
        # self.scrollArea.setLayout(layout_1)
        self.central_widget.setLayout(layout)

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_frames)
        self.timer.start(10)  # Update frames every 30 milliseconds

        self.is_recording = False
        self.video_writers = [None] * len(self.num_cameras)
        self.showMaximized()

    def update_frames(self):
        data = self.client.recv()

        # check if data received isn't None
        if data is None:
            return
        unique_address, frame = data
        print(f"Port address:{unique_address}")
        i=0
        if unique_address=="5566":
            i=0
        if unique_address=="5567":
            i=1
        if unique_address=="5568":
            i=2
        frame=cv2.resize(frame, (640, 480), interpolation=cv2.INTER_LINEAR) 
        frame = self.zoom_frame(frame)
        self.display_frame(frame, i)
        if self.scroll_cam==i:
            self.display_main_frame(frame)
            

    def zoom_frame(self, frame):
        height, width, _ = frame.shape
        new_height, new_width = int(height * self.zoom_factor), int(width * self.zoom_factor)
        # new_height, new_width = int(height * 0.5), int(width * 0.5)
        resized_frame = cv2.resize(frame, (new_width, new_height))
        return resized_frame

    def resize_thumbnail_frame(self, frame):
        height, width, _ = frame.shape
        # new_height, new_width = int(height * self.zoom_factor), int(width * self.zoom_factor)
        new_height, new_width = 48*2, 64*2
        resized_frame = cv2.resize(frame, (new_width, new_height))
        return resized_frame
        
    def on_mouse_press_scroll(self, event):
        if event.button() == Qt.LeftButton:
            # print('Left mouse button clicked')
            if (self.zoom_factor<2):
                self.zoom_factor+=0.5
        elif event.button() == Qt.RightButton:
            # print('Right mouse button clicked')
            if (self.zoom_factor>1):
                self.zoom_factor-=0.5
        
    def display_frame(self, frame, index):
        frame=self.resize_thumbnail_frame(frame)
        rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        qt_image = QImage(rgb_image.data, rgb_image.shape[1], rgb_image.shape[0], QImage.Format_RGB888)
        self.video_labels[index].setPixmap(QPixmap.fromImage(qt_image))

    def display_main_frame(self, frame):
        rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        qt_image = QImage(rgb_image.data, rgb_image.shape[1], rgb_image.shape[0], QImage.Format_RGB888)
        self.main_video_label.setPixmap(QPixmap.fromImage(qt_image))

    def selectionchange(self,i):
        self.scroll_cam=i
	
    
    def toggle_recording(self):
        if not self.is_recording:
            fourcc = cv2.VideoWriter_fourcc(*"XVID")
            for i in range(self.num_cameras):
                self.video_writers[i] = cv2.VideoWriter(f"camera_{i}.avi", fourcc, 20.0, (640, 480))
            self.is_recording = True
            self.record_button.setText("Stop Recording")
        else:
            for writer in self.video_writers:
                writer.release()
            self.is_recording = False
            self.record_button.setText("Record")

    def closeEvent(self, event):
        for video_capture in self.video_captures:
            video_capture.release()
        if self.is_recording:
            for writer in self.video_writers:
                writer.release()
        super().closeEvent(event)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    viewer = MultiCameraViewer()
    viewer.show()
    sys.exit(app.exec_())
