import cv2 as cv

if __name__ == '__main__':
    image = cv.imread('~/Downloads/1211078.jpeg')
    cv.imshow(image)
    # cv.imwrite('~/Downloads/gray.jpeg', img)