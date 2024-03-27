import sys
import cv2
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QPushButton,QComboBox, QHBoxLayout,QVBoxLayout, QWidget,QGridLayout,QScrollArea
from PyQt5.QtCore import QTimer
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPixmap, QImage 
import datetime
import os

class MultiCameraViewer(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Winch Camera")
        self.setGeometry(100, 100, 800, 600)
        self.video_path=""
        self.num_cameras = ["http://192.168.0.106:8081/camera_0","http://192.168.0.106:8082/camera_1","http://192.168.0.106:8083/camera_2"]
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
        for i, video_capture in enumerate(self.video_captures):
            ret, frame = video_capture.read()
            if ret:    
                frame = self.zoom_frame(frame)
                self.display_frame(frame, i)
                if self.scroll_cam==i:
                    self.display_main_frame(frame)
                if self.is_recording:
                    self.video_writers[i].write(frame)

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

    def checkVideoDir(self,current_time,camera_number):
        month=current_time.month
        year=current_time.year
        if not os.path.exists(self.video_path+"cam_"+str(camera_number)+"/"+str(month)+"_"+str(year)):
            os.mkdir(self.video_path+"cam_"+str(camera_number)+"/"+str(month)+"_"+str(year))
	
    
    def toggle_recording(self):
        if not self.is_recording:
            fourcc = cv2.VideoWriter_fourcc(*"XVID")
            current_time = datetime.datetime.now()
            month=current_time.month
            year=current_time.year
            vid_name=current_time.strftime("%d_%m_%Y-%H_%M_%S")
            print("date:",vid_name)
            for i in range(len(self.num_cameras)):
                self.checkVideoDir(current_time,i)
                self.video_writers[i] = cv2.VideoWriter(self.video_path+"/cam_"+str(i)+"/"+str(month)+"_"+str(year)+"/"+vid_name+".avi", fourcc, 20.0, (640, 480))
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
