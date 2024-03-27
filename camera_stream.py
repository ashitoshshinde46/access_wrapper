import cv2
import threading
from mjpeg_streamer import MjpegServer, Stream

cap0 = cv2.VideoCapture("/home/goto/Videos/captured_video17_03_2023.mp4")
cap1 = cv2.VideoCapture("/home/goto/Videos/captured_video_16_03_2023.mp4")
cap2 = cv2.VideoCapture("/home/goto/Videos/IMG_2377_.mp4")

stream_0 = Stream("camera_0", size=(640, 480), quality=100, fps=30)
stream_1 = Stream("camera_1", size=(640, 480), quality=100, fps=30)
stream_2 = Stream("camera_2", size=(640, 480), quality=100, fps=30)

server_0 = MjpegServer("0.0.0.0", 8081)
server_0.add_stream(stream_0)
server_0.start()

server_1 = MjpegServer("0.0.0.0", 8082)
server_1.add_stream(stream_1)
server_1.start()

server_2 = MjpegServer("0.0.0.0", 8083)
server_2.add_stream(stream_2)
server_2.start()

def stream_frames(cap, stream):
	while True:
	    _, frame = cap.read()
	    stream.set_frame(frame)



# Start threads for streaming from each camera
thread0 = threading.Thread(target=stream_frames, args=(cap0, stream_0))
thread1 = threading.Thread(target=stream_frames, args=(cap1, stream_1))
thread2 = threading.Thread(target=stream_frames, args=(cap2, stream_2))

thread0.start()
thread1.start()
thread2.start()

# Wait for threads to finish (you can add more logic here if needed)
thread0.join()
thread1.join()
thread2.join()




server_0.stop()
cap0.release()

server_1.stop()
cap1.release()

server_2.stop()
cap2.release()
