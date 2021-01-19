import cv2
import numpy

if __name__ == '__main__':

    # 1.载入图像
    image = cv2.imread("original.jpg", 1)
    # print(image.shape)
    height, width, channel = image.shape
    image = cv2.resize(image, (int(0.5 * width), int(0.5 * height)), interpolation=cv2.INTER_CUBIC)
    cv2.imshow("original", image)
    cv2.waitKey()

    # 2.预处理
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # print(gray.shape)
    cv2.imshow("gray", gray)

    gray = cv2.GaussianBlur(gray, (3, 3), 1)
    ret, binary = cv2.threshold(gray, 80, 255, cv2.THRESH_BINARY_INV)
    cv2.imshow("binary", binary)

    element = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))  # 3 * 3 正方形，8位uchar型，全1结构元素
    binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, element)

    cv2.imshow("morphology", binary)
    cv2.waitKey()