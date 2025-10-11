import sys
import time
from dataclasses import dataclass
import numpy as np
import cv2 as cv
from numpy import ndarray

# === CONSTANTS ===
CAMERA_SOURCE: int = 0

FD_MIN_NEIGHBORS: int = 7
FD_SCALE_FACTOR: float = 1.2

FACEBOX_COLOR: tuple[int, int, int] = (255, 0, 0)
FACEBOX_THICKNESS: int = 2

TEXT_DEFAULT_SIZE = 25  # don't touch, corresponds to font width at scale=0
TEXT_COEFF: int = 200
TEXT_MARGIN = 5
TEXT_FONT = cv.FONT_HERSHEY_SIMPLEX

SMOOTH_ALPHA: float = 0.2
SMOOTH_THRESHOLD: int = 2

MATCH_MAX_DISTANCE: int = 150

FPS_COLOR: tuple[int, int, int] = (0, 255, 0)
FPS_FONT_SCALE: float = 0.8
FPS_THICKNESS: int = 1
FPS_POSITION: tuple[int, int] = (0, int(TEXT_DEFAULT_SIZE * FPS_FONT_SCALE))
FPS_FONT = cv.FONT_HERSHEY_SIMPLEX

# === DATA CLASS ===
@dataclass()
class FaceBox:
    x: int = 0
    y: int = 0
    w: int = 0
    h: int = 0

    def get_center(self) -> tuple[int, int]:
        return self.x + self.w // 2, self.y + self.h // 2

    def get_vars(self) -> tuple[int, int, int, int]:
        return self.x, self.y, self.w, self.h


# === FACE DETECTOR CLASS ===
class FaceDetector:
    def __init__(self):
        """
        face_cascade: HAAR cascade for frontal face detection
        tracked_faces: list of faces from previous frame to smooth positions
        """
        self.face_cascade = cv.CascadeClassifier(
            cv.data.haarcascades + "haarcascade_frontalface_default.xml"
        )
        self.tracked_faces: list[FaceBox] = []

    def detect_faces(self, frame: ndarray) -> ndarray:
        """
        Detect faces, smooth their positions using EMA, and draw rectangles with labels.
        """
        frame_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        detected_raw = self.face_cascade.detectMultiScale(
            frame_gray, scaleFactor=FD_SCALE_FACTOR, minNeighbors=FD_MIN_NEIGHBORS
        )

        if len(detected_raw) == 0:
            return frame

        detected_faces = [FaceBox(x, y, w, h) for (x, y, w, h) in detected_raw]
        prev_tracked = self.tracked_faces.copy()
        render_faces: list[FaceBox] = []

        # Match & smooth each detected face
        for det_face in detected_faces:
            smoothed_face = self._match_and_smooth_face(det_face, prev_tracked)
            render_faces.append(smoothed_face)

        # Draw faces
        for face in render_faces:
            x, y, w, h = face.get_vars()
            frame = cv.rectangle(frame, (x, y), (x + w, y + h), FACEBOX_COLOR, FACEBOX_THICKNESS)
            frame = add_text(frame, "Face", (x + w + TEXT_MARGIN, y - TEXT_MARGIN), font_scale=h / TEXT_COEFF)

        self.tracked_faces = render_faces
        return frame

    def _match_and_smooth_face(self, det_face: FaceBox, prev_tracked: list[FaceBox]) -> FaceBox:
        """
        Match a detected face with tracked faces from previous frame and smooth its position.
        If no match found, returns detected face as is.
        """
        det_center = det_face.get_center()
        best_match_idx = -1
        best_match_dist = float('inf')

        for i, tracked_face in enumerate(prev_tracked):
            tracked_center = tracked_face.get_center()
            dist = np.linalg.norm(np.array(det_center) - np.array(tracked_center))
            if dist < best_match_dist and dist < MATCH_MAX_DISTANCE:
                best_match_dist = dist
                best_match_idx = i

        if best_match_idx != -1:
            matched_face = prev_tracked.pop(best_match_idx)
            sx, sy = self.smooth((matched_face.x, matched_face.y), (det_face.x, det_face.y))
            sw, sh = self.smooth((matched_face.w, matched_face.h), (det_face.w, det_face.h))
            return FaceBox(sx, sy, sw, sh)
        else:
            return det_face


    @staticmethod
    def smooth(
        last_pos: tuple[int, int],
        cur_pos: tuple[int, int],
        alpha: float = SMOOTH_ALPHA,
        threshold: int = SMOOTH_THRESHOLD
    ) -> tuple[int, int]:
        """
        Apply Exponential Moving Average (EMA) smoothing to positions.
        """
        dx = cur_pos[0] - last_pos[0]
        dy = cur_pos[1] - last_pos[1]

        if abs(dx) < threshold:
            cur_pos = (last_pos[0], cur_pos[1])
        if abs(dy) < threshold:
            cur_pos = (cur_pos[0], last_pos[1])

        x = int(alpha * cur_pos[0] + (1 - alpha) * last_pos[0])
        y = int(alpha * cur_pos[1] + (1 - alpha) * last_pos[1])

        return x, y

# === FPSCounter CLASS ===
class FPSCounter:
    def __init__(self):
        self.start_time = time.time()
        self.frame_count = 0
        self.fps = 0

    def update(self):
        self.frame_count += 1
        now = time.time()
        elapsed = now - self.start_time

        if elapsed >= 1.0:
            self.fps = int(self.frame_count / elapsed)
            self.frame_count = 0
            self.start_time = now

        return self.fps


# === HELPERS ===
def get_camera(idx: int = CAMERA_SOURCE) -> cv.VideoCapture:
    cam = cv.VideoCapture(idx)

    if not cam.isOpened():
        print("Cannot open camera")
        sys.exit()

    return cam

def add_text(
    frame: ndarray,
    text: str,
    point: tuple[int, int] = (0, 0),
    font_scale: float = 1,
    font_face = TEXT_FONT,
    color: tuple[int, int, int]=(255, 0, 0),
    thickness: int = 1
) -> np.ndarray:
    frame = cv.putText(frame, text, point, font_face, font_scale, color, thickness, lineType=cv.LINE_AA)
    return frame


# === MAIN ===
def main():
    face_detector = FaceDetector()
    fps_counter = FPSCounter()
    cam = get_camera()

    while True:
        res, frame = cam.read()
        if not res:
            print("Cannot read frame")
            break

        fps = fps_counter.update()

        # If we had added a few more processes to a frame (different features or recognitions),
        # I would have moved this to a new function called something like process_frame()
        frame = face_detector.detect_faces(frame)
        frame = add_text(
            frame=frame,
            text=f"FPS: {fps}",
            point=FPS_POSITION,
            color=FPS_COLOR,
            font_scale=FPS_FONT_SCALE,
            font_face=FPS_FONT,
            thickness=FPS_THICKNESS
        )

        cv.imshow("Face detector", frame)

        if cv.waitKey(1) & 0xFF == ord('q'):
            break

    cam.release()
    cv.destroyAllWindows()


if __name__ == '__main__':
    main()