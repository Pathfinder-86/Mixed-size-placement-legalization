import cv2
import numpy as np
import random

path = 'result//init.txt'
dieW,dieH,rowHeight,group_num = 1000,1000,40,0
idx = 0
WH_rate,scaleH,scaleW = 0,0,0
lenX,lenY = 0,1000
board = 2

x1,y1,x2,y2,type,group = [],[],[],[],[],[]
with open(path) as f:
    for line in f.readlines():
        s = line.split(' ')       
        if(idx==0):            
            dieW = int(s[0])
            dieH = int(s[1])
            rowHeight = int(s[2])
            WH_rate = dieW/dieH             
            scaleH = 1000 / dieH
            rowHeight = int(rowHeight*scaleH)
            scaleW = 1000*WH_rate / dieW
            lenX = int(1000*WH_rate)
        else:
            num0 = int(s[0])
            num1 = int(s[1])
            num0 = int (int(s[0]) * scaleW)
            num1 = lenY - int (int(s[1]) * scaleH)
            num2 = int ((int(s[0]) + int(s[2])) * scaleW)
            num3 = lenY - int ((int(s[3])+int(s[1])) * scaleH)
            x1.append(num0)
            y1.append(num3)
            x2.append(num2)
            y2.append(num1)
            type.append(int(s[4]))
        idx+=1

image = np.zeros((lenX,lenY, 3), np.uint8)
image.fill(255)
cv2.rectangle(image, (0, 0), (lenX, lenY), (0, 0, 0), 10)
row_num = dieH//rowHeight
for i in range(row_num-1):
    cv2.line(image, (0, rowHeight*(i+1)), (lenX, rowHeight*(i+1)), (255, 255, 0), 2)

size = len(x1)

for i in range(size):
    if type[i] == 0:
        cv2.rectangle(image, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (0, 0, 220), -1)
        cv2.putText(image, str(i) , ((x1[i]+board + x2[i]-board)//2-10 , (y1[i]+board+y2[i]-board)//2), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 255, 255), 1, cv2.LINE_AA)
    else:
        cv2.rectangle(image, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (0, 220, 0), 1)

cv2.imwrite('init_layout.png',image)



path = 'result//cluster.txt'
idx = 0
color_group = {}

x1,y1,x2,y2,type,group = [],[],[],[],[],[]
with open(path) as f:
    for line in f.readlines():
        s = line.split(' ')       
        if(idx==0):            
            group_num = int(s[3])           
            for i in range(group_num):
                b = random.randint(0,255)
                g = random.randint(0,255)
                r = random.randint(0,255)
                color_group[i] = [b,g,r]
        else:
            num0 = int(s[0])
            num1 = int(s[1])
            num0 = int (int(s[0]) * scaleW)
            num1 = lenY - int (int(s[1]) * scaleH)
            num2 = int ((int(s[0]) + int(s[2])) * scaleW)
            num3 = lenY - int ((int(s[3])+int(s[1])) * scaleH)
            x1.append(num0)
            y1.append(num3)
            x2.append(num2)
            y2.append(num1)
            type.append(int(s[4]))
            group.append(int(s[5]))
        idx+=1


image2 = np.zeros((lenX,lenY, 3), np.uint8)
image2.fill(255)
cv2.rectangle(image2, (0, 0), (lenX, lenY), (0, 0, 0), 10)
for i in range(row_num-1):
    cv2.line(image2, (0, rowHeight*(i+1)), (lenX, rowHeight*(i+1)), (255, 255, 0), 2)

size = len(x1)
for i in range(size):
    if type[i] == 0:
        cv2.rectangle(image2, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (color_group[group[i]][0], color_group[group[i]][1], color_group[group[i]][2]), -1)
        cv2.putText(image2, str(group[i]) , ((x1[i]+board + x2[i]-board)//2-10 , (y1[i]+board+y2[i]-board)//2), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 255, 255), 1, cv2.LINE_AA)
    else:
        cv2.rectangle(image2, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (0, 220, 0), 1)

cv2.imwrite('cluster_layout.png',image2)



path = 'result//yAdjust.txt'
idx = 0

x1,y1,x2,y2,type,group = [],[],[],[],[],[]
with open(path) as f:
    for line in f.readlines():
        s = line.split(' ')       
        if(idx!=0):
            num0 = int(s[0])
            num1 = int(s[1])
            num0 = int (int(s[0]) * scaleW)
            num1 = lenY - int (int(s[1]) * scaleH)
            num2 = int ((int(s[0]) + int(s[2])) * scaleW)
            num3 = lenY - int ((int(s[3])+int(s[1])) * scaleH)
            x1.append(num0)
            y1.append(num3)
            x2.append(num2)
            y2.append(num1)
            type.append(int(s[4]))
            group.append(int(s[5]))
        idx+=1

image3 = np.zeros((lenX,lenY, 3), np.uint8)
image3.fill(255)
cv2.rectangle(image3, (0, 0), (lenX, lenY), (0, 0, 0), 10)
for i in range(row_num-1):
    cv2.line(image3, (0, rowHeight*(i+1)), (lenX, rowHeight*(i+1)), (255, 255, 0), 2)
size = len(x1)
for i in range(size):
    if type[i] == 0:
        cv2.rectangle(image3, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (color_group[group[i]][0], color_group[group[i]][1], color_group[group[i]][2]), -1)
        cv2.putText(image3, str(group[i]) , ((x1[i]+board + x2[i]-board)//2-10 , (y1[i]+board+y2[i]-board)//2), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 255, 255), 1, cv2.LINE_AA)
    else:
        cv2.rectangle(image3, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (0, 220, 0), 1)
cv2.imwrite('yAdjust_layout.png',image3)


path = 'result//xAdjust.txt'
idx = 0

x1,y1,x2,y2,type,group = [],[],[],[],[],[]
with open(path) as f:
    for line in f.readlines():
        s = line.split(' ')       
        if(idx!=0):
            num0 = int(s[0])
            num1 = int(s[1])

            num0 = int (int(s[0]) * scaleW)
            num1 = lenY - int (int(s[1]) * scaleH)
            num2 = int ((int(s[0]) + int(s[2])) * scaleW)
            num3 = lenY - int ((int(s[3])+int(s[1])) * scaleH)

            x1.append(num0)
            y1.append(num3)
            x2.append(num2)
            y2.append(num1)
            type.append(int(s[4]))
            group.append(int(s[5]))
        idx+=1



image4 = np.zeros((lenX,lenY, 3), np.uint8)
image4.fill(255)
cv2.rectangle(image4, (0, 0), (lenX, lenY), (0, 0, 0), 10)
for i in range(row_num-1):
    cv2.line(image4, (0, rowHeight*(i+1)), (lenX, rowHeight*(i+1)), (255, 255, 0), 2)


size = len(x1)
for i in range(size):
    if type[i] == 0:
        cv2.rectangle(image4, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (color_group[group[i]][0], color_group[group[i]][1], color_group[group[i]][2]), -1)
        cv2.putText(image4, str(group[i]) , ((x1[i]+board + x2[i]-board)//2-10 , (y1[i]+board+y2[i]-board)//2), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 255, 255), 1, cv2.LINE_AA)
    else:
        cv2.rectangle(image4, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (0, 220, 0), 1)

cv2.imwrite('xAdjust_layout.png',image4)



path = 'result//ans.txt'
idx = 0

x1,y1,x2,y2,type,group = [],[],[],[],[],[]
with open(path) as f:
    for line in f.readlines():
        s = line.split(' ')       
        if(idx!=0):
            num0 = int(s[0])
            num1 = int(s[1])
            num0 = int (int(s[0]) * scaleW)
            num1 = lenY - int (int(s[1]) * scaleH)
            num2 = int ((int(s[0]) + int(s[2])) * scaleW)
            num3 = lenY - int ((int(s[3])+int(s[1])) * scaleH)

            x1.append(num0)
            y1.append(num3)
            x2.append(num2)
            y2.append(num1)
            type.append(int(s[4]))
            group.append(int(s[5]))
        idx+=1



image5 = np.zeros((lenX,lenY, 3), np.uint8)
image5.fill(255)
cv2.rectangle(image5, (0, 0), (lenX, lenY), (0, 0, 0), 10)
for i in range(row_num-1):
    cv2.line(image5, (0, rowHeight*(i+1)), (lenX, rowHeight*(i+1)), (255, 255, 0), 2)

size = len(x1)

for i in range(size):
    if type[i] == 0:
        cv2.rectangle(image5, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (color_group[group[i]][0], color_group[group[i]][1], color_group[group[i]][2]), -1)
        cv2.putText(image5, str(group[i]) , ((x1[i]+board + x2[i]-board)//2-10 , (y1[i]+board+y2[i]-board)//2), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 255, 255), 1, cv2.LINE_AA)
    else:
        cv2.rectangle(image5, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (0, 220, 0), 1)

cv2.imwrite('ans_layout.png',image5)



path = 'result//final_ans.txt'
idx = 0

x1,y1,x2,y2,type,group = [],[],[],[],[],[]
with open(path) as f:
    for line in f.readlines():
        s = line.split(' ')       
        if(idx!=0):
            num0 = int(s[0])
            num1 = int(s[1])
            num0 = int (int(s[0]) * scaleW)
            num1 = lenY - int (int(s[1]) * scaleH)
            num2 = int ((int(s[0]) + int(s[2])) * scaleW)
            num3 = lenY - int ((int(s[3])+int(s[1])) * scaleH)

            x1.append(num0)
            y1.append(num3)
            x2.append(num2)
            y2.append(num1)
            type.append(int(s[4]))
            group.append(int(s[5]))
        idx+=1



image6 = np.zeros((lenX,lenY, 3), np.uint8)
image6.fill(255)
cv2.rectangle(image6, (0, 0), (lenX, lenY), (0, 0, 0), 10)
for i in range(row_num-1):
    cv2.line(image6, (0, rowHeight*(i+1)), (lenX, rowHeight*(i+1)), (255, 255, 0), 2)

size = len(x1)

for i in range(size):
    if type[i] == 0:
        cv2.rectangle(image6, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (color_group[group[i]][0], color_group[group[i]][1], color_group[group[i]][2]), -1)
        cv2.putText(image6, str(group[i]) , ((x1[i]+board + x2[i]-board)//2-10 , (y1[i]+board+y2[i]-board)//2), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 255, 255), 1, cv2.LINE_AA)
    else:
        cv2.rectangle(image6, (x1[i]+board, y1[i]+board), (x2[i]-board, y2[i]-board), (0, 220, 0), 1)

cv2.imwrite('final_ans_layout.png',image6)


cv2.waitKey(0)
cv2.destroyAllWindows()